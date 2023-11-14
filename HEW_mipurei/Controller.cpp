#include "Controller.h"
#include "Angle.h"
#include <Windows.h>
#include <Xinput.h>
#include <math.h>

#pragma comment (lib,"xinput.lib")

#define THUMBSTICKMAXVALUE 32767.0f

XINPUT_STATE State; //! コントローラーの状態
XINPUT_STATE OldState; //! コントローラーの前フレームの状態
int ButtonID[Button_Max];
bool ButtonState[Button_Max];
bool ButtonOldState[Button_Max];

XINPUT_VIBRATION Vibration; //! コントローラーのバイブレーションの状態
WORD LeftMotorSpeed = 0;
WORD RightMotorSpeed = 0;
float RightStickDif = 0;      //! 右スティックのレバガチャをするときに使う変数
float LeftStickDif = 0;       //! 左スティックのレバガチャをするときに使う変数
int CurrentVibrationFrame = 0; //! 振動の経過時間
int VibrationFrame = 0;	      //! 振動する時間の長さ

bool ControllerInit()
{
	// ボタンIDの設定
	ButtonID[Button_UP] = 0x0001;
	ButtonID[Button_DOWN] = 0x0002;
	ButtonID[Button_LEFT] = 0x0004;
	ButtonID[Button_RIGHT] = 0x0008;
	ButtonID[Button_MENU] = 0x0010;
	ButtonID[Button_SCREEN] = 0x0020;
	ButtonID[LEFT_STICK_THUMB] = 0x0040;
	ButtonID[RIGHT_STICK_THUMB] = 0x0080;
	ButtonID[Button_LB] = 0x0100;
	ButtonID[Button_RB] = 0x0200;
	ButtonID[Button_LT] = 0x0400;
	ButtonID[Button_RT] = 0x0800;
	ButtonID[Button_A] = 0x1000;
	ButtonID[Button_B] = 0x2000;
	ButtonID[Button_X] = 0x4000;
	ButtonID[Button_Y] = 0x8000;
	
	// 配列の初期化
	for (int num = 0; num < Button_Max; num ++) {
		ButtonState[num] = false;
		ButtonOldState[num] = false;
	}

	ZeroMemory(&State, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &State);

	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	
	if (dwResult != ERROR_SUCCESS) {
		//	MessageBoxA(NULL, "コントローラー接続失敗", "エラー", MB_OK);
		return false;
	}
	else {
		return true;
	}
}

/* コントローラーの状態の更新 *******/
bool ControllerUpdate()
{	
	// 前フレームの情報として保存
	for (int num = 0; num < Button_Max; num++) {
		ButtonOldState[num] = ButtonState[num];
	}

	//! 前フレームのコントローラーの状態として保存
	OldState = State;
	// コントローラーの状態の取得
	DWORD dwResult = XInputGetState(0, &State);	


	// 押されているボタンを探す
	for (int num = 0; num < Button_Max; num++) {

		if (State.Gamepad.wButtons == ButtonID[num]) {
			ButtonState[num] = true;
		}
		else {
			ButtonState[num] = false;
		}
	}

	// 左トリガーボタンの押下の判断
	if (State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		ButtonState[Button_LT] = true;
	}
	else {
		ButtonState[Button_LT] = false;
	}

	// 右トリガーボタンの押下の判断
	if (State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		ButtonState[Button_RT] = true;
	}
	else {
		ButtonState[Button_RT] = false;
	}

	// 振動の設定
	Vibration.wLeftMotorSpeed = LeftMotorSpeed ;
	Vibration.wRightMotorSpeed = RightMotorSpeed;

	XInputSetState(0, &Vibration);

	//! バイブレーションの時間がセットされていたら時間をはかる
	if (VibrationFrame != 0) {
		//! 設定された時間経過したら振動をやめる
		if (CurrentVibrationFrame >= VibrationFrame) {
			LeftMotorSpeed = 0;
			RightMotorSpeed = 0;
			VibrationFrame = 0;
		}
		CurrentVibrationFrame += 1;
	}
	else {
		// 振動の速度を減らしていく
		if (LeftMotorSpeed != 0) {
			LeftMotorSpeed -= 1000;

			if (LeftMotorSpeed < 0) {
				LeftMotorSpeed = 0;
			}
		}

		if (RightMotorSpeed != 0) {
			RightMotorSpeed -= 1000;

			if (RightMotorSpeed < 0) {
				RightMotorSpeed = 0;
			}
		}
	}
	if (dwResult != ERROR_SUCCESS) {
		return false;
	}
	else {
		return true;
	}
}


