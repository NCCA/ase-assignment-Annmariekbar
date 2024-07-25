#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Random.h>
#include <iostream>
#include "PhysicsWorld.h"//chat glObjectPtrLabel
#include "CollisionShape.h"
#include <QDebug>

//to do:
//be able to jump
//fix collision damage
//fix orientation (either freeze stage or fix it)
//fix level label when expanding window


NGLScene::NGLScene()
{
  setTitle("Bullet Physics and  NGL Demo");
  m_animate = true;
  m_randomPlace = false;
  m_bboxDraw = false;
  m_wireframe = false;
  m_physics.reset(new PhysicsWorld());
  m_physics->setGravity(ngl::Vec3(0.0f, -10.0f, 0.0f));
  m_physics->addGroundPlane(ngl::Vec3(0.0f, 0.0f, 0.0f), ngl::Vec3(50.0f, 0.01f, 50.0f));
  m_player.setPosition(-5.0f,0.5f,0.0f);
  ngl::Random::setSeed();
  gameWon = false;
}

void NGLScene::addMesh(MeshType _m)
{
    ngl::Vec3 pos = ngl::Random::getRandomVec3();
    pos *= 10;
    pos.m_y = 10;
    if (m_randomPlace == false)
        pos.set(0, 10, 0);
    if (_m == TEAPOT)
        m_physics->addMesh("teapot", pos);
}

void NGLScene::restartGame()
{
    m_player.resetHealth();
    level.resetLevel();
    gameWon = false;
    reloadScene(true);

}

void NGLScene::reloadScene(bool r)
{
    // Reset the physics world
    resetSim();

    // Get the player back in
    m_player.setPosition(-5.0f, 0.5f, 0.0f);
    m_physics->addMesh("player", m_player.getPosition());

    loadScene();
}
void NGLScene::loadScene()
{
    ngl::Vec3 pos;

        // Load the map for the initial level
        std::map<int, obsData> map = level.loadMap();


        for (int i = 1; i < 20; ++i)
        {
            for(int j = 0; j < map[i].height; j++)
            {
                auto jFloat = static_cast<float>(j);
                pos.set(map[i].position.m_x,1+jFloat*4,map[i].position.m_z);

                if(map[i].obj == "sphere")
                {
//                m_physics->addSphere("sphere", pos, ngl::Random::randomPositiveNumber(5.0f),
//                                     ngl::Random::getRandomVec3() * 20.0f);
                    m_physics-> addMesh("enemy1", pos);
                }
                else
                {
                    m_physics->addBox("box", pos);
                }

            }
        }

        m_physics->addMesh("teapot", {map[0].position.m_x,1,map[0].position.m_z});

}

void NGLScene::addSphere()
{
  ngl::Vec3 pos = ngl::Random::getRandomVec3();
  pos *= 10.0f;
  pos.m_y = 10.0f;
  if (m_randomPlace == false)
    pos.set(0.0f, 10.0f, 0.0f);
  ngl::Vec3 color = ngl::Random::getRandomColour3();
  m_physics->addSphere("sphere", pos, ngl::Random::randomPositiveNumber(5.0f), ngl::Random::getRandomVec3() * 20.0f);
}


NGLScene::~NGLScene()
{

    resetSim();
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_project = ngl::perspective(45.0f, static_cast<float>(_w) / _h, 0.05f, 350.0f);
  m_win.width = static_cast<int>(_w * devicePixelRatio());
  m_win.height = static_cast<int>(_h * devicePixelRatio());
}

