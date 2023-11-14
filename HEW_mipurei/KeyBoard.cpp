#include "KeyBoard.h"





KeyBoard::KeyBoard()
{
	mlpDIKeyBoard = NULL;

}

KeyBoard::~KeyBoard()
{

}


//! �L�[�{�[�h�̏���������
void KeyBoard::Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd)
{
	HRESULT ret;

	mHwnd = _hwnd;

	//! �f�o�C�X�̍쐬
	ret = _mlpDI8->CreateDevice(GUID_SysKeyboard,&mlpDIKeyBoard,NULL);
	//if (FAILED(ret)) {
	//	//! �쐬�Ɏ��s
	//	MessageBox(NULL, L"�L�[�{�[�h�f�o�C�X�̍쐬�Ɏ��s", L"�G���[����", MB_OK);
	//}

	//! �f�o�C�X�̃t�H�[�}�b�g�ݒ�
	ret = mlpDIKeyBoard->SetDataFormat(&c_dfDIKeyboard);
	//if (FAILED(ret)) {
	//	//! �쐬�Ɏ��s
	//	MessageBox(NULL, L"�f�o�C�X�̃t�H�[�}�b�g�̐ݒ�Ɏ��s", L"�G���[����", MB_OK);
	//}

	//! �������[�h�̐ݒ�
	ret = mlpDIKeyBoard->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	//if (FAILED(ret)) {
	//	//! �������[�h�̐ݒ�Ɏ��s
	//	MessageBox(NULL, L"�������[�h�̐ݒ�Ɏ��s", L"�G���[����", MB_OK);
	//}

	//! �f�o�C�X�̐���J�n
	ret = mlpDIKeyBoard->Acquire();
	//if (FAILED(ret)) {
	//	//! �f�o�C�X����J�n�Ɏ��s
	//	MessageBox(NULL, L"�f�o�C�X����J�n�Ɏ��s", L"�G���[����", MB_OK);
	//}
}

//! �L�[�{�[�h�̍X�V����
void KeyBoard::Update()
{
	for (int num = 0; num < 256; num++) {
		mPrevKeyState[num] = mCurrentKeyState[num];
	}
	HRESULT hr;
	// �L�[�{�[�h�f�o�C�X�̃Q�b�^�[
	hr = mlpDIKeyBoard->GetDeviceState(256, mCurrentKeyState);

	//! ��Ԃ̎擾�Ɏ��s�����ꍇ�͍ēx�f�o�C�X�̐�����J�n����
	if (hr != S_OK) {
		//! �f�o�C�X�̃t�H�[�}�b�g�ݒ�
		hr = mlpDIKeyBoard->SetDataFormat(&c_dfDIKeyboard);

		//! �������[�h�̐ݒ�
		hr = mlpDIKeyBoard->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		
		//! �f�o�C�X�̐���J�n
		hr = mlpDIKeyBoard->Acquire();

	}
}

//! �L�[�{�[�h�̏I������
void KeyBoard::UnInit()
{
	mlpDIKeyBoard->Unacquire(); //! �f�o�C�X����I��
	mlpDIKeyBoard->Release();   //! �f�o�C�X�̉��
}

//! �L�[�{�[�h�̃g���K�[�擾
bool KeyBoard::GetKeyTrigger(int _key)
{
	return !(mPrevKeyState[_key] & 0x80) && (mCurrentKeyState[_key] & 0x80);
}

//! �L�[�{�[�h�̃v���X�擾
bool KeyBoard::GetKeyPress(int _key)
{
	return (mCurrentKeyState[_key] & 0x80);
}
