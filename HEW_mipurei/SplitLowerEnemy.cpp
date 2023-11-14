#include "SplitLowerEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "Camerah.h"
#include "Time.h"
#include "WinMain.h"
#include "Controller.h"
#include <math.h>

//! �Â��@�X�v���b�^�[�̉摜��K�����Ă��������B
//! �����蔻��ƍ��킹��Ƃ���܂ł��܂����B���͓������Ă��񂾂��Ȃ���������Ă�������
//1 ���̂��Ƃɕ����̓����蔻������肢���܂�

//! �R���X�g���N�^
SplitLowerEnemy::SplitLowerEnemy()
{
	//! ���������Ԃł̓����蔻������
	msSize.x = 0.5f;
	msSize.y = 0.6f;
	mcCombiPos = Vector2(mcVec.x,mcVec.y - 0.1f); //! ���W
	mcCombColSize = Vector2(0.2f, 0.56f);          //! �T�C�Y
	mcpCombiCol = new Box(mcCombiPos,mcCombColSize.x,mcCombColSize.y);
	ColSize = Vector2(0.3f, 0.3f);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Splitter));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	Combi = true;
	Count = 0;
	
	//! �����̓����蔻��̐���
	mcpSplitedCol = new Box(mcSplitedColPos,0.2f,0.3f);

	mfSpeed = 0.006f;
	TotalMove = 0.0f;
	mTag = Tag_Enemy_SplitD;
	MutekiCount = 0;
	//! ��̓G�̐���
	mcpSpltterUP = new SplitUpperEnemy(mcVec, Combi);
	mcpSpltterUP->SetCameraActiv(false);

	TotalMove = 0;
	FollowMove = 0;
	mAlive = true;
}

SplitLowerEnemy::SplitLowerEnemy(float _x, float _y)
{
	//! ���������Ԃł̓����蔻������
	mcVec = Vector2(_x, _y);
	mcCombiPos = Vector2(mcVec.x, mcVec.y + 0.1f); //! ���W
	mcCombColSize = Vector2(0.2f, 0.4f);          //! �T�C�Y
	mcpCombiCol = new Box(mcCombiPos, mcCombColSize.x, mcCombColSize.y);
	Combi = true;
	ColSize = Vector2(0.3f, 0.3f);
	mfSpeed = 0.006f;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Splitter));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mTag = Tag_Enemy_SplitD;
	Count = 0;
	TotalMove = 0;
	FollowMove = 0;
	//! ��̓G�̐���
	mcpSpltterUP = new SplitUpperEnemy(mcVec, Combi);
	mAlive = true;
}


//! �f�X�g���N�^
SplitLowerEnemy::~SplitLowerEnemy()
{
	delete mcpCombiCol;
	delete mcpSpltterUP;
}

/* ----------- 
// �X�V���� */
void SplitLowerEnemy::Update()
{
	if (Combi) {
		mcMoveVector.x += mfSpeed; //! �X�s�[�h�����Z
		TotalMove += fabs(mfSpeed);
		if (TotalMove > 0.6f) {
			mfSpeed *= -1; //! �ړ��ʂ𔽓]������
			TotalMove = 0;
		}
	}
	else {
		if (Follow) {
			//! �v���C���[�ɑ΂��ĉE�ɂ���Ƃ�	
			FollowMove += fabs(mfSpeed);
			mcMoveVector.x += mfSpeed; //! �X�s�[�h����
			if (mcPlayer->GetVec().x < mcVec.x) {
				mfSpeed = -0.008f;
			}
			//! �v���C���[�ɑ΂��č��ɂ���Ƃ�
			else {
				mfSpeed = 0.008f;
			}
			if (FollowMove >= 3.0f) {
				Follow = false;
			}
		}
	}

	//! �摜�̂��䂤�̌����̃Z�b�g
	if (mfSpeed < 0) {
		mcpAnimsprite->SetYSplit(1);
	}
	else {
		mcpAnimsprite->SetYSplit(0);
	}

	if (mAlive) {
		bool Vibe = CAMERA->GetVibration();
		bool OnObj = mcpBoxCol->GetOnObj(); //! �I�u�W�F�N�g�̏�ɂ̂��Ă��邩���擾
		if (OnObj == true) {
			mTouchGraund = true;
		}
		//! ��ʐU�����Ă���Ƃ��͏d�͂������Ȃ�
		if (mTouchGraund == false && Vibe == false) {
			double ElapsedTime = CurrentTime - GravityTime;
			float Gravtiy = -ga * pow(ElapsedTime, 2) / 2.0f; //! �d�͂ɂ�鉺�����̗͂̌v�Z	�~���b�ł̌v�Z�Ȃ̂�1000�Ŋ���
			//! �d�͂̉e���̍ő�l�𒴂��Ȃ��悤�ɂ���
			if (Gravtiy >= 0.02f) {
				Gravtiy = 0.02f;
			}
			mcMoveVector.y += Gravtiy; //! �d�̗͂͂����Z
		}
		else {
			GravityTime = CurrentTime; //! �b�P�ʂ̍��̎��Ԃ��擾����
		}

		mcVec += mcMoveVector;              //! ���̃L�����N�^�[�ɂ������Ă���͂𑫂�
		if (Combi) {
			mcpCombiCol->SetMoveVec(mcMoveVector);  //! �����蔻��Ɏg���܂�
		}
		else {
			mcpSplitedCol->SetMoveVec(mcMoveVector);    //! �����蔻��Ɏg�����߂̏����Z�b�g	
		}
		CurrentTime += (1.0f / 60.0f);  //! �o�ߎ��Ԃ𑝂₷
		mcMoveVector.SetVector(0, 0);        //! ���̃L�����N�^�[�ɂ������Ă���͂��O�ɂ���
		mcpBoxCol->SetOnObj(false);         //! ��ɂ͏���Ă��Ȃ����Ƃɂ���@������false�ɂ�������Collsion���������肷��̂ł�����false�ɂ��܂�
	}

	//! ���������W���炭�����Ă鎞�̓����蔻��̒��S���W���v�Z����
	if (Combi) {
		mcCombiPos = Vector2(mcVec.x, mcVec.y - 0.04f); //! ���W
		mcpSpltterUP->SetDrawActiv(false);
	}
	else {
		mcSplitedColPos = Vector2(mcVec.x, mcVec.y -0.2f);
		MutekiCount++;
	}
	mcpSpltterUP->Update();
	
	if (!mAlive) {
		mcpSplitedCol->SetActiv(false);
		BaseEnemy::Destroy();
	}
}

