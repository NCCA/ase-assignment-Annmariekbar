
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

Research notes:

- Player controls - WASD, arrow keys (Depending on if you're fire/water)
- Aim is to win individual levels
- Win level by finding a diamond without dying (1 life)
- If one charcater dies, it's over for the both of them
- Levels increase in difficulty

#### game2
![alt tag](https://github.com/NCCA/ase-assignment-Annmariekbar/blob/main/fireboy-and-watergirl-in-the-forest-temple-full-walkthrough.mp4.jpg)

Research notes:

- Player controls - WASD, arrow keys (Depending on if you're fire/water)
- Aim is to win individual levels
- Win level by finding a diamond without dying (1 life)
- If one charcater dies, it's over for the both of them
- Levels increase in difficulty

### More Bullet Physics Engine research
  ![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Bullet.png)
I studied Jon Macey's BulletNGL code as this had a wider implementation of the Bullet Physics.

Algorithms to note:

>h
>
>y


## Starting my code
These are some more ideas on what my game should be able to do:

- use arrow keys to move the player character
- have a level system, aim is to level up


### Concluded ideas prior to coding:

- use WASD to move player
- space to jump
- collect an object to level up
- win when reach a certain level

### Changing from mouse control to WASD

### Adding a player class
Intially, I was going to have specifically a fish, but I changed my mind and want my class to be able to fit any model.

### Adding a level system




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
