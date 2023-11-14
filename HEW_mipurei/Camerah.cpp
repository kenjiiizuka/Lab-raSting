#include "Camerah.h"
#include "DirectInput8.h"
#include "Log.h"

Camera * Camera::mcpIns = nullptr;

//! �R���X�g���N�^
Camera::Camera()
{
	mcPos.x = 0;
	mcPos.y = 0;
	mZoomX = 1.0f;
	mZoomY = 1.0f;
	mcpFollowObj = nullptr;
	mcpFollowPlayer = nullptr;

	//! �t���O��������
	mLeftMove = false;
	mRightMove = false;
	mTopMove = false;
	mDownMove = false;
	mFollowPlayer = false;
	mFollowObj = false;
	mVibration = false;
}

//! �f�X�g���N�^
Camera::~Camera()
{
	mcpFollowObj = nullptr;
}

Camera * Camera::GetIns()
{
	return mcpIns;
}

void Camera::Create()
{
	if (mcpIns == nullptr) { mcpIns = new Camera; }
}

void Camera::Destroy()
{
	delete mcpIns;
}

void Camera::Update()
{
	mcMovement = 0; //! �ړ��ʂ̃N���A

	//! ��ʐU�������������̏���
	if (mVibration) { Vibration(); }

	//! �v���C���[�͕����̃I�u�W�F�N�g�ō\������Ă���̂œ��ʂɏ��������܂�
	//! �v���C���[��Ǐ]����ꍇ�̏���
	else if (mFollowPlayer) {
		//! �Ǐ]X����
		if (Follow_x) {
			if (mcpFollowPlayer->GetVec().x <= -msFollowThreshold.x && mLeftMove) { //! ��
				mcMovement.x = -msFollowThreshold.x - mcpFollowPlayer->GetVec().x;
				//mcpFollowPlayer->SetVec(Vector2(-msFollowThreshold.x, mcpFollowPlayer->GetVec().y));
			}
			else if (mcpFollowPlayer->GetVec().x >= msFollowThreshold.x && mRightMove) { //! �E
				mcMovement.x = msFollowThreshold.x - mcpFollowPlayer->GetVec().x;
				//mcpFollowPlayer->SetVec(Vector2(msFollowThreshold.x, mcpFollowPlayer->GetVec().y));
			}
		}
		//! �Ǐ]Y����
		if (Follow_y) {			
			if (mcpFollowPlayer->GetVec().y <= -msFollowThreshold.y && mDownMove) { //! ��
				mcMovement.y = -msFollowThreshold.y - mcpFollowPlayer->GetVec().y;
				//mcpFollowPlayer->SetVec(Vector2(mcpFollowPlayer->GetVec().x, -msFollowThreshold.y + 0.001f));
			}
			else if (mcpFollowPlayer->GetVec().y >= msFollowThreshold.y && mTopMove) { //! ��
				mcMovement.y = msFollowThreshold.y - mcpFollowPlayer->GetVec().y;
				//mcpFollowPlayer->SetVec(Vector2(mcpFollowPlayer->GetVec().x, msFollowThreshold.y - 0.001f));
			}
		}
		mcpFollowPlayer->SetVec(mcpFollowPlayer->GetVec() + mcMovement);
	}
}

/* ================
// ��ʐU���֐�  */
void Camera::Vibration()
{
	if (FrameCnt <= 2) {
		mcMovement = Vector2(0.001f, 0.001f) * mVibePower;
		VibeMent += Vector2(0.001f, 0.001f) * mVibePower;
	}
	else if (FrameCnt <= 4) {
		mcMovement = Vector2(-0.002f, 0.001f) * mVibePower;
		VibeMent += Vector2(-0.002f, 0.001f) * mVibePower;
	}
	else if (FrameCnt <= 6) {
		mcMovement = Vector2(0.003f, -0.002f) * mVibePower;
		VibeMent += Vector2(0.003f, -0.002f) * mVibePower;
	}
	else if (FrameCnt <= 8) {
		mcMovement = Vector2(0.001f, -0.002f) * mVibePower;
		VibeMent += Vector2(0.001f, -0.002f) * mVibePower;
	}
	else if (FrameCnt <= 10) {
		mcMovement = Vector2(-0.002f, -0.001f) * mVibePower;
		VibeMent += Vector2(-0.002f, -0.001f) * mVibePower;
	}
	else if (FrameCnt <= 11) {
		mcMovement = Vector2(-VibeMent.x, -VibeMent.y);
		VibeMent = 0;
	}
	else {
		mVibration = false;
		mLeftMove = false;

		FrameCnt = 0;
	}
	FrameCnt += 1; // �t���[���𐔂���
}

//! �J�����̈ʒu�̃Q�b�^�[
Vector2 Camera::GetCameraPos()
{
	return mcPos;
}

Vector2 Camera::GetCameraMove()
{
	return mcMovement;
}

FLOAT2 Camera::GetScale()
{
	return FLOAT2(mZoomX, mZoomY);
}

