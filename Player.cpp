#include "Player.h"

Player::Player(Camera & camera_)
: camera(camera_)
, position(camera_.getPosition())
, directionLook(camera_.getLookDirection())
, direction(camera_.getDirection())
{

}

Player::~Player()
{

}
