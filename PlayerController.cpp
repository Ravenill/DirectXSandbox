#include "PlayerController.h"
#include "Defines.h"

PlayerController::PlayerController()
: camera()
, player(camera)
{

}


PlayerController::~PlayerController()
{

}

void PlayerController::update(float deltaTime)
{
    handleSteering(deltaTime);
    camera.update(deltaTime);
    player.update(deltaTime);
}

void PlayerController::handleSteering(float deltaTime)
{
    D3DXVECTOR2 actualMousePos = GetMousePosition();
    D3DXVECTOR2 diff = actualMousePos - centralMousPos;

    if (IsKeyPressed(Key::KEY_W) || IsKeyPressed(Key::KEY_UP))
    {
        camera.moveForward(CAMERA_SPEED_FORWARD * deltaTime);
    }
    if (IsKeyPressed(Key::KEY_A) || IsKeyPressed(Key::KEY_LEFT))
    {
        camera.moveHorizontal(-CAMERA_SPEED_HORIZONTAL * deltaTime);
    }
    if (IsKeyPressed(Key::KEY_D) || IsKeyPressed(Key::KEY_RIGHT))
    {
        camera.moveHorizontal(CAMERA_SPEED_HORIZONTAL * deltaTime);
    }
    if (IsKeyPressed(Key::KEY_S) || IsKeyPressed(Key::KEY_DOWN))
    {
        camera.moveForward(-CAMERA_SPEED_FORWARD * deltaTime);
    }

    if (diff.x > 0)
    {
        camera.yawOperation(D3DXToRadian(CAMERA_SPEED_ROTATION * diff.x));
    }
    if (diff.x < 0)
    {
        camera.yawOperation(D3DXToRadian(-CAMERA_SPEED_ROTATION * -diff.x));
    }
    if (diff.y > 0)
    {
        camera.pitchOperation(D3DXToRadian(CAMERA_SPEED_ROTATION * diff.y));
    }
    if (diff.y < 0)
    {
        camera.pitchOperation(D3DXToRadian(-CAMERA_SPEED_ROTATION * -diff.y));
    }

    SetCursorPos(SIZE_SCREEN_X / 2, SIZE_SCREEN_Y / 2);

    if (LeftMouseButton())
    {
        player.shoot();
    }
}
