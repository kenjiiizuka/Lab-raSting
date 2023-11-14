#pragma once
#include <math.h>

//! �}�N����`�@
#define F_SQRT(v) sqrtf(v.x*v.x+v.y*v.y)


/* =================================================== 
// Vctor2�N���X                                       //
// ���W�Ɏg��x,y�����A�x�N�g�����m�̉��Z�����Ă���܂�//
// ����� : �ђ� ���i                                 */
class Vector2
{
public:
	Vector2();                   //! �R���X�g���N�^
	Vector2(float _x, float _y); //! �������R���X�g���N�^
	
	//! ���Z�q�̃I�[�o�[���[�h
	Vector2 operator+(Vector2  _vec);//! +  ���Z�q
	void operator+=(Vector2  _vec);  //! += ���Z�q
	Vector2 operator-(Vector2 _vec); //! -  ���Z�q
	void operator-=(Vector2 _vec);   //! -  ���Z�q
	Vector2 operator/(float _v);     //! /  ���Z�q
	void operator/=(float _v);       //! /= ���Z�q
	void operator=(float _v);        //! =  ���Z�q   
	bool operator==(Vector2 _vec);   //! == ���Z�q
	bool operator==(float _v);       //! == ���Z�q
	bool operator!=(float _v);       //! != ���Z�q
	Vector2 operator*(float _v);     //! *  ���Z�q
	Vector2 operator*(int _v);       //! *  ���Z�q
	void operator*=(float _v);       //! *= ���Z�q
	bool operator>(Vector2 _v);      //! >  ���Z�q

	float PosToPos(Vector2 _pos);    //! ���g�Ƒ���Ƃ̋��������߂�֐�
	float GetVetor(); //! ���̃x�N�g����x,y�v�f�𒼐��ɂ����Ƃ��̗�
	void SetVector(float _x, float _y); //! Vector�̃Z�b�^�[
	
	//! �v���C�x�[�g�̕��������̂� �p�u���b�N�̕��������̂�
	float x;
	float y;

private:

};

