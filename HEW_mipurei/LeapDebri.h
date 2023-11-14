#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

//! �{�X�̍U���Ŕ��ł��邪�ꂫ

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
		State_Ground, //! �n�ʂɂ��Ă鎞
		State_None
	};
	LeapState State = State_None;
	Box * Col;	
	Box * AtkCol;
	float MaxMoveMent = 0;
	Vector2 Speed;
	float TotalMoveMent_Y = 0;  //! ���̂��ꂫ�ō����B�_	
	float PrevTime;
	float LeapFrame = 0;
	float Decrece_Y;  //! �ō����B�_��Y�̈ړ��ʂ��[���ɂȂ錸�Z�l
	float Decrece_X;  //! �ō����B�_��X�̈ړ��ʂ��[���ɂȂ錸�Z�l
	int AliveCnt;
	float Arufa = 0.0;
};

