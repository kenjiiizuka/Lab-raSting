#include "DIMouse.h"
#include "WinMain.h"
#include <math.h>


//--------------------------
//! コンストラクタ
//! 変数の初期化
DIMouse::DIMouse()
{
	mlpMouse = NULL;
	mMouseSpeed = 2;    //! スピードは２
	mDefoultSpeed = 0;

	//! マウスステート構造体も初期化した方がいいかも

}


DIMouse::~DIMouse()
{

}

/* -----------------------------------------
// マウスの初期化関数                     //
// DirectInput8による初期化を行っています //
// ※一度だけ使用してください             //
// -------------------------------------- */
void DIMouse::Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd)
{

	mHwnd = _hwnd;

	HRESULT ret;

	//! ゲーム開始前のスピードを取得
	SystemParametersInfo(SPI_GETMOUSESPEED, 0, &mDefoultSpeed, 0);

	//! マウスデバイスの作成
	ret = _mlpDI8->CreateDevice(GUID_SysMouse, &mlpMouse, NULL);
	if (FAILED(ret)) {
	//	//! 作成に失敗
	//	MessageBox(NULL, L"マウスデバイスの作成に失敗", L"エラー発生", MB_OK);
	}

	//! デバイスのフォーマット設定
	ret = mlpMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(ret)) {
		//! 作成に失敗
	//	MessageBox(NULL, L"デバイスのフォーマットの設定に失敗", L"エラー発生", MB_OK);
	}

	//! 協調モードの設定
	ret = mlpMouse->SetCooperativeLevel(mHwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		//! 協調モードの設定に失敗
	//	MessageBox(NULL, L"協調モードの設定に失敗", L"エラー発生", MB_OK);
	}

	//! デバイスの制御開始
	ret = mlpMouse->Acquire();
	if (FAILED(ret)) {
		//! デバイス制御開始に失敗
		//MessageBox(NULL, L"デバイス制御開始に失敗", L"エラー発生", MB_OK);
	}

	//! ポーリング開始
	ret = mlpMouse->Poll();
	if (FAILED(ret)) {
		//! ポーリング開始に失敗
		//MessageBox(NULL, L"ポーリング開始に失敗", L"エラー発生", MB_OK);
	}
}

/*--------------------------------------------------------------
// マウスの更新関数                                           //
// フレームマウスの入力や座標、マウスの状態を更新しています   //
// 引数 : マウスのスピード                                    //
// ※毎フレーム使用してください                               //
// ---------------------------------------------------------- */
void DIMouse::Update()
{
	//! 前フレームのマウスの情報を保存
	mDIPrevMouseState = mDICurrentMouseState;

	//! 現マウスの状態の取得
	HRESULT ret = mlpMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mDICurrentMouseState);
	if (FAILED(ret)) {
		if ((ret == DIERR_INPUTLOST) || (ret == DIERR_NOTACQUIRED)) {
			mlpMouse->Acquire();
		}
		else {
		//	MessageBox(NULL, L"マウスの状態を取得できません", L"エラー発生", MB_OK);
		}
	}

	//毎フレームやる必要がないのでどうにかしたい
	//! Mouseのスピードのセット
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)mMouseSpeed, 0);
}

/* -----------------------------------------------------------------------------------
// マウスの解放関数                                                                 //
// DirectInput8による解放を行っています                                             //
// ※MouseInit関数をしようしたら必ずプログラムの終わりに一度だけ使用してください    //
// -------------------------------------------------------------------------------- */
void DIMouse::UnInit()
{
	//! ゲーム起動前のスピードに戻す
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)mDefoultSpeed, 0);
	mlpMouse->Unacquire(); //! デバイス制御終了
	mlpMouse->Release();   //! デバイスの解放
}


// マウスのスピードのセッター
void DIMouse::SetMouseSpeed(int _mousespeed)
{
	mMouseSpeed = _mousespeed;
}


/* ---------------------------------------
// マウスの1フレームの移動量を返す関数  //
// 戻り値 x,y方向の移動量               //
// ------------------------------------ */
Vector2 DIMouse::GetMouseVelocity()
{
	return Vector2((float)mDICurrentMouseState.lX, (float)mDICurrentMouseState.lY * -1);
}

Vector2 DIMouse::GetMouseVelocityNonFix()
{
	return Vector2((float)mDICurrentMouseState.lX, (float)mDICurrentMouseState.lY);
}


/* --------------------------------------------
// マウスの現在位置(描画座標)の取得関数      //
// 戻り値 : マウスのx,y座標　　　　　　　　　//
// ----------------------------------------- */
FLOAT2 DIMouse::GetMousePos()
{

	POINT pos1;
	FLOAT2 pos2;

	GetCursorPos(&pos1);         //! マウスカーソルの位置を取得
	ScreenToClient(mHwnd, &pos1); //! ウィンドウ上の座標に変換

	float ScreenHalfWidth = (SCREEN_WIDTH / 2) / 1.925; //! 画面の比率に補正をかけているためこちらにもかける
	float ScreenHalfHeight = SCREEN_HEIGHT / 2;

	pos2.x = ((pos1.x - ScreenHalfWidth) / ScreenHalfWidth) - 0.925f; //! X座標値を -1.3〜1.3 に変換する	
	pos2.y = (ScreenHalfHeight - pos1.y) / ScreenHalfHeight;          //! Y座標値を -1.0〜1.0 に変換する

	return pos2;
}



