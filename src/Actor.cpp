#include "Actor.h"
#include "IncludeGL.h"
#include "Utility.h"

#include <algorithm>
#include <cmath>

namespace asteroids
{

    inline float wrap( float x, float min, float max )
    {
        if( x < min )
        {
            return max - ( min - x );
        }

        if( x > max )
        {
            return min + ( x - max );
        }

        return x;
    }

    Actor::Actor()
        : x( 0 )
        , y( 0 )
        , velX( 0 )
        , velY( 0 )
        , mass( 1.0f )
        , radius( 0.0f )        
        , angle( 0.0f )
        , rotation( 120 )       
    {
        state = NORMAL_STATE;   
    }

    Actor::~Actor()
    {}

    void Actor::ApplyImpulse( float impulseX, float impulseY )
    {
        if( mass > 0 )
        {
            velX += ( impulseX / mass ) * cosf( convertToRad( rotation ) );
            velY += impulseY / mass * sinf( convertToRad( rotation ) );
        }
    }

    bool Actor::CouldCollide() const
    {
        return state == NORMAL_STATE;
    }

    bool Actor::IsColliding() const
    {
        return state == COLLIDED_STATE;
    }

    bool Actor::IsDisappearing() const
    {
        return state == DELETE_STATE;
    }

    bool Actor::DetectCollision( Actor* actor )
    {
        float radii = ( radius + actor->radius );

        // Checking for collision
        bool collision = ( radii * radii) >= calculateSquaredDistance( x, y, actor->x, actor->y );

        // Setting the actors state
        if( collision )
        {
            state = COLLIDED_STATE;
            actor->state = COLLIDED_STATE;
        }

        return collision;
    }

    void Actor::Draw()
    {
        glLoadIdentity();
        glTranslatef( x, y, 0 );
        glRotatef( angle, 0, 0, 1.0f );

        glLineWidth( 2.0f );

        glBegin( GL_LINE_LOOP );

        for( auto iter = m_points.begin(); iter != m_points.end(); iter+= 2)
        {
            glVertex2f( *iter, *(iter + 1) );
        }

        glEnd();
    }

    float Actor::GetX()
    {
        return x;
    }

    float Actor::GetY()
    {
        return y;
    }

    void Actor::Teleport( float newX, float newY )
    {
        x = newX;
        y = newY;
    }

    void Actor::UpdateSimulation( float deltaTime, float worldMinX, float worldMaxX, float worldMinY, float worldMaxY )
    {
        x += velX * static_cast<float>( deltaTime );
        y += velY * static_cast<float>( deltaTime );

        x = wrap( x, worldMinX, worldMaxX );
        y = wrap( y, worldMinY, worldMaxY );                
    }
}