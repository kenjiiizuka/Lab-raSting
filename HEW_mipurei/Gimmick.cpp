#include "Gimmick.h"
#include "TextureManager.h"
#include "EffectManager.h"

//! �R���X�g���N�^
Gimmick::Gimmick()
{
	//! ��`�̓����蔻��̐���
	mcpBoxCol = new Box(mcVec, msSize.x, msSize.y);
	mcpShape = mcpBoxCol;
	//mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_nuko04));
	//mcpAnimsprite->SetAnimtionTable(1, 1);
	mActuation = false;
	mDoing = false;
}

//! �f�X�g���N�^
Gimmick::~Gimmick()
{
	delete mcpBoxCol;
}

//! �X�V����
void Gimmick::Update()
{
	//! ���d�@���`���[�W���ꂽ�����f����
	if (mcpDynamo->GetChargeState() && !mDoing) {
		//! �{���͔z���ɓd�C������鉉�o�����Ă���
		mActuation = true; //! �`���[�W���ꂽ��쓮������
	}
}


Box * Gimmick::GetBoxCol()
{
	return mcpBoxCol;
}

//! ���d�@�̃Z�b�g�֐�
void Gimmick::SetDynamo(Dynamo * _dynamo)
{
	mcpDynamo = _dynamo;
}