//! �J�����̃��Z�b�g�֐�
void Camera::Reset()
{
	mcPos.x = 0;
	mcPos.y = 0;
	mZoomX = 1.0f;
	mZoomY = 1.0f;
	mcpFollowObj = nullptr;
	mcpFollowPlayer = nullptr;

	//! �t���O��������
	mLeftMove = false;
	mRightMove = false;
	mTopMove = false;
	mDownMove = false;
	mFollowPlayer = false;
	mFollowObj = false;
	mVibration = false;
	Follow_x = true;
	Follow_y = true;
}


//! �J�����̈ʒu��g��k�������I�u�W�F�N�g�ɔ��f������
void Camera::CameraFix(GameObject * _gameobj)
{
	//! ��ʐU�������Ă�����Ǐ]�֌W�Ȃ��S�ẴI�u�W�F�N�g����炷
	if (mVibration) {
		_gameobj->SetVec(_gameobj->GetVec() + mcMovement);
	}
	else {
		//! �v���C���[��Ǐ]���Ă�����
		if (mFollowPlayer) {
			//! �v���C���[�ȊO�̃I�u�W�F�N�g�ɃJ��������݂��ʒu����n��
		
			if (mcpFollowPlayer != _gameobj && mcpFollowPlayer->GetTail() != _gameobj) {
				Vector2 FixPos = _gameobj->GetVec() + mcMovement;
				_gameobj->SetVec(FixPos);
			}
			
		}
		//! �I�u�W�F�N�g��Ǐ]���Ă�����
		else if (mFollowObj) {
			//! �Ǐ]���Ă���I�u�W�F�N�g�ɂ̓J�����̈ړ��ʂ����Z���Ȃ�
			if (mcpFollowObj != _gameobj) {
				_gameobj->SetVec(_gameobj->GetVec() + mcMovement);
			}
		}
		else {	
			if (_gameobj->GetTag() != Tag_Tail) {
				_gameobj->SetVec(_gameobj->GetVec() + mcMovement);
			}
		}
	}
	_gameobj->SetScale(mZoomX,mZoomY);	
}

void Camera::EffectFix(float & _x, float & _y, float & _scale_x, float & _scale_y)
{
	_x += mcMovement.x; //! �J�������猩���ʒu�ɂ���
	_y += mcMovement.y;
	_scale_y = mZoomY;
	_scale_x = mZoomX;
}

/* ------------------------------------------------- */
//! �Ǐ]�������I�u�W�F�N�g�̃Z�b�^�[
//! ���� : �Ǐ]����I�u�W�F�N�g , ��ʏ�̂ǂ�����Ǐ]����̂�
void Camera::FollowObj(GameObject * _followobj, float _followthresholdX, float _followthresholdY )
{
	mcpFollowObj = _followobj;
	msFollowThreshold.x = _followthresholdX;
	msFollowThreshold.y = _followthresholdY;
	mFollowObj = true;

	if (_followobj == nullptr) {
		mFollowObj = false;
	}
}

/* ------------------------------------------------- */
//! �v���C���[��Ǐ]����悤�ɃZ�b�g����֐�
//! ���� : �Ǐ]����I�u�W�F�N�g , ��ʏ�̂ǂ�����Ǐ]����̂�
void Camera::FollowPlayer(Player * _player, float _followthresholdX, float _followthresholdY)
{
	mcpFollowPlayer = _player;
	msFollowThreshold.x = _followthresholdX;
	msFollowThreshold.y = _followthresholdY;
	mFollowPlayer = true;

	if (_player == nullptr) {
		mFollowPlayer = false;
	}
}

/* -------------------------- 
// ��ʐU�����J�n����֐�  //
// ���� : �U���̋��� �T�i�K*/
void Camera::StartVibration(int _vibepower)
{
	mVibration = true;
	if (_vibepower > 5) {
		_vibepower = 5;
	}
	else if (_vibepower < 1) {
		_vibepower = 1;
	}
	mVibePower = _vibepower;
}

bool Camera::GetVibration()
{
	return mVibration;
}

//! �J�����̕����̈ړ��\�����Z�b�g����֐�
void Camera::MoveLeft(bool _state)
{
	if(!mVibration)
	mLeftMove = _state;
}

void Camera::MoveRight(bool _state)
{
	if (!mVibration)
	mRightMove = _state;
}

void Camera::MoveTop(bool _state)
{
	if (!mVibration)
	mTopMove = _state;
}

void Camera::MoveDown(bool _state)
{
	if (!mVibration)
	mDownMove = _state;
}

bool Camera::GetRightMove()
{
	return mRightMove;
}

void Camera::SetFollowWay(bool _x, bool _y)
{
	Follow_x = _x;
	Follow_y = _y;
}

void Camera::MoveCamera(Vector2 _move)
{
	mcMovement += _move;
}

void Camera::SetZoom(float _x, float _y)
{
	mZoomX = _x;
	mZoomY = _y;
}
