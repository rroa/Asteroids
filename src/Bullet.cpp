#include "Bullet.h"
#include "IncludeGL.h"
#include <cmath>

namespace asteroids
{
    Bullet::Bullet()
        : currentLifespan ( 0.f )
        , lifespan ( 120.f )
    {

    }

    void Bullet::ApplyImpulse( float impulseX, float impulseY )
    {
        if( mass > 0 )
        {
            velX += ( impulseX / mass ) ;
            velY += impulseY / mass ;
        }
    }

    void Bullet::UpdateSimulation( float deltaTime, float worldMinX, float worldMaxX, float worldMinY, float worldMaxY )
    {
        if( currentLifespan < lifespan )
            currentLifespan++;
        else
            state = DELETE_STATE;

        Actor::UpdateSimulation( deltaTime, worldMinX, worldMaxX, worldMinY, worldMaxY );
    }

    void Bullet::Draw()
    {
        glLoadIdentity();
        
        glBegin(GL_LINE_LOOP);
        
        for(int ii = 0; ii < 360; ii++)
        {
            float theta = 2.0f * 3.1415926f * float(ii) / float(360);//get the current angle

            float _x = 2 * cosf(theta);//calculate the x component
            float _y = 2 * sinf(theta);//calculate the y component

            glVertex2f(x + _x, y + _y);//output vertex

        }    

        glEnd();
    }
}