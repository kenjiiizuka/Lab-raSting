#include "Box.h"

//! �R���X�g���N�^
Box::Box(Vector2 & _pos, float  _width, float  _height)
	: Shape(_pos)
{
	mWidth = _width;
	mHeight = _height;
}

//! �T�C�Y�̃Q�b�^�[
FLOAT2 Box::GetSize()
{
	return FLOAT2(mWidth, mHeight);
}

//! �T�C�Y�̃Z�b�^�[
void Box::SetSize(float _width, float _height)
{
	mWidth = _width;
	mHeight = _height;
}


//! ���̕ӂ̃Q�b�^�[
float Box::GetLeft()
{
	return (mcPos.x - mWidth /2.0f);
}

//! �E�ӂ̃Q�b�^�[
float Box::GetRight()
{
	return (mcPos.x + mWidth /2.0f);
}

//! ��ӂ̃Q�b�^�[
float Box::GetTop()
{
	return (mcPos.y + mHeight / 2.0f);
}

//! ���ӂ̃Q�b�^�[
float Box::GetBottom()
{
	return (mcPos.y - mHeight / 2.0f);
}

