
# My Report

## Annmarie Bartholomew Assignment, s5417041

### Initial ideas
I am creating a simple game, these are my initial ideas on what it should be able to do:

- the player move an object around the scene
- interact with other objects in the scene

To explore:
- how the user is going to be controlled (e.g. moving the mouse around)
- objective of the game

So far, an idea is to have the player be a fish and it will interact with spheres in a tank, the player will move around using the mouse.
The tank would be a transparent simple cube shape like this:


![alt tag](https://github.com/NCCA/ase-assignment-Annmariekbar/blob/main/thetank.jpg)


*Photo source [link](https://www.istockphoto.com/photos/transparent-cube) here.*

And the fish would also be very simple.

### Bullet Physics Engine research
I read into this [guide](http://bulletphysics.org/wordpress/) to start to understand Bullet Physics. This engine will be useful with my code as I would like to interact with other objects, meaning that I need a collision detection.


#### Algorithms for further insight:
I studied algorithms that were linked on the guide.

I found this section in "animation.py" on github, *source [link](https://github.com/google-research/kubric/blob/main/examples/animation.py) here.*


>scene.camera.position = (5.0, -5.8, 2.8)
>
>scene.camera.look_at((0.0, 0.0, 2.2))

This section raised the importance of having a camera in my scene.



I also found this section in "simulator.py" , *source [link](https://github.com/google-research/kubric/blob/main/examples/simulator.py) here.*

>scene = kb.Scene(resolution=(256, 256))
>
>scene.frame_end = 48   # < numbers of frames to render
>
>scene.frame_rate = 24  # < rendering framerate
>
>scene.step_rate = 240  # < simulation framerate
>
>renderer = KubricBlender(scene)
>
>simulator = KubricSimulator(scene)

This is a way of implementing a scene and attaching important features, one being the frame rate which I didn't consider before.

### Existing  simple games:
#### Fireboy and Watergirl
![alt tag](https://github.com/NCCA/ase-assignment-Annmariekbar/blob/main/fireboy-and-watergirl-in-the-forest-temple-full-walkthrough.mp4.jpg)

*click [here](https://www.coolmathgames.com/0-fireboy-and-water-girl-in-the-forest-temple) to play*

Research notes:

- Player controls - WAD, arrow keys (Depending on if you're fire/water)
- Aim is to win individual levels
- Win level by finding a diamond without dying (1 life)
- If one charcater dies, it's over for the both of them
- Dies by touching alternate property (fire/water)
- Levels increase in difficulty

#### Moto X3M Winter

![alt tag](https://github.com/NCCA/ase-assignment-Annmariekbar/blob/main/moto_x3m_winter.png))



*click [here](https://www.friv.com/z/games/motox3mwinter/game.html) to play*

Research notes:

- Player controls - WAD or arrow keys
- R - restart
- P - pause
- Aim is to win individual levels
- Win level by reaching end of path without dying (1 life)
- Levels increase in difficulty

  #### Bloons Tower Defence

![alt tag](https://github.com/NCCA/ase-assignment-Annmariekbar/blob/main/bloonstd.jpg)


*Click [here](https://www.crazygames.com/game/bloons-tower-defense) to play*

Research notes:

- Player controls - mouse clicks, drags and drops
- Aim is to win individual levels
- Win level by reaching end without dying (40 lives)
- Levels increase in difficulty
- Earn money from victories
- Buy resources with money to help with increasing difficulty


### More Bullet Physics Engine research
  ![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Bullet.png)
  
I studied Jon Macey's [BulletNGL code](https://github.com/NCCA/BulletNGL) as this had a wider implementation of the Bullet Physics.

Jon Macey implements algorithms for rendering and for the camera, having access to this means I am able to focus more on coding the gameplay aspect rather than the technicalities of the scene.


J. Macey's code for setting up the camera:


>   ngl::Vec3 from(0.0f, 5.0f, 15.0f);
> 
>   ngl::Vec3 to(0.0f, 0.0f, 0.0f);
> 
>   ngl::Vec3 up(0.0f, 1.0f, 0.0f);
> 
> 
>   m_view = ngl::lookAt(from, to, up);
> 
>   m_project = ngl::perspective(45.0f, 720.0f / 576.0f, 0.05f, 350.0f);


I will use this BulletNGL code as a basis for the physics and scene set up in my game.


## Starting my code
I wasn't completely sure on everything I wanted to do with this game, based on my research, there was a lot of gameplay I was missing such as a way to lose/win. I deicded to start with the basics, which was being abe to move the fish around.


### The basics

- use mouse to move fish 
- have this player character interact with other objects


### Changing from mouse control to WASD
After a lot of experimenting, this was my best algorithm for controlling the player character with a mouse

>std::cout << "origx: " << m_win.origXPos << ", origy: " << m_win.origYPos << std::endl;
>
>std::cout << "winWidth: " << m_win.width <<  std::endl;
>
>//  int diffX = static_cast<int>(position.x() - m_win.origXPos);
>
>//  int diffY = static_cast<int>(position.y() - m_win.origYPos);
>
>float X;
>
>float Y;
>
>X = (static_cast<float>(position.x()));//-((static_cast<float>(m_win.width)/4));
>
>Y = -(static_cast<float>(position.y()));
>
>//  m_win.origXPos = position.x();
>
>//  m_win.origYPos = position.y();
>
>ngl::Vec3 fishPos= m_fish.getPosition();
>
>m_fish.setPosition( X*INCREMENT, Y*INCREMENT,0);
>
>//  m_fish.setPosition( fishPos.m_x += INCREMENT * diffX, fishPos.m_y-= INCREMENT * diffY,0);
>
>fishPos= m_fish.getPosition();
>
>m_physics->updateMeshPosition("apple", fishPos);
>
>std::cout << "Fish position - x: " << fishPos.m_x << ", y: " << fishPos.m_y << std::endl;
>
>std::cout << "Mouse position - x: " << position.x() << ", y: " << position.y() << std::endl;
>
>update();

It still didn't have the results I wanted because the character model was always away from the mouse and the distance from the mouse widget changed due to the perspective of the scene; expanding the window made these effects worse. As this was taking too long, I decided to chnage tactic and use the WASD keys instead. This ended up being better and more immersive.

### Adding a player class
To make the updating of the position of the player charcater easier, I designed a player class. Intially, I was going to have specifically a fish, but I changed my mind and want my class to be able to fit any model.

My algorithm to set the position:

>void Player::setPosition(float x,float y,float z)
>
>{
>
>//    Sets position using the variables in the parameters
>
>    Player::myPos.m_x = x;
>
>    Player::myPos.m_y = y;
>
>    Player::myPos.m_z = z;
>
>}

### Adding a game objective & enemy class
Now wanting a way to "lose" and "win" the game, I created an enemy class so that different enemies caused different types of damage.

My enemy class:

>// Constructor definition
>
>Enemy::Enemy(const std::string &name, float dmg, const ngl::Vec3 &col)
>
>        : name(name), damage(dmg), colour(col) {}
>
>
>// Implementation of damage retrieval method
>
>float Enemy::getDmg() const {
>
>    return damage;
>
>}
>
>// Implementation of colour retrieval method
>
>ngl::Vec3 Enemy::getCol() const {
>
>    return colour;
>
>}

I also implemented a health tracker in my player class to enable "death":

>bool Player::decreaseHealth(float dmge)
>
>{
>
>    health -= dmge;
>
>    if (health <= 0) return 0;
>
>    else return 1;
>
>};

### Level class
I designed a level class to create a random "map" based on the difficulty of the level and the map dictated which shapes were going to be imported. I decided to get rid of the enemy class to focus more on the levels, but I did keep one enemy being the "spheres".

Load map section of my level class:

>std::map<int, obsData> Level::loadMap() {
>
>    mapData.clear(); // Clear existing data if any
>
>    for (int i = 1; i < obs; ++i) {
>
>        ngl::Vec3 pos;
>
>        std::string obj;
>
>        do {
>
>            pos = ngl::Random::getRandomVec3() * ngl::Vec3{3.0f, 3.0f, 3.0f};
>
>        }while (!isPositionValid(pos, mapData, minDistance));
>
>        int height = 1+ static_cast<int>(ngl::Random::randomPositiveNumber(maxHeight));
>
>        float randomNum = ngl::Random::randomPositiveNumber(1.0f); // Generate random number between 0 and 1
>
>        obj = (randomNum < 0.5f) ? "box" : "sphere";
>
>
>
>        mapData[i] = obsData{height, pos, obj};
>
>    }
>
>
>
>    return mapData;
>
>}


### Collision detection
I created a collision detected algorithm, with some help from ChatGPT, it distinguishes which shape is being hit and returns if there has been a collision with a sphere. I have a delayed timer so that it doesn't constant output "hit" in the terminal.


> std::string PhysicsWorld::getCollision()
> 
> {
> 
>     --- code omission for simplicity ---
> 
> 
>     auto now = std::chrono::steady_clock::now();
> 
>     bool collisionDetected = false;
> 
> 
>     --- code omission for simplicity ---
> 
>     {
> 
>         auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - m_lastHitTime);
> 
>         if (elapsed >= m_hitInterval)
> 
>         {
>             std::cout << "hit" << std::endl;
> 
>             m_lastHitTime = now; // Update the last hit time
> 
>         }
> 
>         return 1;
> 
>     }
> 
>     return 0;
> 
> }


### Collision detection update
The spheres were rendering the same colour as the main character, to avoid this, I stopped using "addSphere" for adding the enemies and instead uses "addMesh", this alongside other adjustments has made the collision detection inaccurate. On the other hand, the player character is now distinguishable! I also took away the delay timer in the collision detection algorithm and instead of returning if something was hit, I returned which shape has been hit, so that I was able to create different events based on what was hit.

Section of collision detection code:

>         else if ((nameA == "player" && nameB == "box") || (nameA == "teapot" && nameB == "box"))
> 
>         {
> 
>             return "box";
> 
>         }
> 


## Successes and limitations
### Successes
- I succesfully am able to move the character depending on the WASD keys
- There is feedback when the player wins and loses
- The game resets the levels and character when restarted
- Damage is  applied when a collision with the enemy is detected
- There is  no damage when other objects are collided with
- It levels up when the teapot is found
- Levels increase in difficulty further into the game
- Instructions on how to play the game
- Instructions disappear after level 1
- Health bar shows how much health the player has

### Limitations
- The collision detection is faulty
- The player isn't able to jump as the positon in the y axis is always set to 0.5
- The WASD inputs are unaffected by the orientation of the scene so it may not go the right way relative to the camera
- The "level" "instructions" and "health" labels don't always poition properly when modifying the window size
- Simple criteria for the game, overall not the most interesting


```
