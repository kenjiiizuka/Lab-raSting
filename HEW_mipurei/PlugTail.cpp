#include "PlugTail.h"
#include "TextureManager.h"
#include "DirectInput8.h"
#include "Angle.h"
#include "Controller.h" 
#include "Game.h"
#include <math.h>
#include "EffectManager.h"
#include "Dynamo.h"
#include "Camerah.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "WeakDynamo.h"
#include "Pimp.h"
#include "WinMain.h"
#include "SoundManager.h"


//! �R���X�g���N�^
PlugTail::PlugTail(Vector2 & _tailvec, Vector2 & _playervec, ePlayerState & _state, eDirection & _direction, eElectricity & _electstate)
	: mcTailRoot(_tailvec), mcPlayerVec(_playervec), mPlayerState(_state), mDirection(_direction), ElectState(_electstate)
{
	//! �ϐ��̏����l�ݒ�
	mcOldPlayerVec = mcPlayerVec;
	mDownAtkSpeed = 1.0f;
	mReturnSpeed = 0.005f;
	AttackInitSpeed = 0.00048f;
	AttackRadius = 0.06f; //! �U���̑傫��
	mTailRange = 0.125f;	                               //! �����ۂ̓͂��͈�	
	mcDefaultSize = Vector2(0.1f, 0.1f);                   //! �f�t�H���g�̃T�C�Y
	mcAimeSize = Vector2(0.2f, 0.2f);                       //! �G�C���̎��̃T�C�Y
	msSize = FLOAT2(mcDefaultSize.x, mcDefaultSize.y);      //! �����ۂ̃T�C�Y�̐ݒ� �f�t�H���g�̃T�C�Y
	AtkStop = false;
	mOverheat = false;
	SetCameraActiv(false);
	msDisCharge = { false,false,false,0 ,false };           //! ���d�\���̂̏�����
	msBounce = { 0,0,false,false };                         //! �͂�����郊�A�N�V�����̍\����
	Nomal = Blue = Yellow = Red = false;
	Nomal = true;
	ReactionDerection = Direction_None;

	//! �����ۂ̃T�C�Y
	msSection.DefaultSize = { 0.15f, 0.1f };
	msSection.AimSize = { 0.3f,0.2f };
	msSection.Size = msSection.DefaultSize;
	msSection.Pich = msSection.PichDefault = 0.014f;
	msSection.PichAim = 0.028f;

	//! �����ۂ̏����ʒu�̌v�Z
	RStickAngle = DegreeToRadian(110);
	mcVec.x = cos(RStickAngle) * mTailRange + mcTailRoot.x;
	mcVec.y = sin(RStickAngle) * mTailRange + mcTailRoot.y;
	mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));  //! �����ۂ̊p�x

	//! �����ۖ{�̂̓����蔻��
	mcpCol = new Box(mcVec, 0.05f, 0.05f); // ��`�̓����蔻����̐ݒ�
	mcpShape = mcpCol;
	mcpAttackCircle = new Circle(mcAttackPos, AttackRadius);
	mcpAttackCircle->SetActiv(false);

	//! �`��̂��߂̏����ݒ�
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Plug));	//! �摜�̃Z�b�g
	mcpAnimsprite->SetAngle(mTailAngle + DegreeToRadian(90));       //! �`��p�x�̃Z�b�g
	mcpAnimsprite->SetAnimtionTable(1, 1);                           //! �A�j���[�V�����e�[�u���̃Z�b�g	

	//! �����ۂ̒��ԕ����悤�̕`��N���X
	msSection.Section = new AnimationHitObject;
	msSection.Section->SetCameraActiv(false); //! �v���C���[�ɂ��ē����̂ŃJ��������̏C�����󂯎��Ȃ�
	AnimationSprite * SectionSprite = msSection.Section->GetAnimSprite();
	SectionSprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Tail));         //! �摜�̃Z�b�g
	msSection.Section->SetSize(msSection.Size.x, msSection.Size.y);         //! �T�C�Y�̃Z�b�g
	SectionSprite->SetAnimtionTable(1, 1);                                 //! �A�j���[�V�����e�[�u���̃Z�b�g
	SectionSprite->SetAngle(mTailAngle + DegreeToRadian(270), 1.0f, 0.5f);

	Tail(); //! �����ۂ̊e�߂̈ʒu�����߂�
	mReaction = TailReaction::TailReaction_None;

	//! �d�C�̑��̏����ݒ�
	msSpear.ElectSting = new AnimationHitObject();
	msSpear.ElectSting->SetDrawActiv(false);
	AnimationSprite * ElectStingSp = msSpear.ElectSting->GetAnimSprite();
	ElectStingSp->SetTexture(TexMgr->GetTextuer(Tex_Player_ElectSting));
	ElectStingSp->SetAnimtionTable(5, 1);
	msSpear.DefaultSize = Vector2(0.5f, 0.5f);
	msSpear.SmallSize = Vector2(0.3f, 0.3f);
	msSpear.TailDistance = 0.1f;
	msSpear.ElectSting->SetSize(msSpear.DefaultSize);
	//! �����蔻��̐���
	//! ��[
	msSpear.Col = new Circle(msSpear.ColPos, 0.04f);
	msSpear.Col->SetActiv(false);
	//! ���{
	msSpear.ColRoot = new Circle(msSpear.ColRootPos, 0.04f);
	msSpear.ColRoot->SetActiv(false);

	mAimeAngleSet = true;

	mTag = ObjectTag::Tag_Tail;
}

//! �f�X�g���N�^
PlugTail::~PlugTail()
{
	delete msSection.Section;
	delete mcpCol;
	delete msSpear.ElectSting;
	delete msSpear.ColRoot;
	delete msSpear.Col;
	delete mcpAttackCircle;
}

