#include "Dynamo.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "SoundManager.h"

Dynamo::Dynamo()
{
	mTag = Tag_Dynamo; //! タグのセット
	
	mCharge = false;
	mChargeFin = false;
	Doing = false;
	//! 当たり判定クラスの生成
	msSize = FLOAT2(0.4f, 0.4f);
	ColSize = Vector2(0.26f, 0.18f);
	mcpBox = new Box(mcVec, ColSize.x, ColSize.y);
	mcpShape = mcpBox;

	//! 描画ための情報のセット
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Dynamo01));
	mcpAnimsprite->SetAnimtionTable(1, 1);
}



//! デストラクタ
Dynamo::~Dynamo()
{
	delete mcpBox;
}

//! 更新処理Update
void Dynamo::Update()
{
	mChargeFin = false;
	//! チャージがされたらエフェクトを出す
	if (mCharge) {
		EffMgr->PlayEffect(DaynamoEffect,mcVec.x,mcVec.y,1.0f,1.0f);
		Doing = true;
		mCharge = false; //! 本来は対応しているギミックに作動することを伝える
		SoundMgr->PlaySE(SE_Dynamo_Charge,0.1f);
	}
	//! エフェクトが終了したらチャージ完了にする
	else if (EffMgr->GetState(DaynamoEffect) == EffectState::End && Doing) {
		mChargeFin = true; 
		Doing = false;
		mcpBox->SetActiv(false);
	}
}

void Dynamo::Draw()
{
	GameObject::Draw();
}

/* -------------------------------------
//! 刺された後にリアクションを返す関数 */
TailReaction Dynamo::ReturnReaction(float _power, bool _elect)
{	
	TailReaction Reaction; //! リアクションを返す
	if (STING_STRONG < _power) {
		Reaction = TailReaction_StingDeep; //! 深く刺さる
		SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
	}
	else if (STING_MIDIUME < _power) {
		Reaction = TailReaction_Sting;     //! 刺さる
		SoundMgr->PlaySE(SE_Timpiller_Sasaru,0.07f);
	}
	else {		
		Reaction = TailReaction_StingStop;      //! 止まる
		SoundMgr->PlaySE(SE_Dynamo_NotSting, 0.04f);
	}

	return Reaction;
}

void Dynamo::SetChrage(bool _state)
{
	mCharge = _state;
}

Box * Dynamo::GetBoxCol()
{
	return mcpBox;
}

bool Dynamo::GetChargeState()
{
	//! チャージが完了して居たらtrueを返す
	if (mChargeFin) {
		return true;
	}
	return false;
}
