# Installation Guide

This document explains how to install the dependencies required to build and run **Asteroids** on various platforms. You need a C++ compiler and the OpenGL development libraries (GL, GLU and GLUT). Clang or GCC are both suitable.

## Windows

1. Install [Visual Studio](https://visualstudio.microsoft.com) or [MinGW](http://mingw.org/).
2. Download and install the [freeglut](http://freeglut.sourceforge.net/) development package. When using Visual Studio, copy the header and library files into your Visual Studio include and lib directories.
3. Ensure that the freeglut `dll` is available in your PATH when running the program.
4. Build the project by opening a Visual Studio command prompt and running `nmake` with the provided `Makefile`, or create a Visual Studio project and add the source files.

## Windows Subsystem for Linux (WSL)

WSL behaves much like a normal Linux environment. You can install the dependencies using `apt` and build with `make`:

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev
cd /path/to/Asteroids/src
make
```

## macOS

1. Install Xcode from the App Store.
2. Install the command line tools if you have not already done so (`xcode-select --install`).
3. Install [Homebrew](https://brew.sh/) and then the GLUT package:

```bash
brew install freeglut
```

4. Build the project from the `src` directory using `make`.

## Linux (Debian/Ubuntu)

Install the compiler and OpenGL development packages from your package manager:

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev
cd src
make
```

After installation the `Asteroids` executable will be created in the `src` directory.

