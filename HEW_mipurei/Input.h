#pragma once
#include "FLOAT2.h"
#include <Windows.h>

/* =========================================== **
** キーボード、マウスの入力クラス              **
** 制作者 : 飯塚 健司                          **
** =========================================== */

#define In Input::GetInstance() //! ゲットインスタンス関数省略のためのマクロ

class Input
{
public:

	static Input * GetInstance();
	static void Create();
	static void Destroy();
	
	void SetKeyDown(int key);
	void SetKeyUp(int key);
	bool GetKeyTrigger(int Key);     //! 押した瞬間
	bool GetKeyDownPress(int key);   //! 長押し
	
private:
	Input();  //! コンストラクタ
	~Input(); //! デストラクタ

	//! 全キー状態を保存する配列
	bool mKeyState[256];
	bool mOldKeyState[256];

	static Input * mcpInstance; //! 実体	
};