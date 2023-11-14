#pragma once
#include "BaseScene.h"
#include "Map1_1.h"
#include "Player.h"
#include "EnemyManager.h"
#include "DrawMovei.h"
#include "CheackBox.h"
#include "BreakObj.h"
#include "BigDoor.h"
#include "Dynamo.h"

//! 1-1シーンです

class Stage1_1 :
	public BaseScene
{
public:
	Stage1_1();
	~Stage1_1();

	void Update();
	void Draw();
	void CollisionUpdate();
private:
	//! リスポーン関数(リトライをしたときにステージやプレイヤー、エネミーをリセットする関数)
	void ReSpawn();
	bool ThoutrialMovie;
	Player * mcpPlayer;
	Map1_1 * mcpMap;
	EnemyManager * mcpEnemyManager;

	//! チュートリアルに必要なもの
	CheackBox * Cheak01;
	CheackBox * Cheak02;
	CheackBox * Cheak03;	
	DrawMovei * Movei01; //! チュートリアルムービー
	DrawMovei * Movei02; //! チュートリアルムービー
	DrawMovei * Movei03; //! チュートリアルムービー
	NormalEnemy * Timpiller01;
	BreakObj * Glass01;
	Dynamo * Dynamo01;
	BigDoor * Door01;


	//! 成功音用のフラグ
	bool Glass_Success = true;
	bool Timpiller_Succes = true;
	bool Dynamo_Success = true;

	//! チュートリアルから始まるか、1-1から始まるか別れるのでそれを判断するフラグが必要
	bool mCheackPoint; //! 中間に触れているかのフラグ
	bool OnCamera;
	bool PlayBGM;

};

