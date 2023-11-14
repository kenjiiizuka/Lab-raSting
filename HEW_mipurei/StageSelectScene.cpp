#include "StageSelectScene.h"
#include "TextureManager.h"
#include "Camerah.h"
#include "SceneManager.h"
#include "Controller.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

StageSelectScene::StageSelectScene()
{
	Tag = Scene_StageSelect;	
	mcpMap = new StageSelectMap_1("assets/StageSelectScene/StageSelectMap.csv", "", TexMgr->GetTextuer(Tex_MapTip01));

	//! プレイしていたステージを取得
	OldStage = GameMgr->GetNowStage();
	Vector2 PlayerPos;
	float Add = 0;
	if (OldStage == Scene_1_1) {
		PlayerPos = mcpMap->GetDoorPos(1);
		PlayerPos.x = -0.8f;
	}
	else if(OldStage == Scene_1_2){
		PlayerPos = mcpMap->GetDoorPos(2);
		PlayerPos.x = 0.3f;

	}
	else if (OldStage == Scene_1_3) {
		PlayerPos = mcpMap->GetDoorPos(3);
		Add = -0.4f - PlayerPos.x;
		mcpMap->AddX(Add);
		PlayerPos.x = -0.4f;
	}
	else if (OldStage == Scene_1_4) {
		PlayerPos = mcpMap->GetDoorPos(4);
		Add = 0.3f - PlayerPos.x;
		mcpMap->AddX(Add);
		PlayerPos.x = 0.3f;
	}
	else if (OldStage == Scene_1_5) {
		PlayerPos = mcpMap->GetDoorPos(5);
		Add = 0.8f - PlayerPos.x;
		mcpMap->AddX(Add);
		PlayerPos.x = 0.8f;
	}
	else {
		PlayerPos = mcpMap->GetDoorPos(1);
	}
	
	mcpPlayer = new Player(PlayerPos.x , -0.7f);
	mcpPlayer->SetUIActiv(false);
	CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
	CAMERA->SetFollowWay(true, false);
}

StageSelectScene::~StageSelectScene()
{	
	delete mcpPlayer;
	delete mcpMap;
	CAMERA->FollowPlayer(nullptr);
	CAMERA->Reset();
	EffMgr->Reset();
	SoundMgr->StopBGM();
}

void StageSelectScene::Update()
{
	SoundMgr->PlayBGM(BGM_SelectScene, 0.08f);
	//! 中間をリセットする
	GameMgr->SetBossCheackPoint(false);
	GameMgr->SetCheackPoint(false);
	GameMgr->SetNowPlayerStage(Scene_StageSelect);

	mcpMap->Update();
	mcpPlayer->Update();
	//! ポーズ画面への遷移
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Pause, false, false, true);
	}
	//! Mapとの当たり判定
	if (mcpMap->CollisionUpdate(mcpPlayer)) {
		mcpPlayer->SetTouchGround(true);
	}
	else {
		mcpPlayer->SetTouchGround(false);
	}
}

void StageSelectScene::Draw()
{
	mcpMap->Draw();
	mcpPlayer->Draw();
}

