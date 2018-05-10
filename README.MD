# PacManCG

3D PacMan game using pure OpenGL and free-glut.

## Prerequisites

Run the command below to install the packages necessary:
```
sudo apt-get install cmake build-essential libgl1-mesa-dev freeglut3 freeglut3-dev binutils-gold libglm-dev xutils-dev
```

## Run

To compile and run you must run the following commands:
```
g++ -o Pacman *.cpp -lGL -lGLU -lglut -lm
./Pacman
```
