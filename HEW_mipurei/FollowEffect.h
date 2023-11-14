#pragma once
#include "Effect.h"

//! 追従するエフェクトです

class FollowEffect :
	public Effect
{
public:
	FollowEffect(EffectInf _effect, eEffect _effectid, float & _x, float & _y);
	
	void Update() override;
	void SetLoop(bool _loop) { Loop = _loop; }
private:
	float & x;
	float & y;

	bool Loop = false;
};

