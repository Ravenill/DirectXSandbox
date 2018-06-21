#include "CrosshairPrimitive.h"
#include "Defines.h"

CrosshairPrimitive::CrosshairPrimitive(Player& player_)
: mesh(nullptr)
, position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, playerPosition(player_.getPlayerPosition())
, playerLookDirection(player_.getPlayerLookDir())
, rotationLookDirMatrix(player_.getPlayerRotationLookDirectionMatrix())
{
    
}

CrosshairPrimitive::~CrosshairPrimitive()
{
    Release(mesh);
}

void CrosshairPrimitive::init()
{
    mesh = LoadFromFile("resources/meshes/unitsphere.x");
}

void CrosshairPrimitive::update()
{
    const float HOW_FAR = 1.0f;
    const D3DXVECTOR3 forward(0.0f, 0.0f, 1.0f);

    position = playerPosition;
    position += (playerLookDirection * HOW_FAR);
}

void CrosshairPrimitive::render()
{
    Render(mesh, position, rotation, CROSSHAIR_SCALE, CROSSHAIR_COLOR);
}
