#include "BigDoor.h"
#include "SoundManager.h"
#include"TextureManager.h"

//! コンストラクタ
BigDoor::BigDoor()
{
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	msSize.x = 0.7f;
	msSize.y = 1.0f;
	mcpBoxCol->SetSize(0.2f,1.0f);
	mTotal = 0;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Door));
	mcpAnimsprite->SetAnimtionTable(9, 1);
	mcpAnimsprite->SetStopAnimation(true);
	mFrameCnt = 0;
}

//! デストラクタ
BigDoor::~BigDoor()
{

}

//! 更新処理
void BigDoor::Update()
{
	Gimmick::Update();
	//! 作動
	if (mTotal > 1.0f) {
		mActuation = false;
		mDoing = false;
	}

	if (mActuation) {
		if (Sound) {
			SoundMgr->PlaySE(SE_Door_Stage,0.1f);
			Sound = false;
		}

		mDoing = true;
		mcpAnimsprite->SetStopAnimation(false); //! アニメーションを再開する
		mFrameCnt++;

		//! 60フレーム経過したら当たり判定を消す
		if (mFrameCnt >= 60) {
			SetHitActiv(false);
		}
		if (mFrameCnt >= 70) {
			mcpAnimsprite->SetStopAnimation(true);
		}
	}	
}