//! �X�V����
void PlugTail::Update()
{
	//! �v���C���[�̈ړ��ʂ����Z����	
	mcVec += mcPlayerVec - mcOldPlayerVec;
	for (int i = 0; i < 100; i++) {
		msSection.Inf[i].Pos += mcPlayerVec - mcOldPlayerVec;
	}

	//! �������ς�������Ɉ�x�������W������	
	if (PrevDirection != mDirection) {
		if (mDirection == Left) {
			mcVec.x = mcTailRoot.x + -mcTailDistance.x;
		}
		else if (mDirection == Right) {
			mcVec.x = mcTailRoot.x + -mcTailDistance.x;
		}
		mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));//! �����ۂ̊p�x�̎擾
		RStickAngle = mTailAngle - DegreeToRadian(180);
	}

	PrevDirection = mDirection;          //! �܂��̃t���[��������ۑ�
	mcTailDistance = mcVec - mcTailRoot; //! �����ۂ̕t�����Ƃ̋������m�F����	
	State(); //! �X�e�[�g�̏���
	mcOldPlayerVec = mcPlayerVec;        //! �O�t���[���̈ʒu�Ƃ��đ��
}

/* ---------------
// �X�e�[�g���� */
void PlugTail::State()
{
	switch (mState)
	{
	case Tail_Idol:
		Idol_Controller();
		break;
	case Tail_Attack:
		Attack_Controller();
		break;
	}
}

//! �v���C���[�̓����蔻�菈���̌�̏C������
void PlugTail::LastUpdate()
{

}

//! �`�揈��
void PlugTail::Draw()
{
	if (Nomal) {
		mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_Plug));
		msSection.Section->GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_Tail));
	}
	else if (Red) {
		mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_PlugR));
		msSection.Section->GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_TailR));
	}
	else if (Yellow) {
		mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_PlugY));
		msSection.Section->GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_TailY));
	}
	
	msSpear.ElectSting->GetAnimSprite()->SetAngle(mTailAngle + DegreeToRadian(180));
	msSpear.ElectSting->Draw();

	//! �K���̕`��
	for (int i = 0; i < msSection.Num; i++) {
		msSection.Section->SetSize(msSection.Size.x, msSection.Size.y);
		msSection.Section->SetVec(msSection.Inf[i].Pos);
		msSection.Section->GetAnimSprite()->SetAngle(msSection.Inf[i].Angle + DegreeToRadian(270));
		msSection.Section->Draw();
	}
	mcpAnimsprite->SetAngle(mTailAngle + DegreeToRadian(90));
	AnimationHitObject::Draw();
}

/* ------------------
// ��Ԃ̃Z�b�g�֐�*/
bool PlugTail::SetState(TailState _state)
{
	//! �A�C�h����ԂɈڍs
	if (_state == TailState::Tail_Idol) {
		//! �U�����Ă��Ȃ��Ƃ��̂݃A�C�h����ԂɂȂ��
		if (AttackState == AttackState_Aim || AttackState == AttackState_None) {
			mState = _state;
		}
		else {
			return false;
		}
	}
	else {
		mState = _state;
	}
	return true;
}

/* ------------------------------
// �A�C�h����� �R���g���[���[ */
void PlugTail::Idol_Controller()
{
	//! Idol�̈ʒu�ɂ����ۂ��ړ������邵���ۂ̈ʒu�͌Œ�H	
	//! �U���̓r����idol��ԂɂȂ�Ȃ��悤�ɂ���
	if (mTailRange >= 0.15) {
		mTailRange -= 0.025;
	}
	//! �����ۂ̃T�C�Y��傫������
	if (msSize.x > mcDefaultSize.x) {
		//! Y���������������Ȃ̂œ����ɉ��Z����
		msSize.x -= 0.025f;
		msSize.y -= 0.025f;
	}
	//! �����ۂ̒��ԕ����̑傫����傫������	
	if (msSection.Size.x > msSection.DefaultSize.x) {
		msSection.Size.x -= 0.025f;
	}
	if (msSection.Size.y > msSection.DefaultSize.y) {
		msSection.Size.y -= 0.02f;
	}
	if (msSection.Pich > msSection.PichDefault) {
		msSection.Pich -= 0.0028f;
	}

	mAimeAngleSet = true;

	AttackState = TailAttackState::AttackState_None;
	mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));//! �����ۂ̊p�x�̎擾	
	mStingPower = 0; //! �U�����Ă��Ȃ��Ƃ��͂O�ɂ���@�b�菈���ł�
	mReactionFrameCnt = 0;
	mDownAtkSpeed = 1.0f;
	MoveLimit();
	Tail();
	ElectSpear();
}

/* -----------------------------------
// �U����Ԃ̏����i�R���g���[���[�j */
void PlugTail::Attack_Controller()
{
	//! Idol����Attack�Ɉȍ~���鏈�� �t���O��������Ǝv��
	//! �����ۂ̃T�C�Y��傫������
	if (msSize.x < mcAimeSize.x) {
		//! Y���������������Ȃ̂œ����ɉ��Z����
		msSize.x += 0.025f;
		msSize.y += 0.025f;
	}
	//! �����ۂ̒��ԕ����̑傫����傫������
	if (msSection.Size.x < msSection.AimSize.x) {
		msSection.Size.x += 0.025f;
	}
	if (msSection.Size.y < msSection.AimSize.y) {
		msSection.Size.y += 0.02f;
	}

	if (msSection.Pich < msSection.PichAim) {
		msSection.Pich += 0.0028f;
	}

	switch (AttackState)
	{
	case AttackState_Aim:
		Aim_Controller();
		break;
	case AttackState_Sting:
		AttackPosture_Controller();
		break;
	case AttackState_Reaction:
		Reaction_Controller();
		break;
	case AttackState_End:
		AttackState = AttackState_None;
		break;
	}

	//! ���d�̏���
	if (msDisCharge.Able) {
		DisCharge();
	}
	Tail();
	ElectSpear();

}

