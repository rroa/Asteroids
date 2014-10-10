#pragma once

#include <vector>

namespace asteroids
{
    enum PlayerType { ASTEROID_PLAYERTYPE, PLAYER_PLAYERTYPE, BULLET_PLAYERTYPE };
    enum ActorState { NORMAL_STATE, COLLIDED_STATE, DELETE_STATE };
    enum AsteroidSize { NORMAL_SIZE = 0, MEDIUM_SIZE = 1, SMALL_SIZE = 2 };
}

namespace asteroids
{
    class Actor
    {
        public:
            // Constructors
            //
            Actor();
            virtual ~Actor();           
            
            // Methods
            //                  
            virtual void ApplyImpulse( float impulseX, float impulseY );            
            bool CouldCollide() const;
            bool DetectCollision( Actor* actor );
            virtual void Draw();
            bool IsColliding() const;
            bool IsDisappearing() const;
            virtual void Teleport( float newX, float newY );            
            virtual void UpdateSimulation( 
                float deltaTime, 
                float worldMinX, 
                float worldMaxX, 
                float worldMinY, 
                float worldMaxY );
            
            // Public Data
            //
            virtual float GetX();
            virtual float GetY();                       
    protected:
            float x;
            float y;            
            float radius;
            float angle;
            float velX;
            float velY;
            float rotation;
            float mass; // If mass == 0, the mass is infinite.          
            std::vector< float > m_points;
            ActorState state;
            PlayerType type;
    };
}