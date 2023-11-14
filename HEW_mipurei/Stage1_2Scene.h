#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map1_2.h"

class Stage1_2 :
	public BaseScene
{
public:
	Stage1_2();
	~Stage1_2();

	void Update();
	void Draw();
	void CollisionUpdate();
private:
	//! リスポーン関数(リトライをしたときにステージやプレイヤー、エネミーをリセットする関数)
	void ReSpawn();

	Player * mcpPlayer;
	Map1_2 * mcpMap;
	EnemyManager * mcpEnemyManager;
	
	bool mCheackPoint; //! 中間に触れているかのフラグ
	bool PlayBGM;     
};