void PlugTail::Destroy()
{
	SetDrawActiv(false);
	SetHitActiv(false);
	msSection.Section->SetHitActiv(false);
	msSection.Section->SetDrawActiv(false);
}

//! �`���[�W�t���O��Ԃ�
bool PlugTail::GetChrage()
{
	if (mCharge) {
		mCharge = false;
		return true;
	}
	return false;
}

//! �����ۂ̍U����̃��A�N�V����
void PlugTail::Reaction_Controller()
{
	//! �������A�N�V�������Ă��Ȃ����ɍU���ł���	
	switch (mReaction)
	{
	case TailReaction_Bounce:
		Bounce();
		break;

	case TailReaction_Stop:
		Stop();
		break;

	case TailReaction_StingStop:
		StingStop_Controller();
		break;

	case TailReaction_Through:
		Through(); //! �����ۂ��h�����Ƃ��ɂ��̂܂܊т��Ƃ��̏���
		break;

	case TailReaction_Sting:
		StingObj();
		Sting_Controller();
		break;

	case TailReaction_StingDeep:
		StingObj();
		StingDeep_Controller();
		break;

	case TailReaction_End:
		ReturnTail();
		break;
	}
}

//! �G�C�����̑���
void PlugTail::Aim_Controller()
{
	//! �_���Ƃ��̂����ۂ̎˒��ɂ���
	//mTailRange = 0.4f;
	if (mTailRange < 0.4f) { 
		mTailRange += 0.04f;
		if (mTailRange >= 0.4f) {
			mTailRange = 0.4f;
		}
	}
	else if (mTailRange > 0.4f) {
		mTailRange -= 0.04f; 
		if (mTailRange <= 0.4f) {
			mTailRange = 0.4f;
		}
	}

	//! �h���ɂ���
	int RT = GetControllerRightTrigger();
	if (RT >= 5) {
		AttackState = TailAttackState::AttackState_Sting;
	}
	MoveLimit();
}


/* -------------------------------------------
//! �U���Ԑ��̊֐� �R���g���[���[����̏ꍇ */
void PlugTail::AttackPosture_Controller()
{
	float distance = mcVec.PosToPos(mcTailRoot); //! �v���C���[�Ƃ̋��������߂�

	//! �g���K�[�̉������݋���擾
	int RT = GetControllerRightTrigger();
	//! �g���K�[���T�ȏ��������Ă�����v���J�n
	if (Attack_C == false && TriggerStart_C == false && RT >= 5) {
		TriggerStart_C = true;
		mTailRange = 0.4f;
		SoundMgr->PlaySE(SE_Tame,0.1f);
	}

	//! �v����
	if (TriggerStart_C && !Attack_C) {
		//! ����������������
		MoveLimit(1);

		mDownAtkSpeed = 1.0f;
		//! �������܂�Ă���l���ő�l���傫����Α������
		Red = Blue = Yellow = false;
		Nomal = false;

		if (RT > MaxTrigger_C) { MaxTrigger_C = RT - 5;}

		//! �g���K�[��255�ɂȂ���������i���銴���ŐK���̂Ȃ�����Z������
		if (RT == 255) {
			mTailRange -= 0.005f;
			if (mTailRange < 0.3f) {
				mTailRange = 0.31f;
				MaxTrigger_C = 255;	
			}
		}

		//Tail();
		//! �g���K�[�̒l���O�ɂȂ�����U���J�n
		if (RT == 0) {
			Attack_C = true;
			SoundMgr->PlaySE(SE_Sting01, 0.06f);
			//EffMgr->PlayEffect();
		}
	}

	//! ���̏����ł� //! �Q�T�O
	//! �f�o�b�O�悤�ɐF��ς��܂�
	if (AttackInitSpeed * MaxTrigger_C > STING_STRONG) {
		Red = true;
	}
	else {
		Yellow = true;
	}
	/*else if (AttackInitSpeed * MaxTrigger_C > STING_MIDIUME) {
		Yellow = true;
	}*/
	
	if (Attack_C) 
	{
		//! �����ۂ̐i�ރX�s�[�h���v�Z����
		mAtkSpeed = AttackInitSpeed * MaxTrigger_C;
		mTailRange = 1.4f;
		mcVec.y += sin(RStickAngle) * (mAtkSpeed * mDownAtkSpeed);
		mcVec.x += cos(RStickAngle) * (mAtkSpeed * mDownAtkSpeed);
		//! �U���̍��W���Z�b�g����
		mcAttackPos.x = mcVec.x;
		mcAttackPos.y = mcVec.y;
		mcpAttackCircle->SetActiv(true); //! �U���̓����蔻����I���ɂ���
		mStingPower = mAtkSpeed;

		//! �����ۂ��͈͊O�ɂł邩�@�X�s�[�h�����ȉ��ɂȂ�����߂�
		if ((distance > mTailRange) || mStingPower < 0.006f) 
		{
			mAtkSpeed = 0;
			MaxTrigger_C = 0;
			TriggerStart_C = false;
			Attack_C = false;
			mcpAttackCircle->SetActiv(false);   //! �U���̓����蔻����I�t�ɂ���
			mStingPower = 0;
			AttackState = AttackState_Reaction; //! ���A�N�V�����ɍs��
			mReaction = TailReaction_End;       //! �U���I���ɂ���
			msSpear.Col->SetActiv(false);       //! �d�C�̑��̓����蔻�������
		}
	}
}

