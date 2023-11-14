#pragma once
#include <math.h>

//! マクロ定義　
#define F_SQRT(v) sqrtf(v.x*v.x+v.y*v.y)


/* =================================================== 
// Vctor2クラス                                       //
// 座標に使うx,y持ち、ベクトル同士の演算もしてくれます//
// 制作者 : 飯塚 健司                                 */
class Vector2
{
public:
	Vector2();                   //! コンストラクタ
	Vector2(float _x, float _y); //! 引数つきコンストラクタ
	
	//! 演算子のオーバーロード
	Vector2 operator+(Vector2  _vec);//! +  演算子
	void operator+=(Vector2  _vec);  //! += 演算子
	Vector2 operator-(Vector2 _vec); //! -  演算子
	void operator-=(Vector2 _vec);   //! -  演算子
	Vector2 operator/(float _v);     //! /  演算子
	void operator/=(float _v);       //! /= 演算子
	void operator=(float _v);        //! =  演算子   
	bool operator==(Vector2 _vec);   //! == 演算子
	bool operator==(float _v);       //! == 演算子
	bool operator!=(float _v);       //! != 演算子
	Vector2 operator*(float _v);     //! *  演算子
	Vector2 operator*(int _v);       //! *  演算子
	void operator*=(float _v);       //! *= 演算子
	bool operator>(Vector2 _v);      //! >  演算子

	float PosToPos(Vector2 _pos);    //! 自身と相手との距離を求める関数
	float GetVetor(); //! このベクトルのx,y要素を直線にしたときの量
	void SetVector(float _x, float _y); //! Vectorのセッター
	
	//! プライベートの方がいいのか パブリックの方がいいのか
	float x;
	float y;

private:

};

