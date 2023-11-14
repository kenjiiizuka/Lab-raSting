#include "Vector2.h"
#include <math.h>

//! コンストラクタ
Vector2::Vector2()
{
	x = y = 0;
}

//! 引数付きコンストラクタ
Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}


//! +演算子のオーバーロード
Vector2 Vector2::operator+(Vector2  _vec)
{
	Vector2 tmp;
	tmp.x = x + _vec.x;
	tmp.y = y + _vec.y;

	return tmp;
}


//! +=演算子のオーバーロード
void Vector2::operator+=(Vector2  _vec)
{	
	x += _vec.x;
	y += _vec.y;
}


//! -演算子のオーバーロード
Vector2 Vector2::operator-(Vector2 _vec)
{
	Vector2 tmp;
	tmp.x = x - _vec.x;
	tmp.y = y - _vec.y;

	return tmp;
}

//! -=演算子のオーバーロード
void Vector2::operator-=(Vector2 _vec)
{
	x -= _vec.x;
	y -= _vec.y;
}

//! / 演算子のオーバーロード
Vector2 Vector2::operator/(float _v)
{
	Vector2 tmp;

	tmp.x = x / _v;
	tmp.y = y / _v;

	return tmp;
}

//! /=演算子
void Vector2::operator/=(float _v)
{
	x /= _v;
	y /= _v;
}

//! =演算子
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

//! *演算子 引数 : float
Vector2 Vector2::operator*(float _v)
{
	Vector2 tmp;
	tmp.x = x * _v;
	tmp.y = y * _v;


	return tmp;
}

//! *演算子 引数 : int
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
// 相手と自身の直線距離を求める関数                           //
// 引数   : 相手の位置                                        //
// 戻り値 : 相手との直線距離                                  */
float Vector2::PosToPos(Vector2 _pos)
{
	float distance; //! 相手と自身との直線距離
	
	//! 三平方の定理を使って求める
	float xdis = x - _pos.x;
	float ydis = y - _pos.y;
	distance = sqrt(pow(xdis, 2) + pow(ydis, 2));

	return distance;
}


/* ------------------------------------------------------------
// このベクトルのx,y要素を一つの量にした値を返す             //
// 戻り値 : ベクトルの要素を一つにした値                     */
float Vector2::GetVetor()
{	
	return sqrt(powf(x,2) + powf(y,2));
}

//! 座標のセッター
void Vector2::SetVector(float _x, float _y)
{
	x = _x;
	y = _y;
}
