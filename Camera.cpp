#include "Camera.h"
#include "Defines.h"

Camera::Camera()
: fov(45.0f)
, aspect(1.33f)
, nearPlane(0.1f)
, farPlane(100.0f)
, yaw(0)
, pitch(0)
, maxPitch(D3DXToRadian(80.0f))
, maxVelocityForward(0.5f)
, maxVelocityHorizontal(0.25f)
, velocityForward(0)
, velocityHorizontal(0)
, position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, target(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
, defaultTarget(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
, direction(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, lookDirection(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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

void Camera::update(float deltaTime)
{
    handleSteering(deltaTime);
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

D3DXVECTOR3& Camera::getPosition()
{
    return position;
}

D3DXVECTOR3& Camera::getLookDirection()
{
    return lookDirection;
}

D3DXVECTOR3 & Camera::getDirection()
{
    return direction;
}

void Camera::handleSteering(float deltaTime)
{
    D3DXVECTOR2 actualMousePos = GetMousePosition();
    D3DXVECTOR2 diff = actualMousePos - centralMousPos;
    
    if (IsKeyPressed(Key::KEY_W) || IsKeyPressed(Key::KEY_UP))
    {
        moveForward(CAMERA_SPEED_FORWARD * deltaTime);
    }
    if (IsKeyPressed(Key::KEY_A) || IsKeyPressed(Key::KEY_LEFT))
    {
        moveHorizontal(-CAMERA_SPEED_HORIZONTAL * deltaTime);
    }
    if (IsKeyPressed(Key::KEY_D) || IsKeyPressed(Key::KEY_RIGHT))
    {
        moveHorizontal(CAMERA_SPEED_HORIZONTAL * deltaTime);
    }
    if (IsKeyPressed(Key::KEY_S) || IsKeyPressed(Key::KEY_DOWN))
    {
        moveForward(-CAMERA_SPEED_FORWARD * deltaTime);
    }
    
    if (diff.x > 0)
    {
        yawOperation(D3DXToRadian(CAMERA_SPEED_ROTATION * diff.x));
    }
    if (diff.x < 0)
    {
        yawOperation(D3DXToRadian(-CAMERA_SPEED_ROTATION * -diff.x));
    }
    if (diff.y > 0)
    {
        pitchOperation(D3DXToRadian(CAMERA_SPEED_ROTATION * diff.y));
    }
    if (diff.y < 0)
    {
        pitchOperation(D3DXToRadian(-CAMERA_SPEED_ROTATION * -diff.y));
    }
    
    SetCursorPos(SIZE_SCREEN_X / 2, SIZE_SCREEN_Y / 2);
}

void Camera::updateView()
{
    D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0);

    D3DXVec3TransformCoord(&target, &defaultTarget, &rotationMatrix);
    D3DXVec3TransformCoord(&rightDirection, &defaultRightDirection, &rotationMatrix);
    D3DXVec3Normalize(&lookDirection, &target);

    // feature - slow down, while looking up or down
    D3DXVECTOR3 forward = *(D3DXVec3Normalize(&lookDirection, &lookDirection)) * velocityForward;
    D3DXVECTOR3 horizontal = *(D3DXVec3Normalize(&rightDirection, &rightDirection)) * velocityHorizontal;
    forward.y = 0;
    horizontal.y = 0; //to be sure :)

    position += forward;
    position += horizontal;

    D3DXVec3Normalize(&direction, &forward);

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