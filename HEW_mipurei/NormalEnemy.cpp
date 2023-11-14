#include "NormalEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

/* -----------
// コンストラクタ　*/
NormalEnemy::NormalEnemy()
{
	//! アニメーション関係
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! エネミー画像のセット

	//! 攻撃判定？
	mcpShape->SetAttack(true);
	//! タグ
	mTag = Tag_Enemy_Tinpillar;
	//! スピードの初期値設定
	BaseEnemy::SetMove(0.004);

	ColSize.x = ColSize.y = 0.28;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// コンストラクタ */
NormalEnemy::NormalEnemy(float _x,float _y)
{
	//! 初期位置の設定
	mcVec = Vector2(_x, _y);
	//! アニメーション関係
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! エネミー画像のセット

	//! 攻撃判定？
	mcpShape->SetAttack(true);
	//! タグ
	mTag = Tag_Enemy_Tinpillar;
	//! スピードの初期値設定
	BaseEnemy::SetMove(0.004);

	ColSize.x = ColSize.y = 0.28;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// デストラクタ */
NormalEnemy::~NormalEnemy()
{
	//! 特に書くことなし
}

/* -----------
// 更新処理 */
void NormalEnemy::Update()
{
	//! 本体の更新
	BaseEnemy::Update();

	//! 死んだときの処理
	if (!mAlive)
	{
		//! 死
		BaseEnemy::Destroy();
	}
	
}

/* -----------
// 描画処理 */
void NormalEnemy::Draw()
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
	BaseEnemy::Draw();
}

/* -----------
// 尻尾で刺されたときの強さと処理 */
TailReaction NormalEnemy::SetStingPower(float _Power ,bool _Elect)
{
	Reaction = TailReaction_None;
	//! 雑魚敵は普通以上で死ぬ(仮)
	if (_Elect) {
		Stinged = true;
		mAlive = false;
		Reaction = TailReaction::TailReaction_Through;
		SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.07);
		EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.7f,0.7f));
	}
	else {
		if (_Power >= STING_STRONG)
		{
			//! 強い
			Reaction = TailReaction_StingStop;
			Stinged = true;
			mAlive = false;
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
			//! 刺された音
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
		}
		else if (_Power >= STING_MIDIUME)
		{
			//! 普通
			Reaction = TailReaction_StingStop;
			mAlive = false;
			Stinged = true;
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
			//! 刺された音
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
		}
	}
	return Reaction;
}

