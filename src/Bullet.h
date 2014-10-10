#pragma once

#include "Actor.h"

namespace asteroids
{
    class Bullet : public Actor
    {
    public:
        Bullet();   
        // Base class overrides
        //
        void ApplyImpulse( float impulseX, float impulseY );
        void Draw();
        void UpdateSimulation( 
            float deltaTime, 
            float worldMinX, 
            float worldMaxX, 
            float worldMinY, 
            float worldMaxY ) override;
    private:
        float lifespan;
        float currentLifespan;
    };
}