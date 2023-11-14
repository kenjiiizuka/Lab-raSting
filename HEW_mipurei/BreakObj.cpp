#include "BreakObj.h"
#include "TextureManager.h"
#include "SoundManager.h"

//! �R���X�g���N�^
BreakObj::BreakObj()
{
	mBreak = false;
	mBreaked = false;
	msSize = {0.6f,0.6f};
	mcpBox = new Box(mcVec,0.2f, 0.6f);
	mcpShape = mcpBox;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Galss));
	mcpAnimsprite->SetAnimtionTable(14,1);
	mcpAnimsprite->SetStopAnimation(true);
	Cnt = 0;
	Arufa = 1.0f;
}

//! �f�X�g���N�^
BreakObj::~BreakObj()
{
	delete mcpBox;
}

//! �X�V����
void BreakObj::Update()
{
	if (mBreak && !mBreaked) {
		mcpAnimsprite->SetStopAnimation(false);
		Cnt++;
		//! �Ō�̃A�j���[�V�����܂ł�������~�߂ď��X�ɏ���
		if (Cnt >= (8 * 14)) {
			mcpAnimsprite->SetStopAnimation(true);
			//! �����ɂ��Ă���
			Arufa -= 0.01f;
			mcpAnimsprite->SetArufa(Arufa);
			if (Arufa < 0 ) {
				Arufa = 0;
				mBreaked = true;
				SetDrawActiv(false);
			}
		}
	}
}

//! �`�揈��
void BreakObj::Draw()
{
	GameObject::Draw();
}

Box * BreakObj::GetBoxCol()
{
	return mcpBox;
}

//! �h���ꂽ�Ƃ��̃��A�N�V������Ԃ��֐�
TailReaction BreakObj::ReturnReaction(float _power)
{
	TailReaction Reaction = TailReaction_None;
	if (_power >STING_STRONG) {
		mBreak = true;
		Reaction = TailReaction_StingStop;
		SetHitActiv(false);
		SoundMgr->PlaySE(SE_Glass_Break,0.1f);
	}
	else if (_power > STING_MIDIUME) {
		Reaction = TailReaction_Stop;
		SoundMgr->PlaySE(SE_Glass_Hajiku,0.1f);
	}
	

	return Reaction;
}

bool BreakObj::GetBreaked()
{
	return mBreak;
}
