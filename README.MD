This is my 3D interpretation of pacman in openGL. How it works-

The program consists of 4 classes
-pacman:
  x, y coordinates
  angle for direction vector
  lives left
  speed
  animation controls

-ghost:
  used in an array of 4 ghosts with different attributes
  color
  speed
  x, y, angle
  edible state (can/cannot be eaten by pacman)

-board:
  pebbles left
  position of all remaining pebbles
  board drawing data

-camera:
  allows dynamic camera movement in 3D mode as well
  as stationary classic view

  camera x,y,z
  look at point

Gameplay is exactly like the original pacman game.