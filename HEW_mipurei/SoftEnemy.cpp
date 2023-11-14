#include "SoftEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

/* -----------
// コンストラクタ */
SoftEnemy::SoftEnemy()
{
	//! アニメーション関係
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetAnimSpeed(12);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Soft));	//! エネミー画像のセット
	//! 攻撃判定？
	mcpShape->SetAttack(true);
	//! タグ
	mTag = Tag_Enemy_Soft;
	//! スピードの初期値設定
	BaseEnemy::SetMove(0.001);

	AnimFrm = 0;
	ColSize.x = 0.26f;
	ColSize.y = 0.34f;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// コンストラクタ */
SoftEnemy::SoftEnemy(float _x, float _y)
{
	//! 初期位置の設定
	mcVec = Vector2(_x, _y);
	//! アニメーション関係
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetAnimSpeed(12);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Soft));	//! エネミー画像のセット
	//! 攻撃判定？
	mcpShape->SetAttack(true);
	//! タグ
	mTag = Tag_Enemy_Soft;
	//! スピードの初期値設定
	BaseEnemy::SetMove(0.0015);

	AnimFrm = 0;
	ColSize.x = 0.26f;
	ColSize.y = 0.34f;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// デストラクタ */
SoftEnemy::~SoftEnemy()
{
	//! 特に書くことなし
}

/* -----------
// 更新処理 */
void SoftEnemy::Update()
{
	//! 本体の更新
	BaseEnemy::Update();
	int AnimX = mcpAnimsprite->GetCurrentXSplit();
	if (AnimX == 5) {
		Stop = true;
		
	}
	//! 止まっている時
	if (Stop) {
		AnimFrm++;
		mcpAnimsprite->SetStopAnimation(true);

		//! 5秒止まる
		if (AnimFrm >= 30) {
			Stop = false;
			AnimFrm = 0;
			mcpAnimsprite->SetStopAnimation(false);
			mcpAnimsprite->ResetAnimCnt();
		}
	}

	//! 死んでいるかの判断
	if (!mAlive)
	{
		BaseEnemy::Destroy();
	}
}

/* -----------
// 描画処理 */
void SoftEnemy::Draw()
{
	//! 本体の描画
	if (!Status.MoveDirFlg)
	{
		mcpAnimsprite->SetYSplit(eDirection::Right);
	}
	if (Status.MoveDirFlg)
	{
		mcpAnimsprite->SetYSplit(eDirection::Left);
	}
	//! 本体の描画
	BaseEnemy::Draw();
}

/* -----------
// 尻尾で刺されたときの強さと処理 */
TailReaction SoftEnemy::SetStingPower(float _Power, bool _Elect)
{
	
	//!	やわらかい敵は弱く刺された時に死ぬ
	if (_Elect) {
		Reaction = TailReaction_Through;
		mAlive = false;		//! 死
		Stinged = true;
		SoundMgr->PlaySE(SE_Hoder_Sasaru, 0.1f);
		EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.7f,0.7f));
	}
	else if (mcpAnimsprite->GetCurrentXSplit() == 2 ||
		mcpAnimsprite->GetCurrentXSplit() == 3 || mcpAnimsprite->GetCurrentXSplit() == 4)
	{
		Reaction = TailReaction_Through;
		mAlive = false;		//! 死
		Stinged = true;
		SoundMgr->PlaySE(SE_Hoder_Sasaru, 0.1f);
		EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
	}

	else {
		if (_Power >= STING_STRONG)
		{
			//! 強い
			Reaction = TailReaction_Bounce;
			SoundMgr->PlaySE(SE_Hoder_Haziku,0.07f);
			EffMgr->PlayEffect(Hibana, mcVec, Vector2(0.7f, 0.7f));
		}
		else if (_Power >= STING_MIDIUME)
		{
			//! 普通
			mMidHitcount++;
			if (mMidHitcount < 2) {
				Reaction = TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Hoder_Haziku, 0.07f);
				EffMgr->PlayEffect(Hibana, mcVec, Vector2(0.7f, 0.7f));
			}
			else {
				Reaction = TailReaction_Through;
				mAlive = false;		//! 死
				Stinged = true;
				SoundMgr->PlaySE(SE_Hoder_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
			}
		}	
	}

	//! 弱い以外で刺されたら跳ね返る

	return Reaction;

}
