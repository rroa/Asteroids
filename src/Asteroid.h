#pragma once

#include "Actor.h"

namespace asteroids
{
    class Asteroid : public Actor
    {
    public:
        // Constructors
        //
        Asteroid( AsteroidSize size = NORMAL_SIZE );

        // Base class overrides
        //
        void UpdateSimulation( 
                            float deltaTime,
                            float worldMinX,
                            float worldMaxX,
                            float worldMinY,
                            float worldMaxY ) override;
        void ApplyImpulse( float impulseX, float impulseY ) override;

        AsteroidSize GetSize();

    private:
        AsteroidSize m_size;
        int m_sizeFactor;
    };
}