#include "SplitLowerEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "Camerah.h"
#include "Time.h"
#include "WinMain.h"
#include "Controller.h"
#include <math.h>

//! つづき　スプリッターの画像を適応してください。
//! 当たり判定と合わせるところまでやりました。次は動かしてもんだいないかをやってください
//1 そのあとに分裂後の当たり判定をお願いします

//! コンストラクタ
SplitLowerEnemy::SplitLowerEnemy()
{
	//! くっついる状態での当たり判定を作る
	msSize.x = 0.5f;
	msSize.y = 0.6f;
	mcCombiPos = Vector2(mcVec.x,mcVec.y - 0.1f); //! 座標
	mcCombColSize = Vector2(0.2f, 0.56f);          //! サイズ
	mcpCombiCol = new Box(mcCombiPos,mcCombColSize.x,mcCombColSize.y);
	ColSize = Vector2(0.3f, 0.3f);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Splitter));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	Combi = true;
	Count = 0;
	
	//! 分裂後の当たり判定の生成
	mcpSplitedCol = new Box(mcSplitedColPos,0.2f,0.3f);

	mfSpeed = 0.006f;
	TotalMove = 0.0f;
	mTag = Tag_Enemy_SplitD;
	MutekiCount = 0;
	//! 上の敵の生成
	mcpSpltterUP = new SplitUpperEnemy(mcVec, Combi);
	mcpSpltterUP->SetCameraActiv(false);

	TotalMove = 0;
	FollowMove = 0;
	mAlive = true;
}

SplitLowerEnemy::SplitLowerEnemy(float _x, float _y)
{
	//! くっついる状態での当たり判定を作る
	mcVec = Vector2(_x, _y);
	mcCombiPos = Vector2(mcVec.x, mcVec.y + 0.1f); //! 座標
	mcCombColSize = Vector2(0.2f, 0.4f);          //! サイズ
	mcpCombiCol = new Box(mcCombiPos, mcCombColSize.x, mcCombColSize.y);
	Combi = true;
	ColSize = Vector2(0.3f, 0.3f);
	mfSpeed = 0.006f;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Splitter));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mTag = Tag_Enemy_SplitD;
	Count = 0;
	TotalMove = 0;
	FollowMove = 0;
	//! 上の敵の生成
	mcpSpltterUP = new SplitUpperEnemy(mcVec, Combi);
	mAlive = true;
}


//! デストラクタ
SplitLowerEnemy::~SplitLowerEnemy()
{
	delete mcpCombiCol;
	delete mcpSpltterUP;
}

/* ----------- 
// 更新処理 */
void SplitLowerEnemy::Update()
{
	if (Combi) {
		mcMoveVector.x += mfSpeed; //! スピードを加算
		TotalMove += fabs(mfSpeed);
		if (TotalMove > 0.6f) {
			mfSpeed *= -1; //! 移動量を反転させる
			TotalMove = 0;
		}
	}
	else {
		if (Follow) {
			//! プレイヤーに対して右にいるとき	
			FollowMove += fabs(mfSpeed);
			mcMoveVector.x += mfSpeed; //! スピードを加
			if (mcPlayer->GetVec().x < mcVec.x) {
				mfSpeed = -0.008f;
			}
			//! プレイヤーに対して左にいるとき
			else {
				mfSpeed = 0.008f;
			}
			if (FollowMove >= 3.0f) {
				Follow = false;
			}
		}
	}

	//! 画像のさゆうの向きのセット
	if (mfSpeed < 0) {
		mcpAnimsprite->SetYSplit(1);
	}
	else {
		mcpAnimsprite->SetYSplit(0);
	}

	if (mAlive) {
		bool Vibe = CAMERA->GetVibration();
		bool OnObj = mcpBoxCol->GetOnObj(); //! オブジェクトの上にのっているかを取得
		if (OnObj == true) {
			mTouchGraund = true;
		}
		//! 画面振動しているときは重力をかけない
		if (mTouchGraund == false && Vibe == false) {
			double ElapsedTime = CurrentTime - GravityTime;
			float Gravtiy = -ga * pow(ElapsedTime, 2) / 2.0f; //! 重力による下方向の力の計算	ミリ秒での計算なので1000で割る
			//! 重力の影響の最大値を超えないようにする
			if (Gravtiy >= 0.02f) {
				Gravtiy = 0.02f;
			}
			mcMoveVector.y += Gravtiy; //! 重力の力を加算
		}
		else {
			GravityTime = CurrentTime; //! 秒単位の今の時間を取得する
		}

		mcVec += mcMoveVector;              //! このキャラクターにかかっている力を足す
		if (Combi) {
			mcpCombiCol->SetMoveVec(mcMoveVector);  //! 当たり判定に使います
		}
		else {
			mcpSplitedCol->SetMoveVec(mcMoveVector);    //! 当たり判定に使うための情報をセット	
		}
		CurrentTime += (1.0f / 60.0f);  //! 経過時間を増やす
		mcMoveVector.SetVector(0, 0);        //! このキャラクターにかかっている力を０にする
		mcpBoxCol->SetOnObj(false);         //! 上には乗っていないことにする　ここでfalseにした方がCollsionがすっきりするのでここでfalseにします
	}

	//! 動いた座標からくっついてる時の当たり判定の中心座標を計算する
	if (Combi) {
		mcCombiPos = Vector2(mcVec.x, mcVec.y - 0.04f); //! 座標
		mcpSpltterUP->SetDrawActiv(false);
	}
	else {
		mcSplitedColPos = Vector2(mcVec.x, mcVec.y -0.2f);
		MutekiCount++;
	}
	mcpSpltterUP->Update();
	
	if (!mAlive) {
		mcpSplitedCol->SetActiv(false);
		BaseEnemy::Destroy();
	}
}

