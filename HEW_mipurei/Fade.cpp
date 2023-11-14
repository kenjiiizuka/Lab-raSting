#include "Fade.h"
#include "TextureManager.h"

// コンストラクタ
Fade::Fade()
{
	mState = NONE;                   //! 初期の状態はなにもしていない状態
	mcpFadePanel = new StaticObject; //! フェードに使う用のオブジェクトを生成
	mcpFadePanel->SetCameraActiv(false);
	mcpFadePanel->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	mcpFadePanel->SetSize(3.85f,2.0f);
	mAlpha = 1.0f;	
}

// デストラクタ
Fade::~Fade()
{
	delete mcpFadePanel;
}

// 更新処理
void Fade::Update()
{
	const float AlphaSpeed = 0.015f; // 透明度をフレーム毎に変化させる値

	//! 状態毎にフェードイン、フェードアウトの処理を行う
	switch (mState)
	{
	case FADEIN:
		mAlpha-= AlphaSpeed ;
		if (mAlpha <= 0.0f) {
			mState = NONE;
		}
		mcpFadePanel->GetSprite()->SetArufa(mAlpha);
		break;

	case FADEOUT:
		mAlpha += AlphaSpeed ;
		if (mAlpha >= 1.0f) {
			mState = NONE;
		}
		mcpFadePanel->GetSprite()->SetArufa(mAlpha);
		break;
	}
}

//! 描画処理
void Fade::Draw()
{
	mcpFadePanel->Draw();
}

//! フェードインの開始関数
void Fade::FadeIn()
{
	if (mState == NONE)
	mState = FADEIN;
}

//! フェードアウトの開始関数
void Fade::FadeOut()
{
	if(mState == NONE)
	mState = FADEOUT;
}

//! 現在のフェードの状態を取得する関数
int Fade::GetFadeState()
{
	return mState;
}
