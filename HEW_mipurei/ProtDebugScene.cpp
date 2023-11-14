#include "ProtDebugScene.h"
#include "TextureManager.h"
#include "Camerah.h"
#include "Collision.h"
#include "SceneManager.h"
#include "DirectInput8.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "Camerah.h"

//! コンストラクタ
ProtDebugScene::ProtDebugScene()
{
	TestMap = new Map1_1("assets/Map/Map1/1/MapDate.csv","assets/Map/Map1/1/ItemDate.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Map/Map1/1/MapObjectData.csv");
	TestPlayer = new Player(-0.8f,-0.5f);
	Chara[0] = TestPlayer;
	
	TestEnemy[0] = new EnemyProt(-0.3f, -0.55f);	
	TestEnemy[1] = new EnemyProt(1.3f, 0.0f);
	TestEnemy[2] = new EnemyProt(1.6f, 0.3f);	
	TestEnemy[3] = new EnemyProt(1.3f, 0.6f);	
	TestEnemy[4] = new EnemyProt(2.0f, 0.0f);	
	TestEnemy[5] = new EnemyProt(0.6f, 0.65f);	
	TestEnemy[6] = new EnemyProt(0.6f, 0.85f);	
	TestEnemy[7] = new EnemyProt(1.6f, 0.35f);	
	TestEnemy[8] = new EnemyProt(1.3f, 0.0f);
	
	for (int num = 1; num < MaxChar; num ++) {
		Chara[num] = TestEnemy[num - 1];
	}

	ShowCursor(false);
	CAMERA->FollowPlayer(TestPlayer, 0.9f, 0.9f);
}

//! デストラクタ
ProtDebugScene::~ProtDebugScene()
{
	delete TestMap;
	delete TestPlayer;
	for (int num = 0; num < 9; num++) {
		delete TestEnemy[num];
	}

	CAMERA->FollowPlayer(nullptr);
	ShowCursor(true);
}


//! 更新処理
void ProtDebugScene::Update()
{	
	//! キャラクターのアップデート
	for (int num = 0; num < MaxChar; num++) {
		Chara[num]->Update();
	}
	//TestPlayer->Update();
	TestMap->Update();

	CollisionUpdate();	
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_BACK))
	{
		SceneMgr->ChageScene(Scene_Debug,true);
	}	
	for (int num = 0; num < MaxChar; num++) {
		Chara[num]->LastUpdate();
	}
}


//! 描画処理
void ProtDebugScene::Draw()
{
	TestMap->Draw();
	//TestPlayer->Draw();
	for (int num = 0; num < MaxChar; num++) {
		Chara[num]->Draw();
	}
}

void ProtDebugScene::CollisionUpdate()
{
	//! Mapとの当たり判定
	for (int num = 0; num < 2; num++) {
		if (TestMap->CollisionUpdate(Chara[num])) {
			Chara[num]->SetTouchGround(true);
		}
		else {
			Chara[num]->SetTouchGround(false);
		}
	}
	
	//! 攻撃の当たり判定処理
	//! 攻撃が発生しているか
	if (TestPlayer->GetAttackFlg() == true) {
		for (int num = 0; num < 9; num ++) {
			if (Collision::Point_Box_Hit(*TestPlayer->GetAttackCol(), *TestEnemy[num]->GetBoxCol())) {
				TestEnemy[num]->SetDrawActiv(false);
				TestEnemy[num]->SetHitActiv(false);
			//	SoundMgr->PlaySE(SE_Sasu01);
				//EffMgr->PlayEffect(HitEffect, TestPlayer->GetAttackCol().GetVec().x, TestPlayer->GetAttackCol().GetVec().y);

			}
		}
	}
}