void NGLScene::initializeGL()
{
  // we must call this first before any other GL commands to load and link the
  // gl commands from the lib, if this is not done program will crash
  ngl::NGLInit::initialize();

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f); // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);


  ngl::ShaderLib::use("nglDiffuseShader");
  ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 0.0f, 1.0f);
  ngl::ShaderLib::setUniform("lightPos", 1.0f, 1.0f, 1.0f);
  ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);

  // Camera creation---------------------------------------------------------------------
  // Camera position
  ngl::Vec3 from(0.0f, 5.0f, 15.0f);
  ngl::Vec3 to(0.0f, 0.0f, 0.0f);
  ngl::Vec3 up(0.0f, 1.0f, 0.0f);
  // now load to our new camera
  m_view = ngl::lookAt(from, to, up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_project = ngl::perspective(45.0f, 720.0f / 576.0f, 0.05f, 350.0f);
  ngl::VAOPrimitives::createSphere("sphere", 0.5f, 40.0f);
  ngl::VAOPrimitives::createLineGrid("plane", 140.0f, 140.0f, 40.0f);

  //creating rigid bodies-----------------------------------------------------------------
  m_teapotMesh.reset(new ngl::Obj("models/teapot.obj"));
  m_teapotMesh->createVAO();
//  m_playerMesh.reset(new ngl::Obj("models/apple.obj"));
//  m_playerMesh->createVAO();
//  m_playerMesh->calcBoundingSphere();
  ngl::VAOPrimitives::createCapsule("defaultCap", 0.5, 1.0, 20);
  ngl::VAOPrimitives::createCone("cone", 0.5, 1.0, 20, 20);
  ngl::VAOPrimitives::createCylinder("cylinder", 0.5, 2.0, 20, 20);

  startTimer(10);
  // as re-size is not explicitly called we need to do this.
  glViewport(0, 0, width(), height());

  //Creating shapes to be reused later
  CollisionShape *shapes = CollisionShape::instance();
  shapes->addMesh("teapot", "models/teapotCollisionMesh.obj");
//  shapes->addMesh("apple", "models/appleCollisionMesh.obj");
  shapes->addMesh("player", "models/appleCollisionMesh.obj");
  shapes->addMesh("enemy1", "models/appleCollisionMesh.obj");
//  shapes->addMesh("tank","../models/tankTriangle.obj");
  shapes->addBox("box", 1.0f, 1.0f, 1.0f);
  shapes->addSphere("sphere", 1.0f);
  shapes->addCapsule("capsule", 0.5f, 1.0f);
  shapes->addCone("cone", 0.5f, 2.0f);
  shapes->addCylinder("cylinder", 0.5f, 1.0f);
  m_text = std::make_unique<ngl::Text>("fonts/Arial.ttf", 50);
  m_text->setScreenSize(width(), height());
  m_instruct = std::make_unique<ngl::Text>("fonts/Arial.ttf", 18);
  m_instruct->setScreenSize(width(), height());
  m_gameState->setColour(1, 1, 1);
//  m_physics->addMesh("tank", {0,0.5f,0});
  m_physics->addMesh("player", {-10,0,0});
  loadScene();
}

void NGLScene::loadMatricesToShader()
{
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  MV = m_view * m_globalTransformMatrix * m_bodyTransform;
  MVP = m_project * MV;

  normalMatrix = MV;

  normalMatrix.inverse().transpose();
  ngl::ShaderLib::setUniform("MVP", MVP);
  ngl::ShaderLib::setUniform("normalMatrix", normalMatrix);
}

void NGLScene::renderTextMultiline(ngl::Text *textRenderer, float startX, float startY, const std::string &text)
{
    float lineHeight = 20;

    std::istringstream stream(text);
    std::string line;
    float y = startY;

    while (std::getline(stream, line))
    {
        textRenderer->renderText(startX, y, line);
        y -= lineHeight; // Move to the next line
    }
}

