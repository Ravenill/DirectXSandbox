#include "BirdFlock.h"
#include "Defines.h"

BirdFlock::BirdFlock(const int amountOfBirds, const float height, Map& map_, std::vector<RedBall>& redBallList_)
: map(map_)
, heightOfFlight(height)
, redBallList(redBallList_)
{
    birds.reserve(amountOfBirds);
    
    for (int i = 0; i < amountOfBirds; i++)
    {
        Bird newBird(map);
        birds.push_back(newBird);
    }
}

BirdFlock::~BirdFlock()
{

}

void BirdFlock::initializeFlock(const D3DXVECTOR3 startingPosition)
{  
    const float SPACE = 2.0f;

    int modifier = -1;
    for (auto& bird : birds)
    {
        D3DXVECTOR3 position = startingPosition;
        int birdNumber = (&bird - &*(birds.begin())) + 1;
        int diff = birdNumber / 2;

        position.x += (diff * SPACE * modifier);
        position.z += (diff * SPACE);
        bird.initialize(position, BIRD_ROTATION, BIRD_SCALE, BIRD_COLOR, MAX_BIRD_SPEED, INITIAL_BIRD_SPEED);
        modifier = -modifier;
    }
    changeFlockTarget();
}

void BirdFlock::updateFlock(float deltaTime)
{
    for (auto& bird : birds)
    {
        bird.update(deltaTime);
    }

    for (auto& bird : birds)
    {
        if (bird.isReachedTarget())
        {
            changeFlockTarget();
        }
    }

    checkCollisionWithRedBalls();
    avoidOtherBirds();
    addNewBird();
}

void BirdFlock::changeFlockTarget()
{
    float x = static_cast<float>((rand() % (static_cast<int>(SIZE_OF_GROUND_X) + 20)) - (SIZE_OF_GROUND_X / 2));
    float z = static_cast<float>((rand() % (static_cast<int>(SIZE_OF_GROUND_Z) + 20)) - (SIZE_OF_GROUND_Z / 2));

    const D3DXVECTOR3 NEW_TARGET(x, heightOfFlight, z);
    flockTarget = NEW_TARGET;

    for (auto& bird : birds)
    {
        bird.setTarget(NEW_TARGET);
    }
}

void BirdFlock::renderFlock(Mesh* mesh)
{
    for (auto& bird : birds)
    {
        bird.render(mesh);
    }
}

void BirdFlock::checkCollisionWithRedBalls()
{
    if (redBallList.empty())
    {
        return;
    }

    int birdNumber = -1;

    for (auto& bird : birds)
    {
        for (auto& ball : redBallList)
        {
            const D3DXVECTOR3 DISTANCE_VECTOR = ball.getPosition() - bird.getPosition();
            const float DISTANCE = D3DXVec3Length(&DISTANCE_VECTOR);

            if (DISTANCE <= (BIRD_SCALE.y / 2 + BALL_SCALE.y / 2))
            {
                birdNumber = (&bird - &*(birds.begin()));
                ball.increaseVelocity(INCREASE_VELOCITY_OF_RED_BALLS);
                ball.setIsBird(true);
            }
        }
    }

    if (birdNumber != -1)
    {
        birds.erase(birds.begin() + birdNumber);
    }
}

void BirdFlock::avoidOtherBirds()
{
    //other flock will be placed on other heights
    for (auto& bird1 : birds)
    {
        for (auto& bird2 : birds)
        {
            if (bird1 == bird2)
            {
                continue;
            }

            D3DXVECTOR3 distanceVec = bird1.getPosition() - bird2.getPosition();
            const float DISTANCE = D3DXVec3Length(&distanceVec);

            if (DISTANCE <= (BIRD_SCALE.x * RADIUS_OF_UNITSPHERE) * 3)
            {
                const float FORCE = 1 / (DISTANCE * 75);
                bird1.getPosition() += *(D3DXVec3Normalize(&distanceVec, &distanceVec)) * FORCE;
            }
        }
    }
}

void BirdFlock::addNewBird()
{
    if (redBallList.empty())
    {
        return;
    }
    
    int ballNumber = -1;

    for (auto& ball : redBallList)
    {
        if ((ball.getVelocity() <= DECREASING_VELOCITY_OF_RED_BALLS) && ball.getIsBird() == true)
        {
            Bird newBird(map);
            D3DXVECTOR3 position = ball.getPosition();

            position.y = heightOfFlight;
            newBird.initialize(position, BIRD_ROTATION, BIRD_SCALE, BIRD_COLOR, MAX_BIRD_SPEED, INITIAL_BIRD_SPEED);

            birds.push_back(newBird);

            ballNumber = (&ball - &*(redBallList.begin()));
        }
    }

    if (ballNumber != -1)
    {
        redBallList.erase(redBallList.begin() + ballNumber);
    }
}
