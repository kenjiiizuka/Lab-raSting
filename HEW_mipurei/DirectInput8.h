#pragma once
#include "DIMouse.h"
#include "KeyBoard.h"

//! �����J�[�t��
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")


/* ==========================================================================
** DirectInput8�N���X(�V���O���g��)                                        **
** DirectInput8�ɂ��L�[�{�[�h�A�}�E�X�̓��͂Ȃǂ̋@�\���������N���X�ł�  **
** ����� : �ђ� ���i                    */



#define DI8 DirectInput8::GetIns()

class DirectInput8
{
public:	
	static void Create();                //! �����֐�
	static void Destroy();               //! �j���֐�
	static DirectInput8* GetIns();

	void Init(HINSTANCE _hinstance, HWND _hwnd); //! �������֐�
	void Update();						         //! �X�V�֐�
	void UnInit();						         //! �I���֐�

	DIMouse * mDIMouse;                          //! �}�E�X�N���X
	KeyBoard * mKeyBoard;                        //! �L�[�{�[�h�N���X
private:
	DirectInput8();                      //! �R���X�g���N�^
	~DirectInput8();                     //! �f�X�g���N�^
	
	static DirectInput8 * mcpInstance;   //! ���g

	LPDIRECTINPUT8 mlpDI8;               //! DirectInpoutObject
	HWND mCooperationhWnd;               //! ��������E�B���h�E�n���h��

};

