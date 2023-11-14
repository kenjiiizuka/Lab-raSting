#include "Game.h"
#include "SceneManager.h"
#include "EffectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Controller.h"
#include "direct3d.h"
#include "Mouse.h"
#include "Camerah.h"
#include "DirectInput8.h"
#include "DrawValue.h"
#include "GameManager.h"

//! �f�o�b�O�p
extern DrawValue * cpDv;
extern float fps;

Game* Game::mcpInstance = nullptr;

//! �R���X�g���N�^
Game::Game()
{
}

//! �f�X�g���N�^
Game::~Game()
{		
}

//! ���̂̎擾�֐�
Game * Game::GetInstance()
{
	return mcpInstance;
}

void Game::Create()
{
	if (!mcpInstance) {
		mcpInstance = new Game();
	}
}

void Game::Destroy()
{
	delete mcpInstance;
}

void Game::GameInit(HINSTANCE _hinstsnce, HWND _hwnd)
{

	//! �Q�[���}�l�[�W���[�̐���
	GameManager::Create();
	//! �e�N�X�`���̓ǂݍ���
	TextureManager::Create();
	{
		ID3D11ShaderResourceView* test;
		LoadTexture(L"assets/Stage1/back1.png", &test);
		test->Release();
	}

	//! �G�t�F�N�g�̓ǂݍ���
	EffectManager::Create();
	

	//! �V�[���}�l�[�W���[�̐���
	SceneManager::Create();
	

	//! �T�E���h�}�l�[�W���[�̐���
	SoundManager::Create();	
	// �N���V�[���̐ݒ�

	

	SceneMgr->ChageScene(Scene_Title,false);
	// �T�E���h�̏�����
	SoundMgr->Init();
	// �R���g���[���[�̏�����
	bool controller = ControllerInit();
	//! �J�����̐���
	Camera::Create();
	
	mOperation = Controller;



}

//! �Q�[���̍X�V����
void Game::GameUpdate()
{
	SoundMgr->SoundUpdate();
	ControllerUpdate();
	CAMERA->Update();

	SceneMgr->Update();
	if (SceneMgr->GetNowScene() != Scene_Pause) {
		EffMgr->EffectUpdate();
	}

	//! �Q�[���I��
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_ESCAPE)) {
		Activ = false;
	}
}

//! �Q�[���̕`�揈��
void Game::GameDraw()
{
	float color[4] = { 0.0f,0.0f,0.0f,1.0f };
	Direct3D_Get()->context->ClearRenderTargetView(Direct3D_Get()->renderTarget, color);
	SceneMgr->Draw();	
}

//! �Q�[���̊J������
void Game::GameRelease()
{
	CAMERA->Destroy();
	SceneMgr->Destroy();
	SoundMgr->Destroy();
	EffMgr->Destroy();
	TexMgr->Destroy();
	GameMgr->Destroy();
}

bool Game::GetActiv()
{
	return Activ;
}

void Game::SetActiv(bool _state)
{
	Activ = _state;
}

//! ���݂̑�����@�̎擾
Operation Game::GetOperation()
{
	return mOperation;
}

//! ������@�̐؂�ւ��֐�
void Game::ChangeOperation(Operation _operation)
{
	mOperation = _operation;
}


