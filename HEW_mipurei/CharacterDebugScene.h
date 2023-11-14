#pragma once
#include "BaseScene.h"
#include "Map1_1.h"
#include "Player.h"
#include "EnemyManager.h"
#include "BreakObj.h"
#include "WeakDynamo.h"
#include "Fordon.h"
#include "PressMachine.h"
#include "DrawMovei.h"
#define MaxChar 10


class CharacterDebugScene :
	public BaseScene
{
public:
	CharacterDebugScene();
	~CharacterDebugScene();

	void Update();
	void Draw();
private:
	void CollisionUpdate();

	DrawMovei * Movei;
	BreakObj * mcpBreakObj;
	Map1_1 * TestMap;
	Player * TestPlayer;
	EnemyManager * mcpEnemyManager; //! エネミーマネージャー
	WeakDynamo * mcpWDynamo;
	Fordon * fordon;
	
};