//! �����ۂ��_�炩���G�ɂ͂����ꂽ�Ƃ��̏���
void PlugTail::Bounce()
{
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mcpAttackCircle->SetActiv(false); //! �U���̓����蔻����I�t

	msBounce.Flg = true;

	//! 4�t���[���~�܂�
	if (msBounce.Cnt > 4) 
	{
		//! ���̎��̊p�x��120�x����
		//! 120�x���Z�������߂�
		if (msBounce.TotalAngle < 110) 
		{
			if (ReactionDerection == Left) 
			{
				mTailAngle += DegreeToRadian(110);
			}
			else if (ReactionDerection == Right) 
			{
				mTailAngle -= DegreeToRadian(110);
			}
			msBounce.TotalAngle += 110;
			msBounce.speed = mStingPower * 0.3f;
			msBounce.ReTail = false;
		}

		//! ���̊p�x�Ői�܂���	
		if (!msBounce.ReTail) {
			//! �����ۂ̈ړ�������
			msBounce.TotalMove += fabs(cos(mTailAngle) * -msBounce.speed);
			msBounce.TotalMove += fabs(sin(mTailAngle) * -msBounce.speed);
			//! �K�����ړ�������
			mcVec.x += cos(mTailAngle) * -msBounce.speed;
			mcVec.y += sin(mTailAngle) * -msBounce.speed;
			msBounce.speed *= 0.9f; //! �X�s�[�h�x������

		}
		//! �X�s�[�h���O�ɂȂ�����߂�n�߂�
		if (msBounce.speed < 0.001f && !msBounce.ReTail) {
			msBounce.speed = 0.002f;
			msBounce.ReTail = true;
		}

		float distance = 0;
		//! �K����߂�
		if (msBounce.ReTail) 
		{
			//! �t���[���҂�
			if (msBounce.Cnt > 20) 
			{
				//! �X�s�[�h�̍ő�l�𒴂���܂ő��₷
				if (msBounce.speed < 0.02f) 
				{
					msBounce.speed *= 1.1f;
				}
				//! �����ۂ̐߂�S�đO�̐߂Ɍ������Ă��ړ�������
				//! �����ɂȂ�����ړ�����߂�
				float Angle; //! �i�ފp�x
				//! �K���{�̂̈ړ�
				Angle = PositionRelationAngle(FLOAT2(mcVec.x, mcVec.y), FLOAT2(msSection.Inf[msSection.Num - 1].Pos.x, msSection.Inf[msSection.Num - 1].Pos.y));
				//! �ړ�
				//speed = 0.001f;
				mcVec.x += cosf(Angle) * -msBounce.speed;
				mcVec.y += sinf(Angle) * -msBounce.speed;
				//! �`�掞�̊p�x�̃Z�b�g
				mTailAngle = PositionRelationAngle(FLOAT2(mcVec.x, mcVec.y), FLOAT2(msSection.Inf[msSection.Num - 1].Pos.x, msSection.Inf[msSection.Num - 1].Pos.y));
				mTailAngle += DegreeToRadian(180);
				//! �K���̐߂̈ړ�
				for (int i = msSection.Num - 1; i > -1; i--) 
				{
					if (i != 0) 
					{ //! ���{�ȊO
						//! �i�ފp�x�����߂�
						FLOAT2 Section1(msSection.Inf[i].Pos.x, msSection.Inf[i].Pos.y);
						FLOAT2 Section2(msSection.Inf[i - 1].Pos.x, msSection.Inf[i - 1].Pos.y);
						Angle = PositionRelationAngle(Section1, Section2);
						//! �ړ�
						msSection.Inf[i].Pos.x += cosf(Angle) * -msBounce.speed;
						msSection.Inf[i].Pos.y += sinf(Angle) * -msBounce.speed;
						//! �`�掞�̊p�x�̃Z�b�g
						msSection.Inf[i].Angle = Angle + DegreeToRadian(180);
					}
				}
				//! ���{�̎�O�̐߂����{�Ƃ�����x�߂�������A�����ɂ��Đ߂̐������炷
				//! ���������߂�
				distance = msSection.Inf[1].Pos.PosToPos(msSection.Inf[0].Pos);
				if (distance < (msSection.Pich * 0.6f)) { //! �������K���̃s�b�`�̔����ȉ��Ȃ�
					//! �z������炷
					for (int j = 0; j < msSection.Num; j++) {
						//! �擪�ɂ͑�����Ȃ�
						if (j != msSection.Num - 1) {
							msSection.Inf[j] = msSection.Inf[j + 1];
						}
					}
					msSection.Num--; //! �߂ɐ������炷
				}

				distance = mcVec.PosToPos(mcTailRoot);
				if (distance < 0.3f) {
					msBounce.ReTail = false;
					msBounce.Flg = false;
					msBounce.TotalAngle = 0;
					msBounce.TotalMove = 0;
					msBounce.Cnt = 0;
					mStingPower = 0;
					mReaction = TailReaction_End;
				}
			}
		}
	}
	msBounce.Cnt++;
}



//! �h���炸�Ɏ~�܂鎞(�����͎h�����Ď~�܂�Ƃ��Ƃقړ���)�G�͓|��Ȃ�
void PlugTail::Stop()
{
	//! 15�t���[���~�܂�	
	if (!mReactionFrameCnt <= 20) {
		mReaction = TailReaction_End;
	}
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! �U���̓����蔻����I�t�ɂ���

	mReactionFrameCnt++;
}

/* ---------------------------------
// �����ۂ��h���Ď~�܂�Ƃ��̏��� */
void PlugTail::StingStop_Controller()
{
	//! 15�t���[���~�܂�	
	if (!mReactionFrameCnt <= 15) {
		mReaction = TailReaction_End;
	}

	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! �U���̓����蔻����I�t�ɂ���
	mReactionFrameCnt++;
}

//! �����ۂ�G�Ɏh���Ă��̂܂܊т�����
void PlugTail::Through()
{
	//! �h���З͂����炷
	if (ElectState == eElectricity::Elect_Super) {
		mDownAtkSpeed -= 0.15f; //! ���~�␳�̒l�𑝂₷
	}
	else {
		mDownAtkSpeed -= 0.3f; //! ���~�␳�̒l�𑝂₷
	}
	if (mDownAtkSpeed <= 0) {
		mDownAtkSpeed = 0.1f;
	}
	mReaction = TailReaction_None;
	//! �h���ɖ߂�
	AttackState = AttackState_Sting;
}

