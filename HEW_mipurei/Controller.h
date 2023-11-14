#pragma once
#include "FLOAT2.h"
#include "Vector2.h"
// �{�^��ID
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

/* �R���g���[���[�������֐� */
bool ControllerInit();
/* �R���g���[���[�X�V�֐� */
bool ControllerUpdate();

/* ���E�̃X�e�B�b�N�̎擾 */
Vector2 GetControllerLeftStick();
Vector2 GetControllerRightStick();

/* ���E�̃X�e�B�b�N�̑O�t���[���Ƃ̓|���̍� */
Vector2 GetControllerLeftStickDif();
Vector2 GetControllerRightStickDif();

/* ���E�̃X�e�B�b�N�̑O�t���[���Ƃ̓|���̍��̃x�N�g�� */
float GetControllerLeftStickDifVector();
float GetControllerRightStickDifVector();

/* ���E�̃X�e�B�b�N�̊p�x�̎擾(Radian)*/
float GetControllerRightStickAngle();
float GetControllerLeftStickAngle();

/* ���E�̃X�e�B�b�N�̊p�x�̎擾(Degree)*/
float GetControllerRightStickAngleDeg();
float GetControllerLeftStickAngleDeg();

/* �w�肵���{�^���̃v���X�擾�i�������j*/
bool GetControllerButtonPress(eButton _button);

/* �w�肵���{�^���̃g���K�[�擾�֐��i�������u�ԁj*/
bool GetControllerButtonTrigger(eButton _button);

/* �E�g���K�[�̑O�t���[���Ƃ̉����̍����擾(�����Ƃ�)*/
int GetControllerRightTriggerDifPush();
/* �E�g���K�[�̑O�t���[���Ƃ̉����̍����擾(�����Ƃ�)*/
int GetControllerRightTriggerDifRelease();

int GetControllerRightTrigger();

//! ���o�K�`��
bool RightStickMashing();
bool LeftStickMashing();

/* �R���g���[���[�̐U����ݒ�ł��� */
void SetControllerVibration(int _leftvibrationpower, int _rightvibrationpower);

void SetControllerVibrationTime(int _leftvibrationpower, int _rightvibrationpower ,int _frame);