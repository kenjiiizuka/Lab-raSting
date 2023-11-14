#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "PlayerState.h"
class Dynamo :
	public AnimationHitObject
{
public:
	Dynamo();
	~Dynamo();

	//! 刺さる、放電されたら、電気が撮ったことを対象にギミックに伝える
	void Update();
	void Draw();
	virtual TailReaction ReturnReaction(float _power, bool _elect); //! 刺されてしっぽにリアクションを返す
	virtual void SetChrage(bool _state);               //! 発電機のチャージされたかどうかのセッター
	Box * GetBoxCol(); //! 当たり判定のゲッター
	bool GetChargeState();  //! チャージされたかどうかを返す 

protected:
	bool mCharge;      //! 放電されたかどうか
	bool Doing;        //! チャージ中
	bool mChargeFin;   //! チャージ完了
	Box * mcpBox;      //! 当たり判定
private:
	
	Vector2 ColSize;   //! 当たり判定のサイズ	
};
