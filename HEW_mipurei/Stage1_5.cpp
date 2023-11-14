#include "Stage1_5.h"
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
#include "Collision.h"
#include "GameManager.h"


//! コンストラクタ
Stage1_5::Stage1_5()
{
	Tag = Scene_1_5;
	if (GameMgr->GetBossCheackPoint()) {
		mBossCheackPoint = true;
		ReSpawn();
	}
	else if (GameMgr->GetCheackPoint()) {
		mCheackPoint = true;
		ReSpawn();
	}
	else {
		mBossCheackPoint = mCheackPoint = false;
		mBossBgmStart = false;
		mcpPlayer = new Player(-1.2f, -0.68f);   //! プレイヤーの生成
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_5("assets/Stage1/5/MapDate.csv", "assets/Stage1/5/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! 敵のマネージャーの生成
		mcpEnemyManager = new EnemyManager("assets/Stage1/5/EnemyData.csv", *mcpPlayer, *mcpMap);
		mcpNecthor = new Necthor1_5(13.0f, -0.16f);
		Box01 = new CheackBox(Vector2(13.4f,0.0),Vector2(0.2f,1.6f));
		mcpNecthor->SetPlayer(mcpPlayer);
	}
	BossBattleStart = BossCamera = false;
	PlayBGM = true;
	//! 透明にする
	EndDoor = new StageDoor;
	DoorArufa = 0;
	EndDoor->GetAnimSprite()->SetArufa(DoorArufa);
}

//! デストラクタ
Stage1_5::~Stage1_5()
{
	delete mcpPlayer;
	delete mcpMap;
	delete mcpEnemyManager;
	delete Box01;
	CAMERA->Reset();
	GameMgr->SetCheackPoint(mCheackPoint);
	GameMgr->SetBossCheackPoint(mBossCheackPoint);
	SoundMgr->StopBGM();
	EffMgr->Reset();
}

//! 更新処理
void Stage1_5::Update()
{
	if (!mCheackPoint && PlayBGM)	{
		SoundMgr->PlayBGM(BGM_1_5, 0.15f);
	}
	GameMgr->SetNowPlayerStage(Scene_1_5);

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
	if (mCheackPoint && !BossCamera)
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
		if (PlayBGM) {
			SoundMgr->PlayBGM(BGM_BossBattle, 0.15f);
		}
		mcpNecthor->BattleStart();
	}

	mcpNecthor->Update();
	mcpEnemyManager->Update();
	//! Mapの更新
	mcpMap->Update();

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
		EndingFlg = true;	
	}

	//! ゴール演出終了後にステージ選択画面に戻る
	if (EndingFlg) {
		Ending();
	}
}

//! 描画処理
void Stage1_5::Draw()
{
	mcpMap->Draw();
	mcpNecthor->Draw();
	EndDoor->Draw();
	mcpPlayer->Draw();
	mcpEnemyManager->Draw();
	Box01->Draw();
}

void Stage1_5::CollisionUpdate()
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

	if (EndingFlg) {
		if (BBH(*mcpPlayer->GetBoxCol(), *EndDoor->GetBoxCol())) {
			EndDoor->SetHit(true);
		}
		else {
			EndDoor->SetHit(false);
		}
	}
	Box01->Collision(mcpPlayer);
}

void Stage1_5::ReSpawn()
{
	mcpMap = new Map1_5("assets/Stage1/5/MapDate.csv", "assets/Stage1/5/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));

	Vector2 CheackPos;
	float add;

	//! プレイヤーの生成
	if (mBossCheackPoint) {
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
	mcpNecthor = new Necthor1_5(13.0f + add, -0.16f);
	Box01 = new CheackBox(Vector2(13.4f + add, 0.0), Vector2(0.2f, 1.6f));
	mcpNecthor->SetPlayer(mcpPlayer);
	mcpEnemyManager = new EnemyManager("assets/Stage1/5/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
}

//! エンディングの処理
void Stage1_5::Ending()
{
	//! 扉を出す
	EndDoor->SetVec(Vector2(1.3f, -0.527f));
	EndDoor->Update();
	AnimationSprite * DoorSp = EndDoor->GetAnimSprite();
	if (DoorArufa < 1.0f) {
		DoorArufa += 0.04f;
	}
	DoorSp->SetArufa(DoorArufa);
	
	//! 扉にはいったらエンディングに行く
	if (GetControllerButtonTrigger(Button_A)) {
		if (EndDoor->GetHit()) {
			SceneMgr->ChageScene(Scene_Ending, true);
			GameMgr->SetStageClear(eStage::Stage_1_5);
		}
	}
}
