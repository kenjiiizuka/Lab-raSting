#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "TextureManager.h"

/* --------------------------------- 
// ステージセレクト画面の時にある */
class StageDoor :
	public AnimationHitObject
{
public:
	StageDoor();
	
	~StageDoor();

	void Update();
	void Draw();
	Box * GetBoxCol();
	void SetColSize(float _x, float _y); 
	void SetHit(bool _state); 
	bool GetHit();

private:

	enum DoorState{
		Door_Open,  //! 開いてる途中
		Door_Close, //! 閉じてる途中
		Door_Opned, //! 開ききった状態
		Door_Closed //! 閉じ切った状態
	};

	
	DoorState State;   //! 状態
	Vector2 ColSize;   //! 当たり判定のサイズ
	Box * mcpBox;
	AnimationHitObject * AbuttonObj;
	bool CurrentHit;   //! 現在プレイヤーがドアの前にいるのかを判断するフラグ
	int FrameCnt;      //! フレームを数える
	int CloseFrameCnt; //! 閉じるとき用のフレームカウント
	bool Open;         //! 扉が空いてるか空いてないか
	bool Sound = false;
	bool Abutton;        //! Aボタン描画フラグ

};