void NGLScene::paintGL()
{
    // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_win.width, m_win.height);
  // grab an instance of the shader manager
  ngl::ShaderLib::use("nglDiffuseShader");

  // Rotation based on the mouse position for our global transform
  auto rotX = ngl::Mat4::rotateX(m_win.spinXFace);
  auto rotY = ngl::Mat4::rotateY(m_win.spinYFace);
  // create the rotation matrices
  // multiply the rotations
  m_globalTransformMatrix = rotX * rotY;
  // add the translations
  m_globalTransformMatrix.m_m[3][0] = m_modelPos.m_x;
  m_globalTransformMatrix.m_m[3][1] = m_modelPos.m_y;
  m_globalTransformMatrix.m_m[3][2] = m_modelPos.m_z;
  // set this in the TX stack

  ngl::Vec3 posPlayer = m_player.getPosition();
  m_physics->updateMeshPosition("player", posPlayer);



  size_t bodies = m_physics->getNumCollisionObjects();
  for (unsigned int i = 1; i < bodies; ++i)
  {

    m_bodyTransform = m_physics->getTransformMatrix(i);

    loadMatricesToShader();
    ngl::ShaderLib::setUniform("Colour", 0.0f, 0.0f, 1.0f, 1.0f);
    switch (m_physics->getCollisionShape(i))
    {
    case BOX_SHAPE_PROXYTYPE:
      ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 1.0f, 1.0f);
      ngl::VAOPrimitives::draw("cube");
      break;
//    case SPHERE_SHAPE_PROXYTYPE:
//      ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
//      ngl::VAOPrimitives::draw("sphere");

      break;
    case CAPSULE_SHAPE_PROXYTYPE:
      ngl::ShaderLib::setUniform("Colour", 0.0f, 0.0f, 1.0f, 1.0f);
      ngl::VAOPrimitives::draw("defaultCap");
      break;

    case CONE_SHAPE_PROXYTYPE:
      ngl::ShaderLib::setUniform("Colour", 0.0f, 1.0f, 1.0f, 1.0f);
      ngl::VAOPrimitives::draw("cone");
      break;
    case CYLINDER_SHAPE_PROXYTYPE:
      ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 0.0f, 1.0f);
      ngl::VAOPrimitives::draw("cylinder");
      break;
    case 4:
      std::string name = m_physics->getBodyNameAtIndex(i);
      if (name == "teapot")
      {
        ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 0.5f, 1.0f);
        m_teapotMesh->draw();
      }
      else if (name == "player")
      {
        ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 0.0f, 1.0f);
        //m_playerMesh->draw();
        ngl::VAOPrimitives::draw("sphere");
      }
      else if (name == "enemy1")
      {
          ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
          ngl::VAOPrimitives::draw("sphere");
      }
      break;
    }

  }

  ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 1.0f, 1.0f);

  m_bodyTransform.identity();
  loadMatricesToShader();

  ngl::VAOPrimitives::draw("plane");
  int levelNum = level.getLevelNum();


  m_text->setColour(1, 1, 1);

  if(m_player.decreaseHealth(0)){
      if (gameWon)
      {
          float sizeGameOver = static_cast<float>(width())*0.19f;
          m_gameState = std::make_unique<ngl::Text>("fonts/Arial.ttf", sizeGameOver);
          m_gameState->setScreenSize(width(), height());

          m_gameState->setColour(1, 1, 1);

          // Adjust text position to be centered
          std::string gameOverText = fmt::format("YOU WON");
          float xPosGO = (static_cast<float>(width()) - (sizeGameOver*4.8)) / 2.0f;
          float yPosGO = static_cast<float>(height()) / 2.0f;

          m_gameState->renderText(xPosGO, yPosGO, gameOverText);
          //m_gameState->renderText(static_cast<float>(width()) / 6, static_cast<float>(height()) / 2, fmt::format("YOU DIED", level.getLevelNum()));

          float sizeRestart = static_cast<float>(width())*0.05f;
          m_gameState = std::make_unique<ngl::Text>("fonts/Arial.ttf", sizeRestart);
          m_gameState->setColour(1, 1, 1);

          // Adjust text position to be centered
          std::string restartText = fmt::format("press SPACE to play again");
          float xPosR = (static_cast<float>(width()) - (sizeRestart*4.8)) / 2.0f;
          float yPosR = yPosGO - (sizeGameOver*0.6);

          m_gameState->renderText(xPosR, yPosR, restartText);
      }
      else
      {
          float textPosY = (static_cast<float>(height())-60.0f);
          m_text->renderText(70, textPosY, fmt::format("LEVEL: {}", levelNum));
          m_text->renderText(70, 50, fmt::format("Health: {}", m_player.getHealth()));
          if (level.getLevelNum() < 2)
          {
              std::string multilineText = "Find the teapot and avoid the red shapes!\nWASD - move\nSpace - jump";
              renderTextMultiline(m_instruct.get(), 70.0f, textPosY - 40.0f, multilineText);// Render the multiline text
          }
      }
  }

  else
  {
      float sizeGameOver = static_cast<float>(width())*0.19f;
      m_gameState= std::make_unique<ngl::Text>("fonts/Arial.ttf", sizeGameOver);
      m_gameState->setScreenSize(width(), height());

      m_gameState->setColour(1, 1, 1);

      // Adjust text position to be centered
      std::string gameOverText = fmt::format("YOU DIED");
      float xPosGO = (static_cast<float>(width()) - (sizeGameOver*4.8)) / 2.0f;
      float yPosGO = static_cast<float>(height()) / 2.0f;

      m_gameState->renderText(xPosGO, yPosGO, gameOverText);
      //m_gameState->renderText(static_cast<float>(width()) / 6, static_cast<float>(height()) / 2, fmt::format("YOU DIED", level.getLevelNum()));

      float sizeRestart = static_cast<float>(width())*0.05f;
      m_gameState = std::make_unique<ngl::Text>("fonts/Arial.ttf", sizeRestart);
      m_gameState->setColour(1, 1, 1);

      // Adjust text position to be centered
      std::string restartText = fmt::format("press SPACE to restart");
      float xPosR = (static_cast<float>(width()) - (sizeRestart*4.8)) / 2.0f;
      float yPosR = yPosGO - (sizeGameOver*0.6);

      m_gameState->renderText(xPosR, yPosR, restartText);

  }

}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent(QMouseEvent *_event)
{
// note the method buttons() is the button state when event was called
// that is different from button() which is used to check which button was
// pressed when the mousePress/Release event is generated
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
  auto position = _event->position();
#else
  auto position = _event->pos();
#endif
 if (m_win.rotate && _event->buttons() == Qt::LeftButton)
  {
    int diffx = position.x() - m_win.origX;
    int diffy = position.y() - m_win.origY;
    m_win.spinXFace += static_cast<int>(0.5f * diffy);
    m_win.spinYFace += static_cast<int>(0.5f * diffx);
    m_win.origX = position.x();
    m_win.origY = position.y();
    update();
  }
  // right mouse translate code
  else if (m_win.translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = static_cast<int>(position.x() - m_win.origXPos);
    int diffY = static_cast<int>(position.y() - m_win.origYPos);
    m_win.origXPos = position.x();
    m_win.origYPos = position.y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
  }}


