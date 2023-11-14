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


//! �R���X�g���N�^
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
		mcpPlayer = new Player(-1.2f, -0.68f);   //! �v���C���[�̐���
		CAMERA->FollowPlayer(mcpPlayer, 0.4f, 1.0f);
		CAMERA->SetFollowWay(true, false);
		mcpMap = new Map1_5("assets/Stage1/5/MapDate.csv", "assets/Stage1/5/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01));
		//! �G�̃}�l�[�W���[�̐���
		mcpEnemyManager = new EnemyManager("assets/Stage1/5/EnemyData.csv", *mcpPlayer, *mcpMap);
		mcpNecthor = new Necthor1_5(13.0f, -0.16f);
		Box01 = new CheackBox(Vector2(13.4f,0.0),Vector2(0.2f,1.6f));
		mcpNecthor->SetPlayer(mcpPlayer);
	}
	BossBattleStart = BossCamera = false;
	PlayBGM = true;
	//! �����ɂ���
	EndDoor = new StageDoor;
	DoorArufa = 0;
	EndDoor->GetAnimSprite()->SetArufa(DoorArufa);
}

//! �f�X�g���N�^
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

//! �X�V����
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
	if (mCheackPoint && !BossCamera)
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
		if (PlayBGM) {
			SoundMgr->PlayBGM(BGM_BossBattle, 0.15f);
		}
		mcpNecthor->BattleStart();
	}

	mcpNecthor->Update();
	mcpEnemyManager->Update();
	//! Map�̍X�V
	mcpMap->Update();

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
		EndingFlg = true;	
	}

	//! �S�[�����o�I����ɃX�e�[�W�I����ʂɖ߂�
	if (EndingFlg) {
		Ending();
	}
}

//! �`�揈��
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

	//! �v���C���[�̐���
	if (mBossCheackPoint) {
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
	mcpNecthor = new Necthor1_5(13.0f + add, -0.16f);
	Box01 = new CheackBox(Vector2(13.4f + add, 0.0), Vector2(0.2f, 1.6f));
	mcpNecthor->SetPlayer(mcpPlayer);
	mcpEnemyManager = new EnemyManager("assets/Stage1/5/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(add);
}

//! �G���f�B���O�̏���
void Stage1_5::Ending()
{
	//! �����o��
	EndDoor->SetVec(Vector2(1.3f, -0.527f));
	EndDoor->Update();
	AnimationSprite * DoorSp = EndDoor->GetAnimSprite();
	if (DoorArufa < 1.0f) {
		DoorArufa += 0.04f;
	}
	DoorSp->SetArufa(DoorArufa);
	
	//! ���ɂ͂�������G���f�B���O�ɍs��
	if (GetControllerButtonTrigger(Button_A)) {
		if (EndDoor->GetHit()) {
			SceneMgr->ChageScene(Scene_Ending, true);
			GameMgr->SetStageClear(eStage::Stage_1_5);
		}
	}
}
