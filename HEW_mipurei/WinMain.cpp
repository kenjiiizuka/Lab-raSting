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

#pragma comment (lib,"winmm.lib") //! timeGetTime関数のため

//---------------------------------------------------------------------------------------
//! 関数プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//! グローバル変数の宣言-------------------------------------------------------------------
//! デバッグのために宣言しています。
float fps;
int PrevFrame; 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPravlnstance, LPSTR lpComdLine, int nCmdShow)
{
	//// メモリリーク検出
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//! 乱数ジェネレータの初期化
	srand((unsigned)time(nullptr));

	//! 構造体宣言
	WNDCLASSEX wc;
	HWND hWnd;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_HELP); //カーソルの形
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//ウィンドウの背景の設定
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);//Windowsにウィンドウ情報を登録する

	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX ,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ


	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	//Direct3Dの初期化関数を呼び出す
	Direct3D_Init(hWnd);
		
	DIRECT3D *d3d = Direct3D_Get();
	MSG msg;


	FrameRateCalculator* cFrame = new FrameRateCalculator(); // FPS計算用オブジェクト

	//! フレーム処理用変数
	char gBuf[BUFFREE] = { 0 };
	PrevFrame = 0;
	int FrameLate = 60;
	int PrevSecond = 0;
	fps = 0;
	long long end = GetNowMicro();                    // 現在時刻を取得（1秒 = 1000000）
	long long next = end + (1000 * 1000 / FrameLate); // 次の更新時間を計算(1秒/フレームレート)

	timeBeginPeriod(1);



    DirectInput8::Create();
	In->Create();
	Game::Create();      //! Gameクラスの生成
	GameIns->GameInit(hInstance,hWnd); //! GameInit関数
	DI8->Init(hInstance,hWnd);
	FPSControl::Init(60);

	//! メインループ
	while (ACTIV) {
		//前回のループからユーザー操作があったか調べる
		BOOL doesMessageExist = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (doesMessageExist) {
			//間接的にウインドウプロシージャ関数を呼び出す
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
			sprintf_s(gBuf, BUFFREE, "fps %f 経過fps %d %d秒経過", fps, PrevFrame, PrevSecond);
			SetWindowText(hWnd, gBuf);

			Direct3D_Get()->swapChain->Present(0, 0); //! ダブルバッファの切り替え
		}
	}
	timeEndPeriod(1);

	// 終了処理
	delete cFrame;	
	In->Destroy();
	DI8->UnInit();
	DI8->Destroy();
	GameIns->GameRelease();
	GameIns->Destroy();
	//Direct3Dの解放関数を呼び出す
	Direct3D_Release();
	UnregisterClass(CLASS_NAME, hInstance);
	return (int)msg.wParam;
}

//ウィンドウプロシージャ関数を作る
//※関数を作れるのはグローバル領域だけ！
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg/*イベントの内容が格納されている*/, WPARAM wParam, LPARAM lParam)
{
	bool gResult = false;
	//uMsg　ユーザー操作のID情報
	switch (uMsg)
	{
	case WM_KEYDOWN: //! キー入力があった時	
		In->SetKeyDown(LOWORD(wParam));		
		break;

	case WM_KEYUP:   //! キーが話されたとき
		In->SetKeyUp(LOWORD(wParam));
		break;

	case WM_LBUTTONDOWN: //! 右クリックされたとき
		In->SetKeyDown(VK_LBUTTON);
		break;

	case WM_LBUTTONUP: //! マウスの左のボタンが離されたとき
		In->SetKeyUp(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN: //! 左クリックされたとき
		In->SetKeyDown(VK_RBUTTON);
		break;

	case WM_RBUTTONUP: //! マウスの右のボタンが離されたとき
		In->SetKeyUp(VK_RBUTTON);
		break;

	case WM_MBUTTONDOWN: //! マウスの中央ボタン(ホイール)が押されたとき
		In->SetKeyDown(VK_MBUTTON);
		break;
		
	case WM_MBUTTONUP:   //! マウスの中央ボタン(ホイール)が離されたとき
		In->SetKeyUp(VK_MBUTTON);
		break;

	case WM_DESTROY: //! ウィンドウ破棄のメッセージ
		PostQuitMessage(0); //"WM_QUIT"メッセージを送る
		break;

	case WM_CLOSE:  //! ×ボタン押したとき
		DestroyWindow(hWnd); //! "WM_DESTROY"メッセージを送る
		break;
		
	default:
		//! 上のケース以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}

