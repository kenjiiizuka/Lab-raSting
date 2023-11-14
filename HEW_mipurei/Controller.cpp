#include "Controller.h"
#include "Angle.h"
#include <Windows.h>
#include <Xinput.h>
#include <math.h>

#pragma comment (lib,"xinput.lib")

#define THUMBSTICKMAXVALUE 32767.0f

XINPUT_STATE State; //! �R���g���[���[�̏��
XINPUT_STATE OldState; //! �R���g���[���[�̑O�t���[���̏��
int ButtonID[Button_Max];
bool ButtonState[Button_Max];
bool ButtonOldState[Button_Max];

XINPUT_VIBRATION Vibration; //! �R���g���[���[�̃o�C�u���[�V�����̏��
WORD LeftMotorSpeed = 0;
WORD RightMotorSpeed = 0;
float RightStickDif = 0;      //! �E�X�e�B�b�N�̃��o�K�`��������Ƃ��Ɏg���ϐ�
float LeftStickDif = 0;       //! ���X�e�B�b�N�̃��o�K�`��������Ƃ��Ɏg���ϐ�
int CurrentVibrationFrame = 0; //! �U���̌o�ߎ���
int VibrationFrame = 0;	      //! �U�����鎞�Ԃ̒���

bool ControllerInit()
{
	// �{�^��ID�̐ݒ�
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
	
	// �z��̏�����
	for (int num = 0; num < Button_Max; num ++) {
		ButtonState[num] = false;
		ButtonOldState[num] = false;
	}

	ZeroMemory(&State, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &State);

	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	
	if (dwResult != ERROR_SUCCESS) {
		//	MessageBoxA(NULL, "�R���g���[���[�ڑ����s", "�G���[", MB_OK);
		return false;
	}
	else {
		return true;
	}
}

