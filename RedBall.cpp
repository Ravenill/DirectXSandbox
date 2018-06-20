#include "RedBall.h"
#include "Defines.h"

RedBall::RedBall(Map& map_, D3DXVECTOR3 position_, D3DXVECTOR3 direction_, D3DXVECTOR3 rotation_, D3DXVECTOR3 scale_, D3DXVECTOR4 color_)
: Drawable(position_, rotation_, scale_, color_)
, direction(direction_)
, velocity(BALL_INIT_VELOCITY)
, map(map_)
{

}

RedBall::~RedBall()
{
    
}

void RedBall::update(float deltaTime)
{
    position += *(D3DXVec3Normalize(&direction, &direction)) * velocity * deltaTime;
    
    decreasingVelocity();
}

void RedBall::decreasingVelocity()
{
    if (velocity >= 0.0005f)
        velocity -= 0.0005f;
    else if (velocity < 0.0005f)
        velocity = 0;
}

void RedBall::render(Mesh* mesh)
{
    Render(mesh, position, rotation, scale, color);
}
