#include "PressMachine.h"
#include "TextureManager.h"
#include "SoundManager.h"

//! �R���X�g���N�^
PressMachine::PressMachine()
{
	//! �T�C�Y�̃Z�b�g
	SetSize(1.4f,1.0f);
	
	//! �摜�̃Z�b�g
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PressMachine));
	mcpAnimsprite->SetAnimtionTable(13,1);

	//! �����蔻��̐���
	mColSize.x = 0.8f;
	mColSize.y = 0.2f;
	mBoxCol = new Box(ColPos, mColSize.x, mColSize.y);

	ColPos.x = mcVec.x;
	ColPos.y = mcVec.y - 0.4f;

	Stop = false;
	StopCnt = 0;

	mTag = Tag_Press;
}

//! �f�X�g���N�^
PressMachine::~PressMachine()
{
	delete mBoxCol;
}

//! �X�V����
void PressMachine::Update()
{
	Gimmick::Update();

	ColPos.x = mcVec.x;
	ColPos.y = mcVec.y - 0.4f;

	int AnimX = mcpAnimsprite->GetCurrentXSplit();
	if (mActuation) {
		//! ���d�@���`���[�W����āA�A�j���[�V�������Ō�̃R�}�ɂ������炵�΂炭�~�܂�
		if (AnimX == 12) {
			Stop = true;
			StopCnt = 0;
		}
	}
	//! �~�܂��Ă��鎞
	if (Stop) {
		StopCnt++;
		mcpAnimsprite->SetStopAnimation(true);
	
		//! 5�b�~�܂�
		if (StopCnt > (60 * 5)) {
			Stop = false;
			mActuation = false;
			mcpAnimsprite->SetStopAnimation(false);
		}
	}
	//! �����Ă鎞
	else {
		if (AnimX == 12) { mcpAnimsprite->ResetAnimCnt();}
		mBoxCol->SetActiv(false);
		if (AnimX == 4 || AnimX == 5) {
			mBoxCol->SetActiv(true);
		}

		if (AnimX == 4 && Sound) {
			SoundMgr->PlaySE(SE_Press, 0.4f);
			Sound = false;
		}

		if (AnimX == 5) { Sound = true; }
	}
}

//! �`�揈��
void PressMachine::Draw()
{
	GameObject::Draw();

}

Box * PressMachine::GetBoxCol()
{
	return mBoxCol;
}


