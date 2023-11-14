#pragma once
#include "BaseScene.h"
#include "Map1_3.h"
#include "EnemyManager.h"
#include "ReNecthor.h"
#include "CheackBox.h"

class Stage1_3 :
	public BaseScene
{
public:
	Stage1_3();
	~Stage1_3();

	void Update();
	void Draw();
	void CollisionUpdate();
private:
	//! リスポーン関数(リトライをしたときにステージやプレイヤー、エネミーをリセットする関数)
	void ReSpawn();
	bool BossCamera;  //! ボスようにカメラの位置を固定
	bool BossBattleStart; 
	Player * mcpPlayer;
	Map1_3 * mcpMap;
	ReNecthor * mcpNecthor;
	EnemyManager * mcpEnemyManager;
	CheackBox * Box01;                  //! ネクトールの後ろにおく見えない壁
	//! チュートリアルから始まるか、1-1から始まるか別れるのでそれを判断するフラグが必要
	bool mCheackPoint; //! 中間に触れているかのフラグ
	bool mCheackPointBoss; //! ボス前中間
	bool PlayBGM;  
};

