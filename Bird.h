#pragma once
#include "CPR_Framework.h"
#include "Map.h"

class Bird
{
public:
    Bird(Map & map_);
    Bird(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const float maxVelocityForward, Map& map_);
    ~Bird();

public:
    void initialize(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const float maxVelocityForward, const float startVelocityForward);

    void update();
    void setTarget(D3DXVECTOR3 target_);
    void changeColor(const D3DXVECTOR4 color_);
    void changeSpeed(const float speed);

    void render(Mesh* mesh);

    bool isReachedTarget();

private:
    void updateDesiredDirection();
    void changeSpeed();
    void createAvoidingForce();

private:
    D3DXVECTOR3 position;
    D3DXVECTOR3 rotation;
    D3DXVECTOR3 scale;
    D3DXVECTOR4 color;

    D3DXVECTOR3 target;
    D3DXVECTOR3 desiredDirection;

    D3DXVECTOR3 direction;
    D3DXMATRIX rotationMatrix;

    float velocityForward;
    float maxVelocityForward;

    float yaw;

    Map& map;
};
