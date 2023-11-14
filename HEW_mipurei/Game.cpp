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

//! デバッグ用
extern DrawValue * cpDv;
extern float fps;

Game* Game::mcpInstance = nullptr;

//! コンストラクタ
Game::Game()
{
}

//! デストラクタ
Game::~Game()
{		
}

//! 実体の取得関数
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

	//! ゲームマネージャーの生成
	GameManager::Create();
	//! テクスチャの読み込み
	TextureManager::Create();
	{
		ID3D11ShaderResourceView* test;
		LoadTexture(L"assets/Stage1/back1.png", &test);
		test->Release();
	}

	//! エフェクトの読み込み
	EffectManager::Create();
	

	//! シーンマネージャーの生成
	SceneManager::Create();
	

	//! サウンドマネージャーの生成
	SoundManager::Create();	
	// 起動シーンの設定

	

	SceneMgr->ChageScene(Scene_Title,false);
	// サウンドの初期化
	SoundMgr->Init();
	// コントローラーの初期化
	bool controller = ControllerInit();
	//! カメラの生成
	Camera::Create();
	
	mOperation = Controller;



}

//! ゲームの更新処理
void Game::GameUpdate()
{
	SoundMgr->SoundUpdate();
	ControllerUpdate();
	CAMERA->Update();

	SceneMgr->Update();
	if (SceneMgr->GetNowScene() != Scene_Pause) {
		EffMgr->EffectUpdate();
	}

	//! ゲーム終了
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_ESCAPE)) {
		Activ = false;
	}
}

//! ゲームの描画処理
void Game::GameDraw()
{
	float color[4] = { 0.0f,0.0f,0.0f,1.0f };
	Direct3D_Get()->context->ClearRenderTargetView(Direct3D_Get()->renderTarget, color);
	SceneMgr->Draw();	
}

//! ゲームの開放処理
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

//! 現在の操作方法の取得
Operation Game::GetOperation()
{
	return mOperation;
}

//! 操作方法の切り替え関数
void Game::ChangeOperation(Operation _operation)
{
	mOperation = _operation;
}


