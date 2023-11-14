#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

//! ボスの攻撃で飛んでくるがれき

class LeapDebri :
	public AnimationHitObject
{
public:
	LeapDebri();
	~LeapDebri();

	void Update();
	void Draw();

	void Leap(Vector2 _InitPos,Vector2 _power);
	void Fadeout();

	Box * GetCol();
	Box * GetAtkCol();
private:
	enum LeapState {
		State_Leap,
		State_Ground, //! 地面についてる時
		State_None
	};
	LeapState State = State_None;
	Box * Col;	
	Box * AtkCol;
	float MaxMoveMent = 0;
	Vector2 Speed;
	float TotalMoveMent_Y = 0;  //! このがれき最高到達点	
	float PrevTime;
	float LeapFrame = 0;
	float Decrece_Y;  //! 最高到達点でYの移動量がゼロになる減算値
	float Decrece_X;  //! 最高到達点でXの移動量がゼロになる減算値
	int AliveCnt;
	float Arufa = 0.0;
};

