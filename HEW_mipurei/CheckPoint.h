#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

/* --------------- 
// 中間ポイント */

class CheackPoint :
	public AnimationHitObject
{
public:
	CheackPoint();
	~CheackPoint();
	void Update() override;
	void HitCheckPoint(); //! 中間に触れた
	bool GetCheck();      //! 中間に触れたかどうかのゲッター
	Box * GetBox();       //! 矩形の当たりゲッター
private:
	Box * mcpBox;   //! 矩形の当たり
	bool Check;     //! 中間に触れたかどうか
	bool Sound = false; //! SEをならしたかどうか
};

