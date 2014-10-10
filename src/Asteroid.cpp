#include "Asteroid.h"
#include "IncludeGL.h"
#include "Utility.h"

#include <algorithm>
#include <cmath>

namespace asteroids
{   
    const size_t NUM_POINTS = 16;
    const float MIN_SIZE = 25.0f;
    const float MAX_SIZE = 45.0f;   

    Asteroid::Asteroid( AsteroidSize size )
        : m_size ( size )       
    {               
        m_sizeFactor = (int) size + 1;
        
        // Calculating the MIN/MAX size of the asteroid based on the size enum value
        //
        float min = MIN_SIZE / m_sizeFactor;
        float max = MAX_SIZE / m_sizeFactor;

        type = ASTEROID_PLAYERTYPE;
        
        for ( size_t i = 0; i < NUM_POINTS; ++i)
        {
            const float radians = (i / (float) NUM_POINTS) * 2.0f * asteroids::PI;
            const float randDist = asteroids::randInRange( min, max );

            m_points.push_back( sin( radians ) * randDist );
            m_points.push_back( cos( radians ) * randDist );
        }

        radius = ( min + max ) * 0.5f;
    }

    void Asteroid::UpdateSimulation( 
        float deltaTime, 
        float worldMinX, 
        float worldMaxX, 
        float worldMinY, 
        float worldMaxY )
    {
        // Rotate the asteroid.
        //
        angle += rotation * deltaTime;

        Actor::UpdateSimulation( deltaTime, worldMinX, worldMaxX, worldMinY, worldMaxY );
    }

    void Asteroid::ApplyImpulse( float impulseX, float impulseY )
    {
        if( mass > 0 )
        {
            velX += ( impulseX / mass ) * cosf( convertToRad( rotation ) ) + m_sizeFactor;
            velY += ( impulseY / mass ) * sinf( convertToRad( rotation ) ) + m_sizeFactor;
        }
    }

    asteroids::AsteroidSize Asteroid::GetSize()
    {
        return m_size;
    }

}