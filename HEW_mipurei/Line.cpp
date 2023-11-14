#include "Line.h"
#include <math.h>
#include "Angle.h"
//! �R���X�g���N�^
Line::Line(Vector2 _pos, float _length, float _angle)
	: Shape::Shape(_pos)
{
	mLength = _length;
	mAngle = _angle;
}

//! �����̒����̃Q�b�^�[
float Line::GetLength()
{
	return mLength;
}

//! �����̃Z�b�^�[
void Line::SetLength(float _length)
{
	mLength = _length;
}

//! �p�x�̃Q�b�^�[
float Line::GetAngle()
{
	return mAngle;
}

//! �p�x�̃Q�b�^�[
void Line::SetAngle(float _angle)
{
	mAngle = _angle;
}

//! �����̎n�_�̃Q�b�^�[
Vector2 Line::GetLine_StartPos()
{
	float x = mcPos.x + cos(mAngle) *mLength;
	float y = mcPos.y + sin(mAngle) *mLength;
	return Vector2(x,y);
}

//! �I�_�̃Q�b�^�[
Vector2 Line::GetLine_EndPos()
{
	float x = mcPos.x + cos(mAngle + PI) *mLength;
	float y = mcPos.y + sin(mAngle + PI) *mLength;
	return Vector2(x, y);
}
