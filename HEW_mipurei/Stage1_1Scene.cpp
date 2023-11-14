#include "Stage1_1Scene.h"
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
#include "WinMain.h"
#include "GameManager.h"

using namespace std;

//! �R���X�g���N�^
Stage1_1::Stage1_1()
{
	

	Tag = Scene_1_1;
	if (GameMgr->GetCheackPoint()) {
		ReSpawn();
		ThoutrialMovie = false;
	}
	else {
		OnCamera = false;
		mCheackPoint = false;
		mcpPlayer = new Player(-1.2f, -0.68f);   //! �v���C���[�̐���

		mcpMap = new Map1_1("assets/Stage1/1/MapDate.csv", "assets/Stage1/1/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Stage1/1/MapObjectData.csv");
		//! �G�̃}�l�[�W���[�̐���
		mcpEnemyManager = new EnemyManager("assets/Stage1/1/EnemyData.csv", *mcpPlayer, *mcpMap);	

		Glass01 = new BreakObj;
		Dynamo01 = new Dynamo;
		Door01 = new BigDoor;
		Timpiller01 = new NormalEnemy;
		Timpiller01->SetVec(Vector2(3.0f, -0.67f));
		Timpiller01->SetPlayer(mcpPlayer);
		Glass01->SetVec(Vector2(-0.02f, -0.5f));
		Dynamo01->SetVec(Vector2(8.4f,-0.67f));
		Door01->SetVec(Vector2(8.96f,-0.3f));
		Door01->SetDynamo(Dynamo01);
		//! �`���[�g���A���ł͂Ȃ�������X�e�[�W�̊J�n�n�_�����炷
		if (!GameMgr->GetThutrial()) {
			mcpMap->AddX(-10.8f);
			mcpEnemyManager->AddX(-10.8f);
			Timpiller01->SetVec(Vector2(3.0f -10.8f, -0.67f));
			Glass01->SetVec(Vector2(-0.02f - 10.8f, -0.5f));
			Dynamo01->SetVec(Vector2(8.4f -10.8f, -0.67f));
			Door01->SetVec(Vector2(8.96f - 10.8f, -0.3f));
			ThoutrialMovie = false;
		}
		else {
			ThoutrialMovie = true;
			Movei01 = new DrawMovei(L"assets/tutorial_movie/tutorial_movie ",222,Vector2(1.4f,1.0f));
			Movei02 = new DrawMovei(L"assets/tutorial_movie2/tutorial_movie2 ",194, Vector2(1.4f, 1.0f));
			Movei03 = new DrawMovei(L"assets/tutorial_movie3/tutorial_movie3 ",147,Vector2(1.4f,1.0f));
			//! ����Đ��ʒu�𒲂ׂ邽�߂̓����蔻��I�u�W�F�N�g
			Cheak01 = new CheackBox(Vector2(-0.7f, -0.7f), Vector2(0.2f, 0.2f));
			Cheak02 = new CheackBox(Vector2(1.2f, -0.7f), Vector2(0.2f, 0.2f));
			Cheak03 = new CheackBox(Vector2(7.8f, -0.7f), Vector2(0.2f, 0.2f));
		}
	}

	PlayBGM = true;
}

//! �f�X�g���N�^
Stage1_1::~Stage1_1()
{		
	delete mcpPlayer;
	delete mcpEnemyManager;
	delete mcpMap;
	delete Glass01;
	delete Dynamo01;
	delete Door01;
	delete Timpiller01;
	
	//! �`���[�g���A���𗬂����Ƃ��̂�
	if (ThoutrialMovie) {
		delete Movei01;
		delete Movei02;
		delete Movei03;
		delete Cheak01;
		delete Cheak02;
		delete Cheak03;
	}
	GameMgr->SetCheackPoint(mCheackPoint);
	if (mCheackPoint) {
		GameMgr->SetThutrial(false);
	}
	CAMERA->Reset();
	SoundMgr->StopBGM();
	EffMgr->Reset();
	
}

