#include "Vector2.h"
#include <math.h>

//! �R���X�g���N�^
Vector2::Vector2()
{
	x = y = 0;
}

//! �����t���R���X�g���N�^
Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}


//! +���Z�q�̃I�[�o�[���[�h
Vector2 Vector2::operator+(Vector2  _vec)
{
	Vector2 tmp;
	tmp.x = x + _vec.x;
	tmp.y = y + _vec.y;

	return tmp;
}


//! +=���Z�q�̃I�[�o�[���[�h
void Vector2::operator+=(Vector2  _vec)
{	
	x += _vec.x;
	y += _vec.y;
}


//! -���Z�q�̃I�[�o�[���[�h
Vector2 Vector2::operator-(Vector2 _vec)
{
	Vector2 tmp;
	tmp.x = x - _vec.x;
	tmp.y = y - _vec.y;

	return tmp;
}

//! -=���Z�q�̃I�[�o�[���[�h
void Vector2::operator-=(Vector2 _vec)
{
	x -= _vec.x;
	y -= _vec.y;
}

//! / ���Z�q�̃I�[�o�[���[�h
Vector2 Vector2::operator/(float _v)
{
	Vector2 tmp;

	tmp.x = x / _v;
	tmp.y = y / _v;

	return tmp;
}

//! /=���Z�q
void Vector2::operator/=(float _v)
{
	x /= _v;
	y /= _v;
}

//! =���Z�q
void Vector2::operator=(float _v)
{
	x = _v;
	y = _v;
}

bool Vector2::operator==(Vector2 _vec)
{
	if (x == _vec.x && y == _vec.y) {
		return true;
	}

	return false;
}

bool Vector2::operator==(float _v)
{
	if (x == _v && y == _v) {
		return true;
	}

	return false;
}

bool Vector2::operator!=(float _v)
{
	if (x != _v && y != _v) {
		return true;
	}
	return false;
}

//! *���Z�q ���� : float
Vector2 Vector2::operator*(float _v)
{
	Vector2 tmp;
	tmp.x = x * _v;
	tmp.y = y * _v;


	return tmp;
}

//! *���Z�q ���� : int
Vector2 Vector2::operator*(int _v)
{
	Vector2 tmp;
	tmp.x = x * _v;
	tmp.y = y * _v;


	return tmp;
}

void Vector2::operator*=(float _v)
{
	x *= _v;
	y *= _v;
}

bool Vector2::operator>(Vector2 _v)
{
	float tmp = x + y;
	float tmp2 = _v.x + _v.y;
	if (tmp > tmp2) {
		return true;
	}
	return false;
}



/* -------------------------------------------------------------
// ����Ǝ��g�̒������������߂�֐�                           //
// ����   : ����̈ʒu                                        //
// �߂�l : ����Ƃ̒�������                                  */
float Vector2::PosToPos(Vector2 _pos)
{
	float distance; //! ����Ǝ��g�Ƃ̒�������
	
	//! �O�����̒藝���g���ċ��߂�
	float xdis = x - _pos.x;
	float ydis = y - _pos.y;
	distance = sqrt(pow(xdis, 2) + pow(ydis, 2));

	return distance;
}


/* ------------------------------------------------------------
// ���̃x�N�g����x,y�v�f����̗ʂɂ����l��Ԃ�             //
// �߂�l : �x�N�g���̗v�f����ɂ����l                     */
float Vector2::GetVetor()
{	
	return sqrt(powf(x,2) + powf(y,2));
}

//! ���W�̃Z�b�^�[
void Vector2::SetVector(float _x, float _y)
{
	x = _x;
	y = _y;
}
