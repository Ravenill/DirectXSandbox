#include "Camera.h"
#include "Defines.h"

Camera::Camera()
: fov(45.0f)
, aspect(1.33f)
, nearPlane(0.1f)
, farPlane(100.0f)
, yaw(0)
, pitch(0)
, maxPitch(D3DXToRadian(89.0f))
, maxVelocityForward(0.5f)
, maxVelocityHorizontal(0.25f)
, velocityForward(0)
, velocityHorizontal(0)
, position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, target(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
, defaultTarget(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
, up(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
, forwardDirection(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rightDirection(D3DXVECTOR3(1.0f, 0.0f, 0.0f))
, defaultRightDirection(D3DXVECTOR3(1.0f, 0.0f, 0.0f))
, centralMousPos(D3DXVECTOR2(SIZE_SCREEN_X / 2, SIZE_SCREEN_Y / 2))
{
    D3DXMatrixIdentity(&viewMatrix);
    setProjectionMatrix();
}

Camera::~Camera()
{

}

void Camera::update()
{
    moveCamera();
    updateView();
}

void Camera::setProjectionMatrix()
{
    float FOV = D3DXToRadian(fov);
    D3DXMatrixPerspectiveFovLH(&projectionMatrix, FOV, aspect, nearPlane, farPlane);
}

void Camera::yawOperation(float radians)
{
    yaw += radians;

    if ((yaw >= (D3DX_PI * 2)) || (yaw <= -(D3DX_PI * 2)))
    {
        yaw = 0;
    }
}

void Camera::pitchOperation(float radians)
{
    pitch += radians;

    if (pitch > maxPitch)
    {
        pitch = maxPitch;
    }
    else if (pitch < -maxPitch)
    {
        pitch = -maxPitch;
    }
}

void Camera::moveForward(float units)
{
    velocityForward += units;

    if (velocityForward > maxVelocityForward)
    {
        velocityForward = maxVelocityForward;
    }
    else if (velocityForward < -maxVelocityForward)
    {
        velocityForward = -maxVelocityForward;
    }
}

void Camera::moveHorizontal(float units)
{
    velocityHorizontal += units;

    if (velocityHorizontal > maxVelocityHorizontal)
    {
        velocityHorizontal = maxVelocityHorizontal;
    }
    else if (velocityHorizontal < -maxVelocityHorizontal)
    {
        velocityHorizontal = -maxVelocityHorizontal;
    }
    
}

void Camera::moveCamera()
{
    D3DXVECTOR2 actualMousePos = GetMousePosition();
    D3DXVECTOR2 diff = actualMousePos - centralMousPos;
    
    if (IsKeyPressed(Key::KEY_W) || IsKeyPressed(Key::KEY_UP))
    {
        moveForward(0.01f);
    }
    if (IsKeyPressed(Key::KEY_A) || IsKeyPressed(Key::KEY_LEFT))
    {
        moveHorizontal(-0.01f);
    }
    if (IsKeyPressed(Key::KEY_D) || IsKeyPressed(Key::KEY_RIGHT))
    {
        moveHorizontal(0.005f);
    }
    if (IsKeyPressed(Key::KEY_S) || IsKeyPressed(Key::KEY_DOWN))
    {
        moveForward(-0.005f);
    }
    
    if (diff.x > 0)
    {
        yawOperation(D3DXToRadian(0.05f * diff.x));
    }
    if (diff.x < 0)
    {
        yawOperation(D3DXToRadian(-0.05f * -diff.x));
    }
    if (diff.y > 0)
    {
        pitchOperation(D3DXToRadian(0.05f * diff.y));
    }
    if (diff.y < 0)
    {
        pitchOperation(D3DXToRadian(-0.05f * -diff.y));
    }
    
    SetCursorPos(SIZE_SCREEN_X / 2, SIZE_SCREEN_Y / 2);
}

void Camera::updateView()
{
    D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0);

    D3DXVec3TransformCoord(&target, &defaultTarget, &rotationMatrix);
    D3DXVec3TransformCoord(&rightDirection, &defaultRightDirection, &rotationMatrix);
    D3DXVec3Normalize(&forwardDirection, &target);

    D3DXVECTOR3 forward = *(D3DXVec3Normalize(&forwardDirection, &forwardDirection)) * velocityForward;
    D3DXVECTOR3 horizontal = *(D3DXVec3Normalize(&rightDirection, &rightDirection)) * velocityHorizontal;
    forward.y = 0;
    horizontal.y = 0; //to be sure :)

    position += forward;
    position += horizontal;

    decreaseVelocity();
    //velocityForward = 0;
    //velocityHorizontal = 0;
    
    target = position + target;

    LookAt(position, target);
}

void Camera::decreaseVelocity()
{
    const float DECREASING_VALUE = 0.025f;
    
    if (velocityForward > 0)
        velocityForward -= DECREASING_VALUE;
    else if (velocityForward < 0)
        velocityForward += DECREASING_VALUE;

    if (velocityForward < DECREASING_VALUE && velocityForward > -DECREASING_VALUE)
        velocityForward = 0;

    if (velocityHorizontal > 0)
        velocityHorizontal -= DECREASING_VALUE;
    else if (velocityHorizontal < 0)
        velocityHorizontal += DECREASING_VALUE;

    if (velocityHorizontal < DECREASING_VALUE && velocityHorizontal > -DECREASING_VALUE)
        velocityHorizontal = 0;
}