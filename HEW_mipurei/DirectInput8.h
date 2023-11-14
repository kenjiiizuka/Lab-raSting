#pragma once
#include "DIMouse.h"
#include "KeyBoard.h"

//! リンカー付け
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")


/* ==========================================================================
** DirectInput8クラス(シングルトン)                                        **
** DirectInput8によるキーボード、マウスの入力などの機能を持ったクラスです  **
** 制作者 : 飯塚 健司                    */



#define DI8 DirectInput8::GetIns()

class DirectInput8
{
public:	
	static void Create();                //! 生成関数
	static void Destroy();               //! 破棄関数
	static DirectInput8* GetIns();

	void Init(HINSTANCE _hinstance, HWND _hwnd); //! 初期化関数
	void Update();						         //! 更新関数
	void UnInit();						         //! 終了関数

	DIMouse * mDIMouse;                          //! マウスクラス
	KeyBoard * mKeyBoard;                        //! キーボードクラス
private:
	DirectInput8();                      //! コンストラクタ
	~DirectInput8();                     //! デストラクタ
	
	static DirectInput8 * mcpInstance;   //! 自身

	LPDIRECTINPUT8 mlpDI8;               //! DirectInpoutObject
	HWND mCooperationhWnd;               //! 協調するウィンドウハンドル

};

