#pragma once
#include "Shape.h"
#include "FLOAT2.h"


/* ------ 
** ��`*/
class Box :
	public Shape
{
public:
	Box(Vector2 & _pos, float _width, float _height);
	FLOAT2 GetSize(); //! �c���̑傫���̃Q�b�^�[

	void SetSize(float _width, float _height);
	//! �e�ӂ̈ʒu�̃Q�b�^�[
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

private:
	float  mWidth;
	float  mHeight;
};

