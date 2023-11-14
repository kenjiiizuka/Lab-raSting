#pragma once
#include "Vector2.h"

/* -------------------------------------------------------------------
// Shapeクラス                                                      //
// 形の情報を持つクラスです。                                       //
// 当たり判定を持ちたいオブジェクトに持たせて情報を設定してください */
class Shape
{
public:
	Shape(Vector2 & _pos); //! コンストラクタ
	
	Vector2 GetVec();
	void SetMoveVec(Vector2 _movevec);
	Vector2 GetMoveVec();
	void SetActiv(bool _state);     //! 当たり判定の切り替えのセッター
	bool GetActiv();                //! 当たり判定の切り替えのゲッター
	void SetAttack(bool _state);    //! 攻撃判定フラグのセッター 
	bool GetAttack();               //! 攻撃判定フラグのゲッター
	void SetPrevVec(Vector2 _vec);  //! 前フレームの座標のセッター
	Vector2 GetPrevVec();           //! 前フレームの座標のセッター

	void SetPenetration(float _x, float _y);
	void AddPenetration(float _x, float _y);
	Vector2 GetPetration();

	//! 座標のセッター　当たり判定関係でのみ使う
	void SetPos(float _x, float _y);
	void SetX(float _x);
	void SetY(float _y);
	void SetOnObj(bool _state);
	bool GetOnObj();
	//! 自身のアドレスを返す
	Shape * Getthis();
protected:
	Vector2 & mcPos;     //! 座標
	Vector2 mPrevPos;    //! 前フレームの座標
	Vector2 mcMoveVec;   //! このクラスを持つ、オブジェクトの移動量 
	Vector2 Penetration; //! めり込んでいる修正する量
	bool Attack;         //! 攻撃の判定なのかを判断する 多分これいらん
	bool Activ;          //! 当たり判定のオンオフ切り替え
	bool mOnObj;      //! 何かに乗っているか(Characterのタッチグラウンドの参照にするといいかも)
};

