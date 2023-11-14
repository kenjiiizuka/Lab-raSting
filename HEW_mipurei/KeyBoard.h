#pragma once
#include <dinput.h>
#include <Windows.h>

/* ----------------------------------------------------------------------
// �L�[�{�[�h�N���X                                                    //
// �L�[�{�[�h�̓��͂̎擾���ł��܂�                                    //
// ����� : �ђ� ���i                                                  */
class KeyBoard
{
public:
	KeyBoard(); //! �R���X�g���N�^
	~KeyBoard(); //! �f�X�g���N�^

	void Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd); //! ����������
	void Update();                                                       //! �X�V����
	void UnInit();                                                       //! �I������
	
	bool GetKeyTrigger(int _key);                           //! �L�[�{�[�h�̃g���K�[�擾
	bool GetKeyPress(int _key);                             //! �L�[�{�[�h�̃v���X�擾

private:
	LPDIRECTINPUTDEVICE8 mlpDIKeyBoard; //! �L�[�{�[�h�f�o�C�X
	BYTE mPrevKeyState[256];            //! �O�t���[���̃L�[�{�[�h�̏��
	BYTE mCurrentKeyState[256];         //! �����_�̃t���[���̃L�[�{�[�h�̏��
 
	HWND mHwnd; //! ��������E�B���h�E�n���h��
};

