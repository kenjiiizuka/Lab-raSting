#include "PressMachine.h"
#include "TextureManager.h"
#include "SoundManager.h"

//! コンストラクタ
PressMachine::PressMachine()
{
	//! サイズのセット
	SetSize(1.4f,1.0f);
	
	//! 画像のセット
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PressMachine));
	mcpAnimsprite->SetAnimtionTable(13,1);

	//! 当たり判定の生成
	mColSize.x = 0.8f;
	mColSize.y = 0.2f;
	mBoxCol = new Box(ColPos, mColSize.x, mColSize.y);

	ColPos.x = mcVec.x;
	ColPos.y = mcVec.y - 0.4f;

	Stop = false;
	StopCnt = 0;

	mTag = Tag_Press;
}

//! デストラクタ
PressMachine::~PressMachine()
{
	delete mBoxCol;
}

//! 更新処理
void PressMachine::Update()
{
	Gimmick::Update();

	ColPos.x = mcVec.x;
	ColPos.y = mcVec.y - 0.4f;

	int AnimX = mcpAnimsprite->GetCurrentXSplit();
	if (mActuation) {
		//! 発電機がチャージされて、アニメーションが最後のコマにいったらしばらく止まる
		if (AnimX == 12) {
			Stop = true;
			StopCnt = 0;
		}
	}
	//! 止まっている時
	if (Stop) {
		StopCnt++;
		mcpAnimsprite->SetStopAnimation(true);
	
		//! 5秒止まる
		if (StopCnt > (60 * 5)) {
			Stop = false;
			mActuation = false;
			mcpAnimsprite->SetStopAnimation(false);
		}
	}
	//! 動いてる時
	else {
		if (AnimX == 12) { mcpAnimsprite->ResetAnimCnt();}
		mBoxCol->SetActiv(false);
		if (AnimX == 4 || AnimX == 5) {
			mBoxCol->SetActiv(true);
		}

		if (AnimX == 4 && Sound) {
			SoundMgr->PlaySE(SE_Press, 0.4f);
			Sound = false;
		}

		if (AnimX == 5) { Sound = true; }
	}
}

//! 描画処理
void PressMachine::Draw()
{
	GameObject::Draw();

}

Box * PressMachine::GetBoxCol()
{
	return mBoxCol;
}


