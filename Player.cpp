#include "Player.h"
#include "Defines.h"
#include "Map.h"
#include "Collision.h"

Player::Player(Camera & camera_, Map& map_)
: camera(camera_)
, position(camera_.getPosition())
, direction(camera_.getDirection())
, directionLook(camera_.getLookDirection())
, rotationLookMatrix(camera_.getRotationMatrix())
, ballMesh(nullptr)
, map(map_)
, score(0)
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

#ifndef __DEBUG
    playerGuard();
#endif // __DEBUG
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

int Player::getScore() const
{
    return score;
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
        if (redBallList[i].getVelocity() < DECREASING_VELOCITY_OF_RED_BALLS && redBallList[i].getIsBird() == true)
        {
            score++;
        }
        
        if (redBallList[i].getVelocity() < DECREASING_VELOCITY_OF_RED_BALLS && redBallList[i].getIsBird() == false)
        {
            redBallList.erase(redBallList.begin() + i);
        }
    }
}

void Player::playerGuard()
{
    //quickfix
    const float MODIFIER = 0.9f;
    const float DIMENSION = (BUILDING_SCALE.x * DIMENSION_OF_UNITBOX) / MODIFIER;

    std::vector<Skycrapper> skycrapperWithColision;
    if (!Collision::detectBuildings(map, position, (BUILDING_SCALE.x * DIMENSION_OF_UNITBOX ) / MODIFIER, skycrapperWithColision))
    {
        return;
    }

    for (auto& building : skycrapperWithColision)
    {
        const float WZ = DIMENSION * (building.getPosition().z - position.z);
        const float HX = DIMENSION * (building.getPosition().x - position.x);

        if (WZ > HX)
        {
            if (WZ > -HX)
            {
                position.z = (building.getPosition().z) - DIMENSION;
            }
            else
            {
                position.x = (building.getPosition().x) + DIMENSION;
            }
        }
        else
        {
            if (WZ > -HX)
            {
                position.x = (building.getPosition().x) - DIMENSION;
            }
               
            else
            {
                position.z = (building.getPosition().z) + DIMENSION;
            }
        }      
    }
}
