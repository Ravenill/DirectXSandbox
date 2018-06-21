#include "RedBall.h"
#include "Defines.h"
#include "Collision.h"

RedBall::RedBall(Map& map_, const D3DXVECTOR3 position_, const D3DXVECTOR3 direction_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_)
: Drawable(position_, rotation_, scale_, color_)
, direction(direction_)
, velocity(BALL_INIT_VELOCITY)
, isBird(false)
, map(map_)
{

}

RedBall& RedBall::operator=(const RedBall& a)
{
    position = a.position;
    rotation = a.rotation;
    scale = a.scale;
    color = a.color;
    
    direction = a.direction;
    velocity = a.velocity;
    isBird = a.isBird;

    map = a.map;;

    return *this;
}

RedBall::~RedBall()
{
    
}

void RedBall::update(float deltaTime)
{
    position += *(D3DXVec3Normalize(&direction, &direction)) * velocity * deltaTime;
    
    detectWallCollision();
    decreasingVelocity();
}

void RedBall::decreasingVelocity()
{
    if (velocity >= DECREASING_VELOCITY_OF_RED_BALLS)
        velocity -= DECREASING_VELOCITY_OF_RED_BALLS;
    else if (velocity < DECREASING_VELOCITY_OF_RED_BALLS)
        velocity = 0;
}

void RedBall::detectWallCollision()
{
    std::vector<Skycrapper> skycrapperWithColision;
    if (!Collision::detectBuildings(map, position, (BUILDING_SCALE.x * DIMENSION_OF_UNITBOX) + (BALL_SCALE.x * RADIUS_OF_UNITSPHERE), skycrapperWithColision))
    {
        return;
    }

    for (auto& building : skycrapperWithColision)
    {
        D3DXVECTOR3 buildingPosition = building.getPosition();
        buildingPosition.y = position.y;
        D3DXVECTOR3 whichWall = position - buildingPosition;
        D3DXVec3Normalize(&whichWall, &whichWall);

        const D3DXVECTOR3 startOfCoordinateSystem(1.0f, 0.0f, 0.0f);
        float dotProduct = D3DXVec3Dot(&startOfCoordinateSystem, &whichWall);
        dotProduct = (dotProduct > 1) ? 1 : ((dotProduct < -1) ? -1 : dotProduct); //quickfix TODO: find better solution

        const float angle = acos(dotProduct);

        D3DXVECTOR3 wallDirection;
        if (angle >= (D3DX_PI / 4) && angle < ((D3DX_PI * 3) / 4))
        {
            wallDirection = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
        }
        else if (angle >= ((D3DX_PI * 3) / 4) && angle < ((D3DX_PI * 5) / 4))
        {
            wallDirection = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
        }
        else if (angle >= ((D3DX_PI * 5) / 4) && angle < ((D3DX_PI * 7) / 4))
        {
            wallDirection = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
        }
        else
        {
            wallDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
        }
        D3DXVec3Normalize(&wallDirection, &wallDirection);
        dotProduct = D3DXVec3Dot(&direction, &wallDirection);
        const D3DXVECTOR3 projectedDirectionVector = wallDirection * dotProduct;

        D3DXVECTOR3 newDirectionVector = direction - (2 * projectedDirectionVector);
        direction = newDirectionVector;
    }
}

void RedBall::render(Mesh* mesh)
{
    Render(mesh, position, rotation, scale, color);
}

void RedBall::increaseVelocity(const float unit)
{
    velocity += unit;
}

D3DXVECTOR3 & RedBall::getPosition()
{
    return position;
}

bool RedBall::getIsBird() const
{
    return isBird;
}

void RedBall::setIsBird(bool value)
{
    isBird = value;
}

float RedBall::getVelocity() const
{
    return velocity;
}
