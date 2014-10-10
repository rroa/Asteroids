#pragma once

#include <cstdlib>

namespace asteroids
{   
    const float PI = 3.141592653f;

    inline int randInRange( int min, int max )
    {
        return min + rand() % ( max - min + 1 );
    }

    inline float randInRange( float min, float max )
    {
        return min + ( max - min ) * ( rand() / (float) RAND_MAX );
    }

    inline double randInRange( double min, double max )
    {
        return min + ( max - min ) * ( rand() / (double) RAND_MAX );
    }

    inline float convertToRad( float degrees )
    {
        return degrees * ( PI / 180 );
    }

    inline float convertToDegrees( float radians )
    {
        return radians * ( 180 / PI );
    }

    inline float calculateSquaredDistance( float x1, float y1, float x2, float y2 )
    {
        float xdiff = x2 - x1;
        float ydiff = y2 - y1;
        
        return ( xdiff * xdiff ) + ( ydiff * ydiff );
    }
}