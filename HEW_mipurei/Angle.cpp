#include "Angle.h"
#include <math.h>


/*=================================== 
** �x���@���ʓx�@�ɕϊ�����֐�    **
** ���� : �x���@�̊p�x             **
**=================================*/
float DegreeToRadian(float _degree)
{
	return (_degree * PI) / 180;
}


/*===================================
** �ʓx�@��x���@�ɕϊ�����֐�    **
** ���� : �ʓx�@�̊p�x             **
**=================================*/
float RadianToDegree(double _radian)
{
	return _radian * (180 / PI);
}


/*============================================*
** �����ƁA��ӂ̒�������p�x�����߂�֐��@  **
** ����   : ��� , ����                      **
** �߂�l : 0.0f �` 7.28f(�ʓx�@)            **
**===========================================*/
float GetAngle(float _x, float _y)
{
	double Angle = atan2f(_y, _x);

	// �p�x�����̒l�������ꍇ
	if (Angle < 0) {
		Angle = (PI - fabs(Angle)) + PI;
	}
	return Angle;
}


/*=================================================**
** !����1����݂�����2�ɑ΂��������Ԃ��֐�       **
** !����   : ���W1 , ���W2                         **
** !�߂�l : ���W1����݂����W2�ւ̕���(�ʓx�@)    **
**=================================================*/
double PositionRelationAngle(FLOAT2 _pos1, FLOAT2 _pos2)
{
	// ���W����O�p�`�����v�Z����
	float Widht = _pos1.x - _pos2.x;
	float Height = _pos1.y - _pos2.y;

	double Angle = atan2(Height, Widht); // �I�u�W�F�N�g���m�̊p�x

	if (Angle < 0) {
		Angle = (PI - fabs(Angle)) + PI;
	}

	return Angle;
}

double PositionRelationAngle(Vector2 _pos1, Vector2 _pos2)
{
	// ���W����O�p�`�����v�Z����
	float Widht = _pos1.x - _pos2.x;
	float Height = _pos1.y - _pos2.y;

	double Angle = atan2(Height, Widht); // �I�u�W�F�N�g���m�̊p�x

	if (Angle < 0) {
		Angle = (PI - fabs(Angle)) + PI;
	}

	return Angle;
}


/*====================================================**
** �p�x�̍������߂�֐�(�x���@)                       **
** ����   : �p�x�P�A�@�p�x�Q                          **
** �߂�l : �p�x�̍�                                  */
int GetDiffrenceDegree(int _angle1, int _angle2)
{		
	//! �����v���(����]) �� ���v���(����])���ꂼ��̊p�x�̍������߂āA�߂��������Ƃ��ĕԂ�	
	float Plusdif;  //! �p�x�̍� �{����
	float Minusdif; //! �p�x�̍� �[����

	float tmp_angle1 = _angle1;
	float tmp_angle2 = _angle2;

	//! �{�����̍�
	for (Plusdif = 0; tmp_angle1 != tmp_angle2; Plusdif++) {
		tmp_angle1 += 1;
		//! 360����������0�ɂ���
		if (tmp_angle1 > 360) {
			tmp_angle1 = 0;
		}
	}

	tmp_angle1 = _angle1;
	tmp_angle2 = _angle2;

	for (Minusdif = 0; tmp_angle1 != tmp_angle2; Minusdif++) {
		tmp_angle1 -= 1;
		//! 0��菬�����Ȃ�����360�ɂ���
		if (tmp_angle1 < 0) {
			tmp_angle1 = 360;
		}
	}
	
	if (Plusdif < Minusdif) {
		return Plusdif;
	}

	return Minusdif;
}


int GetPlusDifDegree(int _angle1, int _angle2)
{
	float Plusdif;  //! �p�x�̍� �{����
	float tmp_angle1 = _angle1;
	float tmp_angle2 = _angle2;
	//! �{�����̍�
	for (Plusdif = 0; tmp_angle1 != tmp_angle2; Plusdif++) {
		tmp_angle1 += 1;
		//! 360����������0�ɂ���
		if (tmp_angle1 > 360) {
			tmp_angle1 = 0;
		}
	}
	return Plusdif;
}


int GetMinusDifDegree(int _angle1, int _angle2)
{
	float Minusdif; //! �p�x�̍� �[����
	float tmp_angle1 = _angle1;
	float tmp_angle2 = _angle2;
	for (Minusdif = 0; tmp_angle1 != tmp_angle2; Minusdif++) {
		tmp_angle1 -= 1;
		//! 0��菬�����Ȃ�����360�ɂ���
		if (tmp_angle1 < 0) {
			tmp_angle1 = 360;
		}
	}
	return Minusdif;
}


/*=================================================**
** �����̊p�x(�ʓx�@)�̔��ˊp��Ԃ��֐�            **
** ����   : �p�x(�ʓx�@)�@                         **
** �߂�l : �����̊p�x(�ʓx�@)�̔��ˊp(�ʓx�@)     **
**=================================================*/
double GetReflectionAngle(double _angle)
{
	double ReflectionAngle;			  // ���ˊp
	double CalculationAngle = fabs(_angle); // �v�Z�p�̊p�x
	double Rad180 = (180 * PI) / 180; // 180�x�̃��W�A���̒l
	bool OverPIFlg = false; // 3.14�𒴂��邩�̃t���O

	// PI�𒴂��Ă�����C������
	if (_angle >= PI) {
		CalculationAngle = _angle - PI;
		OverPIFlg = true; // �����Ă������̃t���O
	}

	ReflectionAngle = CalculationAngle + (Rad180 - (CalculationAngle + CalculationAngle));

	if (OverPIFlg == true) {
		ReflectionAngle += PI;
	}

	return ReflectionAngle;
}


/* ==================================================================== **
** �����ɐݒ肵�����S�A���a�̉~�̈����ɐݒ肵���p�x�̉~��̈ʒu��Ԃ�   **
** ����   : ���S, �p�x(�ʓx�@), ���a                                    **
** �߂�l : ���S�A���a�̉~�̈����ɐݒ肵���p�x�̉~��̈ʒu              **
** ==================================================================== */
FLOAT2 CircularMotionCenter(FLOAT2 _centerpos, double _angle, float _radius)
{
	return FLOAT2(_centerpos.x + cos(_angle) * _radius, _centerpos.y + sin(_angle) * _radius);
}


/* ================================================= **
** �p�x�Ɣ��a�ɑΉ������~��̍��W�ւ̈ړ��ʂ�Ԃ�    ** 
** ����   : �p�x(�ʓx�@), ���a�@�@�@�@�@�@�@�@�@     **
** �߂�l : �p�x�Ɣ��a�ɑΉ������~��̍��W�ւ̈ړ��� **
** ================================================= */
FLOAT2 CircularMotion(double _angle, float _radius)
{
	return FLOAT2(cos(_angle) * _radius, sin(_angle) * _radius);
}

