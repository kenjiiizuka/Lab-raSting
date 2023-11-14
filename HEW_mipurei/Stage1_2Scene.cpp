#include "Stage1_2Scene.h"
#include "TextureManager.h"
#include "Camerah.h"
#include "Controller.h"
#include "Collision.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "EffectManager.h"
#include "EnemyID.h"
#include <fstream>
#include <string>
#include <sstream>
#include "WinMain.h"
#include "GameManager.h"


//! コンストラクタ
Stage1_2::Stage1_2()
{
	Tag = Scene_1_2;
	if (GameMgr->GetCheackPoint()) {
		ReSpawn();
	}
	else {
		mCheackPoint = false;
		mcpPlayer = new Player(-1.2f, -0.68f);   //! プレイヤーの生成
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_2("assets/Stage1/2/MapDate.csv", "assets/Stage1/2/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! 敵のマネージャーの生成
		mcpEnemyManager = new EnemyManager("assets/Stage1/2/EnemyData.csv", *mcpPlayer, *mcpMap);	
	}
	PlayBGM = true;
}

//! デストラクタ
Stage1_2::~Stage1_2()
{
	delete mcpPlayer;
	delete mcpMap;
	delete mcpEnemyManager;
	CAMERA->Reset();
	GameMgr->SetCheackPoint(mCheackPoint);
	SoundMgr->StopBGM();
	EffMgr->Reset();
}

//! 更新処理
void Stage1_2::Update()
{
	GameMgr->SetNowPlayerStage(Scene_1_2);

	if (PlayBGM) {
		SoundMgr->PlayBGM(BGM_Hanyou, 0.08f);
	}

	
	if (mcpPlayer->GetVec().x > -0.1f) {
		CAMERA->FollowPlayer(mcpPlayer, 0.1f, 1.0f);
		CAMERA->SetFollowWay(true, false);
	}


	//! ポーズ画面への遷移
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Pause, false, false ,true);
	}

	//! 負けシーンへの遷移
	if (mcpPlayer->GetAlive() == false) {
		SceneMgr->ChageScene(Scene_Lose, false, false, true);
	}
	
	//! プレイヤーの更新
	if (mcpPlayer->GetAlive()) {
		mcpPlayer->Update();
	}

	//!プレイヤーのHPが0になったらBGM再生をやめる
	if (mcpPlayer->GetHP() == 0) { 
		PlayBGM = false; 
		SoundMgr->StopBGM();
	}

	mcpEnemyManager->Update();

	//! Mapの更新
	mcpMap->Update();

	//! 当たり判定処理
	CollisionUpdate();

	//! 当たり判定処理後の更新処理
	mcpPlayer->LastUpdate();
	mcpEnemyManager->LastUpdate();

	//! 中間地点にを超えたかのゲッター
	//! ギミックマネージャー
	GimmickManager * Gimmicks = mcpMap->GetGimmickManager();

	//! 中間地点にを超えたかのゲッター
	mCheackPoint = Gimmicks->GetCheackPointState();
	//! ゴール演出が始まったらBGMを止める
	if (Gimmicks->GetGoalIns()->GetHit()) {
		PlayBGM = false;
		SoundMgr->StopBGM();
	}

	if (Gimmicks->GetGoal()) {
		//! クリアシーンにいく　今は仮にステージ選択画面にいく
		SceneMgr->ChageScene(Scene_StageSelect, true);
		GameMgr->SetStageClear(eStage::Stage_1_2);
	}

}

//! 描画処理
void Stage1_2::Draw()
{
	mcpMap->Draw();
	mcpPlayer->Draw();
	mcpEnemyManager->Draw();
}

void Stage1_2::CollisionUpdate()
{
	for (int num = 0; num < 2; num++) {
		mcpEnemyManager->CollisionUpdate();
		if ((mcpMap->CollisionUpdate(mcpPlayer))) {
			mcpPlayer->SetTouchGround(true);
		}
		else {
			mcpPlayer->SetTouchGround(false);
		}
	}
}

void Stage1_2::ReSpawn()
{
	//CAMERA->Reset(); //! カメラのリセット
	////! エネミー、プレイヤーはデリートして再度生成する
	//delete mcpPlayer;
	//delete mcpEnemyManager;

	mcpMap = new Map1_2("assets/Stage1/2/MapDate.csv", "assets/Stage1/2/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
	
	//! プレイヤーの生成	
	Vector2 pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	float add = -0.4f - pos.x;
	mcpMap->AddX(add);
	pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	mcpPlayer = new Player(pos.x, pos.y);   //! プレイヤーの生成
				
	mcpEnemyManager = new EnemyManager("assets/Stage1/2/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
}
