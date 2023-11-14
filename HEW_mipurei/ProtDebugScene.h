#pragma once
#include "BaseScene.h"
#include "Map1_1.h"
#include "Player.h"
#include "Enemy.h"

#define MaxChar 10

class ProtDebugScene :
	public BaseScene
{
public:
	ProtDebugScene();
	~ProtDebugScene();

	void Update();
	void Draw();
private:
	void CollisionUpdate();

	EnemyProt * TestEnemy[9];
	Map1_1 * TestMap;
	Player * TestPlayer;


	Character * Chara[MaxChar];
};

