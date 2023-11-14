#include "AnimationHitObject.h"
#include "AnimationSprite.h"
#include "TextureManager.h"
#include <math.h>

//! コンストラクタ
AnimationHitObject::AnimationHitObject()
{
	mcpAnimsprite = new AnimationSprite(mcVec);
	mcpSprite = mcpAnimsprite;	
	msSize = FLOAT2(0.2f,0.2f);
	mcpShape = nullptr;
	//! 下のように画像やアニメーションテーブルは継承先のコンストラクタ等で設定する
	/*mcpSprite->SetTexture(TexMgr->GetTextuer(Tex_Game));
	mcpAnimsprite->SetAnimtionTable(1, 1);*/	
}

//! デストラクタ
AnimationHitObject::~AnimationHitObject()
{	
	delete mcpAnimsprite;
}

//! 更新処理
void AnimationHitObject::Update()
{
	
}

//! 当たり判定処理後
void AnimationHitObject::LastUpdate()
{
	
}


//! Hitフラグのセッター
void AnimationHitObject::SetHit(bool _state)
{
	mHitFlg = _state;
}
//! 当たり判定のオンオフ切り替えのセッター
void AnimationHitObject::SetHitActiv(bool _state)
{
	if (mcpShape != nullptr) {
		mcpShape->SetActiv(_state);
	}
}

AnimationSprite * AnimationHitObject::GetAnimSprite()
{
	return mcpAnimsprite;
}




