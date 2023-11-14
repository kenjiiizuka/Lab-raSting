#undef UNICODE 

#include <Windows.h>
#include <time.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "WinMain.h"
#include "direct3d.h"
#include "Input.h"
#include "Game.h"
#include "Time.h"
#include "Log.h"
#include "Mouse.h"
#include "FrameRateCalculator.h"
#include "DirectInput8.h"
#include "DrawValue.h"
#include "SceneManager.h"
#include "EffectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Camerah.h"
#include "FPSControll.h"
#include "GameManager.h"

#pragma comment (lib,"winmm.lib") //! timeGetTime�֐��̂���

//---------------------------------------------------------------------------------------
//! �֐��v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! �O���[�o���ϐ��̐錾-------------------------------------------------------------------
//! �f�o�b�O�̂��߂ɐ錾���Ă��܂��B
float fps;
int PrevFrame; 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPravlnstance, LPSTR lpComdLine, int nCmdShow)
{
	//// ���������[�N���o
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//! �����W�F�l���[�^�̏�����
	srand((unsigned)time(nullptr));

	//! �\���̐錾
	WNDCLASSEX wc;
	HWND hWnd;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_HELP); //�J�[�\���̌`
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//�E�B���h�E�̔w�i�̐ݒ�
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);//Windows�ɃE�B���h�E����o�^����

	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX ,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^


	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	//Direct3D�̏������֐����Ăяo��
	Direct3D_Init(hWnd);
		
	DIRECT3D *d3d = Direct3D_Get();
	MSG msg;


	FrameRateCalculator* cFrame = new FrameRateCalculator(); // FPS�v�Z�p�I�u�W�F�N�g

	//! �t���[�������p�ϐ�
	char gBuf[BUFFREE] = { 0 };
	PrevFrame = 0;
	int FrameLate = 60;
	int PrevSecond = 0;
	fps = 0;
	long long end = GetNowMicro();                    // ���ݎ������擾�i1�b = 1000000�j
	long long next = end + (1000 * 1000 / FrameLate); // ���̍X�V���Ԃ��v�Z(1�b/�t���[�����[�g)

	timeBeginPeriod(1);



    DirectInput8::Create();
	In->Create();
	Game::Create();      //! Game�N���X�̐���
	GameIns->GameInit(hInstance,hWnd); //! GameInit�֐�
	DI8->Init(hInstance,hWnd);
	FPSControl::Init(60);

	//! ���C�����[�v
	while (ACTIV) {
		//�O��̃��[�v���烆�[�U�[���삪�����������ׂ�
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist) {
			//�ԐړI�ɃE�C���h�E�v���V�[�W���֐����Ăяo��
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)	{
				break;
			}
		}
		else {
			FPSControl::StartFrame();
			DI8->Update();
			GameIns->GameUpdate();
			GameIns->GameDraw();
			
			fps = FPSControl::GetDeltaTime();
			sprintf_s(gBuf, BUFFREE, "fps %f �o��fps %d %d�b�o��", fps, PrevFrame, PrevSecond);
			SetWindowText(hWnd, gBuf);

			Direct3D_Get()->swapChain->Present(0, 0); //! �_�u���o�b�t�@�̐؂�ւ�
		}
	}
	timeEndPeriod(1);

	// �I������
	delete cFrame;	
	In->Destroy();
	DI8->UnInit();
	DI8->Destroy();
	GameIns->GameRelease();
	GameIns->Destroy();
	//Direct3D�̉���֐����Ăяo��
	Direct3D_Release();
	UnregisterClass(CLASS_NAME, hInstance);
	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W���֐������
//���֐�������̂̓O���[�o���̈悾���I
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg/*�C�x���g�̓��e���i�[����Ă���*/, WPARAM wParam, LPARAM lParam)
{
	bool gResult = false;
	//uMsg�@���[�U�[�����ID���
	switch (uMsg)
	{
	case WM_KEYDOWN: //! �L�[���͂���������	
		In->SetKeyDown(LOWORD(wParam));		
		break;

	case WM_KEYUP:   //! �L�[���b���ꂽ�Ƃ�
		In->SetKeyUp(LOWORD(wParam));
		break;

	case WM_LBUTTONDOWN: //! �E�N���b�N���ꂽ�Ƃ�
		In->SetKeyDown(VK_LBUTTON);
		break;

	case WM_LBUTTONUP: //! �}�E�X�̍��̃{�^���������ꂽ�Ƃ�
		In->SetKeyUp(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN: //! ���N���b�N���ꂽ�Ƃ�
		In->SetKeyDown(VK_RBUTTON);
		break;

	case WM_RBUTTONUP: //! �}�E�X�̉E�̃{�^���������ꂽ�Ƃ�
		In->SetKeyUp(VK_RBUTTON);
		break;

	case WM_MBUTTONDOWN: //! �}�E�X�̒����{�^��(�z�C�[��)�������ꂽ�Ƃ�
		In->SetKeyDown(VK_MBUTTON);
		break;
		
	case WM_MBUTTONUP:   //! �}�E�X�̒����{�^��(�z�C�[��)�������ꂽ�Ƃ�
		In->SetKeyUp(VK_MBUTTON);
		break;

	case WM_DESTROY: //! �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0); //"WM_QUIT"���b�Z�[�W�𑗂�
		break;

	case WM_CLOSE:  //! �~�{�^���������Ƃ�
		DestroyWindow(hWnd); //! "WM_DESTROY"���b�Z�[�W�𑗂�
		break;
		
	default:
		//! ��̃P�[�X�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}

