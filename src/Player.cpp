#include "Player.h"
#include "IncludeGL.h"
#include "Utility.h"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace asteroids
{       
    const float DRAG_FORCE = 0.999f;
    const float MAX_VELOCITY = 350.0f;
    const float THRUST = 3.0f;
    const float ANGLE_OFFSET = 90.f;
    const float BULLET_SPEED = 250.f;

    Player::Player()
    {
        type = PLAYER_PLAYERTYPE;               

        m_points.push_back( 0.0f );
        m_points.push_back( 20.0f );
        
        m_points.push_back( 12.0f );
        m_points.push_back( -10.0f );
        
        m_points.push_back( 6.0f );
        m_points.push_back( -4.0f );
        
        m_points.push_back( -6.0f );
        m_points.push_back( -4.0f );

        m_points.push_back( -12.0f );
        m_points.push_back( -10.0f );

        radius = 10.0f;
    }

    void Player::ApplyDrag()
    {
        velX *= DRAG_FORCE;
        velY *= DRAG_FORCE;
    }

    void Player::ApplyImpulse( float impulseX, float impulseY )
    {
        if( mass > 0 )
        {           
            velX += ( impulseX / mass ) * cosf( asteroids::convertToRad( angle + ANGLE_OFFSET ) );
            velY += ( impulseY / mass ) * sinf( asteroids::convertToRad( angle + ANGLE_OFFSET ) );
        }
    }

    void Player::UpdateSimulation( float deltaTime, float worldMinX, float worldMaxX, float worldMinY, float worldMaxY )
    {
        float speed = fabs( sqrtf( velX * velX + velY * velY ) );

        if(speed > MAX_VELOCITY)
        {
            velX = (velX / speed) * MAX_VELOCITY;
            velY = (velY / speed) * MAX_VELOCITY;
        }
        
        currentSpeed = speed;

        ApplyDrag();

        Actor::UpdateSimulation( deltaTime, worldMinX, worldMaxX, worldMinY, worldMaxY );
    }

    void Player::MoveDown()
    {
        ApplyImpulse( -THRUST, -THRUST );
    }

    void Player::MoveLeft()
    {
        Actor::ApplyImpulse( -THRUST, 0 );
    }
    void Player::MoveRight()
    {
        Actor::ApplyImpulse( THRUST, 0 );
    }

    void Player::MoveUp()
    {               
        ApplyImpulse( THRUST, THRUST );
    }

    Bullet* Player::Shoot()
    {
        float shootingAngle = angle + ANGLE_OFFSET;
        float bulletX = m_points[1] * cosf( convertToRad( shootingAngle ) );
        float bulletY = m_points[1] * sinf( convertToRad( shootingAngle ) );

        float vx = ( currentSpeed + BULLET_SPEED ) * cosf( convertToRad( shootingAngle ) );
        float vy = ( currentSpeed + BULLET_SPEED ) * sinf( convertToRad( shootingAngle ) );

        Bullet* bullet = new Bullet();

        bullet->Teleport( x + bulletX, y + bulletY );
        bullet->ApplyImpulse( vx, vy );

        return bullet;
    }

    void Player::RotateRight( float deltaTime )
    {
        angle -= rotation * ( deltaTime );
    }

    void Player::RotateLeft( float deltaTime )
    {
        angle += rotation * ( deltaTime );
    }

    void Player::Reset()
    {
        x = 0;
        y = 0;
        velX = 0;
        velY = 0;
        mass = 1.0f;
        angle = 0.0f;
        rotation = 120.0f;
        state = NORMAL_STATE;
    }

    bool Player::CanShoot()
    {
        return state != COLLIDED_STATE;
    }

    void Player::Respawn()
    {
        if( state == COLLIDED_STATE )
        {
            Reset();
        }       
    }
}