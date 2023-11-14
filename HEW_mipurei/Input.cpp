#include "Input.h"
#include<Windows.h>


Input * Input::mcpInstance = nullptr;

//! 実体の取得関数
Input * Input::GetInstance()
{
	return mcpInstance;
}

//! 実体の生成関数
void Input::Create()
{
	if (mcpInstance == nullptr) {
		mcpInstance = new Input();
	}
}

//! 実態の破棄
void Input::Destroy()
{
	delete mcpInstance;
}


//! 入力があったキーをtrueにする関数
void Input::SetKeyDown(int key)
{
	mKeyState[key] = true;
}


//! キーのトリガー取得関数
bool Input::GetKeyTrigger(int key)
{
	//連続で
	if (mOldKeyState[key] == false && mKeyState[key] == true) {
		mOldKeyState[key] = true;
		return mKeyState[key];		
	}
	return 0;
}


//! キー入力押してる間の取得
bool Input::GetKeyDownPress(int key)
{
	return mKeyState[key];
}


//! コンストラクタ
Input::Input()
{
	//! 配列の初期化
	for (int num = 0; num < 256; num++) {
		mKeyState[num] = false;
		mOldKeyState[num] = false;
	}
}


//! デストラクタ (空実装)
Input::~Input()
{
	
}

//! 離されたキーをfalseにする関数
void Input::SetKeyUp(int key)
{
	mKeyState[key] = false;
	mOldKeyState[key] = false;
}




