#include "DirectInput8.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "BaseDrone.h"
#include "EffectManager.h"

/* -----------
// コンストラクタ */
BaseDrone::BaseDrone()
{
	mTag = ObjectTag::Tag_Drone;
	//! 当たり判定の大きさセット
	ColSize = Vector2(0.3f, 0.3f);

	//! アニメーションテーブル
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));	//! エネミー画像のセット

	//! フラグ関係
	CarryFlg = true;	//! 運搬フラグ

	//! 初期値の設定
	mfSpeed = 0.008f;	//! スピードの初期値設定
	TotalMove = 0.0f;	//! 総移動距離の初期値
}

/* -----------
// コンストラクタ */
BaseDrone::BaseDrone(float _x, float _y)
{
	//! 座標のセット
	mcVec = Vector2(_x, _y);
	//! 当たり判定の大きさセット
	ColSize = Vector2(0.3f, 0.3f);

	//! アニメーションテーブル
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));	//! エネミー画像のセット

	//! フラグ関係
	CarryFlg = true;	//! 運搬フラグ

	//! 初期値の設定
	mfSpeed = 0.008f;	//! スピードの初期値設定
	TotalMove = 0.0f;	//! 総移動距離の初期値
}
/* -----------
// デストラクタ */
BaseDrone::~BaseDrone()
{

}
/* -----------
// 更新処理 */
void BaseDrone::Update()
{
	Fly();						//! 飛行移動
	mcpBoxCol->SetPrevVec(mcVec);       //! 前フレームの座標として保存する
	mcpShape->SetMoveVec(mcMoveVector); //! 当たり判定に使うための情報をセット
	EnemyBase();						//! 敵の呼び出し
	mcMoveVector.SetVector(0, 0);        //! このキャラクターにかかっている力を０にする
	//! 当たり情報にサイズセット
	mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
}

/* -----------
// 描画処理　*/
void BaseDrone::Draw()
{
	GameObject::Draw();
}
/* -----------
// 敵のセッター */
void BaseDrone::SetEnemy(BaseEnemy * _EnemyNo)
{
	//! 敵のセット
	mcpEnemy = _EnemyNo;
	//! 持たれている状態にする
	mcpEnemy->SetCarryFlg(true);
}

/* -----------
// 持たれている敵の処理 */
void BaseDrone::EnemyBase()
{
	//! 持たれている間
	if (CarryFlg)
	{
		if (!mAlive)
		{
			mcMoveVector.x = 0;
		}
		//! ドローンと同じ動きをする
		mcpEnemy->SetMoveVec(mcMoveVector);
	}
}

/* -----------
// ドローンの移動と行動の処理 */
void BaseDrone::Fly()
{
	//! ドローンとプレイヤーとの距離が一定になったら
	float px = mcPlayer->GetVec().x;
	if (fabs(mcVec.x - px) <= 1.9f)
	{
		//! 追跡フラグをtrueにする
		ChaseFlg = true;
	}

	//! 追跡フラグがtrueの場合
	if (ChaseFlg)
	{
		mcMoveVector.x -= mfSpeed;	//! スピードの減算
		TotalMove -= fabs(mfSpeed);	//! 総移動距離の減算
		if (mAlive) {
			mcVec += mcMoveVector;		//! 位置の移動
		}
		//! 左方向移動　運搬フラグtrue ドローン生存フラグtrue　の場合
		if (TotalMove < -1.0f && CarryFlg && mAlive) {

			mfSpeed *= -1;		//! 移動量を反転させる	
			TotalMove = 0;		//! 総移動距離の初期化
			CarryFlg = false;	//! 持っているかどうかのフラグをfalseに
			ChaseFlg = false;
			mcpEnemy->SetCarryFlg(false);	//! 上に同じ
			
			//! いくつかバグを見つけたので修正しておきます
			//SetHitActiv(false); //! 戻るときに他のドローンなどに当たらないようにするために当たり判定をなくします
		}
		
		//if (TotalMove < -1.5f && !CarryFlg)
		//{
		//	//! ここで0にしてしまうと死ぬときの処理に毎フレーム入らないです
		//	//TotalMove = 0;		//! 総移動距離の初期化
		//	//死ぬ処理
		//	BaseEnemy::Destroy();

		//}		
		//! 消す処理
		if (!mAlive)
		{
			if (CarryFlg)
			{
				BaseEnemy::Destroy();	//! ドローン本体の消去
				mcpEnemy->Destroy();	//! 持たれている敵の消去
			}
			else
			{
				BaseEnemy::Destroy();	//! ドローン本体の消去
			}
			
		}
	}
}

bool BaseDrone::GetCarryFlg()
{
	return CarryFlg;
}

/* -----------
// 尻尾の刺す強さ取得関数 */
TailReaction BaseDrone::SetStingPower(float _Power, bool _Elect)
{
	//! ドローンは強弱関係なしに死ぬ
	Reaction = TailReaction_None;
	if (mAlive) {
		if (_Elect) {
			//! 強い
			Reaction = TailReaction_Through;
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.7f,0.7f));
			mAlive = false;
			Stinged = true;
			mcpBoxCol->SetActiv(false);
		}
		else {
			if (_Power >= STING_STRONG)
			{
				//! 強い
				Reaction = TailReaction_StingStop;
				SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
				mAlive = false;
				Stinged = true;
				mcpBoxCol->SetActiv(false);
			}
			else if (_Power >= STING_MIDIUME)
			{
				//! 普通
				Reaction = TailReaction_StingStop;
				SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
				mAlive = false;
				Stinged = true;
				mcpBoxCol->SetActiv(false);
			}
		}
	}
	//! リアクションを返す
	return Reaction;
}

