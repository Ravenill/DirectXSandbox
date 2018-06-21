#include "Player.h"
#include "Defines.h"
#include "Map.h"

Player::Player(Camera & camera_, Map& map_)
: camera(camera_)
, position(camera_.getPosition())
, direction(camera_.getDirection())
, directionLook(camera_.getLookDirection())
, rotationLookMatrix(camera_.getRotationMatrix())
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
    if (redBallList.size() >= MAX_AMOUNT_OF_RED_BALLS)
    {
        return;
    }

    D3DXVECTOR3 ballPosition = position;
    ballPosition += directionLook;

    RedBall bullet(map, ballPosition, directionLook, BALL_ROTATION, BALL_SCALE, BALL_COLOR);
    redBallList.push_back(bullet);
}

D3DXVECTOR3 & Player::getPlayerPosition()
{
    return position;
}

D3DXVECTOR3 & Player::getPlayerLookDir()
{
    return directionLook;
}

D3DXMATRIX & Player::getPlayerRotationLookDirectionMatrix()
{
    return rotationLookMatrix;
}

std::vector<RedBall>& Player::getRedBallList()
{
    return redBallList;
}

void Player::updateRedBalls(float deltaTime)
{
    for (auto& ball : redBallList)
    {
        ball.update(deltaTime);
    }

    const int RED_BALL_LIST_SIZE = redBallList.size();
    for (int i = RED_BALL_LIST_SIZE - 1; i >= 0; i--)
    {
        if (redBallList[i].getVelocity() < DECREASING_VELOCITY_OF_RED_BALLS)
        {
            redBallList.erase(redBallList.begin() + i);
        }
    }
}
