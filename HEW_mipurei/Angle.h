#pragma once
#include "FLOAT2.h"
#include "Vector2.h"

#define PI 3.14159 // �~����

//! �p�x���擾����
float GetAngle(float _x, float _y);

//! �x���@���ʓx�@�ɕϊ������l��Ԃ�
float DegreeToRadian(float _degree);

//! �ʓx�@��x���@�ɕϊ������l��Ԃ�
float RadianToDegree(double _radian);

//! �����P����݂������Q�ւ̊p�x��Ԃ�
double PositionRelationAngle(FLOAT2 _pos1, FLOAT2 _pos2);
double PositionRelationAngle(Vector2 _pos1, Vector2 _pos2);

//! �p�x�̂�����Ԃ�
int GetDiffrenceDegree(int _angle1, int _angle2);

int GetPlusDifDegree(int _angle1, int _angle2);

int GetMinusDifDegree(int _angle1, int _angle2);


//! ���ˊp��Ԃ��@
double GetReflectionAngle(double _angle);

//! �p�x�Ɣ��a�ɑΉ������~��̍��W��Ԃ�
FLOAT2 CircularMotionCenter(FLOAT2 _ceterpos, double _angle, float _rad);

// �p�x�Ɣ��a�ɑΉ������~��̍��W�ւ̈ړ��ʂ�Ԃ�
FLOAT2 CircularMotion(double _angle, float _rad);
