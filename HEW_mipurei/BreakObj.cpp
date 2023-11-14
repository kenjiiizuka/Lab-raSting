#include "BreakObj.h"
#include "TextureManager.h"
#include "SoundManager.h"

//! コンストラクタ
BreakObj::BreakObj()
{
	mBreak = false;
	mBreaked = false;
	msSize = {0.6f,0.6f};
	mcpBox = new Box(mcVec,0.2f, 0.6f);
	mcpShape = mcpBox;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Galss));
	mcpAnimsprite->SetAnimtionTable(14,1);
	mcpAnimsprite->SetStopAnimation(true);
	Cnt = 0;
	Arufa = 1.0f;
}

//! デストラクタ
BreakObj::~BreakObj()
{
	delete mcpBox;
}

//! 更新処理
void BreakObj::Update()
{
	if (mBreak && !mBreaked) {
		mcpAnimsprite->SetStopAnimation(false);
		Cnt++;
		//! 最後のアニメーションまでいったら止めて徐々に消す
		if (Cnt >= (8 * 14)) {
			mcpAnimsprite->SetStopAnimation(true);
			//! 透明にしていく
			Arufa -= 0.01f;
			mcpAnimsprite->SetArufa(Arufa);
			if (Arufa < 0 ) {
				Arufa = 0;
				mBreaked = true;
				SetDrawActiv(false);
			}
		}
	}
}

//! 描画処理
void BreakObj::Draw()
{
	GameObject::Draw();
}

Box * BreakObj::GetBoxCol()
{
	return mcpBox;
}

//! 刺されたときのリアクションを返す関数
TailReaction BreakObj::ReturnReaction(float _power)
{
	TailReaction Reaction = TailReaction_None;
	if (_power >STING_STRONG) {
		mBreak = true;
		Reaction = TailReaction_StingStop;
		SetHitActiv(false);
		SoundMgr->PlaySE(SE_Glass_Break,0.1f);
	}
	else if (_power > STING_MIDIUME) {
		Reaction = TailReaction_Stop;
		SoundMgr->PlaySE(SE_Glass_Hajiku,0.1f);
	}
	

	return Reaction;
}

bool BreakObj::GetBreaked()
{
	return mBreak;
}
