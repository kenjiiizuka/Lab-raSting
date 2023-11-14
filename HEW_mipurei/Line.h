#pragma once
#include "Shape.h"

/* ---------------------------
// 線の情報を持つクラスです */
//! 自身の座標を中心にした、長さの線です
class Line :
	public Shape
{
public:
	Line(Vector2 _pos, float _length, float _angle); //! コンストラクタ

	float GetLength();
	void SetLength(float _length);
	float GetAngle();
	void SetAngle(float _angle);
	Vector2 GetLine_StartPos(); //! 線分の始点のゲッター
	Vector2 GetLine_EndPos();   //! 線分の終点のゲッター
	
private:
	float mLength;
	float mAngle;
};

