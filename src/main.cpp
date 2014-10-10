#include <iostream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>

#include "IncludeGL.h"
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Asteroid.h"
#include "Utility.h"

const float WIDTH = 1136;
const float HEIGHT = 640;

void cleanUp(void);
void shutdown(void);

asteroids::World* g_pWorld = 0;

void onResize( int width, int height )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    glOrtho( g_pWorld->GetWorldLeft(), g_pWorld->GetWorldRight(), g_pWorld->GetWorldBottom(), g_pWorld->GetWorldTop(), -1, 1  );

    glMatrixMode( GL_MODELVIEW );
}

void updateFrame()
{
    // Update input.
    //
    g_pWorld->UpdateInput();

    //Update the simulation
    //  
    g_pWorld->UpdateSimulation();

    // Draw the world
    //
    glClearColor( 0.1f, 0.1f, 0.15f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    g_pWorld->Draw();   
    
    // SWAPPING BUFFERS
    glutSwapBuffers();

    // DRAW AGAIN AS SOON AS YOU CAN
    glutPostRedisplay();
}

void onKeyboardEvent( unsigned char key, int x, int y )
{   
    g_pWorld->OnKeyDown( key );
}

void onKeyboardUpEvent( unsigned char key, int x, int y )
{
    g_pWorld->OnKeyUp( key );

    if( key == 'Q' || key == 'q' )
    {
        shutdown();
    }
}

void cleanUp()
{
}

void shutdown()
{
    delete g_pWorld;
    g_pWorld = 0;

    exit( 0 );  
}

int main(int argc, char** argv)
{
    // Initialize
    //
    glutInit( &argc, argv );            // Initialize GLUT
    glutInitDisplayMode( GLUT_DOUBLE ); // Define the graphics buffer setup
    glutInitWindowSize( 1136, 640 );    // Set the size of the window
    glutCreateWindow( "Asteroids" );   // Create the window

    // Tell GLUT what functions to call for important events.
    //
    glutDisplayFunc( &updateFrame );        // Every frame
    glutReshapeFunc( &onResize );       // When the window changes size
    glutKeyboardFunc( &onKeyboardEvent );   // When a keystroke occurs
    glutKeyboardUpFunc( &onKeyboardUpEvent );

    // TODO setup other call backs such as special keys, mouse input.

    // Create game objects
    //
    g_pWorld = new asteroids::World( WIDTH, HEIGHT );

    std::cout << "Controls:\n";
    std::cout << "Up                    - W\n";
    std::cout << "Down                  - S\n";
    std::cout << "Left                  - A\n";
    std::cout << "Right                 - D\n";
    std::cout << "Shoot                 - SPACE\n";
    std::cout << "Re-spawn              - P\n";
    std::cout << "Spawn asteroids       - O\n";
    std::cout << "Delete asteroids      - L\n";

    // Start the main loop
    //
    glutMainLoop(); 

    return 0;
}