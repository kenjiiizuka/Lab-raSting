#pragma once
#include "FLOAT2.h"
#include "Vector2.h"
// ボタンID
enum eButton {
	Button_UP,
	Button_DOWN,
	Button_LEFT,
	Button_RIGHT,
	Button_MENU,
	Button_SCREEN,
	LEFT_STICK_THUMB,
	RIGHT_STICK_THUMB,
	Button_LB,
	Button_RB,
	Button_LT,
	Button_RT,
	Button_A,
	Button_B,
	Button_X,
	Button_Y,
	Button_Max
};

/* コントローラー初期化関数 */
bool ControllerInit();
/* コントローラー更新関数 */
bool ControllerUpdate();

/* 左右のスティックの取得 */
Vector2 GetControllerLeftStick();
Vector2 GetControllerRightStick();

/* 左右のスティックの前フレームとの倒れ具合の差 */
Vector2 GetControllerLeftStickDif();
Vector2 GetControllerRightStickDif();

/* 左右のスティックの前フレームとの倒れ具合の差のベクトル */
float GetControllerLeftStickDifVector();
float GetControllerRightStickDifVector();

/* 左右のスティックの角度の取得(Radian)*/
float GetControllerRightStickAngle();
float GetControllerLeftStickAngle();

/* 左右のスティックの角度の取得(Degree)*/
float GetControllerRightStickAngleDeg();
float GetControllerLeftStickAngleDeg();

/* 指定したボタンのプレス取得（長押し）*/
bool GetControllerButtonPress(eButton _button);

/* 指定したボタンのトリガー取得関数（押した瞬間）*/
bool GetControllerButtonTrigger(eButton _button);

/* 右トリガーの前フレームとの押下の差を取得(押すとき)*/
int GetControllerRightTriggerDifPush();
/* 右トリガーの前フレームとの押下の差を取得(離すとき)*/
int GetControllerRightTriggerDifRelease();

int GetControllerRightTrigger();

//! レバガチャ
bool RightStickMashing();
bool LeftStickMashing();

/* コントローラーの振動を設定できる */
void SetControllerVibration(int _leftvibrationpower, int _rightvibrationpower);

void SetControllerVibrationTime(int _leftvibrationpower, int _rightvibrationpower ,int _frame);