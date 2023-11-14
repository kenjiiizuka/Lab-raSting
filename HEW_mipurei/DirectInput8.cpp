#include "DirectInput8.h"
#include "Game.h"

#define DIRECTINPUT_VERSION 0x0800          //! DirectInputのバージョン指定

DirectInput8 * DirectInput8::mcpInstance = nullptr; 

//! 生成関数
void DirectInput8::Create()
{
	if (mcpInstance == nullptr) {mcpInstance = new DirectInput8();}
}

//! 破棄関数
void DirectInput8::Destroy()
{
	delete mcpInstance;
}

//! 実体の取得関数
DirectInput8* DirectInput8::GetIns()
{
	return mcpInstance;
}

//-----------------------------------------------
//! DirectInput8初期化関数
//! マウスやキーボードの初期化も行う
void DirectInput8::Init(HINSTANCE _hinstance, HWND _hwnd)
{
	//! 協調するウィンドウハンドルのセット
	mCooperationhWnd = _hwnd;

	//! DirectInout8の初期化
	HRESULT ret = DirectInput8Create(_hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mlpDI8, nullptr);
	if (FAILED(ret)) {
		//! 作成に失敗
	//	MessageBox(NULL, L"DirectInput8オブジェクトの作成に失敗", L"エラー発生", MB_OK);
	}

	//! マウスの初期化
	mDIMouse->Init(mlpDI8,_hinstance,mCooperationhWnd);
	//! キーボードの初期化
	mKeyBoard->Init(mlpDI8, _hinstance, mCooperationhWnd);

}

//-----------------------------------------------
//! 更新処理
//! マウス、キーボードの更新を行う
void DirectInput8::Update()
{
	if (GameIns->GetOperation() == Mouse) {
		mDIMouse->Update();
	}

	mKeyBoard->Update();
}

//-----------------------------------------------
//! 終了処理
//! マウス、キーボード、DirectInput8の終了処理
void DirectInput8::UnInit()
{

	mKeyBoard->UnInit();
	mDIMouse->UnInit();
	mlpDI8->Release();
}


//-----------------------------------------------
//! コンストラクタ
//! 変数の初期化、マウス、キーボードクラスの生成
DirectInput8::DirectInput8()
{
	mlpDI8 = NULL;

	mDIMouse = new DIMouse;
	mKeyBoard = new KeyBoard;
}


//! デストラクタ
DirectInput8::~DirectInput8()
{
	delete mDIMouse;
	delete mKeyBoard;
}
