#include "Stage1_4.h"
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
Stage1_4::Stage1_4()
{
	Tag = Scene_1_4;
	if (GameMgr->GetCheackPoint()) {
		ReSpawn();
	}
	else{
		mCheackPoint = false;
		mcpPlayer = new Player(-1.2f, -0.68f);   //! �v���C���[�̐���
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_4("assets/Stage1/4/MapDate.csv", "assets/Stage1/4/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! �G�̃}�l�[�W���[�̐���
		mcpEnemyManager = new EnemyManager("assets/Stage1/4/EnemyData.csv", *mcpPlayer, *mcpMap);
	}
	PlayBGM = true;
}

//! �f�X�g���N�^
Stage1_4::~Stage1_4()
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
void Stage1_4::Update()
{
	if (PlayBGM) {
		SoundMgr->PlayBGM(BGM_Hanyou, 0.08f);
	}
	GameMgr->SetNowPlayerStage(Scene_1_4);

	if (mcpPlayer->GetVec().x > -0.1f) {
		CAMERA->FollowPlayer(mcpPlayer, 0.1f, 1.0f);
		CAMERA->SetFollowWay(true, false);
	}

	//! �����V�[���ւ̑J��
	if (mcpPlayer->GetAlive() == false) {
		SceneMgr->ChageScene(Scene_Lose, false, false, true);
	}

	//! �|�[�Y��ʂւ̑J��
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Pause, false, false, true);
	}

	//! �v���C���[�̍X�V
	if (mcpPlayer->GetAlive()) {
		mcpPlayer->Update();
	}

	if (mcpPlayer->GetHP() == 0) {
		SoundMgr->StopBGM();
		PlayBGM = false;
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
		GameMgr->SetStageClear(eStage::Stage_1_4);
	}
}

//! �`�揈��
void Stage1_4::Draw()
{
	mcpMap->Draw();
	mcpPlayer->Draw();
	mcpEnemyManager->Draw();

}

void Stage1_4::CollisionUpdate()
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

void Stage1_4::ReSpawn()
{
	mcpMap = new Map1_4("assets/Stage1/4/MapDate.csv", "assets/Stage1/4/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));

	//! �v���C���[�̐���	
	Vector2 pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	float add = -0.4f - pos.x;
	mcpMap->AddX(add);
	pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	mcpPlayer = new Player(pos.x, pos.y);   //! �v���C���[�̐���

	mcpEnemyManager = new EnemyManager("assets/Stage1/4/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
}
