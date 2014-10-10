#pragma once

#if EMSCRIPTEN
    #include <GL/glut.h>
    #include <EGL/egl.h>
#else
    #include <GL/freeglut.h>
    #include <GL/gl.h>
#endif