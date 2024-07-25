#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/Transformation.h>
#include <ngl/Text.h>
#include <ngl/Mat4.h>
#include <ngl/Obj.h>
#include "WindowParams.h"
#include <QOpenGLWindow>
#include <memory>
#include <bullet/btBulletDynamicsCommon.h>
#include <memory>
#include <fish.h>
#include "Enemy.h"
#include "Level.h"
#include <sstream>


//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------
class PhysicsWorld;

class NGLScene : public QOpenGLWindow
{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLScene() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    void renderTextMultiline(ngl::Text *textRenderer, float startX, float startY, const std::string &text);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //---------------------
    void paintGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we resize
    void resizeGL(int _w, int _h) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief  toggle the animation and simulation
     inline void toggleAnimation(){m_animate ^=true;}
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief step the animation when in anim off mode
     void stepAnimation();
    //----------------------------------------------------------------------------------------------------------------------
    void reloadScene(bool);
     //----------------------------------------------------------------------------------------------------------------------
     void loadScene();
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief add a sphere to the simulation
     void addSphere();
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief
     void addCapsule();
     void addCylinder();
     void addCone();
     typedef enum MeshType{APPLE,TEAPOT}MeshType;

     //----------------------------------------------------------------------------------------------------------------------
     /// @brief add an apple to the simulation
     void addMesh(MeshType _m);
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief reset the simulation and remove all bodies
     void resetSim();
     //----------------------------------------------------------------------------------------------------------------------
     void collisionEvent(std::string);
    //----------------------------------------------------------------------------------------------------------------------
    void updateBar(int);
    //----------------------------------------------------------------------------------------------------------------------
    void gameOver();
    //----------------------------------------------------------------------------------------------------------------------
    void setGameWon();
    //----------------------------------------------------------------------------------------------------------------------
    void restartGame();
    //----------------------------------------------------------------------------------------------------------------------

    /// @brief toggle the random placement of objects when added
     inline void toggleRandomPlace(){m_randomPlace^=true;}
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief toggle drawing mesh bounding boxes
     inline void toggleBBox(){m_bboxDraw^=true;}
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief toggle drawing wireframe meshes
     inline void toggleWireframe(){m_wireframe^=true;}
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief access the physics world
     inline PhysicsWorld *getPhysicsWorld(){return m_physics.get();}




private:
    bool gameWon;
     //----------------------------------------------------------------------------------------------------------------------
     /// @brief the windows params such as mouse and rotations etc
     WinParams m_win;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Our Camera
    ngl::Mat4 m_view;
    ngl::Mat4 m_project;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief body transform matrix
    ngl::Mat4 m_bodyTransform;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief world / mouse transform
    ngl::Mat4 m_globalTransformMatrix;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    ngl::Vec3 m_modelPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the ODE physics wrapper
    std::unique_ptr<PhysicsWorld> m_physics;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the ODE physics wrapper
    Player m_player;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to animate / simulate
    bool m_animate;
    //----------------------------------------------------------------------------------------------------------------------
    Level level;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag for random placement of objects
    bool m_randomPlace;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag for drawing bounding boxes
    bool m_bboxDraw;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag for wireframe drawing
    bool m_wireframe;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the meshes used for drawing
    std::unique_ptr<ngl::Obj> m_teapotMesh;

    std::unique_ptr<ngl::Obj> m_playerMesh;

    std::unique_ptr<ngl::Obj> m_tankMesh;

    //----------------------------------------------------------------------------------------------------------------------
    ///@brief text for  level number
    std::unique_ptr<ngl::Text>m_text;
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief text for instructions
    std::unique_ptr<ngl::Text>m_instruct;
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief text for game over
    std::unique_ptr<ngl::Text>m_gameState;
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief text for winning
    std::unique_ptr<ngl::Text>m_winner;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform matrices to the shader
    void loadMatricesToShader();
   //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    void keyPressEvent(QKeyEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    void mouseMoveEvent (QMouseEvent * _event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    void mousePressEvent ( QMouseEvent *_event) override;
    //---------------------------------------------------------------------------------------------------------------------
    ///@brief this method is called when the WASD keys are pressed
    void movePlayer(ngl::Vec3);
    //---------------------------------------------------------------------------------------------------------------------
    ///@brief this method gets the orientation of the player
    ngl::Mat4 getPlayerOrientation();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    void mouseReleaseEvent ( QMouseEvent *_event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    void wheelEvent( QWheelEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief timer event called when timer triggers
    void timerEvent(QTimerEvent *) override;


};



#endif
