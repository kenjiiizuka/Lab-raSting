#include "Angle.h"
#include <math.h>


/*=================================== 
** 度数法を弧度法に変換する関数    **
** 引数 : 度数法の角度             **
**=================================*/
float DegreeToRadian(float _degree)
{
	return (_degree * PI) / 180;
}


/*===================================
** 弧度法を度数法に変換する関数    **
** 引数 : 弧度法の角度             **
**=================================*/
float RadianToDegree(double _radian)
{
	return _radian * (180 / PI);
}


/*============================================*
** 高さと、底辺の長さから角度を求める関数　  **
** 引数   : 底辺 , 高さ                      **
** 戻り値 : 0.0f ～ 7.28f(弧度法)            **
**===========================================*/
float GetAngle(float _x, float _y)
{
	double Angle = atan2f(_y, _x);

	// 角度が負の値だった場合
	if (Angle < 0) {
		Angle = (PI - fabs(Angle)) + PI;
	}
	return Angle;
}


/*=================================================**
** !引数1からみた引数2に対する方向を返す関数       **
** !引数   : 座標1 , 座標2                         **
** !戻り値 : 座標1からみた座標2への方向(弧度法)    **
**=================================================*/
double PositionRelationAngle(FLOAT2 _pos1, FLOAT2 _pos2)
{
	// 座標から三角形を作り計算する
	float Widht = _pos1.x - _pos2.x;
	float Height = _pos1.y - _pos2.y;

	double Angle = atan2(Height, Widht); // オブジェクト同士の角度

	if (Angle < 0) {
		Angle = (PI - fabs(Angle)) + PI;
	}

	return Angle;
}

double PositionRelationAngle(Vector2 _pos1, Vector2 _pos2)
{
	// 座標から三角形を作り計算する
	float Widht = _pos1.x - _pos2.x;
	float Height = _pos1.y - _pos2.y;

	double Angle = atan2(Height, Widht); // オブジェクト同士の角度

	if (Angle < 0) {
		Angle = (PI - fabs(Angle)) + PI;
	}

	return Angle;
}


/*====================================================**
** 角度の差を求める関数(度数法)                       **
** 引数   : 角度１、　角度２                          **
** 戻り値 : 角度の差                                  */
int GetDiffrenceDegree(int _angle1, int _angle2)
{		
	//! 反時計回り(正回転) と 時計回り(負回転)それぞれの角度の差を求めて、近い方を差として返す	
	float Plusdif;  //! 角度の差 ＋方向
	float Minusdif; //! 角度の差 ー方向

	float tmp_angle1 = _angle1;
	float tmp_angle2 = _angle2;

	//! ＋方向の差
	for (Plusdif = 0; tmp_angle1 != tmp_angle2; Plusdif++) {
		tmp_angle1 += 1;
		//! 360をこえたら0にする
		if (tmp_angle1 > 360) {
			tmp_angle1 = 0;
		}
	}

	tmp_angle1 = _angle1;
	tmp_angle2 = _angle2;

	for (Minusdif = 0; tmp_angle1 != tmp_angle2; Minusdif++) {
		tmp_angle1 -= 1;
		//! 0より小さくなったら360にする
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
	float Plusdif;  //! 角度の差 ＋方向
	float tmp_angle1 = _angle1;
	float tmp_angle2 = _angle2;
	//! ＋方向の差
	for (Plusdif = 0; tmp_angle1 != tmp_angle2; Plusdif++) {
		tmp_angle1 += 1;
		//! 360をこえたら0にする
		if (tmp_angle1 > 360) {
			tmp_angle1 = 0;
		}
	}
	return Plusdif;
}


int GetMinusDifDegree(int _angle1, int _angle2)
{
	float Minusdif; //! 角度の差 ー方向
	float tmp_angle1 = _angle1;
	float tmp_angle2 = _angle2;
	for (Minusdif = 0; tmp_angle1 != tmp_angle2; Minusdif++) {
		tmp_angle1 -= 1;
		//! 0より小さくなったら360にする
		if (tmp_angle1 < 0) {
			tmp_angle1 = 360;
		}
	}
	return Minusdif;
}


/*=================================================**
** 引数の角度(弧度法)の反射角を返す関数            **
** 引数   : 角度(弧度法)　                         **
** 戻り値 : 引数の角度(弧度法)の反射角(弧度法)     **
**=================================================*/
double GetReflectionAngle(double _angle)
{
	double ReflectionAngle;			  // 反射角
	double CalculationAngle = fabs(_angle); // 計算用の角度
	double Rad180 = (180 * PI) / 180; // 180度のラジアンの値
	bool OverPIFlg = false; // 3.14を超えるかのフラグ

	// PIを超えていたら修正する
	if (_angle >= PI) {
		CalculationAngle = _angle - PI;
		OverPIFlg = true; // 超えていた時のフラグ
	}

	ReflectionAngle = CalculationAngle + (Rad180 - (CalculationAngle + CalculationAngle));

	if (OverPIFlg == true) {
		ReflectionAngle += PI;
	}

	return ReflectionAngle;
}


/* ==================================================================== **
** 引数に設定した中心、半径の円の引数に設定した角度の円上の位置を返す   **
** 引数   : 中心, 角度(弧度法), 半径                                    **
** 戻り値 : 中心、半径の円の引数に設定した角度の円上の位置              **
** ==================================================================== */
FLOAT2 CircularMotionCenter(FLOAT2 _centerpos, double _angle, float _radius)
{
	return FLOAT2(_centerpos.x + cos(_angle) * _radius, _centerpos.y + sin(_angle) * _radius);
}


/* ================================================= **
** 角度と半径に対応した円上の座標への移動量を返す    ** 
** 引数   : 角度(弧度法), 半径　　　　　　　　　     **
** 戻り値 : 角度と半径に対応した円上の座標への移動量 **
** ================================================= */
FLOAT2 CircularMotion(double _angle, float _radius)
{
	return FLOAT2(cos(_angle) * _radius, sin(_angle) * _radius);
}