/* 左スティックの倒れ具合を取得する関数 *******************************
* 　戻り値　スティックの倒れ具合が (-1.0f ～ 1.0f) の値で返ってきます *
**********************************************************************/
Vector2 GetControllerLeftStick()
{
	// デッドゾーンの設定
	if ((State.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		State.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(State.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			State.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		State.Gamepad.sThumbLX = 0;
		State.Gamepad.sThumbLY = 0;
	}
	// スティックの倒れ具合を計算
	Vector2 Stick;
	Stick.x = State.Gamepad.sThumbLX / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = State.Gamepad.sThumbLY / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}



/* 右スティックの倒れ具合を取得する関数 *******************************
* 　戻り値　スティックの倒れ具合が (-1.0f ～ 1.0f) の値で返ってきます *
**********************************************************************/
Vector2 GetControllerRightStick()
{
	// デッドゾーンの設定
	if ((State.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		State.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(State.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			State.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		State.Gamepad.sThumbRX = 0;
		State.Gamepad.sThumbRY = 0;
	}

	// スティックの倒れ具合を計算
	Vector2 Stick;
	Stick.x = State.Gamepad.sThumbRX / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = State.Gamepad.sThumbRY / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}

/* 左スティックの差の取得 */
Vector2 GetControllerLeftStickDif()
{
	float x = (float)OldState.Gamepad.sThumbLX - State.Gamepad.sThumbLX;
	float y = (float)OldState.Gamepad.sThumbLY - State.Gamepad.sThumbLY;
	Vector2 Stick;
	Stick.x = x / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = y / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}

/* 右スティックの差の取得 */
Vector2 GetControllerRightStickDif()
{
	float x = (float)OldState.Gamepad.sThumbRX - State.Gamepad.sThumbRX;
	float y = (float)OldState.Gamepad.sThumbRY - State.Gamepad.sThumbRY;
	if (x != 0) {
		int iketeruyo = 0;
	}
	Vector2 Stick;
	Stick.x = x / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = y / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}

/* 右スティックの前フレームとの倒れ具合の差のベクトル */
float GetControllerLeftStickDifVector()
{	
	Vector2 vector = GetControllerLeftStickDif();
	return vector.GetVetor() * 100;
}

/* 左スティックの前フレームとの倒れ具合の差のベクトル */
float GetControllerRightStickDifVector()
{
	Vector2 vector = GetControllerRightStickDif();
	return vector.GetVetor() * 100;
}

/* 右スティックの倒れている角度の取得関数 */
float GetControllerRightStickAngle()
{	
	//! デッドゾーン
	int DeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * 2.5f;
	// デッドゾーンの設定
	if ((State.Gamepad.sThumbRX <  DeadZone &&
		State.Gamepad.sThumbRX > -DeadZone) &&
		(State.Gamepad.sThumbRY <  DeadZone &&
			State.Gamepad.sThumbRY > -DeadZone))
	{
		State.Gamepad.sThumbRX = 0;
		State.Gamepad.sThumbRY = 0;
	}

	// スティックの倒れ具合を計算
	Vector2 Right;
	Right.x = State.Gamepad.sThumbRX / (THUMBSTICKMAXVALUE * 100.0f);
	Right.y = State.Gamepad.sThumbRY / (THUMBSTICKMAXVALUE * 100.0f);

	return GetAngle(Right.x,Right.y);
}

/* 左スティックの倒れている角度の取得関数 */
float GetControllerLeftStickAngle()
{
	Vector2 Left = GetControllerLeftStick();
	return GetAngle(Left.x, Left.y);
}

/* 右スティックの倒れている角度の取得(Degree) */
float GetControllerRightStickAngleDeg()
{
	return RadianToDegree(GetControllerRightStickAngle());
}

/* 左スティックの倒れている角度の取得(Degree) */
float GetControllerLeftStickAngleDeg()
{
	return RadianToDegree(GetControllerLeftStickAngle());
}

/* ボタンが押されているかを取得する関数 *******
*  引数　ボタンID                             *
**********************************************/
bool GetControllerButtonPress(eButton  _button)
{
	return ButtonState[_button];
}

/* ボタンのトリガー取得をする関数　**********
** 引数　ボタンID　　　　　　　　           * 
********************************************/
bool GetControllerButtonTrigger(eButton _button)
{
	if (ButtonOldState[_button] != true && ButtonState[_button] == true) {
		return true;
	}
	return false;
}

/* 右のトリガーの前フレームの押下の差を取得する関数(離すとき) */
//! 押下の数値は　0～255の間です
int GetControllerRightTriggerDifRelease()
{
	int dif = 0;
	dif = OldState.Gamepad.bRightTrigger - State.Gamepad.bRightTrigger ;
	return dif;
}

int GetControllerRightTrigger()
{
	return State.Gamepad.bRightTrigger;
}


/* レバガチャ右 */
bool RightStickMashing()
{
	//! 前フレームとの差分が一定を超えたらtrueを返す
	Vector2 Dif = GetControllerRightStickDif();
	if (Dif == 0) {
		int a = 0;
	}
	RightStickDif += fabs(Dif.x) + fabs(Dif.y);

	//! 差が2以上になればtrueを返す
	if (RightStickDif > 0.01f) {
		RightStickDif = 0;
		return true;
	}
	return false;
}

/* レバガチャ左 */
bool LeftStickMashing()
{
	//! 前フレームとの差分が一定を超えたらtrueを返す
	Vector2 Dif = GetControllerRightStickDif();
	LeftStickDif += Dif.x + Dif.y;
	//! 差が2以上になればtrueを返す
	if (LeftStickDif > 2.0f) {
		LeftStickDif = 0;
		return true;
	}
	return false;
}

/* 右のトリガーの前フレームの押下の差を取得する関数(押すとき) */
//! 押下の数値は　0～255の間です
int GetControllerRightTriggerDifPush()
{
	int dif = 0;
	dif = State.Gamepad.bRightTrigger - OldState.Gamepad.bRightTrigger;
	return dif;
}


/* コントローラーの振動の強さ（速さ）を設定できる関数 ************************
*  引数　右のモーターの振動の強さ　左のモーターの振動の強さ                  *
*  引数の詳細 設定した数字 (0～20) の大きさによって振動の強さが変わります    *
*****************************************************************************/
void SetControllerVibration(int _leftvibrationpower, int _rightvibrationpower)
{
	const int VibrationValue = 3276;  //! バイブレーションのレベルごとに増える値
	const int MaxVibrationPower = 20; //! バイブレーションの最大の強さ
	if (_leftvibrationpower > MaxVibrationPower) {
		_leftvibrationpower = MaxVibrationPower;
	}
	if (_rightvibrationpower > MaxVibrationPower) {
		_rightvibrationpower = MaxVibrationPower;
	}
	LeftMotorSpeed = _leftvibrationpower * VibrationValue;
	RightMotorSpeed = _rightvibrationpower * VibrationValue;
}

void SetControllerVibrationTime(int _leftvibrationpower, int _rightvibrationpower, int _frame)
{
	const int VibrationValue = 3276;  //! バイブレーションのレベルごとに増える値
	const int MaxVibrationPower = 20; //! バイブレーションの最大の強さ
	if (_leftvibrationpower > MaxVibrationPower) {
		_leftvibrationpower = MaxVibrationPower;
	}
	if (_rightvibrationpower > MaxVibrationPower) {
		_rightvibrationpower = MaxVibrationPower;
	}
	LeftMotorSpeed = _leftvibrationpower * VibrationValue;
	RightMotorSpeed = _rightvibrationpower * VibrationValue;
	VibrationFrame = _frame;
	CurrentVibrationFrame = 0;
}


