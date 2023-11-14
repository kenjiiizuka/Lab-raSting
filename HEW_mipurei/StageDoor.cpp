#include "StageDoor.h"
#include "SoundManager.h"
#include "TextureManager.h"

//! �R���X�g���N�^
StageDoor::StageDoor()
{
	CurrentHit = false;
	//! �����蔻��̐���
	ColSize = Vector2(0.2f,0.2f);
	SetSize(0.9f,0.9f);
	mcpBox = new Box(mcVec,ColSize.x, ColSize.y);
	mcpShape = mcpBox;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_StageDoor01));
	mcpAnimsprite->SetAnimtionTable(9, 2);
	FrameCnt = CloseFrameCnt = 0;
	mcpAnimsprite->SetStopAnimation(true); //! �A�j���[�V�������~�߂���ԂŃX�^�[�g
	mcpAnimsprite->SetYSplit(0);
	Open = false;
	State = Door_Closed; //! �ŏ��͕��؂������

	Abutton = false;
	AbuttonObj = new AnimationHitObject();
	AnimationSprite * ASp = AbuttonObj->GetAnimSprite();
	ASp->SetTexture(TEXTURE(Tex_AbuttonUI));
	ASp->SetAnimtionTable(4, 1);
	AbuttonObj->SetDrawActiv(false);

}

//! �f�X�g���N�^
StageDoor::~StageDoor()
{
	delete AbuttonObj;
	delete mcpBox;
}

//! �X�V����
void StageDoor::Update()
{
	int CurrentX = mcpAnimsprite->GetCurrentXSplit();
	if (CurrentHit) {
		//! ���Ă���Ƃ������؂��Ă��鎞�̂�
		if (State == Door_Close || State == Door_Closed) {
			if (State == Door_Close) {
				mcpAnimsprite->SetXSplit(8 - CurrentX);
			}
			State = Door_Open;		
		}
		//! A�{�^�����o���t���O�𗧂Ă�
		Abutton = true;
	}
	else {
		//! �J���Ă�Ƃ����J�������Ă���Ƃ��̂�
		if (State == Door_Open || State == Door_Opned) {
			if (State == Door_Open) {	
				mcpAnimsprite->SetXSplit(8 - CurrentX);		
			}
			State = Door_Close;		
		}
		Abutton = false;
	}
	
	switch (State)
	{
	case StageDoor::Door_Open:

		if (!Sound) {
			SoundMgr->PlaySE(SE_Door_Stage,0.1f);
			Sound = true;
		}
		//! �A�j���[�V�������n�߂�
		mcpAnimsprite->SetStopAnimation(false);
		mcpAnimsprite->SetYSplit(0);
		if (mcpAnimsprite->GetCurrentXSplit() == 8) {
			State = Door_Opned;
		}	
		break;

	case StageDoor::Door_Close:
		mcpAnimsprite->SetStopAnimation(false);
		mcpAnimsprite->SetYSplit(1);
		//! �Ō�̃R�}�ɂ�������Opened�ɂ���
		if (mcpAnimsprite->GetCurrentXSplit() == 8) {
			State = Door_Closed;
			Sound = false;
		}		
		break;

	case StageDoor::Door_Opned:
		//! �A�j���[�V��������߂�
		mcpAnimsprite->ResetAnimCnt();
		mcpAnimsprite->SetYSplit(1);
		mcpAnimsprite->SetStopAnimation(true); 
		break;

	case StageDoor::Door_Closed:
		//! �A�j���[�V��������߂�
		mcpAnimsprite->ResetAnimCnt();
		mcpAnimsprite->SetYSplit(0);
		mcpAnimsprite->SetStopAnimation(true);
		break;
	}


	if (Abutton) {
		AbuttonObj->SetDrawActiv(true);
		Vector2 Apos((mcVec.x), (mcVec.y + msSize.y / 2.0f));
		AbuttonObj->SetVec(Apos);
	}
	else {
		AbuttonObj->SetDrawActiv(false);
	}	
}

void StageDoor::Draw()
{
	GameObject::Draw();
	AbuttonObj->Draw();
}

//! �����蔻��̃Q�b�^�[
Box * StageDoor::GetBoxCol()
{
	return mcpBox;
}

//! �����蔻��̃Z�b�^�[
void StageDoor::SetColSize(float _x, float _y)
{
	ColSize = Vector2(_x, _y);
	mcpBox->SetSize(_x, _y);
}

//! �Q�b�^�[ �Z�b�^�[

void StageDoor::SetHit(bool _state)
{
	CurrentHit = _state;
}

bool StageDoor::GetHit()
{
	return CurrentHit;
}
