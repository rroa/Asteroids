#pragma once

#include "Actor.h"
#include "Bullet.h"

namespace asteroids
{
    class Player : public Actor
    {
        public:
            Player();

            // User Input
            //
            void OnKeyDown ( unsigned char key );
            void OnKeyUp( unsigned char key );          

            // Base class overrides
            //
            void UpdateSimulation( 
                float deltaTime, 
                float worldMinX, 
                float worldMaxX, 
                float worldMinY, 
                float worldMaxY ) override;
            void ApplyImpulse( float impulseX, float impulseY ) override;
            
            // Movement
            //
            void ApplyDrag();
            void MoveDown();
            void MoveLeft();
            void MoveRight();
            void RotateRight( float deltaTime );
            void RotateLeft( float deltaTime );
            void MoveUp();
            
            // Respawn
            //
            void Reset();
            void Respawn();

            // Shooting
            //
            Bullet* Shoot();
            bool CanShoot();            
    private:        
            float currentSpeed;         
    };
}