#include "StageDoor.h"
#include "SoundManager.h"
#include "TextureManager.h"

//! コンストラクタ
StageDoor::StageDoor()
{
	CurrentHit = false;
	//! 当たり判定の生成
	ColSize = Vector2(0.2f,0.2f);
	SetSize(0.9f,0.9f);
	mcpBox = new Box(mcVec,ColSize.x, ColSize.y);
	mcpShape = mcpBox;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_StageDoor01));
	mcpAnimsprite->SetAnimtionTable(9, 2);
	FrameCnt = CloseFrameCnt = 0;
	mcpAnimsprite->SetStopAnimation(true); //! アニメーションを止めた状態でスタート
	mcpAnimsprite->SetYSplit(0);
	Open = false;
	State = Door_Closed; //! 最初は閉じ切った状態

	Abutton = false;
	AbuttonObj = new AnimationHitObject();
	AnimationSprite * ASp = AbuttonObj->GetAnimSprite();
	ASp->SetTexture(TEXTURE(Tex_AbuttonUI));
	ASp->SetAnimtionTable(4, 1);
	AbuttonObj->SetDrawActiv(false);

}

//! デストラクタ
StageDoor::~StageDoor()
{
	delete AbuttonObj;
	delete mcpBox;
}

//! 更新処理
void StageDoor::Update()
{
	int CurrentX = mcpAnimsprite->GetCurrentXSplit();
	if (CurrentHit) {
		//! 閉じているときか閉じ切っている時のみ
		if (State == Door_Close || State == Door_Closed) {
			if (State == Door_Close) {
				mcpAnimsprite->SetXSplit(8 - CurrentX);
			}
			State = Door_Open;		
		}
		//! Aボタンを出すフラグを立てる
		Abutton = true;
	}
	else {
		//! 開いてるときか開ききっているときのみ
		if (State == Door_Open || State == Door_Opned) {
			if (State == Door_Open) {	
				mcpAnimsprite->SetXSplit(8 - CurrentX);		
			}
			State = Door_Close;		
		}
		Abutton = false;
	}
	
	switch (State)
	{
	case StageDoor::Door_Open:

		if (!Sound) {
			SoundMgr->PlaySE(SE_Door_Stage,0.1f);
			Sound = true;
		}
		//! アニメーションを始める
		mcpAnimsprite->SetStopAnimation(false);
		mcpAnimsprite->SetYSplit(0);
		if (mcpAnimsprite->GetCurrentXSplit() == 8) {
			State = Door_Opned;
		}	
		break;

	case StageDoor::Door_Close:
		mcpAnimsprite->SetStopAnimation(false);
		mcpAnimsprite->SetYSplit(1);
		//! 最後のコマにいったらOpenedにいく
		if (mcpAnimsprite->GetCurrentXSplit() == 8) {
			State = Door_Closed;
			Sound = false;
		}		
		break;

	case StageDoor::Door_Opned:
		//! アニメーションをやめる
		mcpAnimsprite->ResetAnimCnt();
		mcpAnimsprite->SetYSplit(1);
		mcpAnimsprite->SetStopAnimation(true); 
		break;

	case StageDoor::Door_Closed:
		//! アニメーションをやめる
		mcpAnimsprite->ResetAnimCnt();
		mcpAnimsprite->SetYSplit(0);
		mcpAnimsprite->SetStopAnimation(true);
		break;
	}


	if (Abutton) {
		AbuttonObj->SetDrawActiv(true);
		Vector2 Apos((mcVec.x), (mcVec.y + msSize.y / 2.0f));
		AbuttonObj->SetVec(Apos);
	}
	else {
		AbuttonObj->SetDrawActiv(false);
	}	
}

void StageDoor::Draw()
{
	GameObject::Draw();
	AbuttonObj->Draw();
}

//! 当たり判定のゲッター
Box * StageDoor::GetBoxCol()
{
	return mcpBox;
}

//! 当たり判定のセッター
void StageDoor::SetColSize(float _x, float _y)
{
	ColSize = Vector2(_x, _y);
	mcpBox->SetSize(_x, _y);
}

//! ゲッター セッター

void StageDoor::SetHit(bool _state)
{
	CurrentHit = _state;
}

bool StageDoor::GetHit()
{
	return CurrentHit;
}
