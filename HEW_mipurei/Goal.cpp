#include "Goal.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "WinMain.h"

//! �R���X�g���N�^
Goal::Goal()
{
	//! �T�C�Y��摜�̐ݒ�
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Goal));//! ��荇�������d�@�̉摜
	mcpAnimsprite->SetAnimtionTable(10, 1);
	SetSize(1.5f,0.8f);

	PeaperStream = new AnimationHitObject;
	PeaperStream->SetCameraActiv(false);
	AnimationSprite * Sp = PeaperStream->GetAnimSprite();
	Sp->SetTexture(TEXTURE(Tex_PaperStream));
	Sp->SetAnimtionTable(1,12);
	PeaperStream->SetDrawActiv(false);
	PeaperStream->SetSize(DRAW_WIDTH,DRAW_HEIGHT);
	YSplit = 0;
	//! �����蔻��̐���
	mcpBox = new Box(mcVec, 0.4f,0.4f);
	mcpShape = mcpBox;
	
	mGoal = false;
	Hit = false;
	Hited = false;
	Start = false;
}

//! �f�X�g���N�^
Goal::~Goal()
{
	delete mcpBox;
	delete PeaperStream;
}

//! �X�V����
void Goal::Update()
{
	//! �S�[������O�̓A�j���[�V�������Ȃ�
	if (!Hit) {
		mcpAnimsprite->SetStopAnimation(true);
	}

	if (Hit&& !Hited) {
		mcpAnimsprite->SetStopAnimation(false);		
	}
	
	if (mcpAnimsprite->GetCurrentXSplit() == 9 && !Hited) {
		SoundMgr->PlaySE(SE_Goal, 0.6f);
		Hited = true;
		mcpAnimsprite->SetStopAnimation(true);
	}

	//! �t���[���܂�������
	if (Hited) {
		FrameCnt++;
	}

	if (FrameCnt % 8 == 0) {
		YSplit++;
		if (YSplit == 12) {
			YSplit = 0;
		}
		PeaperStream->GetAnimSprite()->SetYSplit(YSplit);
	}

	if (FrameCnt == 8) {
		EffMgr->PlayEffect(Hanabi_B, -0.4f,0.5f,0.8f,0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu,0.06f);
		PeaperStream->SetDrawActiv(true);
	}
	else if(FrameCnt == 18){
		EffMgr->PlayEffect(Hanabi_R, 0.4f, 0.7f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if(FrameCnt == 25){
		EffMgr->PlayEffect(Hanabi_G, 1.3f, 0.4f, 1.0f, 1.0f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 34) {
		EffMgr->PlayEffect(Hanabi_Y, -1.5f, -0.1f, 1.0f, 1.0f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 40) {
		EffMgr->PlayEffect(Hanabi_P, -0.6f, 0.6f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 44){
		EffMgr->PlayEffect(Hanabi_R, -1.4f, 0.0f, 1.0f, 1.0f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 55) {
		EffMgr->PlayEffect(Hanabi_B, 1.4f, -0.1f, 1.0f, 1.0f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 60) {
		EffMgr->PlayEffect(Hanabi_O, 0.5f, 0.6f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 68) {
		EffMgr->PlayEffect(Hanabi_B, -1.4f, 0.6f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 72) {
		EffMgr->PlayEffect(Hanabi_Y, 1.0f, 0.8f, 1.0f, 1.0f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 80) {
		EffMgr->PlayEffect(Hanabi_Y, 1.3f, 0.0f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 88) {
		EffMgr->PlayEffect(Hanabi_R, -1.4f, 0.2f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 92) {
		EffMgr->PlayEffect(Hanabi_B, 1.2f, 0.2f, 1.0f, 1.0f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}
	else if (FrameCnt == 100) {
		EffMgr->PlayEffect(Hanabi_P, 1.4f, 0.7f, 0.8f, 0.8f);
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu, 0.06f);
	}

	//! 6�b�ҋ@
	if (FrameCnt > 280) {
		mGoal = true;
	}
}

//! �`�揈��
void Goal::Draw()
{
	GameObject::Draw();
	PeaperStream->Draw();
}

//! �����蔻��̃Q�b�^�[
Box * Goal::GetBoxCol()
{
	return mcpBox;
}


bool Goal::GetGoal()
{
	return mGoal;
}

/*----------------------------  
// �K���̃��A�N�V������Ԃ� */
TailReaction Goal::ReturnReaction(float _power)
{
	TailReaction Reaction = TailReaction_None;

	if (_power > STING_STRONG) {
		Reaction = TailReaction_Sting;
		Hit = true;
	}
	else if (_power > STING_MIDIUME) {
		Reaction = TailReaction_Bounce;
	}
	else {
		Reaction = TailReaction_Stop;
	}
	return Reaction;
}

bool Goal::GetHit()
{
	return Hit;
}

//! �S�[���������Ƃɂ���t���O
void Goal::SetGoaled(bool _goaled)
{
	Hit = _goaled;
}


