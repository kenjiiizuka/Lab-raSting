#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "Player.h"
/* --------------------------------------------------------------
// カメラクラス                                                //
// メインとなるカメラです                                      //
// 制作者 : 飯塚 健司                                          */

#define CAMERA Camera::GetIns()

class Camera
{
public:
	static Camera * GetIns();
	static void Create();
	static void Destroy();

	void Update();                                 //! 更新処理
	Vector2 GetCameraPos();                        //! カメラの座標のゲッター
	Vector2 GetCameraMove();                       //! カメラの移動量のゲッター
	FLOAT2 GetScale();                             //! カメラの拡大縮小率のゲッター
	void Reset();                                  //! カメラの位置をリセットする
	void CameraFix(GameObject * _gameobj);         //! カメラので見たときの位置拡大率をしていしたオブジェクトに反映する
	void EffectFix(float & _x, float & _y , float & scale_x,float & _scale_y);                              //! カメラでエフェクトを見たときの位置に調整する
	void SetZoom(float _x, float _y);              //! 拡大縮小率のセッター
	void FollowObj(GameObject * _followobj, float _followthresholdX = 0, float _followthresholdY = 0);    //! 指定したオブジェクトを追従するようにする関数
	void FollowPlayer(Player * _player, float _followthresholdX = 0, float _followthresholdY = 0);
	void StartVibration(int _vibepower); //! 画面振動関数(カメラを小刻みに動かして振動しているように見せます)
	bool GetVibration(); //! 振動しているかを返す関数
	//! カメラを止める関数
	void MoveLeft(bool _state);
	void MoveRight(bool _state);
	void MoveTop(bool _state);
	void MoveDown(bool _state);
	bool GetRightMove();
	void SetFollowWay(bool _x, bool _y); //! 追従してほしい方向のセッター
	void MoveCamera(Vector2 _move);      //!カメラを動かす関数
private:
	Camera();  //! コンストラクタ
	~Camera(); //! デストラクタ
	void Vibration(); //! 画面振動関数

	static Camera * mcpIns;
	Vector2 mcPos;             //! カメラの位置
	Vector2 mcOldPos;          //! カメラの位置
	Vector2 mcMovement;        //! カメラの移動量
	GameObject * mcpFollowObj; //! 追従するオブジェクトのポインタ
	Player * mcpFollowPlayer;  //! 追従するプレイヤーのポインタ
	Vector2 FollowObjOldVec;   //! 追従するオブジェクトの前フレームの座標
	float mZoomX;              //! 拡大縮小率
	float mZoomY;              //! 拡大縮小率
	FLOAT2 msFollowThreshold;  //! 追従する位置

	//! 画面振動に使う変数
	int FrameCnt;     //! 画面振動を開始してから経過したフレームを数える
	Vector2 VibeMent; //! 画面振動して振動した量
	int mVibePower;    //! 画面振動の強さ
	//! それぞれの方向の移動可能か判断フラグ
	bool mLeftMove;
	bool mRightMove;
	bool mTopMove;
	bool mDownMove;
	bool mFollowPlayer; //! プレイヤーを追従しているか
	bool mFollowObj;    //! オブジェクトを追従しているか(プレイヤーはのぞく)
	bool mVibration;    //! 画面振動するかどうかの判断
	bool Follow_y;      //! yの方向に追従するかしないか判断する
	bool Follow_x;		//! xの方向に追従するかしないか判断する

};