/* -------------
// �h���鏈�� */
void PlugTail::Sting_Controller()
{
	//! �U������߂�
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! �U���̓����蔻����I�t

	msDisCharge.Able = true; //! ���d�\�ɂ���

	//! �����������Ƃ��郂�[�V���������ꂽ�炢������
	//! ���d���͔����Ȃ��悤�ɂ���
	if (!msDisCharge.Doing) {
		//! ���o�K�`���ő�������������
		if (RightStickMashing()) {
			mReactionFrameCnt += 4;
		}
		//! 60�t���[���o�߂����甲����
		if (mReactionFrameCnt >= 180) {
			mReaction = TailReaction_End;
			msDisCharge.Able = false; //! ���d�s�ɂ���
			mReactionFrameCnt = 0;
			mcpStingObj = nullptr;
		}
		mReactionFrameCnt++;
		//! �����𖞂������甲����(���o�K�`���H)
	}
}

/* -----------------------
// �[���h����Ƃ��̏��� */
void PlugTail::StingDeep_Controller()
{
	//! �U������߂�
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! �U���̓����蔻����I�t

	msDisCharge.Able = true; //! ���d�\�ɂ���
	//! �����������Ƃ��郂�[�V���������ꂽ�炢������
	if (!msDisCharge.Doing) 
	{
		//! ���o�K�`���ő�������������
		if (RightStickMashing()) {
			mReactionFrameCnt += 4;
		}
		//! 60�t���[���o�߂����甲����
		if (mReactionFrameCnt >= 300) {
			mReaction = TailReaction_End;
			msDisCharge.Able = false; //! ���d�s�ɂ���
			mReactionFrameCnt = 0;
			mcpStingObj = nullptr;
		}
		mReactionFrameCnt++;
	}
}

/* ---------------------------------------
// �����ۂ��h������Ɋ�̈ʒu�ɖ߂鏈�� */
void PlugTail::ReturnTail()
{
	//! 10�t���[���͐Î~����
	if (mReactionFrameCnt > 10) {
		mcVec.x += cos(mTailAngle) * (mReturnSpeed);
		mcVec.y += sin(mTailAngle) * (mReturnSpeed);

		if (mReactionFrameCnt > 12 && mReactionFrameCnt < 20) {
			mReturnSpeed += 0.002f;
		}
		else if (mReactionFrameCnt < 25) {
			mReturnSpeed += 0.004f;
		}
	}
	float distance = mcVec.PosToPos(mcTailRoot); //! �v���C���[�Ƃ̋��������߂�
	if (distance < 0.4f) {
		mReaction = TailReaction_None;
		AttackState = AttackState_End;
		mTailRange = 0.4f;
		mReturnSpeed = 0.005f;
		mReactionFrameCnt = 0;
		msDisCharge.Able = false; //! ���d�s�̏�Ԃɂ���
		Red = Blue = Yellow = false; //! �F����ɖ߂�
		Nomal = true;
	}
	mReactionFrameCnt++;
}

/* -------
// ���d */
void PlugTail::DisCharge()
{
	//if (GetControllerButtonTrigger(Button_RB) && !msDisCharge.Doing) 
	//{
	//	msDisCharge.Doing = true;
	//	msDisCharge.Cnt = 0;
	//	SoundMgr->PlaySE(SE_NormalElec,0.5f);
	//}

	if (mOnElectForDynamo && !msDisCharge.Doing)
	{
		msDisCharge.Doing = true;
		msDisCharge.Cnt = 0;
		SoundMgr->PlaySE(SE_NormalElec, 0.5f);
	}

	if (mOverheat) {
		msDisCharge.End = true;
	}

	//! ���d�����A���d�I���t���O�������Ă��Ȃ��Ƃ�
	if (msDisCharge.Doing && !msDisCharge.End) {

		int NumDraw = msDisCharge.Cnt / 5 + 2;
		if (NumDraw == msSection.Num - 1) {
			NumDraw = msSection.Num - 1;
			msDisCharge.End = true; 	
			msDisCharge.Hit = true; 	
			EffMgr->PlayEffect(eEffect::DisCharge, mcVec.x, mcVec.y, 0.3f,0.2f,(RStickAngle - DegreeToRadian(90)));
		}
		else {
			EffMgr->PlayEffect(eEffect::DisCharge, msSection.Inf[NumDraw].Pos.x, msSection.Inf[NumDraw].Pos.y, 0.4f,0.3f, (RStickAngle - DegreeToRadian(90)));
		}
	}
	else if (msDisCharge.End) {
		//! ���d���I���10�t���[���o�߂�����I���
		msDisCharge.Doing = false;
		msDisCharge.End = false;
		msDisCharge.Cnt = 0; //! �����Ă�t���[�������Z�b�g����
		msDisCharge.Hit = false;
		mReactionFrameCnt = 300;
	}
	msDisCharge.Cnt++;
}

