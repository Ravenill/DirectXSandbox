#pragma once
#include "CPR_Framework.h"
#include "Camera.h"
#include "RedBall.h"
#include <vector>

class Player
{
public:
    Player(Camera& camera_, Map& map_);
    ~Player();

public:
    void loadMeshFromFile(char filename[]);

    void update(float deltaTick);
    void render();
    void shoot();

    D3DXVECTOR3& getPlayerPosition();
    D3DXVECTOR3& getPlayerLookDir();
    D3DXMATRIX& getPlayerRotationLookDirectionMatrix();

    std::vector<RedBall>& getRedBallList();
    int getScore() const;

private:
    void updateRedBalls(float deltaTime);
    void playerGuard();

private:
    Camera& camera;

    D3DXVECTOR3& position;
    D3DXVECTOR3& direction;
    D3DXVECTOR3& directionLook;

    D3DXMATRIX& rotationLookMatrix;

    Mesh* ballMesh;
    std::vector<RedBall> redBallList;
    Map& map;

    int score;
};