/* ----------
// 描画処理 */
void SplitLowerEnemy::Draw()
{
	GameObject::Draw();
	mcpSpltterUP->Draw();	
}

/* -------------------------- 
// 当たり判定処理後の処理  */
void SplitLowerEnemy::LastUpdate()
{
	if (Combi) {
		mcpSpltterUP->FixVec(mcVec);
	}
}

void SplitLowerEnemy::SetInitVec(Vector2 _vec)
{
	mcVec = _vec;
	mcpSpltterUP->FixVec(mcVec);
}

/* ---------------------------
// 上についてる敵のゲッター */
SplitUpperEnemy * SplitLowerEnemy::GetUpperEnemy()
{
	return mcpSpltterUP;
}

/* ----------------------- 
// 当たり判定のゲッター */
Box * SplitLowerEnemy::GetBoxCol()
{
	//! くっついていたら分割前の当たりを返す
	if (Combi) {
		return mcpCombiCol;
	}
	//! くっついていなかったら単独での当たり返す
	return mcpSplitedCol;
}

bool SplitLowerEnemy::GetDeath()
{
	if (Death && !Deathed && Stinged) {
		Deathed = true;
		return true;
	}
	Stinged = false;

	//! 上側にいるほうの倒されたかも返す
	return mcpSpltterUP->GetDeath();
}


//! このオブジェクトが刺された時の
TailReaction SplitLowerEnemy::SetStingPower(float _Power, bool _Elect)
{
	if (Combi) {
		if (_Elect) {
			Reaction = TailReaction::TailReaction_StingStop;
			//! 刺された音
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.5f,0.5f));
			Combi = false; // 強で刺されたら分裂する
			mcpSpltterUP->SetDrawActiv(true);
			mcpAnimsprite->SetTexture(TEXTURE(Tex_Splitter_Leg));
			mcpAnimsprite->ResetAnimCnt();
			mcpSpltterUP->SetCameraActiv(true);
			Follow = true;
		}
		else {
			if (_Power > STING_STRONG) {
				Reaction = TailReaction::TailReaction_StingStop;
				//! 刺された音
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.5f, 0.5f));
				Combi = false; // 強で刺されたら分裂する
				mcpSpltterUP->SetDrawActiv(true);
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Splitter_Leg));
				mcpAnimsprite->ResetAnimCnt();
				mcpSpltterUP->SetCameraActiv(true);
				Follow = true;
			}
			else if (_Power > STING_MIDIUME) {
				Reaction = TailReaction::TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Splitter_Haziku,0.08f);
				EffMgr->PlayEffect(Hibana, mcVec, Vector2(0.5f, 0.5f));
			}
		}
	}
	else if(MutekiCount > 10){
		if (_Elect) {
			mAlive = false;
			Stinged = true;
			Reaction = TailReaction_Through;
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02,Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.5f, 0.5f));
		}
		else {
			if (_Power > STING_STRONG) {
				Reaction = TailReaction::TailReaction_StingStop;
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.5f, 0.5f));
				mAlive = false;
				Stinged = true;
			}
			else if (_Power > STING_MIDIUME) {
				Reaction = TailReaction::TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.07);
				EffMgr->PlayEffect(Hibana, Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.4f, 0.4f));
			}
			else {
				Reaction = TailReaction::TailReaction_Stop;
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.07);
				EffMgr->PlayEffect(Hibana, Vector2(mcVec.x, mcVec.y - 0.1f), Vector2(0.4f, 0.4f));
			}
		}
	}
	return Reaction;
}

void SplitLowerEnemy::SetFollow(bool _state)
{
	if (!Combi) {
		Follow = _state;
		mcpAnimsprite->SetStopAnimation(true);
	}
}

/* ---------------------- 
// 重力の計算をします  */
void SplitLowerEnemy::ForceProces()
{
	
}

/* -----------
// 移動関数 */
void SplitLowerEnemy::Walk()
{
	
}

/* ----------------- 
// 倒れる時の関数 */
void SplitLowerEnemy::Destroy()
{
	
	if (Count <= 50)
	{
		//! 点滅させる
		if ((Count % 20) <= 10) {
			SetDrawActiv(false);

		}
		else {
			mcpAnimsprite->SetColor(1.0f, 0.0f, 0.0f);
			SetDrawActiv(true);
		}
		Count++;
	}
	else
	{
		SetDrawActiv(false);	//! 画像を消す
		SetHitActiv(false);		//! 当たり判定を消す
	}
}
