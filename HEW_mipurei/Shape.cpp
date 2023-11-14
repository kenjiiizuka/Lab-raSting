#include "Shape.h"

//! �R���X�g���N�^
Shape::Shape(Vector2 & _pos) : mcPos(_pos)
{
	Activ = true;
	Attack = true;
	mOnObj = false;

	mPrevPos = 0;    //! �O�t���[���̍��W
	mcMoveVec  = 0;   //! ���̃N���X�����A�I�u�W�F�N�g�̈ړ��� 
	Penetration = 0; //! �߂荞��ł���C�������
}

//! ���W�̃Q�b�^�[
Vector2 Shape::GetVec()
{
	return mcPos;
}

//! �ړ��ʂ̃Z�b�^�[
void Shape::SetMoveVec(Vector2 _movevec)
{
	//! �ړ�����͂������Ă���Ƃ��̂�
	mcMoveVec = _movevec;
}

//! �ړ��ʂ̃Q�b�^�[
Vector2 Shape::GetMoveVec()
{
	return mcMoveVec;
}

//! �����蔻��̐؂�ւ��t���O�̃Z�b�^�[
void Shape::SetActiv(bool _state)
{
	Activ = _state;
}

//! �����蔻��؂�ւ��p�̃Q�b�^�[
bool Shape::GetActiv()
{
	return Activ;
}

//! �U������t���O�̃Z�b�^�[
void Shape::SetAttack(bool _state)
{
	Attack = _state;
}

//! �U������Ȃ̂��̃t���O�̃Q�b�^�[
bool Shape::GetAttack()
{
	return Attack;
}

//! �O�t���[�����W�̃Z�b�^�[
void Shape::SetPrevVec(Vector2 _vec)
{
	mPrevPos = _vec;
}

//! �O�t���[���̍��W�̃Q�b�^�[
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
