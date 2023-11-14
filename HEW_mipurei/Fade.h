#pragma once
#include "StaticObject.h"

/* ==================================================================== ** 
** Fade�N���X                                                           **
** �����o�֐�FadeIn(),FadeOut(),���g���ƃt�F�[�h�C���A�A�E�g���ł��܂��B**
** ==================================================================== */

class Fade
{
public:
	// �t�F�[�h�̏�Ԃ��Ӗ�����񋓌^
	enum {
		NONE,
		FADEIN,
		FADEOUT
	};
	Fade();               //! �R���X�g���N�^
	~Fade();              //! �f�X�g���N�^
	void Update();		  //! �X�V����
	void Draw();		  //! �`�揈��
	void FadeIn();		  //! �t�F�[�h�C���̊J�n�֐�
	void FadeOut();		  //! �t�F�[�h�A�E�g�̊J�n�֐�
	int  GetFadeState();  //! ���݂̃t�F�[�h�̏�Ԃ�Ԃ��֐�
private:
	StaticObject * mcpFadePanel;  //! �t�F�[�h�Ɏg���I�u�W�F�N�g 
	float mAlpha;				  //! �����x
	int mState;					  //! f�t�F�[�h�̏�Ԃ𔻒f����ϐ�

};
