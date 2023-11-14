#pragma once
#include "FLOAT2.h"
#include "Vector2.h"

#define PI 3.14159 // 円周率

//! 角度を取得する
float GetAngle(float _x, float _y);

//! 度数法を弧度法に変換した値を返す
float DegreeToRadian(float _degree);

//! 弧度法を度数法に変換した値を返す
float RadianToDegree(double _radian);

//! 引数１からみた引数２への角度を返す
double PositionRelationAngle(FLOAT2 _pos1, FLOAT2 _pos2);
double PositionRelationAngle(Vector2 _pos1, Vector2 _pos2);

//! 角度のを差を返す
int GetDiffrenceDegree(int _angle1, int _angle2);

int GetPlusDifDegree(int _angle1, int _angle2);

int GetMinusDifDegree(int _angle1, int _angle2);


//! 反射角を返す　
double GetReflectionAngle(double _angle);

//! 角度と半径に対応した円上の座標を返す
FLOAT2 CircularMotionCenter(FLOAT2 _ceterpos, double _angle, float _rad);

// 角度と半径に対応した円上の座標への移動量を返す
FLOAT2 CircularMotion(double _angle, float _rad);
