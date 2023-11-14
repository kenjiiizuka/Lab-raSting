#include "WeakDynamo.h"
#include "Camerah.h"
#include "EffectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"

//! コンストラクタ
WeakDynamo::WeakDynamo()
{
	mBreak = false;
	mOverheat = false;
	mCoolDown = false;
	g = b = 1.0f;
	mTag = Tag_WeakDynamo;
	
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Dynamo02));
}


//! 更新処理
void WeakDynamo::Update()
{
	mChargeFin = false;
	//! チャージがされたらエフェクトを出す
	if (mCharge) {
		EffMgr->PlayEffect(DaynamoEffect, mcVec.x, mcVec.y,1.0f,1.0f);
		SoundMgr->PlaySE(SE_Dynamo_Charge,0.1f);
		Doing = true;
		mCharge = false; //! 本来は対応しているギミックに作動することを伝える
	}
	//! エフェクトが終了したらチャージ完了にする
	else if (EffMgr->GetState(DaynamoEffect) == EffectState::End && Doing) {
		mChargeFin = true;
		Doing = false;
		mcpBox->SetActiv(false);
		
	}

	//! 壊れるフラグが立ったら取り合えず赤くして消す
	if (mBreak && ! mCoolDown) {
		mCharge = false;
		g = b -= 0.01f; //! 赤くする
		//! ０以下の値になったら発電機を消す
		if (g <= 0.0f) {
			g = b = 0.0f;
			mOverheat = true;
			mCoolDown = true;
		}				
	}
	//! クールダウン
	else if (mCoolDown) {
		g = b += 0.01f; //! もとの色に戻す
		if (g >= 1.0f) {
			mBreak = false;
			mCoolDown = false;
		}
	}
	//! 色と透明度をセットする
	mcpAnimsprite->SetColor(1.0f, g, b);
}


//! 尻尾が刺さった時のリアクションを返す関数
TailReaction WeakDynamo::ReturnReaction(float _power, bool _elect)
{
	TailReaction Reaction = TailReaction_None; 

	if (_elect) {
		if (_power > STING_STRONG) {
			Reaction = TailReaction_StingDeep; //! 仮で深く刺さります
			CAMERA->StartVibration(3); //! 画面振動
			mBreak = true;
			mCoolDown = false;
			SoundMgr->PlaySE(SE_Dynamo_OverHeat, 0.1f);
	}
		else if (_power > STING_MIDIUME) {
			Reaction = TailReaction_StingStop;
		}
		else {
			Reaction = TailReaction_StingStop;
		}
	}
	else {
		if (_power > STING_STRONG) {
			Reaction = TailReaction_StingDeep; //! 仮で深く刺さります
			CAMERA->StartVibration(3); //! 画面振動
			mBreak = true;
			mCoolDown = false;
			SoundMgr->PlaySE(SE_Dynamo_OverHeat, 0.1f);
		}
		else if (_power > STING_MIDIUME) {
			Reaction = TailReaction_StingDeep;
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.07f);
		}
		else {
			Reaction = TailReaction_StingStop;
		}
	}
	return Reaction;
}

//! オーバーヒート下かどうかを返す
bool WeakDynamo::Overheat()
{
	if (mOverheat) {
		mOverheat = false;
		return true;
	}
	return false;
}

/* --------------- 
// チャージ関数 */
void WeakDynamo::SetChrage(bool _state)
{
	if (!mBreak) {
		mCharge = _state;
	}
}