//! �ړ������֐�
void PlugTail::MoveLimit(int speed)
{
	//! �X�e�B�b�N�̊p�x�̎擾	
	float RSAngle = GetControllerRightStickAngle();
	float Deg = RadianToDegree(RStickAngle);
	if (mState == TailState::Tail_Idol) {
		float PlusDif_Idol;
		float MinusDif_Idol;
		if (mDirection == Left) {
			//! �����ۂ̊p�x��70�x�ɂ���
			//! �v���X�A�}�C�i�X�����̊p�x�̍����擾
			PlusDif_Idol = GetPlusDifDegree(RadianToDegree(RStickAngle), 70);
			MinusDif_Idol = GetMinusDifDegree(RadianToDegree(RStickAngle), 70);

			if (PlusDif_Idol < MinusDif_Idol) {
				RStickAngle += DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) > 70) {
					RStickAngle = DegreeToRadian(70);
				}
			}
			else {
				RStickAngle -= DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) < 70) {
					RStickAngle = DegreeToRadian(70);
				}
			}
		}
		else {
			//! �����ۂ̊p�x��70�x�ɂ���
			//! �v���X�A�}�C�i�X�����̊p�x�̍����擾
			PlusDif_Idol = GetPlusDifDegree(RadianToDegree(RStickAngle), 110);
			MinusDif_Idol = GetMinusDifDegree(RadianToDegree(RStickAngle), 110);

			if (PlusDif_Idol < MinusDif_Idol) {
				RStickAngle += DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) > 110) {
					RStickAngle = DegreeToRadian(110);
				}
			}
			else {
				RStickAngle -= DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) < 110) {
					RStickAngle = DegreeToRadian(110);
				}
			}
		}
	}
	else if (AttackState == TailAttackState::AttackState_Aim && mAimeAngleSet) {
		//! 0�̎��͑�����Ȃ�
		if (RSAngle != 0) { mAimeAngleSet = false; }
		if (mDirection == Right) {
			RStickAngle -= DegreeToRadian(4);
			if (RadianToDegree(RStickAngle) < 10) {
				RStickAngle = DegreeToRadian(10);
			}
		}

		else {
			//! �����ۂ̊p�x��110�x�ɂ���	
			RStickAngle += DegreeToRadian(4);
			if (RadianToDegree(RStickAngle) > 170) {
				RStickAngle = DegreeToRadian(170);
			}	
		}

	}
	else {
		//! 0�̎��͑�����Ȃ�
		if (RSAngle != 0) {
			//! �v���X�A�}�C�i�X�����̊p�x�̍����擾
			float PlusDif = GetPlusDifDegree(RadianToDegree(RStickAngle), RadianToDegree(RSAngle));
			float MinusDif = GetMinusDifDegree(RadianToDegree(RStickAngle), RadianToDegree(RSAngle));
			//! �������������Ɍ������Ĉړ����Ă���
			if (PlusDif < MinusDif) {
				RStickAngle += DegreeToRadian(speed);
				//! �ʂ�߂�����
				//! �ʂ�߂����Ƃ�
				if (AttackState != AttackState_Sting) {
					if (RStickAngle > RSAngle) {
						RStickAngle = RSAngle;
					}
				}
			}
			else {
				RStickAngle -= DegreeToRadian(speed);
				//! �ʂ�߂����Ƃ�
				if (AttackState != AttackState_Sting) {
					if (RStickAngle < RSAngle) {
						RStickAngle = RSAngle;
					}
				}
			}
		}
	}

	mcVec.x = cos(RStickAngle) * mTailRange + mcTailRoot.x;
	mcVec.y = sin(RStickAngle) * mTailRange + mcTailRoot.y;
	//! �����ۂ̈ʒu����p�x���v�Z
	mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));//! �����ۂ̊p�x�̎擾
}


/* ---------------------------------------------------------------------------------------
// �h���Ă���I�u�W�F�N�g�ɑ΂��鏈��                                                   //
// �����ۂɎh�������܂ܓ������悤�Ȃ��Ƃ������Ă��Ή��ł���悤�ɂ����ۑ��ŏ��������܂� */
void PlugTail::StingObj()
{
	//! �h���Ă���I�u�W�F�N�g�����Ȃ̂����擾
	if (mcpStingObj) {
		ObjectTag Tag = ((AnimationHitObject *)mcpStingObj)->GetTag();

		switch (Tag){
		case Tag_Dynamo:
			mOnElectForDynamo = true;
			((Dynamo *)mcpStingObj)->SetChrage(msDisCharge.Hit);

			if (msDisCharge.Hit)
			{
				mOnElectForDynamo = false;
			}
			break;
		case Tag_WeakDynamo:
			((WeakDynamo *)mcpStingObj)->SetChrage(msDisCharge.Hit);
			mOverheat = ((WeakDynamo *)mcpStingObj)->Overheat(); //! �I�[�o�[�q�[�g�����������炤
			if (!mOverheat)
			{
				mOnElectForDynamo = true;
			}

			if (msDisCharge.Hit)
			{
				mOnElectForDynamo = false;
			}
			break;
		}
	}
}
/* -------------------------------------------
// �d�C�̑��̏���                          */

