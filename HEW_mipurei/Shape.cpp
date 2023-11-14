#include "Shape.h"

//! コンストラクタ
Shape::Shape(Vector2 & _pos) : mcPos(_pos)
{
	Activ = true;
	Attack = true;
	mOnObj = false;

	mPrevPos = 0;    //! 前フレームの座標
	mcMoveVec  = 0;   //! このクラスを持つ、オブジェクトの移動量 
	Penetration = 0; //! めり込んでいる修正する量
}

//! 座標のゲッター
Vector2 Shape::GetVec()
{
	return mcPos;
}

//! 移動量のセッター
void Shape::SetMoveVec(Vector2 _movevec)
{
	//! 移動する力が働いているときのみ
	mcMoveVec = _movevec;
}

//! 移動量のゲッター
Vector2 Shape::GetMoveVec()
{
	return mcMoveVec;
}

//! 当たり判定の切り替えフラグのセッター
void Shape::SetActiv(bool _state)
{
	Activ = _state;
}

//! 当たり判定切り替え用のゲッター
bool Shape::GetActiv()
{
	return Activ;
}

//! 攻撃判定フラグのセッター
void Shape::SetAttack(bool _state)
{
	Attack = _state;
}

//! 攻撃判定なのかのフラグのゲッター
bool Shape::GetAttack()
{
	return Attack;
}

//! 前フレーム座標のセッター
void Shape::SetPrevVec(Vector2 _vec)
{
	mPrevPos = _vec;
}

//! 前フレームの座標のゲッター
Vector2 Shape::GetPrevVec()
{
	return mPrevPos;
}

void Shape::SetPenetration(float _x, float _y)
{
	Penetration.x = _x;
	Penetration.y = _y;
}

void Shape::AddPenetration(float _x, float _y)
{
	Penetration.x += _x;
	Penetration.y += _y;
}



Vector2 Shape::GetPetration()
{
	return Penetration;
}


void Shape::SetPos(float _x, float _y)
{
	mcPos = Vector2(_x, _y);
}

void Shape::SetX(float _x)
{
	mcPos.x = _x;
}

void Shape::SetY(float _y)
{
	mcPos.y = _y;
}

void Shape::SetOnObj(bool _state)
{
	mOnObj = _state;
}

bool Shape::GetOnObj()
{
	return mOnObj;
}

Shape * Shape::Getthis()
{
	return this;
}
