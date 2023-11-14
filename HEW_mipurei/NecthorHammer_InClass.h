#pragma once
#include "Box.h"

//! ボスのハンマー インクラスです
class NecthorHammer
{
public:
	NecthorHammer();
	~NecthorHammer();

	Box * Col;    //! 衝突判定用
	Box * AtkCol; //! 攻撃判定用の当たり判定
	Vector2 Vec;
	Vector2 ColSize;
	bool TailHited = false;
	int Cnt = 0;
	bool Slamed = false;
};

