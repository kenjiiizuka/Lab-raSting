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


//! �R���X�g���N�^
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
		mcpPlayer = new Player(-1.2f, -0.68f);   //! �v���C���[�̐���
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_3("assets/Stage1/3/MapDate.csv", "assets/Stage1/3/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! �G�̃}�l�[�W���[�̐���
		mcpEnemyManager = new EnemyManager("assets/Stage1/3/EnemyData.csv", *mcpPlayer, *mcpMap);
		mcpNecthor = new ReNecthor(33.0f, -0.16);
		Box01 = new CheackBox(Vector2(33.3f,0.0f),Vector2(0.2f,1.0f));
		mcpNecthor->SetPlayer(mcpPlayer);
	}
	BossBattleStart = BossCamera = false;
	PlayBGM = true;
}

//! �f�X�g���N�^
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

//! �X�V����
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
		PlayBGM = false;
		SoundMgr->StopBGM();
	}
	//! �v���C���[�ƃ{�X�̋�����}��
	float BossToPlayer = fabs(mcpPlayer->GetVec().x - mcpNecthor->GetVec().x);
	if (mCheackPointBoss && !BossCamera)
	{
		SoundMgr->StopBGM();
	}

	//! ������x�������Ȃ�����J�������ړ�������
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
	//! �J�����̈ړ�������������{�X�𓮂���
	if (BossBattleStart) {
		mcpNecthor->BattleStart();
		if (PlayBGM) {
			SoundMgr->PlayBGM(BGM_BossBattle, 0.15f);
		}	
	}
	
	mcpNecthor->Update();	
	mcpEnemyManager->Update();	
	mcpMap->Update();                //! Map�̍X�V

	//! �����蔻�菈��
	CollisionUpdate();

	//! �����蔻�菈����̍X�V����
	mcpPlayer->LastUpdate();
	mcpEnemyManager->LastUpdate();
	mcpNecthor->LastUpdate();

	//! ���Ԓn�_�ɂ𒴂������̃Q�b�^�[
	//! �M�~�b�N�}�l�[�W���[
	GimmickManager * Gimmicks = mcpMap->GetGimmickManager();

	//! ���Ԓn�_�ɂ𒴂������̃Q�b�^�[
	mCheackPoint = Gimmicks->GetCheackPointState();

	if (mcpNecthor->GetDestroyed()) {		
		GameMgr->SetStageClear(eStage::Stage_1_3);
		Gimmicks->GetGoalIns()->SetGoaled(true);       //! �S�[���������Ƃ���
	}

	//! �S�[�����o���n�܂�����BGM���~�߂�
	if (Gimmicks->GetGoalIns()->GetHit()) {
		PlayBGM = false;
		SoundMgr->StopBGM();
	}

	if (Gimmicks->GetGoal()) { 
		SceneMgr->ChageScene(Scene_StageSelect, true);
	}
	mCheackPointBoss = mcpMap->GetGimmickManager()->GetCheackPointBossState();
}

//! �`�揈��
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

	//! �{�X�킪�n�܂������ʊO�ɂ����Ȃ��悤����
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
	//! �v���C���[�̐���
	if (mCheackPointBoss) {
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointBossPos();
		add = -0.4f - CheackPos.x; //! ���Ԓn�_�ƃv���C���[�̉�ʏ�̏����ʒu�Ƃ̍������v�Z����
		//! ��������Map�����炷
		mcpMap->AddX(add);
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointBossPos();
		mcpPlayer = new Player(CheackPos.x, CheackPos.y);   //! �v���C���[�̐���

	}
	else if (mCheackPoint) {
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointPos();
		add = -0.4f - CheackPos.x; //! ���Ԓn�_�ƃv���C���[�̉�ʏ�̏����ʒu�Ƃ̍������v�Z����
		//! ��������Map�����炷
		mcpMap->AddX(add);
		CheackPos = mcpMap->GetGimmickManager()->GetCheackPointPos();
		mcpPlayer = new Player(CheackPos.x, CheackPos.y);   //! �v���C���[�̐���
	}
	
	mcpEnemyManager = new EnemyManager("assets/Stage1/3/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
	mcpNecthor = new ReNecthor(33 + add, -0.16);
	Box01 = new CheackBox(Vector2(33.3f + add, 0.0f), Vector2(0.2f, 1.0f));
	mcpNecthor->SetPlayer(mcpPlayer);

}