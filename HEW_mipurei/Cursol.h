#pragma once
#include "AnimationHitObject.h"

//! カーソルクラス
class Cursol :
	public AnimationHitObject
{
public:
	Cursol();
	~Cursol();

	void Update();
	Vector2 GetSelectPos(); //! 決定ボタンを押したかを返す
	Shape * GetShape();     //! 自身の座標
	bool Select();          //! 決定ボタンを押したか
};

