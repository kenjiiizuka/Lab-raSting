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


//! �R���X�g���N�^
Stage1_2::Stage1_2()
{
	Tag = Scene_1_2;
	if (GameMgr->GetCheackPoint()) {
		ReSpawn();
	}
	else {
		mCheackPoint = false;
		mcpPlayer = new Player(-1.2f, -0.68f);   //! �v���C���[�̐���
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_2("assets/Stage1/2/MapDate.csv", "assets/Stage1/2/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! �G�̃}�l�[�W���[�̐���
		mcpEnemyManager = new EnemyManager("assets/Stage1/2/EnemyData.csv", *mcpPlayer, *mcpMap);	
	}
	PlayBGM = true;
}

//! �f�X�g���N�^
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

//! �X�V����
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


	//! �|�[�Y��ʂւ̑J��
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Pause, false, false ,true);
	}

	//! �����V�[���ւ̑J��
	if (mcpPlayer->GetAlive() == false) {
		SceneMgr->ChageScene(Scene_Lose, false, false, true);
	}
	
	//! �v���C���[�̍X�V
	if (mcpPlayer->GetAlive()) {
		mcpPlayer->Update();
	}

	//!�v���C���[��HP��0�ɂȂ�����BGM�Đ�����߂�
	if (mcpPlayer->GetHP() == 0) { 
		PlayBGM = false; 
		SoundMgr->StopBGM();
	}

	mcpEnemyManager->Update();

	//! Map�̍X�V
	mcpMap->Update();

	//! �����蔻�菈��
	CollisionUpdate();

	//! �����蔻�菈����̍X�V����
	mcpPlayer->LastUpdate();
	mcpEnemyManager->LastUpdate();

	//! ���Ԓn�_�ɂ𒴂������̃Q�b�^�[
	//! �M�~�b�N�}�l�[�W���[
	GimmickManager * Gimmicks = mcpMap->GetGimmickManager();

	//! ���Ԓn�_�ɂ𒴂������̃Q�b�^�[
	mCheackPoint = Gimmicks->GetCheackPointState();
	//! �S�[�����o���n�܂�����BGM���~�߂�
	if (Gimmicks->GetGoalIns()->GetHit()) {
		PlayBGM = false;
		SoundMgr->StopBGM();
	}

	if (Gimmicks->GetGoal()) {
		//! �N���A�V�[���ɂ����@���͉��ɃX�e�[�W�I����ʂɂ���
		SceneMgr->ChageScene(Scene_StageSelect, true);
		GameMgr->SetStageClear(eStage::Stage_1_2);
	}

}

//! �`�揈��
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
	//CAMERA->Reset(); //! �J�����̃��Z�b�g
	////! �G�l�~�[�A�v���C���[�̓f���[�g���čēx��������
	//delete mcpPlayer;
	//delete mcpEnemyManager;

	mcpMap = new Map1_2("assets/Stage1/2/MapDate.csv", "assets/Stage1/2/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
	
	//! �v���C���[�̐���	
	Vector2 pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	float add = -0.4f - pos.x;
	mcpMap->AddX(add);
	pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	mcpPlayer = new Player(pos.x, pos.y);   //! �v���C���[�̐���
				
	mcpEnemyManager = new EnemyManager("assets/Stage1/2/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
}
