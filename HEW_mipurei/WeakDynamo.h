#pragma once
#include "Dynamo.h"

//! 壊れやすい発電機です

class WeakDynamo :
	public Dynamo
{
public:
	WeakDynamo();
	
	void Update() override;
	TailReaction ReturnReaction(float _power, bool _elect) override; //! 刺されてしっぽにリアクションを返す
	bool Overheat();                                    //! オーバーヒートしたかを返す
	void SetChrage(bool _state);                        //! 発電機のチャージされたかどうかのセッター
private:
	bool mBreak;    //! 壊れるフラグ
	bool mOverheat; //! オーバーヒートフラグ 赤くなったかどうか
	bool mCoolDown; //! オーバーヒートしたらクールダウンするためのフラグ
	float g,b;      //! グリーン　ブルー
};