/* ----------
// �`�揈�� */
void SplitLowerEnemy::Draw()
{
	GameObject::Draw();
	mcpSpltterUP->Draw();	
}

/* -------------------------- 
// �����蔻�菈����̏���  */
void SplitLowerEnemy::LastUpdate()
{
	if (Combi) {
		mcpSpltterUP->FixVec(mcVec);
	}
}

void SplitLowerEnemy::SetInitVec(Vector2 _vec)
{
	mcVec = _vec;
	mcpSpltterUP->FixVec(mcVec);
}

/* ---------------------------
// ��ɂ��Ă�G�̃Q�b�^�[ */
SplitUpperEnemy * SplitLowerEnemy::GetUpperEnemy()
{
	return mcpSpltterUP;
}

/* ----------------------- 
// �����蔻��̃Q�b�^�[ */
Box * SplitLowerEnemy::GetBoxCol()
{
	//! �������Ă����番���O�̓������Ԃ�
	if (Combi) {
		return mcpCombiCol;
	}
	//! �������Ă��Ȃ�������P�Ƃł̓�����Ԃ�
	return mcpSplitedCol;
}

bool SplitLowerEnemy::GetDeath()
{
	if (Death && !Deathed && Stinged) {
		Deathed = true;
		return true;
	}
	Stinged = false;

	//! �㑤�ɂ���ق��̓|���ꂽ�����Ԃ�
	return mcpSpltterUP->GetDeath();
}


//! ���̃I�u�W�F�N�g���h���ꂽ����
TailReaction SplitLowerEnemy::SetStingPower(float _Power, bool _Elect)
{
	if (Combi) {
		if (_Elect) {
			Reaction = TailReaction::TailReaction_StingStop;
			//! �h���ꂽ��
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.5f,0.5f));
			Combi = false; // ���Ŏh���ꂽ�番�􂷂�
			mcpSpltterUP->SetDrawActiv(true);
			mcpAnimsprite->SetTexture(TEXTURE(Tex_Splitter_Leg));
			mcpAnimsprite->ResetAnimCnt();
			mcpSpltterUP->SetCameraActiv(true);
			Follow = true;
		}
		else {
			if (_Power > STING_STRONG) {
				Reaction = TailReaction::TailReaction_StingStop;
				//! �h���ꂽ��
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.5f, 0.5f));
				Combi = false; // ���Ŏh���ꂽ�番�􂷂�
				mcpSpltterUP->SetDrawActiv(true);
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Splitter_Leg));
				mcpAnimsprite->ResetAnimCnt();
				mcpSpltterUP->SetCameraActiv(true);
				Follow = true;
			}
			else if (_Power > STING_MIDIUME) {
				Reaction = TailReaction::TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Splitter_Haziku,0.08f);
				EffMgr->PlayEffect(Hibana, mcVec, Vector2(0.5f, 0.5f));
			}
		}
	}
	else if(MutekiCount > 10){
		if (_Elect) {
			mAlive = false;
			Stinged = true;
			Reaction = TailReaction_Through;
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02,Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.5f, 0.5f));
		}
		else {
			if (_Power > STING_STRONG) {
				Reaction = TailReaction::TailReaction_StingStop;
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.5f, 0.5f));
				mAlive = false;
				Stinged = true;
			}
			else if (_Power > STING_MIDIUME) {
				Reaction = TailReaction::TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.07);
				EffMgr->PlayEffect(Hibana, Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.4f, 0.4f));
			}
			else {
				Reaction = TailReaction::TailReaction_Stop;
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.07);
				EffMgr->PlayEffect(Hibana, Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.4f, 0.4f));
			}
		}
	}
	return Reaction;
}

void SplitLowerEnemy::SetFollow(bool _state)
{
	if (!Combi) {
		Follow = _state;
		mcpAnimsprite->SetStopAnimation(true);
	}
}

/* ---------------------- 
// �d�͂̌v�Z�����܂�  */
void SplitLowerEnemy::ForceProces()
{
	
}

/* -----------
// �ړ��֐� */
void SplitLowerEnemy::Walk()
{
	
}

/* ----------------- 
// �|��鎞�̊֐� */
void SplitLowerEnemy::Destroy()
{
	
	if (Count <= 50)
	{
		//! �_�ł�����
		if ((Count % 20) <= 10) {
			SetDrawActiv(false);

		}
		else {
			mcpAnimsprite->SetColor(1.0f, 0.0f, 0.0f);
			SetDrawActiv(true);
		}
		Count++;
	}
	else
	{
		SetDrawActiv(false);	//! �摜������
		SetHitActiv(false);		//! �����蔻�������
	}
}
