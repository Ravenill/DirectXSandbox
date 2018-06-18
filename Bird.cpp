#include "Bird.h"

Bird::Bird(Map& map_)
: position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
, velocityForward(0.0f)
, maxVelocityForward(0.0f)
, yaw(0.0f)
, map(map_)
{
    D3DXVECTOR3 target_ = position;
    target_.z += 1.0f;
    target = target_;
    D3DXVec3Normalize(&desiredDirection, &(target - position));
    D3DXVec3Normalize(&direction, &(target - position));
}

Bird::Bird(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const float maxVelocityForward_, Map& map_)
: position(position_)
, rotation(rotation_)
, scale(scale_)
, color(color_)
, velocityForward(0.0f)
, maxVelocityForward(maxVelocityForward_)
, yaw(0.0f)
, map(map_)
{
    D3DXVECTOR3 target_ = position;
    target_.z += 1.0f;
    setTarget(target_);
    D3DXVec3Normalize(&desiredDirection, &(target - position));
    D3DXVec3Normalize(&direction, &(target - position));
}

Bird::~Bird()
{

}

void Bird::initialize(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const float maxVelocityForward_, const float startVelocityForward)
{
    position = position_;
    rotation = rotation_; //this will be sphere - no need of rotation
    scale = scale_;
    color = color_;

    D3DXVECTOR3 target_ = position;
    target_.x += 30.0f;
    target_.z += 30.0f;
    setTarget(target_);
    D3DXVec3Normalize(&desiredDirection, &(target - position));
    D3DXVec3Normalize(&direction, &(target - position));

    velocityForward = startVelocityForward;
    maxVelocityForward = maxVelocityForward_;

    yaw = 0;
}

void Bird::update()
{
    D3DXVec3Normalize(&direction, &direction);
    D3DXVec3Normalize(&desiredDirection, &desiredDirection);
    
    float dotProduct = D3DXVec3Dot(&direction, &desiredDirection);
    // coz this vectors are normalized
    // float lengthDirection = D3DXVec3Length(&direction);
    // float lengthDesiredDirection = D3DXVec3Length(&desiredDirection);

    // quickfix
    // TODO: Check why dotProduct is too high or too low (because float?)
    if (dotProduct > 1)
    {
        dotProduct = 1.0f;
    }
    else if (dotProduct < -1)
    {
        dotProduct = -1.0f;
    }
    // +++++++++++++++++++++++++++++++++++

    float angle = acosf(dotProduct);
    yaw = angle / 4637;
    
    if (yaw != 0)
    {
        D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, 0, 0);
        D3DXVec3TransformCoord(&direction, &direction, &rotationMatrix);
    }
    
    D3DXVECTOR3 velocity = *(D3DXVec3Normalize(&direction, &direction)) * velocityForward;
    position += velocity;

    if ((rand() % 100) > 95)
    {
        changeSpeed();
    }

    createAvoidingForce();
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
    float changer = static_cast<float>((rand() % 3) - 1);
    changer /= 5000;

    velocityForward += changer;

    if (velocityForward <= 0.004f)
    {
        velocityForward = 0.004f;
    }
    else if (velocityForward > maxVelocityForward)
    {
        velocityForward = maxVelocityForward;
    }
}

void Bird::createAvoidingForce()
{
    const float DETECTING_RANGE = 5.0f;
}

void Bird::changeColor(const D3DXVECTOR4 color_)
{
    color = color_;
}

void Bird::changeSpeed(const float speed)
{
    velocityForward = speed;
}

void Bird::render(Mesh* mesh)
{
    Render(mesh, position, rotation, scale, color);
}

bool Bird::isReachedTarget()
{
    D3DXVECTOR3 diff = target - position;
    float lengthDiff = D3DXVec3Length(&diff);

    if (lengthDiff <= 8.0f)
    {
        return true;
    }

    return false;
}
