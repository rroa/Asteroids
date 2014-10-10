#include "World.h"
#include "IncludeGL.h"
#include "Utility.h"

#include <iostream>
#include <algorithm>

#ifdef __unix__
    #include <sys/time.h>
#endif

namespace
{
    bool Fake()
    {
        return false;
    }

    bool NeedsCleanup( asteroids::Actor* actor )
    {
        return actor->IsColliding() || actor->IsDisappearing();
    }
}

namespace asteroids
{      
    const float DESIRED_FRAME_RATE = 60.0f;
    const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE; 
    const float INPUT_BULLET_DELAY = 0.5f;
    float nextBulletTime = 0.f;

    World::World( float width, float height ) 
        : m_pPlayer ( new Player )        
    {                   
        m_dimensions[ 0 ] = width;
        m_dimensions[ 1 ]= height;

        // Initialization
        //

        m_timer = new TimeManager;
        m_lastFrameTime = m_timer->getElapsedTimeInSeconds();
        
        std::generate( m_isDown, m_isDown + 256, Fake );
        m_actors.push_back( m_pPlayer );              
        CreateAsteroid( NORMAL_SIZE , 10);    
    }

    World::~World()
    {
        // Delete pointers
        //
        for(std::list< Actor* >::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
        {
            delete *it;
        }
        
        delete m_timer;
        delete m_pPlayer;

        // Clear containers
        //
        m_actors.clear();
        m_asteroids.clear();
        m_bullets.clear();
    }

    void World::OnKeyDown ( unsigned char key )
    {
        m_isDown[ key ] = true;
    }

    void World::OnKeyUp( unsigned char key )
    {
        m_isDown[ key ] = false;
        
        if( key == 'o' || key == 'O' ) CreateAsteroid( NORMAL_SIZE , 1);
        
        if( key == 'l' || key == 'L' ) RemoveAsteroid();
        
        if( key == 32 ) 
        {
            if( m_pPlayer->CanShoot() )
            {
                CreateBullet();
            }            
        }            
    }

    float World::GetWorldLeft()
    {
        return -( m_dimensions[0] * 0.5f );
    }

    float World::GetWorldRight()
    {
        return ( m_dimensions[0] * 0.5f );
    }

    float World::GetWorldBottom()
    {
        return -( m_dimensions[1] * 0.5f );
    }

    float World::GetWorldTop()
    {
        return ( m_dimensions[1] * 0.5f );
    }

    void World::UpdateInput()
    {       
        if( m_isDown[ 'w' ] || m_isDown[ 'W' ] ) m_pPlayer->MoveUp();
        if( m_isDown[ 'a' ] || m_isDown[ 'A' ] ) m_pPlayer->RotateLeft( DESIRED_FRAME_TIME );
        if( m_isDown[ 's' ] || m_isDown[ 'S' ] ) m_pPlayer->MoveDown();
        if( m_isDown[ 'd' ] || m_isDown[ 'D' ] ) m_pPlayer->RotateRight( DESIRED_FRAME_TIME );
        if( m_isDown[ 'p' ] || m_isDown[ 'P' ] ) RespawnPlayer();   
        //if( m_isDown[ 'o' ] || m_isDown[ 'O' ] ) CreateAsteroid( NORMAL_SIZE , 1);
        //if( m_isDown[ 'l' ] || m_isDown[ 'L' ] ) RemoveAsteroid();
    }

    void World::UpdateSimulation()
    {       
        double startTime = m_timer->getElapsedTimeInSeconds();

        // Drawing the actors
        //
        std::list< Actor* >::iterator ait = m_actors.begin();
        while (ait != m_actors.end())
        {                       
            (*ait)->UpdateSimulation( DESIRED_FRAME_TIME, GetWorldLeft(), GetWorldRight(), GetWorldBottom(), GetWorldTop() );           
            ++ait;                  
        }
        
        // Checking collision between the actors
        //
        CheckCollision();
        
        // Checking for actors marked as collided or for deletion
        //
        CleanActors();
        
        double endTime = m_timer->getElapsedTimeInSeconds();
        double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

        while( endTime < nextTimeFrame )
        {
            // Spin lock
            endTime = m_timer->getElapsedTimeInSeconds();
        }

        //double elapsedTime = endTime - startTime;        
     
        m_lastFrameTime = m_timer->getElapsedTimeInSeconds();
    }

    void World::Draw()
    {
        for(std::list< Actor* >::iterator it = m_actors.begin(); it != m_actors.end(); ++it)
        {           
            if( (*it)->CouldCollide() )
                (*it)->Draw();          
        }        
    }

    void World::CreateBullet()
    {
        Bullet* pBullet = m_pPlayer->Shoot();
        m_actors.push_back( pBullet );
        m_bullets.push_back( pBullet );
    }

    void World::CreateAsteroid( AsteroidSize size, int amount,  float x, float y )
    {
        for( int i = 0; i < amount; ++i )
        {
            Asteroid* pAsteroid = new Asteroid( size );
            m_actors.push_back( pAsteroid );
            m_asteroids.push_back( pAsteroid );

            if( x == 0 && y == 0 )
            {
                const int sideAxis = rand() & 1;
                const float sideDir = ( rand() & 1 ) ? 1.0f : -1.0f;

                const int otherSideAxis = ( sideAxis + 1 ) & 1;

                float point[ 2 ];
                point[ sideAxis ] = sideDir * m_dimensions[ sideAxis ] * 0.5f;
                point[ otherSideAxis ] = randInRange( m_dimensions[ otherSideAxis ] * -0.5f, m_dimensions[ otherSideAxis ] * 0.5f );

                pAsteroid->Teleport( point[ 0 ], point[ 1 ] );
            }
            else
            {
                pAsteroid->Teleport( x, y );
            }           

            // Applying impulse to the asteroid
            //
            float x = randInRange( -150.0f, 150.0f );
            float y = randInRange( -150.0f, 150.0f );

            pAsteroid->ApplyImpulse( x, y );
        }
    }

    void World::CheckCollision()
    {
        for(std::list< Asteroid* >::iterator asteroid = m_asteroids.begin(); asteroid != m_asteroids.end(); ++asteroid)
        {
            if( (*asteroid)->CouldCollide() && m_pPlayer->CouldCollide() )
            {                               
                if ( m_pPlayer->DetectCollision( ( *asteroid ) ) )
                {
                    CreateDebris( (*asteroid) );
                }

                for(std::list< Bullet* >::iterator bullet = m_bullets.begin(); bullet != m_bullets.end(); ++bullet)
                {
                    if( (*bullet)->CouldCollide() && (*asteroid)->CouldCollide() )
                    {
                        if( (*asteroid)->DetectCollision( ( *bullet ) ) )                       
                        {
                            CreateDebris( (*asteroid) );
                        }
                    }
                }
            }
        }
    }

    void World::RespawnPlayer()
    {
        m_pPlayer->Respawn();
    }

    void World::RemoveAsteroid()
    {
        if(m_actors.size() > 1)
        {
            std::list< Asteroid* >::iterator it = m_asteroids.begin();

            DestroyActor( *it );
        }       
    }    

    void World::CleanActors()
    {       
        //[&item](const T&v) { return item == v; }
        auto iter = std::find_if ( m_actors.begin(), m_actors.end(), NeedsCleanup );
            //[&item] ( Actor* actor ) { return actor->IsColliding() || actor->IsDisappearing(); } );
        if(iter != m_actors.end() )
        {                       
            DestroyActor( *iter );
        }

    }

    void World::DestroyActor( Actor* actor )
    {                               
        // Retrieve actor from m_actors list
        //
        auto actorsResult = std::find( m_actors.begin(), m_actors.end(), actor );
        
        // Retrieve actor from m_asteroids list
        //
        auto asteroidsResult = std::find( m_asteroids.begin(), m_asteroids.end(), actor );
        
        // Retrieve actor from m_bullets list
        //
        auto bulletsResult = std::find( m_bullets.begin(), m_bullets.end(), actor );

        if( m_pPlayer == actor)
        {
            return;
            //m_pPlayer = 0;
        }

        // Removing the allocated pointer
        //
        delete actor;

        // Deleting actor iterator from lists
        //
        if( m_actors.size() > 0 && actorsResult != m_actors.end() )
        {
            m_actors.erase( actorsResult );
        }       

        if( m_asteroids.size() > 0 && asteroidsResult != m_asteroids.end() )
        {
            m_asteroids.erase( asteroidsResult );
        }       
        
        if( m_bullets.size() > 0 && bulletsResult != m_bullets.end() )
        {
            m_bullets.erase( bulletsResult );
        }       
    }

    void World::CreateDebris( Actor* actor )
    {       
        auto currentAsteroid = dynamic_cast < Asteroid* >( actor );
        if( currentAsteroid != 0          
            && currentAsteroid->GetSize() != SMALL_SIZE )
        {           
            auto newSize = ( currentAsteroid->GetSize() == NORMAL_SIZE ) ? MEDIUM_SIZE : SMALL_SIZE;            
            CreateAsteroid( newSize, 2, currentAsteroid->GetX(), currentAsteroid->GetY() );
        }
    }
}