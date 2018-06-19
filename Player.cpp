#include "Player.h"
#include "Defines.h"

Player::Player(Camera & camera_)
: camera(camera_)
, position(camera_.getPosition())
, directionLook(camera_.getLookDirection())
, direction(camera_.getDirection())
{
    redBallList.reserve(MAX_AMOUNT_OF_RED_BALLS);
}

Player::~Player()
{

}

void Player::update(float deltaTime)
{
    updateRedBalls();
}

void Player::shoot()
{

}

void Player::updateRedBalls()
{
}
