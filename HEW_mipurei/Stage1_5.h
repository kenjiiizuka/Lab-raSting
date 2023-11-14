#pragma once
#include "BaseScene.h"
#include "Map1_5.h"
#include "EnemyManager.h"
#include "Necthor1_5.h"
#include "StageDoor.h"
#include "CheackBox.h"

class Stage1_5 :
	public BaseScene
{
public:
	Stage1_5();
	~Stage1_5();

	void Update();
	void Draw();

private:
	void CollisionUpdate();
	void ReSpawn();
	void Ending(); //! エンディングようの処理　扉が出てくる
	bool mBossBgmStart;

	EnemyManager * mcpEnemyManager;
	Map1_5 * mcpMap;
	Player * mcpPlayer;
	Necthor1_5 * mcpNecthor;
	CheackBox *  Box01;
	StageDoor * EndDoor;
	float DoorArufa;

	bool mCheackPoint; //! 中間に触れているかのフラグ
	bool mBossCheackPoint;
	bool BossCamera;  //! ボスようにカメラの位置を固定
	bool BossBattleStart;
	bool EndingFlg = false;
	bool PlayBGM;
};

