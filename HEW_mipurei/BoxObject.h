#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
class BoxObject :
	public AnimationHitObject
{
public:
	BoxObject();                   //! コンストラクタ
	BoxObject(float _x, float _y); //! コンストラクタ
	~BoxObject();                  //! デストラクタ
	void Update();		
	Box * GetBoxCol(); //! 矩形の当たりのゲッター

private:
	Box * mcpBoxCol;
};

