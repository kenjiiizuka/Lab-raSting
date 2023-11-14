#include "DIMouse.h"
#include "WinMain.h"
#include <math.h>


//--------------------------
//! �R���X�g���N�^
//! �ϐ��̏�����
DIMouse::DIMouse()
{
	mlpMouse = NULL;
	mMouseSpeed = 2;    //! �X�s�[�h�͂Q
	mDefoultSpeed = 0;

	//! �}�E�X�X�e�[�g�\���̂�����������������������

}


DIMouse::~DIMouse()
{

}

/* -----------------------------------------
// �}�E�X�̏������֐�                     //
// DirectInput8�ɂ�鏉�������s���Ă��܂� //
// ����x�����g�p���Ă�������             //
// -------------------------------------- */
void DIMouse::Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd)
{

	mHwnd = _hwnd;

	HRESULT ret;

	//! �Q�[���J�n�O�̃X�s�[�h���擾
	SystemParametersInfo(SPI_GETMOUSESPEED, 0, &mDefoultSpeed, 0);

	//! �}�E�X�f�o�C�X�̍쐬
	ret = _mlpDI8->CreateDevice(GUID_SysMouse, &mlpMouse, NULL);
	if (FAILED(ret)) {
	//	//! �쐬�Ɏ��s
	//	MessageBox(NULL, L"�}�E�X�f�o�C�X�̍쐬�Ɏ��s", L"�G���[����", MB_OK);
	}

	//! �f�o�C�X�̃t�H�[�}�b�g�ݒ�
	ret = mlpMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(ret)) {
		//! �쐬�Ɏ��s
	//	MessageBox(NULL, L"�f�o�C�X�̃t�H�[�}�b�g�̐ݒ�Ɏ��s", L"�G���[����", MB_OK);
	}

	//! �������[�h�̐ݒ�
	ret = mlpMouse->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		//! �������[�h�̐ݒ�Ɏ��s
	//	MessageBox(NULL, L"�������[�h�̐ݒ�Ɏ��s", L"�G���[����", MB_OK);
	}

	//! �f�o�C�X�̐���J�n
	ret = mlpMouse->Acquire();
	if (FAILED(ret)) {
		//! �f�o�C�X����J�n�Ɏ��s
		//MessageBox(NULL, L"�f�o�C�X����J�n�Ɏ��s", L"�G���[����", MB_OK);
	}

	//! �|�[�����O�J�n
	ret = mlpMouse->Poll();
	if (FAILED(ret)) {
		//! �|�[�����O�J�n�Ɏ��s
		//MessageBox(NULL, L"�|�[�����O�J�n�Ɏ��s", L"�G���[����", MB_OK);
	}
}

/*--------------------------------------------------------------
// �}�E�X�̍X�V�֐�                                           //
// �t���[���}�E�X�̓��͂���W�A�}�E�X�̏�Ԃ��X�V���Ă��܂�   //
// ���� : �}�E�X�̃X�s�[�h                                    //
// �����t���[���g�p���Ă�������                               //
// ---------------------------------------------------------- */
void DIMouse::Update()
{
	//! �O�t���[���̃}�E�X�̏���ۑ�
	mDIPrevMouseState = mDICurrentMouseState;

	//! ���}�E�X�̏�Ԃ̎擾
	HRESULT ret = mlpMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mDICurrentMouseState);
	if (FAILED(ret)) {
		if ((ret == DIERR_INPUTLOST) || (ret == DIERR_NOTACQUIRED)) {
			mlpMouse->Acquire();
		}
		else {
		//	MessageBox(NULL, L"�}�E�X�̏�Ԃ��擾�ł��܂���", L"�G���[����", MB_OK);
		}
	}

	//���t���[�����K�v���Ȃ��̂łǂ��ɂ�������
	//! Mouse�̃X�s�[�h�̃Z�b�g
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)mMouseSpeed, 0);
}

