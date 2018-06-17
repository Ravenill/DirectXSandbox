#pragma once
#include "CPR_Framework.h"

class Camera
{
public:
    Camera();
    ~Camera();

public:
    void update();

    void yawOperation(float radians);
    void pitchOperation(float radians);
    void moveForward(float units);
    void moveHorizontal(float units);

private:
    void setProjectionMatrix();
    void moveCamera();
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
    D3DXVECTOR3 up;

    D3DXVECTOR3 forwardDirection;
    D3DXVECTOR3 rightDirection;
    const D3DXVECTOR3 defaultRightDirection;

    D3DXMATRIX viewMatrix;
    D3DXMATRIX projectionMatrix;
    D3DXMATRIX rotationMatrix;

    D3DXVECTOR2 centralMousPos;
};

