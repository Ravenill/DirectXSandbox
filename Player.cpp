#include "Player.h"
#include "Defines.h"
#include "Map.h"

Player::Player(Camera & camera_, Map& map_)
: camera(camera_)
, position(camera_.getPosition())
, direction(camera_.getDirection())
, directionLook(camera_.getLookDirection())
, ballMesh(0)
, map(map_)
{
    redBallList.reserve(MAX_AMOUNT_OF_RED_BALLS);
}

Player::~Player()
{

}

void Player::loadMeshFromFile(char filename[])
{
    ballMesh = LoadFromFile(filename);
}

void Player::update(float deltaTime)
{
    updateRedBalls(deltaTime);
}

void Player::render()
{
    for (auto& ball : redBallList)
    {
        ball.render(ballMesh);
    }
}

void Player::shoot()
{
    if (redBallList.size() >= 5)
    {
        return;
    }

    D3DXVECTOR3 ballPosition = position;
    ballPosition += directionLook;

    RedBall bullet(map, ballPosition, directionLook, BALL_ROTATION, BALL_SCALE, BALL_COLOR);
    redBallList.push_back(bullet);
}

void Player::updateRedBalls(float deltaTime)
{
    for (auto& ball : redBallList)
    {
        ball.update(deltaTime);
    }
}
