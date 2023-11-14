#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "Dynamo.h"
/* ---------------------------------------------------------------------------------- 
// ギミッククラス　                                                                //
// これを基底クラスにしてギミックを制作してください                                //
// 当たり判定は派生先の基本矩形です 他の形状の場合は派生先であらたに作って下しさい */

class Gimmick 
	: public AnimationHitObject
{
public:
	Gimmick();
	~Gimmick();

	void Update() override;
	virtual Box * GetBoxCol();
	void SetDynamo(Dynamo * _dynamo);
protected:

	Dynamo * mcpDynamo; //! このギミックの作動の条件になる発電機のポインタ
	Box * mcpBoxCol;
	bool mActuation; //! ギミックの作動開始フラグ
	bool mDoing; //! ギミック作動中フラグ
	bool Sound = true;
};


