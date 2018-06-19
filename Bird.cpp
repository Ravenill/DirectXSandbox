#include "Bird.h"
#include "Defines.h"

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
    target_.z += 1.0f;
    setTarget(target_);
    D3DXVec3Normalize(&desiredDirection, &(target - position));
    D3DXVec3Normalize(&direction, &(target - position));

    velocityForward = startVelocityForward;
    maxVelocityForward = maxVelocityForward_;

    yaw = 0;
}

void Bird::update(float deltaTime)
{
    D3DXVec3Normalize(&direction, &direction);
    D3DXVec3Normalize(&desiredDirection, &desiredDirection);
    
    float dotProduct = D3DXVec3Dot(&direction, &desiredDirection);
    // coz this vectors are normalized
    // float lengthDirection = D3DXVec3Length(&direction);
    // float lengthDesiredDirection = D3DXVec3Length(&desiredDirection);

    // quickfix
    // TODO: Check why dotProduct is too high or too low (because float?)
    dotProduct = (dotProduct > 1) ? 1 : ((dotProduct < -1) ? -1 : dotProduct);
    // +++++++++++++++++++++++++++++++++++

    float angle = acosf(dotProduct);
    yaw = angle / 4637;
    
    if (yaw != 0)
    {
        D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, 0, 0);
        D3DXVec3TransformCoord(&direction, &direction, &rotationMatrix);
    }
    
    D3DXVECTOR3 velocity = *(D3DXVec3Normalize(&direction, &direction)) * velocityForward * deltaTime;
    position += velocity;

    if ((rand() % 100) > 95)
    {
        changeSpeed();
    }

    addAvoidingForce();
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
    changer = (changer * (MAX_BIRD_SPEED - MIN_BIRD_SPEED)) / AMOUNT_OF_BIRDS_SPEED;

    velocityForward += changer;

    if (velocityForward <= MIN_BIRD_SPEED)
    {
        velocityForward = MIN_BIRD_SPEED;
    }
    else if (velocityForward > maxVelocityForward)
    {
        velocityForward = maxVelocityForward;
    }
}

void Bird::addAvoidingForce()
{
    const float MAX_SEE_AHEAD = 6.0f;
    std::vector<Skycrapper> nearSkycrappers;
    
    addNearestBuildingTo(nearSkycrappers);
    
    const D3DXVECTOR3 ORIGINAL_POSITION = position;
    const D3DXVECTOR3 HEAD_VECTOR = position + (*(D3DXVec3Normalize(&direction, &direction)) * MAX_SEE_AHEAD);
    for (auto& building : nearSkycrappers)
    {       
        D3DXVECTOR3 buildingPosition = building.getPosition();
        buildingPosition.y = position.y;

        D3DXVECTOR3 avoidingForce = HEAD_VECTOR - buildingPosition;
        D3DXVec3Normalize(&avoidingForce, &avoidingForce);

        const float force = 1 / (D3DXVec3Length(&(buildingPosition - position)) * 75);

        //more push
        D3DXVECTOR3 crossProduct;
        D3DXVec3Cross(&crossProduct, &avoidingForce, &HEAD_VECTOR);
        const float lengthCrossProduct = D3DXVec3Length(&crossProduct);
        float angle = asin(lengthCrossProduct);
        angle = (angle > 1) ? 1 : ((angle < -1) ? -1 : angle); //to be sure - like quickfix in update

        if ((angle > -0.1 && angle < 0.1) || (angle > ((D3DX_PI * 2) - 0.1) && angle < ((D3DX_PI * 2) + 0.1)))
        {
            avoidingForce.x += 0.15f;
        }

        avoidingForce = *(D3DXVec3Normalize(&avoidingForce, &avoidingForce)) * force; 
        position += avoidingForce;
    }
}

void Bird::addNearestBuildingTo(std::vector<Skycrapper>& nearSkycrappers)
{
    const float DETECTING_RANGE = 8.0f;

    const int ROWS = map.getNumberOfRows();
    const int COLUMNS = map.getNumberOfColumns();
    
    for (int row = 0; row < ROWS; row++)
    {
        const D3DXVECTOR3& POSITION_OF_BUILDING = map[row][0].getPosition();

        if ((POSITION_OF_BUILDING.x >= (position.x - DETECTING_RANGE)) && (POSITION_OF_BUILDING.x <= (position.x + DETECTING_RANGE)))
        {
            for (int column = 0; column < COLUMNS; column++)
            {
                const D3DXVECTOR3& POSITION_OF_NEXT_BUILDING = map[row][column].getPosition();

                if ((POSITION_OF_NEXT_BUILDING.z >= (position.z - DETECTING_RANGE)) && (POSITION_OF_NEXT_BUILDING.z <= (position.z + DETECTING_RANGE)))
                {
                    const float HEIGHT_OF_BUILDING = BUILDING_SCALE.y * map[row][column].getHeight();

                    if (position.y <= HEIGHT_OF_BUILDING)
                    {
                        nearSkycrappers.push_back(map[row][column]);
                    }
                }
            }
        }
    }
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

    if (lengthDiff <= 10.0f)
    {
        return true;
    }

    return false;
}
