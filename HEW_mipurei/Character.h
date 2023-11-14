#pragma once
#include "AnimationHitObject.h"
#include "Log.h"
#include "Box.h"
#include "Shape.h"
#include "Image.h"

/* =================================================================================================================================== 
// キャラクタークラス　このクラスを基底にして、敵やプレイヤーを作って下さい														    //
// キャラクター全体に共通する仕様がまで決まっていないため、まだ未完成です。仕様に合わせて変更しやすいように継承先で気を付けて下さい // 
// 制作者 : 飯塚 健司*/


//! キャラクターは基本的に矩形で当たり判定を取ろうと思います　
//! 場合によっては円のキャラもいると思うのでその場合は、そのクラスで新たにCircleクラスを生成し、それのゲッターや必要な処理をしてください

//! 重力などこのキャラクターにかかっている力の計算をします
class Character :
	public AnimationHitObject
{
public:
	Character();  //! コンストラクタ	
	~Character(); //! デストラクタ
	void Update() override; //! 更新処理
	virtual void Draw() override;
	void SetTouchGround(bool _state);   //! タッチグラウンドのセッター
	virtual Box * GetBoxCol();                   //! 矩形の当たり判定情報のゲッター
protected:
	Vector2 mcMoveVector;      //! 移動する量　この値を自身のPosに加算して移動などをするようにする予定
	bool mTouchGraund;          //! 地面にいるかいないか判断する
	double mSecond;             //! 地面についている間現在の時間を取得する	
	Box * mcpBoxCol;            //! 矩形の当たり判定
	Vector2 ColSize;            //! 当たり判定のサイ
	double CurrentTime;         //! このキャラクターが生成されてからの経過時間 
	double PrevTime;            //! このキャラクターが生成されてからの前フレームの経過時間
	double GravityTime;         //! 重力の影響を受け始めた時間
private:
	Log * CharDeLog;
	Image * mcpImage;           //! 当たり判定を見たいときに使ってください
};

