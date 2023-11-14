#include "DirectInput8.h"
#include "Game.h"

#define DIRECTINPUT_VERSION 0x0800          //! DirectInput�̃o�[�W�����w��

DirectInput8 * DirectInput8::mcpInstance = nullptr; 

//! �����֐�
void DirectInput8::Create()
{
	if (mcpInstance == nullptr) {mcpInstance = new DirectInput8();}
}

//! �j���֐�
void DirectInput8::Destroy()
{
	delete mcpInstance;
}

//! ���̂̎擾�֐�
DirectInput8* DirectInput8::GetIns()
{
	return mcpInstance;
}

//-----------------------------------------------
//! DirectInput8�������֐�
//! �}�E�X��L�[�{�[�h�̏��������s��
void DirectInput8::Init(HINSTANCE _hinstance, HWND _hwnd)
{
	//! ��������E�B���h�E�n���h���̃Z�b�g
	mCooperationhWnd = _hwnd;

	//! DirectInout8�̏�����
	HRESULT ret = DirectInput8Create(_hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mlpDI8, nullptr);
	if (FAILED(ret)) {
		//! �쐬�Ɏ��s
	//	MessageBox(NULL, L"DirectInput8�I�u�W�F�N�g�̍쐬�Ɏ��s", L"�G���[����", MB_OK);
	}

	//! �}�E�X�̏�����
	mDIMouse->Init(mlpDI8,_hinstance,mCooperationhWnd);
	//! �L�[�{�[�h�̏�����
	mKeyBoard->Init(mlpDI8, _hinstance, mCooperationhWnd);

}

//-----------------------------------------------
//! �X�V����
//! �}�E�X�A�L�[�{�[�h�̍X�V���s��
void DirectInput8::Update()
{
	if (GameIns->GetOperation() == Mouse) {
		mDIMouse->Update();
	}

	mKeyBoard->Update();
}

//-----------------------------------------------
//! �I������
//! �}�E�X�A�L�[�{�[�h�ADirectInput8�̏I������
void DirectInput8::UnInit()
{

	mKeyBoard->UnInit();
	mDIMouse->UnInit();
	mlpDI8->Release();
}


//-----------------------------------------------
//! �R���X�g���N�^
//! �ϐ��̏������A�}�E�X�A�L�[�{�[�h�N���X�̐���
DirectInput8::DirectInput8()
{
	mlpDI8 = NULL;

	mDIMouse = new DIMouse;
	mKeyBoard = new KeyBoard;
}


//! �f�X�g���N�^
DirectInput8::~DirectInput8()
{
	delete mDIMouse;
	delete mKeyBoard;
}
