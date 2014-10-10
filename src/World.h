#pragma once

#include "Actor.h"
#include "Player.h"
#include "Asteroid.h"
#include "TimeManager.h"
#include <list>

namespace asteroids
{
    class World
    {
        public:
            // Constructors / Destructor
            //
            World( float width, float height );
            ~World();

            // User Input
            //
            void OnKeyDown ( unsigned char key );
            void OnKeyUp( unsigned char key );

            // Main Game Loop elements
            void Draw();                        
            void UpdateInput();
            void UpdateSimulation();
            
            float GetWorldLeft();
            float GetWorldRight();
            float GetWorldBottom();
            float GetWorldTop();
        private:
            // Data Members
            bool m_isDown[ 256 ];            
            float m_dimensions[ 2 ];            
            double m_lastFrameTime;
            std::list< asteroids::Actor* > m_actors;
            std::list< asteroids::Asteroid* > m_asteroids;
            std::list< asteroids::Bullet* > m_bullets;
            std::vector< double > m_frameTime;
            Player* m_pPlayer;
            TimeManager* m_timer;

            // Private functions
            //
            void CleanActors();         
            void CheckCollision();
            void CreateAsteroid( AsteroidSize size, int amount,  float x = 0.f, float y = 0.f );
            void CreateBullet();
            void CreateDebris( Actor* actor );
            void DestroyActor( Actor* actor );
            void RespawnPlayer();
            void RemoveAsteroid();
            //bool NeedsCleanup( Actor* actor );
    };
}
