#pragma once
#include "AnimationHitObject.h"
#include "PlayerState.h"
#include "Box.h"

//! 壊れるオブジェクトです　

class BreakObj :
	public AnimationHitObject
{
public:
	BreakObj();
	~BreakObj();
	void Update() override;
	void Draw() override;
	Box * GetBoxCol();
	TailReaction ReturnReaction(float _power);
	bool GetBreaked(); //! 壊されたか
private:
	Box * mcpBox;   //! 矩形の当たり判定
	bool mBreak;    //! 壊れたどうかのフラグ
	bool mBreaked;  //! 壊れて消えたフラグ
	int Cnt;         //! 壊れてからフレームを数える
	float Arufa;
};

