#include "Gimmick.h"
#include "TextureManager.h"
#include "EffectManager.h"

//! コンストラクタ
Gimmick::Gimmick()
{
	//! 矩形の当たり判定の生成
	mcpBoxCol = new Box(mcVec, msSize.x, msSize.y);
	mcpShape = mcpBoxCol;
	//mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_nuko04));
	//mcpAnimsprite->SetAnimtionTable(1, 1);
	mActuation = false;
	mDoing = false;
}

//! デストラクタ
Gimmick::~Gimmick()
{
	delete mcpBoxCol;
}

//! 更新処理
void Gimmick::Update()
{
	//! 発電機がチャージされたか判断する
	if (mcpDynamo->GetChargeState() && !mDoing) {
		//! 本来は配線に電気が流れる演出をしてから
		mActuation = true; //! チャージされたら作動させる
	}
}


Box * Gimmick::GetBoxCol()
{
	return mcpBoxCol;
}

//! 発電機のセット関数
void Gimmick::SetDynamo(Dynamo * _dynamo)
{
	mcpDynamo = _dynamo;
}


