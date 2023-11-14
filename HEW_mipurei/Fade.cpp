#include "Fade.h"
#include "TextureManager.h"

// �R���X�g���N�^
Fade::Fade()
{
	mState = NONE;                   //! �����̏�Ԃ͂Ȃɂ����Ă��Ȃ����
	mcpFadePanel = new StaticObject; //! �t�F�[�h�Ɏg���p�̃I�u�W�F�N�g�𐶐�
	mcpFadePanel->SetCameraActiv(false);
	mcpFadePanel->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	mcpFadePanel->SetSize(3.85f,2.0f);
	mAlpha = 1.0f;	
}

// �f�X�g���N�^
Fade::~Fade()
{
	delete mcpFadePanel;
}

// �X�V����
void Fade::Update()
{
	const float AlphaSpeed = 0.015f; // �����x���t���[�����ɕω�������l

	//! ��Ԗ��Ƀt�F�[�h�C���A�t�F�[�h�A�E�g�̏������s��
	switch (mState)
	{
	case FADEIN:
		mAlpha-= AlphaSpeed ;
		if (mAlpha <= 0.0f) {
			mState = NONE;
		}
		mcpFadePanel->GetSprite()->SetArufa(mAlpha);
		break;

	case FADEOUT:
		mAlpha += AlphaSpeed ;
		if (mAlpha >= 1.0f) {
			mState = NONE;
		}
		mcpFadePanel->GetSprite()->SetArufa(mAlpha);
		break;
	}
}

//! �`�揈��
void Fade::Draw()
{
	mcpFadePanel->Draw();
}

//! �t�F�[�h�C���̊J�n�֐�
void Fade::FadeIn()
{
	if (mState == NONE)
	mState = FADEIN;
}

//! �t�F�[�h�A�E�g�̊J�n�֐�
void Fade::FadeOut()
{
	if(mState == NONE)
	mState = FADEOUT;
}

//! ���݂̃t�F�[�h�̏�Ԃ��擾����֐�
int Fade::GetFadeState()
{
	return mState;
}
