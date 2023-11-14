#pragma once

#include "Map1_1.h"
#include "Player.h"
#include "BaseScene.h"
#include "EnemyManager.h"
#include "BaseDrone.h"

#define MaxChar 10

class AoiScene :
	public BaseScene
{

public:
	AoiScene();
	~AoiScene();
	void Update();
	void Draw();
private:
	void CollisionUpdate();
	NormalEnemy * testEnemy;
	Map1_1 * TestMap;
	Player * TestPlayer;
	EnemyManager * mcpEnemyManager; //! エネミーマネージャー
	BaseDrone * testDrone;

};