/* �R���g���[���[�̏�Ԃ̍X�V *******/
bool ControllerUpdate()
{	
	// �O�t���[���̏��Ƃ��ĕۑ�
	for (int num = 0; num < Button_Max; num++) {
		ButtonOldState[num] = ButtonState[num];
	}

	//! �O�t���[���̃R���g���[���[�̏�ԂƂ��ĕۑ�
	OldState = State;
	// �R���g���[���[�̏�Ԃ̎擾
	DWORD dwResult = XInputGetState(0, &State);	


	// ������Ă���{�^����T��
	for (int num = 0; num < Button_Max; num++) {

		if (State.Gamepad.wButtons == ButtonID[num]) {
			ButtonState[num] = true;
		}
		else {
			ButtonState[num] = false;
		}
	}

	// ���g���K�[�{�^���̉����̔��f
	if (State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		ButtonState[Button_LT] = true;
	}
	else {
		ButtonState[Button_LT] = false;
	}

	// �E�g���K�[�{�^���̉����̔��f
	if (State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		ButtonState[Button_RT] = true;
	}
	else {
		ButtonState[Button_RT] = false;
	}

	// �U���̐ݒ�
	Vibration.wLeftMotorSpeed = LeftMotorSpeed ;
	Vibration.wRightMotorSpeed = RightMotorSpeed;

	XInputSetState(0, &Vibration);

	//! �o�C�u���[�V�����̎��Ԃ��Z�b�g����Ă����玞�Ԃ��͂���
	if (VibrationFrame != 0) {
		//! �ݒ肳�ꂽ���Ԍo�߂�����U������߂�
		if (CurrentVibrationFrame >= VibrationFrame) {
			LeftMotorSpeed = 0;
			RightMotorSpeed = 0;
			VibrationFrame = 0;
		}
		CurrentVibrationFrame += 1;
	}
	else {
		// �U���̑��x�����炵�Ă���
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


/* ���X�e�B�b�N�̓|�����擾����֐� *******************************
* �@�߂�l�@�X�e�B�b�N�̓|���� (-1.0f �` 1.0f) �̒l�ŕԂ��Ă��܂� *
**********************************************************************/
Vector2 GetControllerLeftStick()
{
	// �f�b�h�]�[���̐ݒ�
	if ((State.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		State.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(State.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			State.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		State.Gamepad.sThumbLX = 0;
		State.Gamepad.sThumbLY = 0;
	}
	// �X�e�B�b�N�̓|�����v�Z
	Vector2 Stick;
	Stick.x = State.Gamepad.sThumbLX / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = State.Gamepad.sThumbLY / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}



/* �E�X�e�B�b�N�̓|�����擾����֐� *******************************
* �@�߂�l�@�X�e�B�b�N�̓|���� (-1.0f �` 1.0f) �̒l�ŕԂ��Ă��܂� *
**********************************************************************/
Vector2 GetControllerRightStick()
{
	// �f�b�h�]�[���̐ݒ�
	if ((State.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		State.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(State.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			State.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		State.Gamepad.sThumbRX = 0;
		State.Gamepad.sThumbRY = 0;
	}

	// �X�e�B�b�N�̓|�����v�Z
	Vector2 Stick;
	Stick.x = State.Gamepad.sThumbRX / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = State.Gamepad.sThumbRY / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}

/* ���X�e�B�b�N�̍��̎擾 */
Vector2 GetControllerLeftStickDif()
{
	float x = (float)OldState.Gamepad.sThumbLX - State.Gamepad.sThumbLX;
	float y = (float)OldState.Gamepad.sThumbLY - State.Gamepad.sThumbLY;
	Vector2 Stick;
	Stick.x = x / (THUMBSTICKMAXVALUE * 100.0f);
	Stick.y = y / (THUMBSTICKMAXVALUE * 100.0f);

	return Stick;
}

/* �E�X�e�B�b�N�̍��̎擾 */
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

/* �E�X�e�B�b�N�̑O�t���[���Ƃ̓|���̍��̃x�N�g�� */
float GetControllerLeftStickDifVector()
{	
	Vector2 vector = GetControllerLeftStickDif();
	return vector.GetVetor() * 100;
}

/* ���X�e�B�b�N�̑O�t���[���Ƃ̓|���̍��̃x�N�g�� */
float GetControllerRightStickDifVector()
{
	Vector2 vector = GetControllerRightStickDif();
	return vector.GetVetor() * 100;
}

/* �E�X�e�B�b�N�̓|��Ă���p�x�̎擾�֐� */
float GetControllerRightStickAngle()
{	
	//! �f�b�h�]�[��
	int DeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * 2.5f;
	// �f�b�h�]�[���̐ݒ�
	if ((State.Gamepad.sThumbRX <  DeadZone &&
		State.Gamepad.sThumbRX > -DeadZone) &&
		(State.Gamepad.sThumbRY <  DeadZone &&
			State.Gamepad.sThumbRY > -DeadZone))
	{
		State.Gamepad.sThumbRX = 0;
		State.Gamepad.sThumbRY = 0;
	}

	// �X�e�B�b�N�̓|�����v�Z
	Vector2 Right;
	Right.x = State.Gamepad.sThumbRX / (THUMBSTICKMAXVALUE * 100.0f);
	Right.y = State.Gamepad.sThumbRY / (THUMBSTICKMAXVALUE * 100.0f);

	return GetAngle(Right.x,Right.y);
}

/* ���X�e�B�b�N�̓|��Ă���p�x�̎擾�֐� */
float GetControllerLeftStickAngle()
{
	Vector2 Left = GetControllerLeftStick();
	return GetAngle(Left.x, Left.y);
}

/* �E�X�e�B�b�N�̓|��Ă���p�x�̎擾(Degree) */
float GetControllerRightStickAngleDeg()
{
	return RadianToDegree(GetControllerRightStickAngle());
}

/* ���X�e�B�b�N�̓|��Ă���p�x�̎擾(Degree) */
float GetControllerLeftStickAngleDeg()
{
	return RadianToDegree(GetControllerLeftStickAngle());
}

/* �{�^����������Ă��邩���擾����֐� *******
*  �����@�{�^��ID                             *
**********************************************/
bool GetControllerButtonPress(eButton  _button)
{
	return ButtonState[_button];
}

/* �{�^���̃g���K�[�擾������֐��@**********
** �����@�{�^��ID�@�@�@�@�@�@�@�@           * 
********************************************/
bool GetControllerButtonTrigger(eButton _button)
{
	if (ButtonOldState[_button] != true && ButtonState[_button] == true) {
		return true;
	}
	return false;
}

/* �E�̃g���K�[�̑O�t���[���̉����̍����擾����֐�(�����Ƃ�) */
//! �����̐��l�́@0�`255�̊Ԃł�
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


/* ���o�K�`���E */
bool RightStickMashing()
{
	//! �O�t���[���Ƃ̍��������𒴂�����true��Ԃ�
	Vector2 Dif = GetControllerRightStickDif();
	if (Dif == 0) {
		int a = 0;
	}
	RightStickDif += fabs(Dif.x) + fabs(Dif.y);

	//! ����2�ȏ�ɂȂ��true��Ԃ�
	if (RightStickDif > 0.01f) {
		RightStickDif = 0;
		return true;
	}
	return false;
}

/* ���o�K�`���� */
bool LeftStickMashing()
{
	//! �O�t���[���Ƃ̍��������𒴂�����true��Ԃ�
	Vector2 Dif = GetControllerRightStickDif();
	LeftStickDif += Dif.x + Dif.y;
	//! ����2�ȏ�ɂȂ��true��Ԃ�
	if (LeftStickDif > 2.0f) {
		LeftStickDif = 0;
		return true;
	}
	return false;
}

/* �E�̃g���K�[�̑O�t���[���̉����̍����擾����֐�(�����Ƃ�) */
//! �����̐��l�́@0�`255�̊Ԃł�
int GetControllerRightTriggerDifPush()
{
	int dif = 0;
	dif = State.Gamepad.bRightTrigger - OldState.Gamepad.bRightTrigger;
	return dif;
}


/* �R���g���[���[�̐U���̋����i�����j��ݒ�ł���֐� ************************
*  �����@�E�̃��[�^�[�̐U���̋����@���̃��[�^�[�̐U���̋���                  *
*  �����̏ڍ� �ݒ肵������ (0�`20) �̑傫���ɂ���ĐU���̋������ς��܂�    *
*****************************************************************************/
void SetControllerVibration(int _leftvibrationpower, int _rightvibrationpower)
{
	const int VibrationValue = 3276;  //! �o�C�u���[�V�����̃��x�����Ƃɑ�����l
	const int MaxVibrationPower = 20; //! �o�C�u���[�V�����̍ő�̋���
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
	const int VibrationValue = 3276;  //! �o�C�u���[�V�����̃��x�����Ƃɑ�����l
	const int MaxVibrationPower = 20; //! �o�C�u���[�V�����̍ő�̋���
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


