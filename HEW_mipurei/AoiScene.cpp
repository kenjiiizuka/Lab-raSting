#include "AoiScene.h"
#include "Collision.h"
#include "HitStop.h"
#include "TextureManager.h"


//! �R���X�g���N�^
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

//! �f�X�g���N�^
AoiScene::~AoiScene()
{
	//! �f���[�g
	delete TestMap;
	delete TestPlayer;
	delete mcpEnemyManager;
	//! delete testDrone;
	//! delete testEnemy;
}

//! �X�V����
void AoiScene::Update()
{
	

	TestPlayer->Update();
	mcpEnemyManager->Update();
	
	TestMap->Update();

	CollisionUpdate();

	mcpEnemyManager->LastUpdate();
}

//! �`�揈��
void AoiScene::Draw()
{
	//! �G�l�~�[�̕`�揈��
	TestMap->Draw();

	TestPlayer->Draw();
	mcpEnemyManager->Draw();

}

void AoiScene::CollisionUpdate()
{
	//! �����蔻�菈�����Q�񂷂邱�ƂŁA�C�������ꏊ�����̃��m�Ƃ߂荞��ł���Ƃ����󋵂��N���Ȃ��悤�ɂ���
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
