#include "CharacterDebugScene.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "Camerah.h"
#include "Collision.h"
#include "DirectInput8.h"
#include "SoundManager.h"
#include "Input.h"
#include "WinMain.h"
#include "PlayerState.h"

CharacterDebugScene::CharacterDebugScene()
{
	mcpImage = new Image;
	mcpWDynamo = new WeakDynamo;
	TestMap = new Map1_1("assets/Stage1/1/MapDate.csv", "assets/Stage1/1/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Stage1/1/MapObjectData.csv");
	TestPlayer = new Player(-1.2f, -0.68f);
	mcpEnemyManager = new EnemyManager("assets/kenjidebug/EnemyData.csv",*TestPlayer,*TestMap);
	fordon = new Fordon();
	//Movei = new DrawMovei(L"assets/Test");
	fordon->CreateMenber(3);
	fordon->SetPlayer(TestPlayer);
	CAMERA->SetFollowWay(true,false);
}

CharacterDebugScene::~CharacterDebugScene()
{
	delete mcpImage;
	delete mcpWDynamo;
	delete TestMap;
	delete TestPlayer;
	delete mcpEnemyManager;

	CAMERA->FollowPlayer(nullptr);
	CAMERA->Reset();
	//ShowCursor(true);
}

void CharacterDebugScene::Update()
{
	CAMERA->FollowPlayer(TestPlayer, 0.4f, 1.0f);
	TestPlayer->Update();
	mcpEnemyManager->Update();
	TestMap->Update();
	//mcpWDynamo->Update();
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_6)) {
		//EffMgr->PlayEffect(DynamoChaege,0,0);
	}

	CollisionUpdate();
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_BACK))	{
		SceneMgr->ChageScene(Scene_Debug, true);
	}

	//fordon->Update();
	mcpEnemyManager->LastUpdate();
	TestPlayer->LastUpdate();
}

void CharacterDebugScene::Draw()
{	
	TestMap->Draw();
	//fordon->Draw();
	TestPlayer->Draw();
//	mcpWDynamo->Draw();
	mcpEnemyManager->Draw();
	float x = -0.9f;
	for (int i = 0; i < TestPlayer->GetHP(); i++) {
		mcpImage->DrawSprite(x,0.9f,0.2f,0.2f,TexMgr->GetTextuer(Tex_UI_HP));
		x += 0.2f;
	}
}

void CharacterDebugScene::CollisionUpdate()
{
	//! “–‚½‚è”»’èˆ—‚ğ‚Q‰ñ‚·‚é‚±‚Æ‚ÅAC³‚µ‚½êŠ‚ª‘¼‚Ìƒ‚ƒm‚Æ‚ß‚è‚ñ‚Å‚¢‚é‚Æ‚¢‚¤ó‹µ‚ğ‹N‚«‚È‚¢‚æ‚¤‚É‚·‚é
	for (int num = 0; num < 2; num++) {

		mcpEnemyManager->CollisionUpdate();

		if (TestMap->CollisionUpdate(TestPlayer)) {
			TestPlayer->SetTouchGround(true);
		}
		else {
			TestPlayer->SetTouchGround(false);
		}

	
	}
}

