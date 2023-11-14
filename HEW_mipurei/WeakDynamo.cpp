#include "WeakDynamo.h"
#include "Camerah.h"
#include "EffectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

//! �R���X�g���N�^
WeakDynamo::WeakDynamo()
{
	mBreak = false;
	mOverheat = false;
	mCoolDown = false;
	g = b = 1.0f;
	mTag = Tag_WeakDynamo;
	
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Dynamo02));
}


//! �X�V����
void WeakDynamo::Update()
{
	mChargeFin = false;
	//! �`���[�W�����ꂽ��G�t�F�N�g���o��
	if (mCharge) {
		EffMgr->PlayEffect(DaynamoEffect, mcVec.x, mcVec.y,1.0f,1.0f);
		SoundMgr->PlaySE(SE_Dynamo_Charge,0.1f);
		Doing = true;
		mCharge = false; //! �{���͑Ή����Ă���M�~�b�N�ɍ쓮���邱�Ƃ�`����
	}
	//! �G�t�F�N�g���I��������`���[�W�����ɂ���
	else if (EffMgr->GetState(DaynamoEffect) == EffectState::End && Doing) {
		mChargeFin = true;
		Doing = false;
		mcpBox->SetActiv(false);
		
	}

	//! ����t���O�����������荇�����Ԃ����ď���
	if (mBreak && ! mCoolDown) {
		mCharge = false;
		g = b -= 0.01f; //! �Ԃ�����
		//! �O�ȉ��̒l�ɂȂ����甭�d�@������
		if (g <= 0.0f) {
			g = b = 0.0f;
			mOverheat = true;
			mCoolDown = true;
		}				
	}
	//! �N�[���_�E��
	else if (mCoolDown) {
		g = b += 0.01f; //! ���Ƃ̐F�ɖ߂�
		if (g >= 1.0f) {
			mBreak = false;
			mCoolDown = false;
		}
	}
	//! �F�Ɠ����x���Z�b�g����
	mcpAnimsprite->SetColor(1.0f, g, b);
}


//! �K�����h���������̃��A�N�V������Ԃ��֐�
TailReaction WeakDynamo::ReturnReaction(float _power, bool _elect)
{
	TailReaction Reaction = TailReaction_None; 

	if (_elect) {
		if (_power > STING_STRONG) {
			Reaction = TailReaction_StingDeep; //! ���Ő[���h����܂�
			CAMERA->StartVibration(3); //! ��ʐU��
			mBreak = true;
			mCoolDown = false;
			SoundMgr->PlaySE(SE_Dynamo_OverHeat, 0.1f);
	}
		else if (_power > STING_MIDIUME) {
			Reaction = TailReaction_StingStop;
		}
		else {
			Reaction = TailReaction_StingStop;
		}
	}
	else {
		if (_power > STING_STRONG) {
			Reaction = TailReaction_StingDeep; //! ���Ő[���h����܂�
			CAMERA->StartVibration(3); //! ��ʐU��
			mBreak = true;
			mCoolDown = false;
			SoundMgr->PlaySE(SE_Dynamo_OverHeat, 0.1f);
		}
		else if (_power > STING_MIDIUME) {
			Reaction = TailReaction_StingDeep;
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.07f);
		}
		else {
			Reaction = TailReaction_StingStop;
		}
	}
	return Reaction;
}

//! �I�[�o�[�q�[�g�����ǂ�����Ԃ�
bool WeakDynamo::Overheat()
{
	if (mOverheat) {
		mOverheat = false;
		return true;
	}
	return false;
}

/* --------------- 
// �`���[�W�֐� */
void WeakDynamo::SetChrage(bool _state)
{
	if (!mBreak) {
		mCharge = _state;
	}
}
