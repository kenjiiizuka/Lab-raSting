#pragma once
#include "Shape.h"
#include "FLOAT2.h"


/* ------ 
** 矩形*/
class Box :
	public Shape
{
public:
	Box(Vector2 & _pos, float _width, float _height);
	FLOAT2 GetSize(); //! 縦横の大きさのゲッター

	void SetSize(float _width, float _height);
	//! 各辺の位置のゲッター
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

private:
	float  mWidth;
	float  mHeight;
};

