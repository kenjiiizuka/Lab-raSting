#include "Stage_1_3.h"
#include "TextureManager.h"
#include "Camerah.h"
#include "Controller.h"
#include "Collision.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "EnemyID.h"
#include <fstream>
#include <string>
#include <sstream>
#include "GameManager.h"
#include "WinMain.h"


//! コンストラクタ
Stage1_3::Stage1_3()
{
	Tag = Scene_1_3;
	if (GameMgr->GetBossCheackPoint()) {
		mCheackPointBoss = true;
		ReSpawn();
	}

	else if (GameMgr->GetCheackPoint()) {
		mCheackPoint = true;
		ReSpawn();
	}
	else {
		mCheackPoint = false;
		mCheackPointBoss = false;
		mcpPlayer = new Player(-1.2f, -0.68f);   //! プレイヤーの生成
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_3("assets/Stage1/3/MapDate.csv", "assets/Stage1/3/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! 敵のマネージャーの生成
		mcpEnemyManager = new EnemyManager("assets/Stage1/3/EnemyData.csv", *mcpPlayer, *mcpMap);
		mcpNecthor = new ReNecthor(33.0f, -0.16);
		Box01 = new CheackBox(Vector2(33.3f,0.0f),Vector2(0.2f,1.0f));
		mcpNecthor->SetPlayer(mcpPlayer);
	}
	BossBattleStart = BossCamera = false;
	PlayBGM = true;
}

//! デストラクタ
Stage1_3::~Stage1_3()
{
	delete mcpPlayer;
	delete mcpMap;
	delete mcpEnemyManager;
	delete mcpNecthor;
	delete Box01;
	CAMERA->Reset();
	GameMgr->SetCheackPoint(mCheackPoint);
	GameMgr->SetBossCheackPoint(mCheackPointBoss);
	EffMgr->Reset();	
	SoundMgr->StopBGM();
}

//! 更新処理
void Stage1_3::Update()
{
	if (!mCheackPointBoss && PlayBGM)
	{
		SoundMgr->PlayBGM(BGM_1_3, 0.045f);
	}
	GameMgr->SetNowPlayerStage(Scene_1_3);


	if (mcpPlayer->GetVec().x > -0.1f && !BossCamera) {
		CAMERA->FollowPlayer(mcpPlayer, 0.1f, 1.0f);
		CAMERA->SetFollowWay(true, false);
	}

	//! 負けシーンへの遷移
	if (mcpPlayer->GetAlive() == false) {
		SceneMgr->ChageScene(Scene_Lose, false, false, true);
	}

	//! ポーズ画面への遷移
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Pause, false, false, true);
	}

	//! プレイヤーの更新
	if (mcpPlayer->GetAlive()) {	
		mcpPlayer->Update();	
	}

	if (mcpPlayer->GetHP() == 0) {
		PlayBGM = false;
		SoundMgr->StopBGM();
	}
	//! プレイヤーとボスの距離を図る
	float BossToPlayer = fabs(mcpPlayer->GetVec().x - mcpNecthor->GetVec().x);
	if (mCheackPointBoss && !BossCamera)
	{
		SoundMgr->StopBGM();
	}

	//! ある程度ちかくなったらカメラを移動させる
	if (BossToPlayer < 1.85f && !BossCamera) {
		BossCamera = true;
		CAMERA->FollowPlayer(nullptr, 0.0f, 0.0f);
	}
	if (BossCamera) {
		if (CAMERA->GetRightMove()) {
			CAMERA->MoveCamera(Vector2(-0.01f, 0));
		}
		else {
			BossBattleStart = true;
		}
	}
	//! カメラの移動が完了したらボスを動かす
	if (BossBattleStart) {
		mcpNecthor->BattleStart();
		if (PlayBGM) {
			SoundMgr->PlayBGM(BGM_BossBattle, 0.15f);
		}	
	}
	
	mcpNecthor->Update();	
	mcpEnemyManager->Update();	
	mcpMap->Update();                //! Mapの更新

	//! 当たり判定処理
	CollisionUpdate();

	//! 当たり判定処理後の更新処理
	mcpPlayer->LastUpdate();
	mcpEnemyManager->LastUpdate();
	mcpNecthor->LastUpdate();

	//! 中間地点にを超えたかのゲッター
	//! ギミックマネージャー
	GimmickManager * Gimmicks = mcpMap->GetGimmickManager();

	//! 中間地点にを超えたかのゲッター
	mCheackPoint = Gimmicks->GetCheackPointState();

	if (mcpNecthor->GetDestroyed()) {		
		GameMgr->SetStageClear(eStage::Stage_1_3);
		Gimmicks->GetGoalIns()->SetGoaled(true);       //! ゴールしたことある
	}

	//! ゴール演出が始まったらBGMを止める
	if (Gimmicks->GetGoalIns()->GetHit()) {
		PlayBGM = false;
		SoundMgr->StopBGM();
	}

	if (Gimmicks->GetGoal()) { 
		SceneMgr->ChageScene(Scene_StageSelect, true);
	}
	mCheackPointBoss = mcpMap->GetGimmickManager()->GetCheackPointBossState();
}

//! 描画処理
void Stage1_3::Draw()
{
	mcpMap->Draw();
	mcpNecthor->Draw();
	mcpPlayer->Draw();
	mcpEnemyManager->Draw();
	Box01->Draw();
}

void Stage1_3::CollisionUpdate()
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

	mcpNecthor->CollisionUpdate();	

	//! ボス戦が始まったら画面外にいけないようする
	Vector2 PlayerPos = mcpPlayer->GetVec();
	if (BossCamera) {
		if (PlayerPos.x <= -1.8f) {
			mcpPlayer->SetVec(Vector2(-1.79f,PlayerPos.y));
		}
	}
	Box01->Collision(mcpPlayer);
	
}

void Stage1_3::ReSpawn()
{
	mcpMap = new Map1_3("assets/Stage1/3/MapDate.csv", "assets/Stage1/3/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));	
	Vector2 CheackPos;
	float add;
	//! プレイヤーの生成
	if (mCheackPointBoss) {
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointBossPos();
		add = -0.4f - CheackPos.x; //! 中間地点とプレイヤーの画面上の初期位置との差分を計算する
		//! 差分だけMapをずらす
		mcpMap->AddX(add);
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointBossPos();
		mcpPlayer = new Player(CheackPos.x, CheackPos.y);   //! プレイヤーの生成

	}
	else if (mCheackPoint) {
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointPos();
		add = -0.4f - CheackPos.x; //! 中間地点とプレイヤーの画面上の初期位置との差分を計算する
		//! 差分だけMapをずらす
		mcpMap->AddX(add);
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointPos();
		mcpPlayer = new Player(CheackPos.x, CheackPos.y);   //! プレイヤーの生成
	}
	
	mcpEnemyManager = new EnemyManager("assets/Stage1/3/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
	mcpNecthor = new ReNecthor(33 + add, -0.16);
	Box01 = new CheackBox(Vector2(33.3f + add, 0.0f), Vector2(0.2f, 1.0f));
	mcpNecthor->SetPlayer(mcpPlayer);

}