/* -----------
// �X�V���� */
void Stage1_1::Update()
{
	GameMgr->SetNowPlayerStage(Scene_1_1);
	//! �ŏ��Ƀ`���[�g���A���̎��ŋ�������
	if (ThoutrialMovie) {	
		if (Cheak01->HitCheack(mcpPlayer)) {
			Movei01->StartMovei(4, Vector2(-0.4f, 0.3f));
		}

		if (Cheak02->HitCheack(mcpPlayer)) {
			Movei02->StartMovei(4, Vector2(0.8f, 0.3f));
		}
	
		if (Cheak03->HitCheack(mcpPlayer)) {
			Movei03->StartMovei(4,Vector2(0.8f,0.3f));
		}
		Movei01->Update();
		Movei02->Update();
		Movei03->Update();
	}

	if (PlayBGM) {
		SoundMgr->PlayBGM(BGM_Hanyou, 0.08f);
	}
	if (mcpPlayer->GetVec().x > -0.1f) {
		CAMERA->FollowPlayer(mcpPlayer, 0.1f, 1.0f);
		CAMERA->SetFollowWay(true, false);
	}

	//! �|�[�Y��ʂւ̑J��
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Pause, false, false, true);
	}

	//! �����V�[���ւ̑J��
	if (mcpPlayer->GetAlive() == false) {
		SceneMgr->ChageScene(Scene_Lose, false, false, true);
	}

	//! �v���C���[��HP���O�ɂȂ�����BGM���~�߂�
	if (mcpPlayer->GetHP() == 0) {
		SoundMgr->StopBGM();
		PlayBGM = false;
	}

	//! �v���C���[�̍X�V
	if (mcpPlayer->GetAlive()) {
		mcpPlayer->Update();
	}

	mcpEnemyManager->Update();

	//! Map�̍X�V
	mcpMap->Update();

	//! �����蔻�菈��
	CollisionUpdate();

	//! �����蔻�菈����̍X�V����
	mcpPlayer->LastUpdate();
	mcpEnemyManager->LastUpdate();

	//! �M�~�b�N�}�l�[�W���[
	GimmickManager * Gimmicks = mcpMap->GetGimmickManager();

	//! ���Ԓn�_�ɂ𒴂������̃Q�b�^�[
	mCheackPoint = Gimmicks->GetCheackPointState();
	if (Gimmicks->GetGoalIns()->GetHit()) {
		PlayBGM = false;
		SoundMgr->StopBGM();
		//! 1-1���N���A������`���[�g���A�����v���C�������Ƃɂ���
		GameMgr->PlayedThoutrial();
	}

	if (Gimmicks->GetGoal()) {
		//! �N���A�V�[���ɂ����@���͉��ɃX�e�[�W�I����ʂɂ���
		SceneMgr->ChageScene(Scene_StageSelect,true);
		GameMgr->SetStageClear(eStage::Stage_1_1);
	}

	Glass01->Update();
	Timpiller01->Update();
	Dynamo01->Update();
	Door01->Update();
	//! �K���X����ꂽ�Ƃ��̐�����
	if (Glass01->GetBreaked() && Glass_Success) {
		Glass_Success = false;
		SoundMgr->PlaySE(SE_Success, 0.5f);
	}
	if (Timpiller01->GetDeath() && Timpiller_Succes) {
		mcpPlayer->AddElect();
		Timpiller_Succes = false;
		SoundMgr->PlaySE(SE_Success,0.5f);
	}
	if (Dynamo01->GetChargeState() && Dynamo_Success) {
		Dynamo_Success = false;
		SoundMgr->PlaySE(SE_Success, 0.5f);
	}

}

/* -----------
// �`�揈�� */
void Stage1_1::Draw()
{
	mcpMap->Draw();	
	Dynamo01->Draw();
	mcpPlayer->Draw();
	mcpEnemyManager->Draw();
	Glass01->Draw();
	Timpiller01->Draw();
	Door01->Draw();
	if (ThoutrialMovie) {
		Movei01->Draw();
		Movei02->Draw();
		Movei03->Draw();
		Cheak01->Draw();
		Cheak02->Draw();
		Cheak03->Draw();
	}
	
}


/* ------------------
// �����蔻��̏���*/
void Stage1_1::CollisionUpdate()
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

	//! �`���[�g���A���Ɏg���I�u�W�F�N�g�ɂ�������Փ˔���
	BBC(*mcpPlayer->GetBoxCol(), *Glass01->GetBoxCol());
	BBC(*Timpiller01->GetBoxCol(), *mcpPlayer->GetBoxCol());
	BBC(*mcpPlayer->GetBoxCol(), *Door01->GetBoxCol());

	float StingPower = mcpPlayer->GetStingPower(); //! �v���C���[�̎h���͂̎擾
	TailReaction Reaction = TailReaction::TailReaction_None; 
	//! �����ۂƂ̓�����̔���
	if (Collision::Box_Circle_Hit(*Glass01->GetBoxCol() ,*mcpPlayer->GetAttackCol())) {
		Reaction = Glass01->ReturnReaction(StingPower);
		mcpPlayer->SetReaction(Reaction,Left);
	}
	if (Collision::Box_Circle_Hit(*Timpiller01->GetBoxCol(), *mcpPlayer->GetAttackCol())) {
		Reaction = Timpiller01->SetStingPower(StingPower,false);
		mcpPlayer->SetReaction(Reaction,Left);
	}
	if (Collision::Box_Circle_Hit(*Dynamo01->GetBoxCol(), *mcpPlayer->GetAttackCol())) {
		Reaction = Dynamo01->ReturnReaction(StingPower,false);
		mcpPlayer->SetReaction(Reaction, Left);
		if (Reaction == TailReaction_StingDeep || Reaction == TailReaction_Sting) {
			mcpPlayer->GetTail()->SetStingObj(Dynamo01);
		}
	}	
}


//! ���X�|�[���֐�
void Stage1_1::ReSpawn()
{	
	mcpMap = new Map1_1("assets/Stage1/1/MapDate.csv", "assets/Stage1/1/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Stage1/1/MapObjectData.csv");
	mcpMap->AddX(-10.8f);

	float addx;
	//! �v���C���[�̐���
	Vector2 pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	addx = -0.4f - pos.x;
	mcpMap->AddX(addx);
	pos = mcpMap->GetGimmickManager()->GetCheackPointPos();
	mcpPlayer = new Player(pos.x,pos.y);

	mcpEnemyManager = new EnemyManager("assets/Stage1/1/EnemyData.csv", *mcpPlayer, *mcpMap);
	mcpEnemyManager->AddX(-10.8f);
	mcpEnemyManager->AddX(addx);


	Glass01 = new BreakObj;
	Dynamo01 = new Dynamo;
	Door01 = new BigDoor;
	Timpiller01 = new NormalEnemy;
	Timpiller01->SetVec(Vector2(3.0f + addx -10.8f, -0.67f));
	Timpiller01->SetPlayer(mcpPlayer);
	Glass01->SetVec(Vector2(0.0f + addx -10.8f, 0.4f));
	Dynamo01->SetVec(Vector2(8.4f + addx - 10.8f, -0.67f));
	Door01->SetDynamo(Dynamo01);
	Door01->SetVec(Vector2(8.96f + addx -10.8f, -0.3f));
}