void PlugTail::ElectSpear()
{
	//!	���ѓd�ɂȂ��Ă��玟�̃G�C����ԂɂȂ�����d�C�̑��t���O�𗧂Ă�
	if (ElectState == eElectricity::Elect_Super) {
		msSpear.Activ = true;
	}
	//! ���ѓd�ȊO�̓I�t�ɂ���
	else {
		msSpear.Activ = false;
	}

	//! �ʒu�Ɠ����蔻��̌v�Z�͏�ɂ���
	//! �d�C�̑��̈ʒu�����߂�
	//! �`��ʒu
	Vector2 SpearPos;
	SpearPos.x = mcVec.x + cosf(mTailAngle) * -msSpear.TailDistance;
	SpearPos.y = mcVec.y + sinf(mTailAngle) * -msSpear.TailDistance;
	msSpear.ElectSting->SetVec(SpearPos);
	//! �����蔻��ʒu
	msSpear.ColPos.x = SpearPos.x + cosf(mTailAngle) * -0.2f;
	msSpear.ColPos.y = SpearPos.y + sinf(mTailAngle) * -0.2f;
	msSpear.ColRootPos.x = SpearPos.x + cosf(mTailAngle) * 0.14f;
	msSpear.ColRootPos.y = SpearPos.y + sinf(mTailAngle) * 0.14f;

	//! ���ѓd�̂Ƃ��̂�
	if (msSpear.Activ) {
		if (msSpear.Arufa < 1.0f) {
			msSpear.Arufa += 0.025f;
		}
		else if(msSpear.Flash){
			msSpear.Arufa = 0.3f;
		}
		//! �G�C����ԂɂȂ��Ă�����傫������
		if (AttackState == TailAttackState::AttackState_Aim || AttackState == TailAttackState::AttackState_Sting) {
			msSpear.ElectSting->SetDrawActiv(true);
			if (msSpear.Size.x < msSpear.DefaultSize.x) {
				msSpear.Size.x += 0.05f;
			}
			if (msSpear.Size.y < msSpear.DefaultSize.y) {
				msSpear.Size.y += 0.05f;
			}
			//! �����ۂ܂ł̋���
			if (msSpear.TailDistance < 0.2f) {
				msSpear.TailDistance += 0.025f;
			}
		}
		//! �A�C�h���Ȃ珬��������
		else if (mState == TailState::Tail_Idol) {
			//! �A�C�h����Ԃ̃T�C�Y
			if (msSpear.SmallSize.x < msSpear.Size.x) {
				msSpear.Size.x -= 0.05f;
			}
			if (msSpear.SmallSize.y < msSpear.Size.y) {
				msSpear.Size.y -= 0.05f;
			}
			//! �����ۂ܂ł̋���
			if (0.1f < msSpear.TailDistance) {
				msSpear.TailDistance -= 0.025f;
			}
		}

		AnimationSprite * AnimSp = msSpear.ElectSting->GetAnimSprite();
		AnimSp->SetColor(0.5f, 0.5f, 1.0f);
		float DrawRad = mTailAngle + 3.14f;
		AnimSp->SetAngle(DrawRad);

		//! �U�����̂ݓ����蔻����I���ɂ���
		if (Attack_C) {
			msSpear.Col->SetActiv(true);
			msSpear.ColRoot->SetActiv(true);
		}
		else {
			msSpear.Col->SetActiv(false);
			msSpear.ColRoot->SetActiv(false);
		}
	}
	//! �ѓd���ĂȂ��Ƃ�
	else {
		msSpear.Col->SetActiv(false);
		msSpear.ColRoot->SetActiv(false);
		//! �����Ă���
		if (0.0f < msSpear.Arufa) {
			msSpear.Arufa -= 0.025f;
		}
		else {
			msSpear.ElectSting->SetDrawActiv(false);
		}
	}


	

	msSpear.ElectSting->SetSize(msSpear.Size);
	msSpear.ElectSting->GetAnimSprite()->SetArufa(msSpear.Arufa);
}

AnimationSprite * PlugTail::GetElestSpear()
{
	return msSpear.ElectSting->GetAnimSprite();
}

void PlugTail::SetFlash(bool _state)
{
	msSpear.Flash = _state;
}

bool PlugTail::GetOverheat()
{
	if (mOverheat) {
		mOverheat = false;
		return true;
	}
	return false;
}

void PlugTail::SetAttackState(TailAttackState _state)
{
	if (AttackState == AttackState_None) {
		AttackState = _state;
	}
}

//! �����ێ��g�̓����蔻��̃Q�b�^�[
Box* PlugTail::GetCol()
{
	return mcpCol;
}

//! �U�������������Ƃ��̓����蔻��̃Q�b�^�[
Circle* PlugTail::GetAttackCol()
{
	mcpAttackCircle->SetPos(mcVec.x, mcVec.y);
	return  mcpAttackCircle;
}

Circle PlugTail::GetSpearCol()
{
	return *msSpear.Col;
}

Circle PlugTail::GetSpearColRoot()
{
	return *msSpear.ColRoot;
}

//! �h���������̃Q�b�^�[
float PlugTail::GetStingPower()
{
	return mStingPower;
}

//! �������炵���ۂ܂ł̋����̃Q�b�^�[
Vector2 PlugTail::GetTailDistance()
{
	//! ���i�Ȓl��Ԃ����߂ɕԂ��u�Ԃɂ��v�Z����
	return mcVec - mcTailRoot;
}

//! ���A�N�V�������w�肷��
void PlugTail::SetReaction(TailReaction _reaction, eDirection _direction)
{
	if (mReaction == TailReaction_None) {
		mReaction = _reaction;
		ReactionDerection = _direction;
		//! �G�t�F�N�g���ʐU��������
		switch (mReaction)
		{
		case TailReaction_Sting:
			CAMERA->StartVibration(3);
			SetControllerVibrationTime(20, 20, 24);
			break;
		case TailReaction_StingDeep:
			CAMERA->StartVibration(4);
			SetControllerVibrationTime(20, 20, 20);
			break;
		case TailReaction_StingStop:
			CAMERA->StartVibration(3);
			SetControllerVibrationTime(20, 20, 20);
			break;
		case TailReaction_Stop:

			//SetControllerVibrationTime(3, 3, 2);
			break;
		case TailReaction_Through:
			CAMERA->StartVibration(4);
			SetControllerVibrationTime(20, 20, 25);
			break;
		case TailReaction_Bounce:
			CAMERA->StartVibration(3);
			SetControllerVibrationTime(13, 13, 30);
			break;
		}
		//mStingPower = 0.0f; //! �͂������悤�ɑ��̕ϐ��ɑ������Ǝv��
		mReactionFrameCnt = 0;
		AttackState = AttackState_Reaction; //! ���A�N�V�����ɍs��

		//! ���̏����@�h�������炢��Ƃ��͑ѓd����
		if (mReaction != TailReaction_Stop && mReaction != TailReaction_Bounce) {
			//mCharge = true;
		}
	}
}

void PlugTail::TailReturn()
{
	mReaction = TailReaction_End;
	msDisCharge.Able = false; //! ���d�s�ɂ���
	mReactionFrameCnt = 0;
	mcpStingObj = nullptr;
}

//! ���A�N�V�������I��������Ƃ�`����
bool PlugTail::GetTailRactionState()
{
	if (mReaction == TailReaction_None) {
		return true;
	}
	return false;
}

bool PlugTail::GetAttackState()
{
	//! �U�����Ȃ�
	if (Attack_C && AttackState != AttackState_None) {
		return true;
	}
	return false;
}