/* --------------------------------------------
// マウスの現在位置(描画座標)の取得関数      //
// 戻り値 : マウスのx,y座標　　　　　　　　　//
// ----------------------------------------- */
Vector2 DIMouse::GetMousePosVec()
{



	POINT pos1;

	GetCursorPos(&pos1);         //! マウスカーソルの位置を取得
	ScreenToClient(mHwnd, &pos1); //! ウィンドウ上の座標に変換

	float ScreenHalfWidth = (SCREEN_WIDTH / 2) / 1.925; //! 画面の比率に補正をかけているためこちらにもかける
	float ScreenHalfHeight = SCREEN_HEIGHT / 2;

	float x = ((pos1.x - ScreenHalfWidth) / ScreenHalfWidth) - 0.925f; //! X座標値を -1.3〜1.3 に変換する	
	float y = (ScreenHalfHeight - pos1.y) / ScreenHalfHeight;          //! Y座標値を -1.0〜1.0 に変換する

	return Vector2(x, y);
}



/* -------------------------------------------
// マウスのウィンドウ上の座標の取得関数     //
// 戻り値 : マウスのウィンドウ上の座標x,y   //
// ---------------------------------------- */
FLOAT2 DIMouse::GetMouseWindowPos()
{
	POINT pos1;
	FLOAT2 pos2;

	GetCursorPos(&pos1); //! マウスカーソルの位置を取得
	ScreenToClient(mHwnd, &pos1); //! ウィンドウ上の座標に変換

	return FLOAT2(pos1.x, pos1.y);
}

/* ------------------------------------------
// マウスに座標(描画座標)をセットする関数  //
// 引数 : x座標 , y座標                    //
// --------------------------------------- */
void DIMouse::SetMousePos(float _x, float _y)
{
	float ScreenHalfWidth = (SCREEN_WIDTH / 2) / 1.925; //! 画面の比率に補正をかけているためこちらにもかける
	float ScreenHalfHeight = SCREEN_HEIGHT / 2;

	//! 引数で指定された値をウィンドウ上の座標に変換
	float x = _x * ScreenHalfWidth + (SCREEN_WIDTH / 2);
	float y = ScreenHalfHeight - fabs(_y * ScreenHalfHeight);

	//! カーソルの位置をセット　※Y座標がなぜか23小さい位置に設置されるの応急処置として [+ 23] しています！！！！
	SetPhysicalCursorPos(fabs(x), fabs(y + 23));
}

/* -------------------------------------------
// マウスのボタンの入力のトリガー取得関数   //
// 引数 : マウスのボタンの種類              //
// 戻り値 : 入力の有無                      //
// ---------------------------------------- */
bool DIMouse::GetMouseButtonTrigger(eMouseButton _button)
{
	return (mDICurrentMouseState.rgbButtons[_button] & 0x80) && !(mDIPrevMouseState.rgbButtons[_button] & 0x80);
}

/* -------------------------------------------
// マウスのボタンの入力のプレス取得関数     //
// 引数 : マウスのボタンの種類              //
// 戻り値 : 入力の有無                      //
// ---------------------------------------- */
bool DIMouse::GetMouseButtonPress(eMouseButton _button)
{
	return mDICurrentMouseState.rgbButtons[_button] & 0x80;
}

/* ------------------------------------------------------------------------
// マウスのボタンを押した瞬間の座標を取得する関数                        //
// 引数 : マウスのボタンの種類                                           //
// 戻り値 : ボタンが押された座標　押されていない場合は-8000がかえります  //
// --------------------------------------------------------------------- */
FLOAT2 DIMouse::GetMouseButtonTriggerPos(eMouseButton _button)
{
	if ((mDICurrentMouseState.rgbButtons[_button] & 0x80)
		&& !(mDIPrevMouseState.rgbButtons[_button] & 0x80))
	{
		return GetMousePos();
	}

	//! NULLなどの0と同じ画面内の座標の範囲にある値を返すと
	//当たり判定などで誤って判定してしまってバグの原因になりそうなので-8000を返します
	return FLOAT2(-8000, -8000);
}


/* ------------------------------------------------------------------------
// マウスのボタンを押している間座標を取得する関数                        //
// 引数 : マウスのボタンの種類                                           //
// 戻り値 : ボタンが押された座標　押されていない場合は-8000がかえります  //
// --------------------------------------------------------------------- */
FLOAT2 DIMouse::GetMouseButtonPressPos(eMouseButton _button)
{
	if ((mDICurrentMouseState.rgbButtons[_button] & 0x80)) {
		return GetMousePos();
	}

	//! NULLなどの0と同じ画面内の座標の範囲にある値を返すと
	//当たり判定などで誤って判定してしまってバグの原因になりそうなので-8000を返します
	return FLOAT2(-8000, -8000);

}



