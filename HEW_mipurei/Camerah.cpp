#include "Camerah.h"
#include "DirectInput8.h"
#include "Log.h"

Camera * Camera::mcpIns = nullptr;

//! コンストラクタ
Camera::Camera()
{
	mcPos.x = 0;
	mcPos.y = 0;
	mZoomX = 1.0f;
	mZoomY = 1.0f;
	mcpFollowObj = nullptr;
	mcpFollowPlayer = nullptr;

	//! フラグを初期化
	mLeftMove = false;
	mRightMove = false;
	mTopMove = false;
	mDownMove = false;
	mFollowPlayer = false;
	mFollowObj = false;
	mVibration = false;
}

//! デストラクタ
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
	mcMovement = 0; //! 移動量のクリア

	//! 画面振動があった時の処理
	if (mVibration) { Vibration(); }

	//! プレイヤーは複数のオブジェクトで構成されているので特別に処理をします
	//! プレイヤーを追従する場合の処理
	else if (mFollowPlayer) {
		//! 追従X方向
		if (Follow_x) {
			if (mcpFollowPlayer->GetVec().x <= -msFollowThreshold.x && mLeftMove) { //! 左
				mcMovement.x = -msFollowThreshold.x - mcpFollowPlayer->GetVec().x;
				//mcpFollowPlayer->SetVec(Vector2(-msFollowThreshold.x, mcpFollowPlayer->GetVec().y));
			}
			else if (mcpFollowPlayer->GetVec().x >= msFollowThreshold.x && mRightMove) { //! 右
				mcMovement.x = msFollowThreshold.x - mcpFollowPlayer->GetVec().x;
				//mcpFollowPlayer->SetVec(Vector2(msFollowThreshold.x, mcpFollowPlayer->GetVec().y));
			}
		}
		//! 追従Y方向
		if (Follow_y) {			
			if (mcpFollowPlayer->GetVec().y <= -msFollowThreshold.y && mDownMove) { //! 下
				mcMovement.y = -msFollowThreshold.y - mcpFollowPlayer->GetVec().y;
				//mcpFollowPlayer->SetVec(Vector2(mcpFollowPlayer->GetVec().x, -msFollowThreshold.y + 0.001f));
			}
			else if (mcpFollowPlayer->GetVec().y >= msFollowThreshold.y && mTopMove) { //! 上
				mcMovement.y = msFollowThreshold.y - mcpFollowPlayer->GetVec().y;
				//mcpFollowPlayer->SetVec(Vector2(mcpFollowPlayer->GetVec().x, msFollowThreshold.y - 0.001f));
			}
		}
		mcpFollowPlayer->SetVec(mcpFollowPlayer->GetVec() + mcMovement);
	}
}

/* ================
// 画面振動関数  */
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
	FrameCnt += 1; // フレームを数える
}

//! カメラの位置のゲッター
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

//! カメラのリセット関数
void Camera::Reset()
{
	mcPos.x = 0;
	mcPos.y = 0;
	mZoomX = 1.0f;
	mZoomY = 1.0f;
	mcpFollowObj = nullptr;
	mcpFollowPlayer = nullptr;

	//! フラグを初期化
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


//! カメラの位置や拡大縮小率をオブジェクトに反映させる
void Camera::CameraFix(GameObject * _gameobj)
{
	//! 画面振動をしていたら追従関係なく全てのオブジェクトをゆらす
	if (mVibration) {
		_gameobj->SetVec(_gameobj->GetVec() + mcMovement);
	}
	else {
		//! プレイヤーを追従していたら
		if (mFollowPlayer) {
			//! プレイヤー以外のオブジェクトにカメラからみた位置情報を渡す
		
			if (mcpFollowPlayer != _gameobj && mcpFollowPlayer->GetTail() != _gameobj) {
				Vector2 FixPos = _gameobj->GetVec() + mcMovement;
				_gameobj->SetVec(FixPos);
			}
			
		}
		//! オブジェクトを追従していたら
		else if (mFollowObj) {
			//! 追従しているオブジェクトにはカメラの移動量を加算しない
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
	_x += mcMovement.x; //! カメラから見た位置にする
	_y += mcMovement.y;
	_scale_y = mZoomY;
	_scale_x = mZoomX;
}

/* ------------------------------------------------- */
//! 追従したいオブジェクトのセッター
//! 引数 : 追従するオブジェクト , 画面上のどこから追従するのか
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
//! プレイヤーを追従するようにセットする関数
//! 引数 : 追従するオブジェクト , 画面上のどこから追従するのか
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
// 画面振動を開始する関数  //
// 引数 : 振動の強さ ５段階*/
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

//! カメラの方向の移動可能かをセットする関数
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
