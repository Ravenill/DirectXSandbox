#include "Bird.h"

Bird::Bird()
: position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
, velocityForward(0.0f)
, maxVelocityForward(0.0f)
{
    D3DXVECTOR3 target_ = position;
    target_.z += 1.0f;
    target = target_;
    D3DXVec3Normalize(&desiredDirection, &(target - position));
    D3DXVec3Normalize(&direction, &(target - position));
}

Bird::Bird(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const float maxVelocityForward_)
: position(position_)
, rotation(rotation_)
, scale(scale_)
, color(color_)
, velocityForward(0.0f)
, maxVelocityForward(maxVelocityForward_)
{
    D3DXVECTOR3 target_ = position;
    target_.z += 1.0f;
    setTarget(target_);
    D3DXVec3Normalize(&direction, &(target - position));
}

Bird::~Bird()
{

}

void Bird::update()
{
    float dotProduct = D3DXVec3Dot(&direction, &desiredDirection);
    float lengthDirection = D3DXVec3Length(&direction);
    float lengthDesiredDirection = D3DXVec3Length(&desiredDirection);

    float angle = acosf(dotProduct / (lengthDirection * lengthDesiredDirection));
    yaw = angle / 10;

    D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, 0, 0);
    D3DXVec3TransformCoord(&direction, &direction, &rotationMatrix);

    D3DXVECTOR3 velocity = *(D3DXVec3Normalize(&direction, &direction)) * velocityForward;
    position += velocity;

    if ((rand() % 9) > 6)
    {
        changeSpeed();
    }

    updateDesiredDirection();
}

void Bird::setTarget(D3DXVECTOR3 target_)
{
    target = target_;
    updateDesiredDirection();
}

void Bird::updateDesiredDirection()
{
    D3DXVec3Normalize(&desiredDirection, &(target - position));
}

void Bird::changeSpeed()
{
    float changer = (rand() % 3) - 1;
    changer /= 50;

    velocityForward += changer;

    if (velocityForward <= 0)
    {
        velocityForward = 0.1;
    }
    else if (velocityForward > maxVelocityForward)
    {
        velocityForward = maxVelocityForward;
    }
}

void Bird::changeColor(const D3DXVECTOR4 color_)
{

}

void Bird::changeSpeed(const float speed)
{
    velocityForward = speed;
}

void Bird::render()
{

}
