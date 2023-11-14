#include "Dynamo.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "SoundManager.h"

Dynamo::Dynamo()
{
	mTag = Tag_Dynamo; //! �^�O�̃Z�b�g
	
	mCharge = false;
	mChargeFin = false;
	Doing = false;
	//! �����蔻��N���X�̐���
	msSize = FLOAT2(0.4f, 0.4f);
	ColSize = Vector2(0.26f, 0.18f);
	mcpBox = new Box(mcVec, ColSize.x, ColSize.y);
	mcpShape = mcpBox;

	//! �`�悽�߂̏��̃Z�b�g
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Dynamo01));
	mcpAnimsprite->SetAnimtionTable(1, 1);
}



//! �f�X�g���N�^
Dynamo::~Dynamo()
{
	delete mcpBox;
}

//! �X�V����Update
void Dynamo::Update()
{
	mChargeFin = false;
	//! �`���[�W�����ꂽ��G�t�F�N�g���o��
	if (mCharge) {
		EffMgr->PlayEffect(DaynamoEffect,mcVec.x,mcVec.y,1.0f,1.0f);
		Doing = true;
		mCharge = false; //! �{���͑Ή����Ă���M�~�b�N�ɍ쓮���邱�Ƃ�`����
		SoundMgr->PlaySE(SE_Dynamo_Charge,0.1f);
	}
	//! �G�t�F�N�g���I��������`���[�W�����ɂ���
	else if (EffMgr->GetState(DaynamoEffect) == EffectState::End && Doing) {
		mChargeFin = true; 
		Doing = false;
		mcpBox->SetActiv(false);
	}
}

void Dynamo::Draw()
{
	GameObject::Draw();
}

/* -------------------------------------
//! �h���ꂽ��Ƀ��A�N�V������Ԃ��֐� */
TailReaction Dynamo::ReturnReaction(float _power, bool _elect)
{	
	TailReaction Reaction; //! ���A�N�V������Ԃ�
	if (STING_STRONG < _power) {
		Reaction = TailReaction_StingDeep; //! �[���h����
		SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
	}
	else if (STING_MIDIUME < _power) {
		Reaction = TailReaction_Sting;     //! �h����
		SoundMgr->PlaySE(SE_Timpiller_Sasaru,0.07f);
	}
	else {		
		Reaction = TailReaction_StingStop;      //! �~�܂�
		SoundMgr->PlaySE(SE_Dynamo_NotSting, 0.04f);
	}

	return Reaction;
}

void Dynamo::SetChrage(bool _state)
{
	mCharge = _state;
}

Box * Dynamo::GetBoxCol()
{
	return mcpBox;
}

bool Dynamo::GetChargeState()
{
	//! �`���[�W���������ċ�����true��Ԃ�
	if (mChargeFin) {
		return true;
	}
	return false;
}