/* -----------------------------------------------------------------------------------
// �}�E�X�̉���֐�                                                                 //
// DirectInput8�ɂ�������s���Ă��܂�                                             //
// ��MouseInit�֐������悤������K���v���O�����̏I���Ɉ�x�����g�p���Ă�������    //
// -------------------------------------------------------------------------------- */
void DIMouse::UnInit()
{
	//! �Q�[���N���O�̃X�s�[�h�ɖ߂�
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)mDefoultSpeed, 0);
	mlpMouse->Unacquire(); //! �f�o�C�X����I��
	mlpMouse->Release();   //! �f�o�C�X�̉��
}


// �}�E�X�̃X�s�[�h�̃Z�b�^�[
void DIMouse::SetMouseSpeed(int _mousespeed)
{
	mMouseSpeed = _mousespeed;
}


/* ---------------------------------------
// �}�E�X��1�t���[���̈ړ��ʂ�Ԃ��֐�  //
// �߂�l x,y�����̈ړ���               //
// ------------------------------------ */
Vector2 DIMouse::GetMouseVelocity()
{
	return Vector2((float)mDICurrentMouseState.lX, (float)mDICurrentMouseState.lY * -1);
}

Vector2 DIMouse::GetMouseVelocityNonFix()
{
	return Vector2((float)mDICurrentMouseState.lX, (float)mDICurrentMouseState.lY);
}


/* --------------------------------------------
// �}�E�X�̌��݈ʒu(�`����W)�̎擾�֐�      //
// �߂�l : �}�E�X��x,y���W�@�@�@�@�@�@�@�@�@//
// ----------------------------------------- */
FLOAT2 DIMouse::GetMousePos()
{

	POINT pos1;
	FLOAT2 pos2;

	GetCursorPos(&pos1);         //! �}�E�X�J�[�\���̈ʒu���擾
	ScreenToClient(mHwnd, &pos1); //! �E�B���h�E��̍��W�ɕϊ�

	float ScreenHalfWidth = (SCREEN_WIDTH / 2) / 1.925; //! ��ʂ̔䗦�ɕ␳�������Ă��邽�߂�����ɂ�������
	float ScreenHalfHeight = SCREEN_HEIGHT / 2;

	pos2.x = ((pos1.x - ScreenHalfWidth) / ScreenHalfWidth) - 0.925f; //! X���W�l�� -1.3�`1.3 �ɕϊ�����	
	pos2.y = (ScreenHalfHeight - pos1.y) / ScreenHalfHeight;          //! Y���W�l�� -1.0�`1.0 �ɕϊ�����

	return pos2;
}



/* --------------------------------------------
// �}�E�X�̌��݈ʒu(�`����W)�̎擾�֐�      //
// �߂�l : �}�E�X��x,y���W�@�@�@�@�@�@�@�@�@//
// ----------------------------------------- */
Vector2 DIMouse::GetMousePosVec()
{



	POINT pos1;

	GetCursorPos(&pos1);         //! �}�E�X�J�[�\���̈ʒu���擾
	ScreenToClient(mHwnd, &pos1); //! �E�B���h�E��̍��W�ɕϊ�

	float ScreenHalfWidth = (SCREEN_WIDTH / 2) / 1.925; //! ��ʂ̔䗦�ɕ␳�������Ă��邽�߂�����ɂ�������
	float ScreenHalfHeight = SCREEN_HEIGHT / 2;

	float x = ((pos1.x - ScreenHalfWidth) / ScreenHalfWidth) - 0.925f; //! X���W�l�� -1.3�`1.3 �ɕϊ�����	
	float y = (ScreenHalfHeight - pos1.y) / ScreenHalfHeight;          //! Y���W�l�� -1.0�`1.0 �ɕϊ�����

	return Vector2(x, y);
}



/* -------------------------------------------
// �}�E�X�̃E�B���h�E��̍��W�̎擾�֐�     //
// �߂�l : �}�E�X�̃E�B���h�E��̍��Wx,y   //
// ---------------------------------------- */
FLOAT2 DIMouse::GetMouseWindowPos()
{
	POINT pos1;
	FLOAT2 pos2;

	GetCursorPos(&pos1); //! �}�E�X�J�[�\���̈ʒu���擾
	ScreenToClient(mHwnd, &pos1); //! �E�B���h�E��̍��W�ɕϊ�

	return FLOAT2(pos1.x, pos1.y);
}

