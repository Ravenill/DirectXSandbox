#pragma once
#include "CPR_Framework.h"

class Camera
{
public:
    Camera();
    ~Camera();

public:
    void update(float deltaTime);

    void yawOperation(float radians);
    void pitchOperation(float radians);
    void moveForward(float units);
    void moveHorizontal(float units);

    D3DXVECTOR3& getPosition();
    D3DXVECTOR3& getLookDirection();
    D3DXVECTOR3& getDirection();
    D3DXMATRIX& getRotationMatrix();

private:
    void setProjectionMatrix();
    void updateView();
    void decreaseVelocity();

private:
    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

    float yaw;
    float pitch;
    float maxPitch;
    float maxVelocityForward;
    float maxVelocityHorizontal;

    float velocityForward;
    float velocityHorizontal;

    D3DXVECTOR3 position;
    D3DXVECTOR3 target;
    const D3DXVECTOR3 defaultTarget;

    D3DXVECTOR3 direction;
    D3DXVECTOR3 lookDirection;
    D3DXVECTOR3 rightDirection;
    const D3DXVECTOR3 defaultRightDirection;

    D3DXMATRIX viewMatrix;
    D3DXMATRIX projectionMatrix;
    D3DXMATRIX rotationMatrix;
};

