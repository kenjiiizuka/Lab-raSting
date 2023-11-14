#pragma once
#include "GameObject.h"



/* =====================================================================
// StaticObjectクラス                                                 //
// 動かないオブジェクトを描画する機能を持っています                   //
// 制作者 : 飯塚 健司                                                 */
class StaticObject :
	public GameObject
{
public:
	StaticObject();  //! コンストラクタ
	~StaticObject(); //! デストラクタ
	void SetPos(float _x, float _y); //! 座標のセッター
	void SetX(float _x);
	void SetY(float _y);
};

