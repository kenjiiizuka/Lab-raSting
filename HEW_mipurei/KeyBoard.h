#pragma once
#include <dinput.h>
#include <Windows.h>

/* ----------------------------------------------------------------------
// キーボードクラス                                                    //
// キーボードの入力の取得ができます                                    //
// 制作者 : 飯塚 健司                                                  */
class KeyBoard
{
public:
	KeyBoard(); //! コンストラクタ
	~KeyBoard(); //! デストラクタ

	void Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd); //! 初期化処理
	void Update();                                                       //! 更新処理
	void UnInit();                                                       //! 終了処理
	
	bool GetKeyTrigger(int _key);                           //! キーボードのトリガー取得
	bool GetKeyPress(int _key);                             //! キーボードのプレス取得

private:
	LPDIRECTINPUTDEVICE8 mlpDIKeyBoard; //! キーボードデバイス
	BYTE mPrevKeyState[256];            //! 前フレームのキーボードの状態
	BYTE mCurrentKeyState[256];         //! 現時点のフレームのキーボードの状態
 
	HWND mHwnd; //! 協調するウィンドウハンドル
};

