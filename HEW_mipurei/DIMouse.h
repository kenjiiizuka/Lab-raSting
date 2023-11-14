#pragma once
#include <dinput.h>
#include <Windows.h>
#include "Vector2.h"
#include "FLOAT2.h"

/* ================================================== 
// マウスクラス                                    //
// 制作者 : 飯塚 健司                              */


/* -------------------------------------------------
// マウスのボタンの列挙型                         //
// マウスのボタンの取得に引数として使うためのモノ //
// ---------------------------------------------- */
enum eMouseButton {
	Mouse_LButton,
	Mouse_RButton,
	Mouse_MButton
};


class DIMouse
{
public:
	DIMouse();                                        //! コンストラクタ
	~DIMouse();                                       //! デストラクタ
	 
	void Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd);      //! 初期化処理
	void Update();                                    //! 更新処理
	void UnInit();									  //! 終了処理

	void SetMouseSpeed(int _mousespeed);                   //! マウススピードのセッター
	Vector2 GetMouseVelocity();                            //! マウスの1フレームの移動量を返えす関数
	Vector2 GetMouseVelocityNonFix();                      //! マウスの1フレームの移動量を返えす関数 Yの値の＋ー補正なし
	FLOAT2 GetMousePos();                                  //! マウスの現在位置(描画座標)の取得関数
	Vector2 GetMousePosVec();                              //! マウスの現在位置(描画座標)の取得関数
	FLOAT2 GetMouseWindowPos();                            //! マウスのウィンドウ上の座標の取得関数
	bool GetMouseButtonTrigger(eMouseButton _button);      //! マウスのボタンの入力のトリガー取得関数
	bool GetMouseButtonPress(eMouseButton _button);        //! マウスのボタンの入力のプレス取得関数     
	FLOAT2 GetMouseButtonTriggerPos(eMouseButton _button); //! マウスのボタンを押した瞬間の座標を取得する関数        
	FLOAT2 GetMouseButtonPressPos(eMouseButton _button);   //! マウスのボタンを押している間座標を取得する関数
	void SetMousePos(float _x, float _y);                  //! マウスに座標(描画座標)をセットする関数

private:
	LPDIRECTINPUTDEVICE8 mlpMouse;        //! マウスデバイス
	DIMOUSESTATE mDICurrentMouseState;    //! マウスの状態
	DIMOUSESTATE mDIPrevMouseState;       //! マウスの前フレームの状態
	int mDefoultSpeed = 0;                //! このゲーム開始前のマウスのスピード
	int mMouseSpeed;                      //! マウスのスピード
	HWND mHwnd;                           //! 協調するウィンドウハンドル


};

