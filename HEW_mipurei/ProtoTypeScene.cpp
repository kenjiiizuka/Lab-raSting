#include "ProtoTypeScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Input.h"
#include"NakanoColi.h"
#include"Collision.h"
#include"Controller.h"
#include"Character.h"
#include"PlayerState.h"
#include"EffectManager.h"

PrototypeScene::PrototypeScene()
{
	tmpPMap1_1 = new Map1_1("assets/Stage1/1/MapDate.csv", "assets/Stage1/1/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Stage1/1/MapObjectData.csv");
	mpNecthor = new Necthor(0.5f, -0.4f);
	tmpPlayer = new Player(-1.0f, 0.0f);//1�L�[�����ă}�E�X�Ή�������
	mpGoal = new ProtoGoal(1.1f,-0.4f);

}

PrototypeScene::~PrototypeScene()
{
	delete mpGoal;
	delete tmpPMap1_1;
	delete tmpPlayer;
	delete mpNecthor;

}

void PrototypeScene::Update()
{
	EffMgr->EffectUpdate();
	tmpPlayer->Update();
	tmpPMap1_1->Update();
	mpNecthor->Update();
	mpGoal->Update();

	//�v���C���[�ƃ{�X�A�n���}�[�̓����蔻��
	//============================ 
	Box* PlayerBox = tmpPlayer->GetBoxCol();
	Circle TailCircle = *tmpPlayer->GetAttackCol();

	////�v���C���[�ƃ{�X�{�́A�{�X�̎��n���}�[�̓����蔻��
	////====================================================================

	//if (mpNecthor->GetAliveFlg() == true)
	//{
	//	//�R���g���[���[��h�炷�悤�Ƀ{�X���n���}�[�����낵�����ǂ�������
	//	if (mpNecthor->GetCtrShakeFlg() == 1)
	//	{
	//		SetControllerVibration(5, 5);
	//	}

	//	//�{�X�̃n���}�[�Ɠ����蔻��
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetBossHunmerCollision());
	//	//�{�X�̑̂Ɠ����蔻��
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetBossBodyCollision());
	//	//�{�X�̓��Ɠ����蔻��
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetBossHeadCollision());


	//	//====================================================================
	//	//�����ۂƃ{�X�̓����蔻��
	//	//====================================================================
	//	//������VS��
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetBossHeadCollision(), TailCircle))
	//	{
	//		//�_���[�W�N�[���^�C���������l�Ȃ烉�C�t�����炷
	//		if (mpNecthor->GetmDamageCoolTime() == 180)
	//		{
	//			if (mpNecthor->GetDownFlg() == false)//�����Ă���΃��C�t�����炷(�_�E�����͔��肵�Ȃ�)
	//			{
	//				mpNecthor->AddLife(-1);
	//				mpNecthor->SetDamageFlg(true);
	//				mpNecthor->SetmDamageCoolTime(179);
	//			}
	//		}
	//		tmpPlayer->SetReaction(TailReaction_StingStop, Direction_None);
	//	}
	//	//������VS�{�X�̓���
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetBossBodyCollision(), TailCircle))
	//	{
	//		tmpPlayer->SetReaction(TailReaction_Stop,Direction_None);
	//	}
	//	//������VS���ꂫ
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetBoxCol(), TailCircle))
	//	{
	//		tmpPlayer->SetReaction(TailReaction_Stop, Direction_None);
	//	}
	//}
	////====================================================================
	////�n���}�[���甭�����邪�ꂫ�ƃv���C���[�̓����蔻��
	//if (mpNecthor->GetDownFlg() == false) 
	//{
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetmpDebriesBox()->GetBoxCol());
	//}
	////====================================================================


	////====================================================================
	////�����ۂƃg�h�����h�����߂̃v���O�̓����蔻��
	//if (mpNecthor->GetDownFlg() == true) //�_�E�����Ă���΃v���O�Ɠ����蔻������n
	//{
	//	//�v���O�Ƃ̓����蔻�肪���n���ꂽ�ꍇ�A�e�X�g�����Ƃ���Boss�{�̂̕`����I�t�ɂ��āA�����ɂ���
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetPlag()->GetPlagCollision(), TailCircle))
	//	{
	//		mpNecthor->SetAliveFlg(false);
	//	}
	//}
	////====================================================================
	//
	////====================================================================
	////�v���C���[�ƏՌ��g�̓����蔻��
	//if (Collision::Box_Box_Hit(*PlayerBox, *mpNecthor->GetmpWavesBox()->GetBoxCol()))
	//{
	//	//�Ռ��g�Ƃ̉������Ƃ��āA�Ռ��g�𓧖��ɂ���
	//	mpNecthor->GetmpWavesBox()->SetDrawActiv(false);
	//	tmpPlayer->SetDamege(Left);

	//}
	////====================================================================

	
	//====================================================================
	//�S�[���Ƃ̓����蔻��(�����ۂ̂�)
	if (Collision::Box_Circle_Hit(*mpGoal->GetmpGoalBox(), TailCircle))
	{
		tmpPlayer->SetReaction(TailReaction_Sting, Direction_None);
		
		if (mpGoal->GetFirstStabFlg() == false)
		{
			mpGoal->SetFirstStabFlg(true);
		}

		if (mpGoal->GetSecondStabFlg() == false)
		{
			mpGoal->SetSecondStabFlg(true);
			if (mpGoal->GetSecondStabFlg())
			{
				//�S�[�������������Ƃ��āA�S�[���̃v���O�𓧖��ɂ���
				mpGoal->SetDrawActiv(false);
				//EffMgr->PlayEffect(DynamoChaege,mpGoal->GetVec().x, mpGoal->GetVec().y);
			}
		}
	}
	//====================================================================


	//====================================================================
	//map�Ƃ̓����蔻��
	if (tmpPMap1_1->CollisionUpdate(tmpPlayer))
	{
		tmpPlayer->SetTouchGround(true);
	}
	else
	{
		tmpPlayer->SetTouchGround(false);
	}
	//====================================================================
	//�v���C���[HP�񕜂̉�����
	if (GetControllerButtonTrigger(Button_UP))
	{
		for (int i = 0; i < 10; i++) 
		{
			tmpPlayer->AddBoruto();
		}
	}
	if (GetControllerButtonTrigger(Button_DOWN))
	{
		tmpPlayer->SetDamege(Direction_None);
	}
	//====================================================================
	//���̃N���A�V�[���J�ڏ���
	if (GetControllerButtonTrigger(Button_X))
	{
		SceneMgr->ChageScene(Scene_Clear,true);
	}
	//���̃��U���g�V�[���J�ڏ���
	if (GetControllerButtonTrigger(Button_Y))
	{
		SceneMgr->ChageScene(Scene_Result, true);
	}
	//���̕����V�[������
	if (GetControllerButtonTrigger(Button_B))
	{
		SceneMgr->ChageScene(Scene_Lose, true);
	}
	//====================================================================
	
	tmpPlayer->LastUpdate();//�����蔻���̏���
}

void PrototypeScene::Draw()
{
	tmpPMap1_1->Draw();
	mpGoal->Draw();
	mpNecthor->Draw();
	tmpPlayer->Draw(); 
	EffMgr->EffectUpdate();
}