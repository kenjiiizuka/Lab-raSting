#include "Line.h"
#include <math.h>
#include "Angle.h"
//! コンストラクタ
Line::Line(Vector2 _pos, float _length, float _angle)
	: Shape::Shape(_pos)
{
	mLength = _length;
	mAngle = _angle;
}

//! 線分の長さのゲッター
float Line::GetLength()
{
	return mLength;
}

//! 長さのセッター
void Line::SetLength(float _length)
{
	mLength = _length;
}

//! 角度のゲッター
float Line::GetAngle()
{
	return mAngle;
}

//! 角度のゲッター
void Line::SetAngle(float _angle)
{
	mAngle = _angle;
}

//! 線分の始点のゲッター
Vector2 Line::GetLine_StartPos()
{
	float x = mcPos.x + cos(mAngle) *mLength;
	float y = mcPos.y + sin(mAngle) *mLength;
	return Vector2(x,y);
}

//! 終点のゲッター
Vector2 Line::GetLine_EndPos()
{
	float x = mcPos.x + cos(mAngle + PI) *mLength;
	float y = mcPos.y + sin(mAngle + PI) *mLength;
	return Vector2(x, y);
}
