#include "KeyBoard.h"





KeyBoard::KeyBoard()
{
	mlpDIKeyBoard = NULL;

}

KeyBoard::~KeyBoard()
{

}


//! キーボードの初期化処理
void KeyBoard::Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd)
{
	HRESULT ret;

	mHwnd = _hwnd;

	//! デバイスの作成
	ret = _mlpDI8->CreateDevice(GUID_SysKeyboard,&mlpDIKeyBoard,NULL);
	//if (FAILED(ret)) {
	//	//! 作成に失敗
	//	MessageBox(NULL, L"キーボードデバイスの作成に失敗", L"エラー発生", MB_OK);
	//}

	//! デバイスのフォーマット設定
	ret = mlpDIKeyBoard->SetDataFormat(&c_dfDIKeyboard);
	//if (FAILED(ret)) {
	//	//! 作成に失敗
	//	MessageBox(NULL, L"デバイスのフォーマットの設定に失敗", L"エラー発生", MB_OK);
	//}

	//! 協調モードの設定
	ret = mlpDIKeyBoard->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	//if (FAILED(ret)) {
	//	//! 協調モードの設定に失敗
	//	MessageBox(NULL, L"協調モードの設定に失敗", L"エラー発生", MB_OK);
	//}

	//! デバイスの制御開始
	ret = mlpDIKeyBoard->Acquire();
	//if (FAILED(ret)) {
	//	//! デバイス制御開始に失敗
	//	MessageBox(NULL, L"デバイス制御開始に失敗", L"エラー発生", MB_OK);
	//}
}

//! キーボードの更新処理
void KeyBoard::Update()
{
	for (int num = 0; num < 256; num++) {
		mPrevKeyState[num] = mCurrentKeyState[num];
	}
	HRESULT hr;
	// キーボードデバイスのゲッター
	hr = mlpDIKeyBoard->GetDeviceState(256, mCurrentKeyState);

	//! 状態の取得に失敗した場合は再度デバイスの制御を開始する
	if (hr != S_OK) {
		//! デバイスのフォーマット設定
		hr = mlpDIKeyBoard->SetDataFormat(&c_dfDIKeyboard);

		//! 協調モードの設定
		hr = mlpDIKeyBoard->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		
		//! デバイスの制御開始
		hr = mlpDIKeyBoard->Acquire();

	}
}

//! キーボードの終了処理
void KeyBoard::UnInit()
{
	mlpDIKeyBoard->Unacquire(); //! デバイス制御終了
	mlpDIKeyBoard->Release();   //! デバイスの解放
}

//! キーボードのトリガー取得
bool KeyBoard::GetKeyTrigger(int _key)
{
	return !(mPrevKeyState[_key] & 0x80) && (mCurrentKeyState[_key] & 0x80);
}

//! キーボードのプレス取得
bool KeyBoard::GetKeyPress(int _key)
{
	return (mCurrentKeyState[_key] & 0x80);
}