void PlugTail::SetStingObj(GameObject * _stingobj)
{
	//! ���d�@�Ɏh�������ꍇ�̓`���[�W���Ȃ��悤�ɂ���
	if (((AnimationHitObject *)_stingobj)->GetTag() == Tag_Dynamo) {
		mCharge = false;
	}
	mcpStingObj = _stingobj;
}

//! �����ۂ̒��ԕ����̏���
void PlugTail::Tail()
{
	AnimationSprite * SectionAnimSprite = msSection.Section->GetAnimSprite();
	msSection.OldNum = msSection.Num; //! �O�t���[���̐߂̐�
	//! �O�t���[���̂����ۂ̋O�ՂƂ��ĕۑ�����
	for (int i = 0; i < 100; i++) {
		msSection.PrevInf[i] = msSection.Inf[i];
	}
	if (!msBounce.Flg) {
		msSection.Length = fabs(mcVec.PosToPos(mcTailRoot) - 0.02f); //! �����ۂ��獪���̒�������
		//! ������������T�C�Y�ŉ��`�悵���炢���̂����o��		

		msSection.Num = msSection.Length / msSection.Pich;
	}

	//! �������W���Z�b�g����
	float DisRemain = 0;

	bool static first = false;
	Vector2	Resistance;				//! ��R��
	float AttCoefficient = 1.66f;    //! �����W��
	float Coefficient = 0.34f;       //! �΂ˌW��
	float Mass = 1.0f;              //! ����

	if (!msBounce.Flg) {
		//! �����_�̈ʒu���o��(����)
		for (int i = 0; i < msSection.Num; i++) {
			//! �܂���ɍ����̈ʒu���v�Z����
			if (i == 0) {
				msSection.Inf[i].Pos = mcTailRoot;
			}
			else {
				msSection.Inf[i].Pos.x = msSection.Inf[i - 1].Pos.x + cos(RStickAngle) * msSection.Pich;
				msSection.Inf[i].Pos.y = msSection.Inf[i - 1].Pos.y + sin(RStickAngle) * msSection.Pich;
			}
			msSection.Inf[i].Angle = RStickAngle;
			first = true;
		}
	}

	//! �K���̐�[�̌����_�����߂�
	Vector2 TailAttach;
	TailAttach.x = mcVec.x + cosf(mTailAngle) * 0.02f;
	TailAttach.y = mcVec.y + sinf(mTailAngle) * 0.02f;

	bool Fin = false;
	if (msBounce.Flg) {

		for (int num = 0; num < 15; num++) {
			for (int i = msSection.Num - 1; i > -1; i--) {
				//! �@�㑤�̐߂�������������
				//! ��[
				if (i == msSection.Num - 1) {
					msSection.Inf[i].Tension_Up = Tension(TailAttach, msSection.Inf[i].Pos, Coefficient, msSection.Pich);
				}
				else {
					//! �K���������������
					msSection.Inf[i].Tension_Up = Tension(msSection.Inf[i + 1].Pos, msSection.Inf[i].Pos, Coefficient, msSection.Pich);
				}

				//! �A�����̐߂�������������
				//! ���{�͈��������Ȃ�		
				msSection.Inf[i].Tension_Down = Tension(msSection.Inf[i - 1].Pos, msSection.Inf[i].Pos, Coefficient, msSection.Pich);

				//! �B�d�͂����߂�
				msSection.Inf[i].Gravity = Mass * -0.001f;
				msSection.Inf[i].Gravity = 0;

				//! �C��R�͂����߂�
				Resistance.x = -msSection.Inf[i].Velocity.x * AttCoefficient;
				Resistance.y = -msSection.Inf[i].Velocity.y * AttCoefficient;

				//! �E������͂�����
				msSection.Inf[i].Resultant.x = msSection.Inf[i].Tension_Up.x + msSection.Inf[i].Tension_Down.x + Resistance.x;
				msSection.Inf[i].Resultant.y = msSection.Inf[i].Gravity + msSection.Inf[i].Tension_Up.y + msSection.Inf[i].Tension_Down.y + Resistance.y;

				//! �F���͂Ǝ��ʂ�������x�����߂�
				msSection.Inf[i].Acceleration.x = msSection.Inf[i].Resultant.x / Mass;
				msSection.Inf[i].Acceleration.y = msSection.Inf[i].Resultant.y / Mass;

				//! �G���x�ɉ����x��������
				msSection.Inf[i].Velocity.x += msSection.Inf[i].Acceleration.x;
				msSection.Inf[i].Velocity.y += msSection.Inf[i].Acceleration.y;

				//! �����̈ʒu�͌Œ�Ȃ̂őS��0�ɂ���
				if (i == 0) {
					msSection.Inf[i].Tension_Down = Vector2(0, 0);
					msSection.Inf[i].Tension_Up = Vector2(0, 0);
					msSection.Inf[i].Resultant = Vector2(0, 0);
					msSection.Inf[i].Velocity = Vector2(0, 0);
					msSection.Inf[i].Acceleration = Vector2(0, 0);
					msSection.Inf[i].Gravity = 0;
					msSection.Inf[i].Pos = mcTailRoot;
				}

				//! �H���x������W���ړ�
				msSection.Inf[i].Pos += msSection.Inf[i].Velocity;

				//! �I����̐߂ɑ΂��Ă̊p�x�����߂�
				if (i == msSection.Num - 1) {
					msSection.Inf[i].Angle = (float)PositionRelationAngle(FLOAT2(TailAttach.x, TailAttach.y), FLOAT2(msSection.Inf[i].Pos.x, msSection.Inf[i].Pos.y));
				}
				else {
					msSection.Inf[i].Angle = (float)PositionRelationAngle(FLOAT2(msSection.Inf[i + 1].Pos.x, msSection.Inf[i + 1].Pos.y), FLOAT2(msSection.Inf[i].Pos.x, msSection.Inf[i].Pos.y));
				}
			}
		}
	}
	SectionAnimSprite->SetAngle(RStickAngle, 1.0f, 0.5f);

}
