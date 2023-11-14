#include "AoiScene.h"
#include "Collision.h"
#include "HitStop.h"
#include "TextureManager.h"


//! コンストラクタ
AoiScene::AoiScene()
{
	TestMap = new Map1_1("assets/Stage1/1/MapDate.csv", "assets/Stage1/1/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Stage1/1/MapObjectData.csv");
	TestPlayer = new Player(-1.2f, -0.68f);
	mcpEnemyManager = new EnemyManager("assets/AoiEnemyData.csv", *TestPlayer, *TestMap);
	//testDEnemy = new SplitLowerEnemy(0.8f, 0.6f);
	//! testEnemy = new NormalEnemy(1.3f, 0.6f);
	//! testDrone = new BaseDrone(1.3f, 0.9f);
	//! testDrone->SetEnemy(testEnemy);
}

//! デストラクタ
AoiScene::~AoiScene()
{
	//! デリート
	delete TestMap;
	delete TestPlayer;
	delete mcpEnemyManager;
	//! delete testDrone;
	//! delete testEnemy;
}

//! 更新処理
void AoiScene::Update()
{
	

	TestPlayer->Update();
	mcpEnemyManager->Update();
	
	TestMap->Update();

	CollisionUpdate();

	mcpEnemyManager->LastUpdate();
}

//! 描画処理
void AoiScene::Draw()
{
	//! エネミーの描画処理
	TestMap->Draw();

	TestPlayer->Draw();
	mcpEnemyManager->Draw();

}

void AoiScene::CollisionUpdate()
{
	//! 当たり判定処理を２回することで、修正した場所が他のモノとめり込んでいるという状況を起きないようにする
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