/* ------------------------------------------
// �}�E�X�ɍ��W(�`����W)���Z�b�g����֐�  //
// ���� : x���W , y���W                    //
// --------------------------------------- */
void DIMouse::SetMousePos(float _x, float _y)
{
	float ScreenHalfWidth = (SCREEN_WIDTH / 2) / 1.925; //! ��ʂ̔䗦�ɕ␳�������Ă��邽�߂�����ɂ�������
	float ScreenHalfHeight = SCREEN_HEIGHT / 2;

	//! �����Ŏw�肳�ꂽ�l���E�B���h�E��̍��W�ɕϊ�
	float x = _x * ScreenHalfWidth + (SCREEN_WIDTH / 2);
	float y = ScreenHalfHeight - fabs(_y * ScreenHalfHeight);

	//! �J�[�\���̈ʒu���Z�b�g�@��Y���W���Ȃ���23�������ʒu�ɐݒu�����̉��}���u�Ƃ��� [+ 23] ���Ă��܂��I�I�I�I
	SetPhysicalCursorPos(fabs(x), fabs(y + 23));
}

/* -------------------------------------------
// �}�E�X�̃{�^���̓��͂̃g���K�[�擾�֐�   //
// ���� : �}�E�X�̃{�^���̎��              //
// �߂�l : ���̗͂L��                      //
// ---------------------------------------- */
bool DIMouse::GetMouseButtonTrigger(eMouseButton _button)
{
	return (mDICurrentMouseState.rgbButtons[_button] & 0x80) && !(mDIPrevMouseState.rgbButtons[_button] & 0x80);
}

/* -------------------------------------------
// �}�E�X�̃{�^���̓��͂̃v���X�擾�֐�     //
// ���� : �}�E�X�̃{�^���̎��              //
// �߂�l : ���̗͂L��                      //
// ---------------------------------------- */
bool DIMouse::GetMouseButtonPress(eMouseButton _button)
{
	return mDICurrentMouseState.rgbButtons[_button] & 0x80;
}

/* ------------------------------------------------------------------------
// �}�E�X�̃{�^�����������u�Ԃ̍��W���擾����֐�                        //
// ���� : �}�E�X�̃{�^���̎��                                           //
// �߂�l : �{�^���������ꂽ���W�@������Ă��Ȃ��ꍇ��-8000��������܂�  //
// --------------------------------------------------------------------- */
FLOAT2 DIMouse::GetMouseButtonTriggerPos(eMouseButton _button)
{
	if ((mDICurrentMouseState.rgbButtons[_button] & 0x80)
		&& !(mDIPrevMouseState.rgbButtons[_button] & 0x80))
	{
		return GetMousePos();
	}

	//! NULL�Ȃǂ�0�Ɠ�����ʓ��̍��W�͈̔͂ɂ���l��Ԃ���
	//�����蔻��ȂǂŌ���Ĕ��肵�Ă��܂��ăo�O�̌����ɂȂ肻���Ȃ̂�-8000��Ԃ��܂�
	return FLOAT2(-8000, -8000);
}


/* ------------------------------------------------------------------------
// �}�E�X�̃{�^���������Ă���ԍ��W���擾����֐�                        //
// ���� : �}�E�X�̃{�^���̎��                                           //
// �߂�l : �{�^���������ꂽ���W�@������Ă��Ȃ��ꍇ��-8000��������܂�  //
// --------------------------------------------------------------------- */
FLOAT2 DIMouse::GetMouseButtonPressPos(eMouseButton _button)
{
	if ((mDICurrentMouseState.rgbButtons[_button] & 0x80)) {
		return GetMousePos();
	}

	//! NULL�Ȃǂ�0�Ɠ�����ʓ��̍��W�͈̔͂ɂ���l��Ԃ���
	//�����蔻��ȂǂŌ���Ĕ��肵�Ă��܂��ăo�O�̌����ɂȂ肻���Ȃ̂�-8000��Ԃ��܂�
	return FLOAT2(-8000, -8000);

}



