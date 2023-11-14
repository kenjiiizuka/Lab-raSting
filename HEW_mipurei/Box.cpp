#include "Box.h"

//! コンストラクタ
Box::Box(Vector2 & _pos, float  _width, float  _height)
	: Shape(_pos)
{
	mWidth = _width;
	mHeight = _height;
}

//! サイズのゲッター
FLOAT2 Box::GetSize()
{
	return FLOAT2(mWidth, mHeight);
}

//! サイズのセッター
void Box::SetSize(float _width, float _height)
{
	mWidth = _width;
	mHeight = _height;
}


//! 左の辺のゲッター
float Box::GetLeft()
{
	return (mcPos.x - mWidth /2.0f);
}

//! 右辺のゲッター
float Box::GetRight()
{
	return (mcPos.x + mWidth /2.0f);
}

//! 上辺のゲッター
float Box::GetTop()
{
	return (mcPos.y + mHeight / 2.0f);
}

//! 下辺のゲッター
float Box::GetBottom()
{
	return (mcPos.y - mHeight / 2.0f);
}

