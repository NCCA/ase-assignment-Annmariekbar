
# My Report

## Annmarie Bartholomew Assignment
## s5417041

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


[photo sourced from here](https://www.istockphoto.com/photos/transparent-cube)

And the fish would also be very simple.

### Bullet Physics Engine research
I read into this [guide](http://bulletphysics.org/wordpress/) to start to understand Bullet Physics. This engine will be useful with my code as I would like to interact with other objects, meaning that I need a collision detection.

Algorithms for further insight:

I found this section in "animation.py" on github, [link](https://github.com/google-research/kubric/blob/main/examples/animation.py) here.

scene.camera.position = (5.0, -5.8, 2.8)

scene.camera.look_at((0.0, 0.0, 2.2))

This section raised the importance of having a camera in my scene.


I also found this section in "simulator.py" , [link](https://github.com/google-research/kubric/blob/main/examples/simulator.py) here.

scene = kb.Scene(resolution=(256, 256))

scene.frame_end = 48   # < numbers of frames to render

scene.frame_rate = 24  # < rendering framerate

scene.step_rate = 240  # < simulation framerate

renderer = KubricBlender(scene)

simulator = KubricSimulator(scene)

This is a way of implementing a scene and attaching important features, one being the frame rate which I didn't consider before.

### Existing similar simple games:
![alt tag](https://github.com/NCCA/ase-assignment-Annmariekbar/blob/main/fireboy-and-watergirl-in-the-forest-temple-full-walkthrough.mp4.jpg)

Fireboy Watergirl
PLayer controls - WASD, arrow keys (Depending on if you're fire/water)

### Further ideas 
These are some more ideas on what my game should be able to do:

- use arrow keys to move the player character
- have a level system, aim is to level up


### Existing similar simple games:

notes: these games WASD more often than the arrow keys, will make it easier for user to use WASD as it would be more familiar for a gamer


### Concluded ideas prior to coding:

- use WASD to move player
- space to jump
- collect an object to level up
- win when reach a certain level

### More Bullet Physics Engine research
  ![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/Bullet.png)
I studied Jon Macey's BulletNGL code as this had a wider implementation of the Bullet Physics.

Algorithms to note:
```
