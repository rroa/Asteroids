# Asteroids

Asteroids is a simple C++ implementation of the classic arcade game. The project uses OpenGL and GLUT for rendering and input handling. It is intended as an educational sample showing how to structure a small game using C++ classes.

**Table of Contents**

1. [Project Structure](#project-structure)
2. [Gameplay](#gameplay)
3. [Building](#building)
4. [Running](#running)
5. [Controls](#controls)
6. [Installation](#installation)

## Project Structure

The source code is located in the `src` directory. The most important files are:

- `main.cpp` – entry point that sets up OpenGL/GLUT and starts the main loop.
- `World.*` – manages the collection of in-game objects and the main update loop.
- `Player.*`, `Asteroid.*`, `Bullet.*`, and `Actor.*` – classes representing the different actors in the game.
- `TimeManager.*` – helper used for frame timing.
- `Makefile` – provides a basic build process for Unix like systems.

## Gameplay

The game is a simple Asteroids clone. A player controlled ship moves and shoots asteroids. Objects collide and break into smaller pieces. The structure was designed for clarity rather than for production use.

## Building

A standard C++ compiler and the OpenGL libraries (GL, GLU, and GLUT) are required. Instructions for obtaining these prerequisites are provided in [INSTALLATION.md](INSTALLATION.md).

To build on platforms where the dependencies are available through a package manager, run:

```bash
cd src
make
```

This compiles the project into an executable called `Asteroids` in the `src` directory.

## Running

After building, run the executable from the `src` directory:

```bash
./Asteroids
```

A window will appear showing the game. Resize events and keyboard input are handled through GLUT.

## Controls

During gameplay, the following default controls are available:

- `W`/`A`/`S`/`D` – Movement
- `SPACE` – Shoot
- `P` – Re-spawn the ship
- `O` – Spawn asteroids
- `L` – Delete all asteroids
- `Q` – Quit the game

## Installation

Instructions for installing the dependencies on different operating systems can be found in [INSTALLATION.md](INSTALLATION.md).