ngl::Mat4 NGLScene::getPlayerOrientation()
{
    // Assuming m_bodyTransform is a member variable
    return m_bodyTransform;
}

void NGLScene::movePlayer(ngl::Vec3 WASD)
{
    // Get the current orientation
    ngl::Mat4 playerOrientation = getPlayerOrientation();

    // Transform the movement vector by the orientation
    ngl::Vec4 transformedWASD = playerOrientation * ngl::Vec4(WASD.m_x, WASD.m_y, WASD.m_z, 0.0f);
    ngl::Vec3 transformedWASDVec3(transformedWASD.m_x, transformedWASD.m_y, transformedWASD.m_z);

    ngl::Vec3 playerPos = m_player.getPosition();
    m_player.setPosition(playerPos + transformedWASDVec3);
    playerPos = m_player.getPosition();
    m_physics->updateMeshPosition("player", playerPos);
    update();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::updateBar(int num)
{
    std::cout << "Health Bar:" << num << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::gameOver()
{
    resetSim();

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::setGameWon()
{
    gameWon = true;
    resetSim();


}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::collisionEvent(std::string collider)
{
    if(collider == "none")
    {
    }
    else if(collider == "enemy1")
    {
        if (m_player.decreaseHealth(0.5f))//0.2
        {
            updateBar(m_player.getHealth());
        }
        else
        {
            updateBar(m_player.getHealth());
            gameOver();
        }
    }
    else if(collider == "teapot")
    {
        std::cout << "teapot!" << std::endl;
        level.incrementLevel();// Increment level
        if(level.getLevelNum() == 4) {
            setGameWon();
        }
        else
        {
            reloadScene(false);
        }
    }

};



//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent(QMouseEvent *_event)
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the mouse was clicked (x,y) and set the Rotate flag to true
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
  auto position = _event->position();
#else
  auto position = _event->pos();
#endif
  if (_event->button() == Qt::LeftButton)
  {
    m_win.origX = position.x();
    m_win.origY = position.y();
    m_win.rotate = true;
  }
  // right mouse translate mode
  else if (_event->button() == Qt::RightButton)
  {
    m_win.origXPos = position.x();
    m_win.origYPos = position.y();
    m_win.translate = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent(QMouseEvent *_event)
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_win.rotate = false;
  }
  // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_win.translate = false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{

  // check the diff of the wheel position (0 means no change)
  if (_event->angleDelta().x() > 0)
  {
    m_modelPos.m_z += ZOOM;
  }
  else if (_event->angleDelta().x() < 0)
  {
    m_modelPos.m_z -= ZOOM;
  }
  update();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the NGLScene
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape:
    QGuiApplication::exit(EXIT_SUCCESS);
    break;
  case Qt::Key_W:
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// turn on wireframe rendering
    movePlayer(ngl::Vec3(0.0f, 0.0f, -0.2f));
    break;
  case Qt::Key_A:
      movePlayer(ngl::Vec3(-0.2f, 0.0f, 0.0f));
      break;
  case Qt::Key_S:
      movePlayer(ngl::Vec3(0.0f, 0.0f, 0.2f));
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // turn off wire frame
    break;
  case Qt::Key_D:
      movePlayer(ngl::Vec3(0.2f, 0.0f, 0.0f));
      break;
  case Qt::Key_Space:
      if(m_player.decreaseHealth(0) && !gameWon)
      {
          m_physics->addImpulse(ngl::Vec3(0.0f, 10.0f, 0.0f), "player");
      }
      else
      {
          restartGame();
      }
      break;
  // show full screen
  case Qt::Key_F:
    showFullScreen();
    break;
  // show windowed
  case Qt::Key_N:
    showNormal();
    break;
//  case Qt::Key_Space:
//    toggleAnimation();
//    break;
  case Qt::Key_X:
    stepAnimation();
    break;
  case Qt::Key_2:
    addSphere();
    break;

  case Qt::Key_B:
    toggleBBox();
    break;
  case Qt::Key_R:
    toggleRandomPlace();
    break;
  case Qt::Key_0:
    resetSim();
    break;

  default:
    break;
  }
  // finally update the GLWindow and re-draw
  // if (isExposed())
  update();
}

void NGLScene::resetSim()
{
  m_physics->reset();
}

void NGLScene::timerEvent(QTimerEvent *)
{
  if (m_animate == true)
  {
    m_physics->step(1.0f / 60.0f, 10);
    collisionEvent(m_physics->getCollision());

  }
  update();
}
void NGLScene::stepAnimation()
{
  m_physics->step(1.0f / 60.0f, 10);
}


