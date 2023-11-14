#include "PlugTail.h"
#include "TextureManager.h"
#include "DirectInput8.h"
#include "Angle.h"
#include "Controller.h" 
#include "Game.h"
#include <math.h>
#include "EffectManager.h"
#include "Dynamo.h"
#include "Camerah.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "WeakDynamo.h"
#include "Pimp.h"
#include "WinMain.h"
#include "SoundManager.h"


//! コンストラクタ
PlugTail::PlugTail(Vector2 & _tailvec, Vector2 & _playervec, ePlayerState & _state, eDirection & _direction, eElectricity & _electstate)
	: mcTailRoot(_tailvec), mcPlayerVec(_playervec), mPlayerState(_state), mDirection(_direction), ElectState(_electstate)
{
	//! 変数の初期値設定
	mcOldPlayerVec = mcPlayerVec;
	mDownAtkSpeed = 1.0f;
	mReturnSpeed = 0.005f;
	AttackInitSpeed = 0.00048f;
	AttackRadius = 0.06f; //! 攻撃の大きさ
	mTailRange = 0.125f;	                               //! しっぽの届く範囲	
	mcDefaultSize = Vector2(0.1f, 0.1f);                   //! デフォルトのサイズ
	mcAimeSize = Vector2(0.2f, 0.2f);                       //! エイムの時のサイズ
	msSize = FLOAT2(mcDefaultSize.x, mcDefaultSize.y);      //! しっぽのサイズの設定 デフォルトのサイズ
	AtkStop = false;
	mOverheat = false;
	SetCameraActiv(false);
	msDisCharge = { false,false,false,0 ,false };           //! 放電構造体の初期化
	msBounce = { 0,0,false,false };                         //! はじかれるリアクションの構造体
	Nomal = Blue = Yellow = Red = false;
	Nomal = true;
	ReactionDerection = Direction_None;

	//! しっぽのサイズ
	msSection.DefaultSize = { 0.15f, 0.1f };
	msSection.AimSize = { 0.3f,0.2f };
	msSection.Size = msSection.DefaultSize;
	msSection.Pich = msSection.PichDefault = 0.014f;
	msSection.PichAim = 0.028f;

	//! しっぽの初期位置の計算
	RStickAngle = DegreeToRadian(110);
	mcVec.x = cos(RStickAngle) * mTailRange + mcTailRoot.x;
	mcVec.y = sin(RStickAngle) * mTailRange + mcTailRoot.y;
	mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));  //! しっぽの角度

	//! しっぽ本体の当たり判定
	mcpCol = new Box(mcVec, 0.05f, 0.05f); // 矩形の当たり判定情報の設定
	mcpShape = mcpCol;
	mcpAttackCircle = new Circle(mcAttackPos, AttackRadius);
	mcpAttackCircle->SetActiv(false);

	//! 描画のための初期設定
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Plug));	//! 画像のセット
	mcpAnimsprite->SetAngle(mTailAngle + DegreeToRadian(90));       //! 描画角度のセット
	mcpAnimsprite->SetAnimtionTable(1, 1);                           //! アニメーションテーブルのセット	

	//! しっぽの中間部分ようの描画クラス
	msSection.Section = new AnimationHitObject;
	msSection.Section->SetCameraActiv(false); //! プレイヤーについて動くのでカメラからの修正を受け取らない
	AnimationSprite * SectionSprite = msSection.Section->GetAnimSprite();
	SectionSprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Tail));         //! 画像のセット
	msSection.Section->SetSize(msSection.Size.x, msSection.Size.y);         //! サイズのセット
	SectionSprite->SetAnimtionTable(1, 1);                                 //! アニメーションテーブルのセット
	SectionSprite->SetAngle(mTailAngle + DegreeToRadian(270), 1.0f, 0.5f);

	Tail(); //! しっぽの各節の位置を求める
	mReaction = TailReaction::TailReaction_None;

	//! 電気の槍の初期設定
	msSpear.ElectSting = new AnimationHitObject();
	msSpear.ElectSting->SetDrawActiv(false);
	AnimationSprite * ElectStingSp = msSpear.ElectSting->GetAnimSprite();
	ElectStingSp->SetTexture(TexMgr->GetTextuer(Tex_Player_ElectSting));
	ElectStingSp->SetAnimtionTable(5, 1);
	msSpear.DefaultSize = Vector2(0.5f, 0.5f);
	msSpear.SmallSize = Vector2(0.3f, 0.3f);
	msSpear.TailDistance = 0.1f;
	msSpear.ElectSting->SetSize(msSpear.DefaultSize);
	//! 当たり判定の生成
	//! 先端
	msSpear.Col = new Circle(msSpear.ColPos, 0.04f);
	msSpear.Col->SetActiv(false);
	//! 根本
	msSpear.ColRoot = new Circle(msSpear.ColRootPos, 0.04f);
	msSpear.ColRoot->SetActiv(false);

	mAimeAngleSet = true;

	mTag = ObjectTag::Tag_Tail;
}

//! デストラクタ
PlugTail::~PlugTail()
{
	delete msSection.Section;
	delete mcpCol;
	delete msSpear.ElectSting;
	delete msSpear.ColRoot;
	delete msSpear.Col;
	delete mcpAttackCircle;
}

//! 更新処理
void PlugTail::Update()
{
	//! プレイヤーの移動量を加算する	
	mcVec += mcPlayerVec - mcOldPlayerVec;
	for (int i = 0; i < 100; i++) {
		msSection.Inf[i].Pos += mcPlayerVec - mcOldPlayerVec;
	}

	//! 向きが変わった時に一度だけ座標をたす	
	if (PrevDirection != mDirection) {
		if (mDirection == Left) {
			mcVec.x = mcTailRoot.x + -mcTailDistance.x;
		}
		else if (mDirection == Right) {
			mcVec.x = mcTailRoot.x + -mcTailDistance.x;
		}
		mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));//! しっぽの角度の取得
		RStickAngle = mTailAngle - DegreeToRadian(180);
	}

	PrevDirection = mDirection;          //! まえのフレーム向きを保存
	mcTailDistance = mcVec - mcTailRoot; //! しっぽの付け根との距離を確認する	
	State(); //! ステートの処理
	mcOldPlayerVec = mcPlayerVec;        //! 前フレームの位置として代入
}

/* ---------------
// ステート処理 */
void PlugTail::State()
{
	switch (mState)
	{
	case Tail_Idol:
		Idol_Controller();
		break;
	case Tail_Attack:
		Attack_Controller();
		break;
	}
}

//! プレイヤーの当たり判定処理の後の修正処理
void PlugTail::LastUpdate()
{

}

//! 描画処理
void PlugTail::Draw()
{
	if (Nomal) {
		mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_Plug));
		msSection.Section->GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_Tail));
	}
	else if (Red) {
		mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_PlugR));
		msSection.Section->GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_TailR));
	}
	else if (Yellow) {
		mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_PlugY));
		msSection.Section->GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_TailY));
	}
	
	msSpear.ElectSting->GetAnimSprite()->SetAngle(mTailAngle + DegreeToRadian(180));
	msSpear.ElectSting->Draw();

	//! 尻尾の描画
	for (int i = 0; i < msSection.Num; i++) {
		msSection.Section->SetSize(msSection.Size.x, msSection.Size.y);
		msSection.Section->SetVec(msSection.Inf[i].Pos);
		msSection.Section->GetAnimSprite()->SetAngle(msSection.Inf[i].Angle + DegreeToRadian(270));
		msSection.Section->Draw();
	}
	mcpAnimsprite->SetAngle(mTailAngle + DegreeToRadian(90));
	AnimationHitObject::Draw();
}

/* ------------------
// 状態のセット関数*/
bool PlugTail::SetState(TailState _state)
{
	//! アイドル状態に移行
	if (_state == TailState::Tail_Idol) {
		//! 攻撃していないときのみアイドル状態になれる
		if (AttackState == AttackState_Aim || AttackState == AttackState_None) {
			mState = _state;
		}
		else {
			return false;
		}
	}
	else {
		mState = _state;
	}
	return true;
}

/* ------------------------------
// アイドル状態 コントローラー */
void PlugTail::Idol_Controller()
{
	//! Idolの位置にしっぽを移動させるしっぽの位置は固定？	
	//! 攻撃の途中でidol状態にならないようにする
	if (mTailRange >= 0.15) {
		mTailRange -= 0.025;
	}
	//! しっぽのサイズを大きくする
	if (msSize.x > mcDefaultSize.x) {
		//! Yも同じおおきさなので同時に加算する
		msSize.x -= 0.025f;
		msSize.y -= 0.025f;
	}
	//! しっぽの中間部分の大きさを大きくする	
	if (msSection.Size.x > msSection.DefaultSize.x) {
		msSection.Size.x -= 0.025f;
	}
	if (msSection.Size.y > msSection.DefaultSize.y) {
		msSection.Size.y -= 0.02f;
	}
	if (msSection.Pich > msSection.PichDefault) {
		msSection.Pich -= 0.0028f;
	}

	mAimeAngleSet = true;

	AttackState = TailAttackState::AttackState_None;
	mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));//! しっぽの角度の取得	
	mStingPower = 0; //! 攻撃していないときは０にする　暫定処理です
	mReactionFrameCnt = 0;
	mDownAtkSpeed = 1.0f;
	MoveLimit();
	Tail();
	ElectSpear();
}

/* -----------------------------------
// 攻撃状態の処理（コントローラー） */
void PlugTail::Attack_Controller()
{
	//! IdolからAttackに以降する処理 フラグが増えると思う
	//! しっぽのサイズを大きくする
	if (msSize.x < mcAimeSize.x) {
		//! Yも同じおおきさなので同時に加算する
		msSize.x += 0.025f;
		msSize.y += 0.025f;
	}
	//! しっぽの中間部分の大きさを大きくする
	if (msSection.Size.x < msSection.AimSize.x) {
		msSection.Size.x += 0.025f;
	}
	if (msSection.Size.y < msSection.AimSize.y) {
		msSection.Size.y += 0.02f;
	}

	if (msSection.Pich < msSection.PichAim) {
		msSection.Pich += 0.0028f;
	}

	switch (AttackState)
	{
	case AttackState_Aim:
		Aim_Controller();
		break;
	case AttackState_Sting:
		AttackPosture_Controller();
		break;
	case AttackState_Reaction:
		Reaction_Controller();
		break;
	case AttackState_End:
		AttackState = AttackState_None;
		break;
	}

	//! 放電の処理
	if (msDisCharge.Able) {
		DisCharge();
	}
	Tail();
	ElectSpear();

}

void PlugTail::Destroy()
{
	SetDrawActiv(false);
	SetHitActiv(false);
	msSection.Section->SetHitActiv(false);
	msSection.Section->SetDrawActiv(false);
}

//! チャージフラグを返す
bool PlugTail::GetChrage()
{
	if (mCharge) {
		mCharge = false;
		return true;
	}
	return false;
}

//! しっぽの攻撃後のリアクション
void PlugTail::Reaction_Controller()
{
	//! 何もリアクションしていない時に攻撃できる	
	switch (mReaction)
	{
	case TailReaction_Bounce:
		Bounce();
		break;

	case TailReaction_Stop:
		Stop();
		break;

	case TailReaction_StingStop:
		StingStop_Controller();
		break;

	case TailReaction_Through:
		Through(); //! しっぽを刺したときにそのまま貫くときの処理
		break;

	case TailReaction_Sting:
		StingObj();
		Sting_Controller();
		break;

	case TailReaction_StingDeep:
		StingObj();
		StingDeep_Controller();
		break;

	case TailReaction_End:
		ReturnTail();
		break;
	}
}

//! エイム時の操作
void PlugTail::Aim_Controller()
{
	//! 狙うときのしっぽの射程にする
	//mTailRange = 0.4f;
	if (mTailRange < 0.4f) { 
		mTailRange += 0.04f;
		if (mTailRange >= 0.4f) {
			mTailRange = 0.4f;
		}
	}
	else if (mTailRange > 0.4f) {
		mTailRange -= 0.04f; 
		if (mTailRange <= 0.4f) {
			mTailRange = 0.4f;
		}
	}

	//! 刺すにうつる
	int RT = GetControllerRightTrigger();
	if (RT >= 5) {
		AttackState = TailAttackState::AttackState_Sting;
	}
	MoveLimit();
}


/* -------------------------------------------
//! 攻撃態勢の関数 コントローラー操作の場合 */
void PlugTail::AttackPosture_Controller()
{
	float distance = mcVec.PosToPos(mcTailRoot); //! プレイヤーとの距離を求める

	//! トリガーの押し込み具合を取得
	int RT = GetControllerRightTrigger();
	//! トリガーが５以上を押されていたら計測開始
	if (Attack_C == false && TriggerStart_C == false && RT >= 5) {
		TriggerStart_C = true;
		mTailRange = 0.4f;
		SoundMgr->PlaySE(SE_Tame,0.1f);
	}

	//! 計測中
	if (TriggerStart_C && !Attack_C) {
		//! すこしだけ動かす
		MoveLimit(1);

		mDownAtkSpeed = 1.0f;
		//! おしこまれている値が最大値より大きければ代入する
		Red = Blue = Yellow = false;
		Nomal = false;

		if (RT > MaxTrigger_C) { MaxTrigger_C = RT - 5;}

		//! トリガーが255になったら引き絞られる感じで尻尾のながさを短くする
		if (RT == 255) {
			mTailRange -= 0.005f;
			if (mTailRange < 0.3f) {
				mTailRange = 0.31f;
				MaxTrigger_C = 255;	
			}
		}

		//Tail();
		//! トリガーの値が０になったら攻撃開始
		if (RT == 0) {
			Attack_C = true;
			SoundMgr->PlaySE(SE_Sting01, 0.06f);
			//EffMgr->PlayEffect();
		}
	}

	//! 仮の処理です //! ２５０
	//! デバッグように色を変えます
	if (AttackInitSpeed * MaxTrigger_C > STING_STRONG) {
		Red = true;
	}
	else {
		Yellow = true;
	}
	/*else if (AttackInitSpeed * MaxTrigger_C > STING_MIDIUME) {
		Yellow = true;
	}*/
	
	if (Attack_C) 
	{
		//! しっぽの進むスピードを計算する
		mAtkSpeed = AttackInitSpeed * MaxTrigger_C;
		mTailRange = 1.4f;
		mcVec.y += sin(RStickAngle) * (mAtkSpeed * mDownAtkSpeed);
		mcVec.x += cos(RStickAngle) * (mAtkSpeed * mDownAtkSpeed);
		//! 攻撃の座標をセットする
		mcAttackPos.x = mcVec.x;
		mcAttackPos.y = mcVec.y;
		mcpAttackCircle->SetActiv(true); //! 攻撃の当たり判定をオンにする
		mStingPower = mAtkSpeed;

		//! しっぽが範囲外にでるか　スピードが一定以下になったら戻る
		if ((distance > mTailRange) || mStingPower < 0.006f) 
		{
			mAtkSpeed = 0;
			MaxTrigger_C = 0;
			TriggerStart_C = false;
			Attack_C = false;
			mcpAttackCircle->SetActiv(false);   //! 攻撃の当たり判定をオフにする
			mStingPower = 0;
			AttackState = AttackState_Reaction; //! リアクションに行く
			mReaction = TailReaction_End;       //! 攻撃終了にいく
			msSpear.Col->SetActiv(false);       //! 電気の槍の当たり判定を消す
		}
	}
}

//! しっぽが柔らかい敵にはじかれたときの処理
void PlugTail::Bounce()
{
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mcpAttackCircle->SetActiv(false); //! 攻撃の当たり判定をオフ

	msBounce.Flg = true;

	//! 4フレーム止まる
	if (msBounce.Cnt > 4) 
	{
		//! その時の角度に120度足す
		//! 120度加算したらやめる
		if (msBounce.TotalAngle < 110) 
		{
			if (ReactionDerection == Left) 
			{
				mTailAngle += DegreeToRadian(110);
			}
			else if (ReactionDerection == Right) 
			{
				mTailAngle -= DegreeToRadian(110);
			}
			msBounce.TotalAngle += 110;
			msBounce.speed = mStingPower * 0.3f;
			msBounce.ReTail = false;
		}

		//! 今の角度で進ませる	
		if (!msBounce.ReTail) {
			//! しっぽの移動した量
			msBounce.TotalMove += fabs(cos(mTailAngle) * -msBounce.speed);
			msBounce.TotalMove += fabs(sin(mTailAngle) * -msBounce.speed);
			//! 尻尾を移動させる
			mcVec.x += cos(mTailAngle) * -msBounce.speed;
			mcVec.y += sin(mTailAngle) * -msBounce.speed;
			msBounce.speed *= 0.9f; //! スピード遅くする

		}
		//! スピードが０になったら戻り始める
		if (msBounce.speed < 0.001f && !msBounce.ReTail) {
			msBounce.speed = 0.002f;
			msBounce.ReTail = true;
		}

		float distance = 0;
		//! 尻尾を戻す
		if (msBounce.ReTail) 
		{
			//! フレーム待つ
			if (msBounce.Cnt > 20) 
			{
				//! スピードの最大値を超えるまで増やす
				if (msBounce.speed < 0.02f) 
				{
					msBounce.speed *= 1.1f;
				}
				//! しっぽの節を全て前の節に向かってい移動させる
				//! 根元になったら移動をやめる
				float Angle; //! 進む角度
				//! 尻尾本体の移動
				Angle = PositionRelationAngle(FLOAT2(mcVec.x, mcVec.y), FLOAT2(msSection.Inf[msSection.Num - 1].Pos.x, msSection.Inf[msSection.Num - 1].Pos.y));
				//! 移動
				//speed = 0.001f;
				mcVec.x += cosf(Angle) * -msBounce.speed;
				mcVec.y += sinf(Angle) * -msBounce.speed;
				//! 描画時の角度のセット
				mTailAngle = PositionRelationAngle(FLOAT2(mcVec.x, mcVec.y), FLOAT2(msSection.Inf[msSection.Num - 1].Pos.x, msSection.Inf[msSection.Num - 1].Pos.y));
				mTailAngle += DegreeToRadian(180);
				//! 尻尾の節の移動
				for (int i = msSection.Num - 1; i > -1; i--) 
				{
					if (i != 0) 
					{ //! 根本以外
						//! 進む角度を求める
						FLOAT2 Section1(msSection.Inf[i].Pos.x, msSection.Inf[i].Pos.y);
						FLOAT2 Section2(msSection.Inf[i - 1].Pos.x, msSection.Inf[i - 1].Pos.y);
						Angle = PositionRelationAngle(Section1, Section2);
						//! 移動
						msSection.Inf[i].Pos.x += cosf(Angle) * -msBounce.speed;
						msSection.Inf[i].Pos.y += sinf(Angle) * -msBounce.speed;
						//! 描画時の角度のセット
						msSection.Inf[i].Angle = Angle + DegreeToRadian(180);
					}
				}
				//! 根本の手前の節が根本とある程度近かったら、根元にして節の数を減らす
				//! 距離を求める
				distance = msSection.Inf[1].Pos.PosToPos(msSection.Inf[0].Pos);
				if (distance < (msSection.Pich * 0.6f)) { //! 距離が尻尾のピッチの半分以下なら
					//! 配列をずらす
					for (int j = 0; j < msSection.Num; j++) {
						//! 先頭には代入しない
						if (j != msSection.Num - 1) {
							msSection.Inf[j] = msSection.Inf[j + 1];
						}
					}
					msSection.Num--; //! 節に数を減らす
				}

				distance = mcVec.PosToPos(mcTailRoot);
				if (distance < 0.3f) {
					msBounce.ReTail = false;
					msBounce.Flg = false;
					msBounce.TotalAngle = 0;
					msBounce.TotalMove = 0;
					msBounce.Cnt = 0;
					mStingPower = 0;
					mReaction = TailReaction_End;
				}
			}
		}
	}
	msBounce.Cnt++;
}



//! 刺さらずに止まる時(処理は刺さって止まるときとほぼ同じ)敵は倒れない
void PlugTail::Stop()
{
	//! 15フレーム止まる	
	if (!mReactionFrameCnt <= 20) {
		mReaction = TailReaction_End;
	}
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! 攻撃の当たり判定をオフにする

	mReactionFrameCnt++;
}

/* ---------------------------------
// しっぽを刺して止まるときの処理 */
void PlugTail::StingStop_Controller()
{
	//! 15フレーム止まる	
	if (!mReactionFrameCnt <= 15) {
		mReaction = TailReaction_End;
	}

	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! 攻撃の当たり判定をオフにする
	mReactionFrameCnt++;
}

//! しっぽを敵に刺してそのまま貫く処理
void PlugTail::Through()
{
	//! 刺す威力を減らす
	if (ElectState == eElectricity::Elect_Super) {
		mDownAtkSpeed -= 0.15f; //! 下降補正の値を増やす
	}
	else {
		mDownAtkSpeed -= 0.3f; //! 下降補正の値を増やす
	}
	if (mDownAtkSpeed <= 0) {
		mDownAtkSpeed = 0.1f;
	}
	mReaction = TailReaction_None;
	//! 刺すに戻る
	AttackState = AttackState_Sting;
}

/* -------------
// 刺さる処理 */
void PlugTail::Sting_Controller()
{
	//! 攻撃をやめる
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! 攻撃の当たり判定をオフ

	msDisCharge.Able = true; //! 放電可能にする

	//! 引き抜こうとするモーションを居れたらいいかも
	//! 放電中は抜けないようにする
	if (!msDisCharge.Doing) {
		//! レバガチャで速く引き抜ける
		if (RightStickMashing()) {
			mReactionFrameCnt += 4;
		}
		//! 60フレーム経過したら抜ける
		if (mReactionFrameCnt >= 180) {
			mReaction = TailReaction_End;
			msDisCharge.Able = false; //! 放電不可にする
			mReactionFrameCnt = 0;
			mcpStingObj = nullptr;
		}
		mReactionFrameCnt++;
		//! 条件を満たしたら抜ける(レバガチャ？)
	}
}

/* -----------------------
// 深く刺さるときの処理 */
void PlugTail::StingDeep_Controller()
{
	//! 攻撃をやめる
	mAtkSpeed = 0;
	MaxTrigger_C = 0;
	TriggerStart_C = false;
	Attack_C = false;
	mStingPower = 0;
	mcpAttackCircle->SetActiv(false); //! 攻撃の当たり判定をオフ

	msDisCharge.Able = true; //! 放電可能にする
	//! 引き抜こうとするモーションを居れたらいいかも
	if (!msDisCharge.Doing) 
	{
		//! レバガチャで速く引き抜ける
		if (RightStickMashing()) {
			mReactionFrameCnt += 4;
		}
		//! 60フレーム経過したら抜ける
		if (mReactionFrameCnt >= 300) {
			mReaction = TailReaction_End;
			msDisCharge.Able = false; //! 放電不可にする
			mReactionFrameCnt = 0;
			mcpStingObj = nullptr;
		}
		mReactionFrameCnt++;
	}
}

/* ---------------------------------------
// しっぽが刺した後に基の位置に戻る処理 */
void PlugTail::ReturnTail()
{
	//! 10フレームは静止する
	if (mReactionFrameCnt > 10) {
		mcVec.x += cos(mTailAngle) * (mReturnSpeed);
		mcVec.y += sin(mTailAngle) * (mReturnSpeed);

		if (mReactionFrameCnt > 12 && mReactionFrameCnt < 20) {
			mReturnSpeed += 0.002f;
		}
		else if (mReactionFrameCnt < 25) {
			mReturnSpeed += 0.004f;
		}
	}
	float distance = mcVec.PosToPos(mcTailRoot); //! プレイヤーとの距離を求める
	if (distance < 0.4f) {
		mReaction = TailReaction_None;
		AttackState = AttackState_End;
		mTailRange = 0.4f;
		mReturnSpeed = 0.005f;
		mReactionFrameCnt = 0;
		msDisCharge.Able = false; //! 放電不可の状態にする
		Red = Blue = Yellow = false; //! 色を基に戻す
		Nomal = true;
	}
	mReactionFrameCnt++;
}

/* -------
// 放電 */
void PlugTail::DisCharge()
{
	//if (GetControllerButtonTrigger(Button_RB) && !msDisCharge.Doing) 
	//{
	//	msDisCharge.Doing = true;
	//	msDisCharge.Cnt = 0;
	//	SoundMgr->PlaySE(SE_NormalElec,0.5f);
	//}

	if (mOnElectForDynamo && !msDisCharge.Doing)
	{
		msDisCharge.Doing = true;
		msDisCharge.Cnt = 0;
		SoundMgr->PlaySE(SE_NormalElec, 0.5f);
	}

	if (mOverheat) {
		msDisCharge.End = true;
	}

	//! 放電中かつ、放電終了フラグが立っていないとき
	if (msDisCharge.Doing && !msDisCharge.End) {

		int NumDraw = msDisCharge.Cnt / 5 + 2;
		if (NumDraw == msSection.Num - 1) {
			NumDraw = msSection.Num - 1;
			msDisCharge.End = true; 	
			msDisCharge.Hit = true; 	
			EffMgr->PlayEffect(eEffect::DisCharge, mcVec.x, mcVec.y, 0.3f,0.2f,(RStickAngle - DegreeToRadian(90)));
		}
		else {
			EffMgr->PlayEffect(eEffect::DisCharge, msSection.Inf[NumDraw].Pos.x, msSection.Inf[NumDraw].Pos.y, 0.4f,0.3f, (RStickAngle - DegreeToRadian(90)));
		}
	}
	else if (msDisCharge.End) {
		//! 放電が終わり10フレーム経過したら終わる
		msDisCharge.Doing = false;
		msDisCharge.End = false;
		msDisCharge.Cnt = 0; //! 数えてるフレームをリセットする
		msDisCharge.Hit = false;
		mReactionFrameCnt = 300;
	}
	msDisCharge.Cnt++;
}

//! 移動制限関数
void PlugTail::MoveLimit(int speed)
{
	//! スティックの角度の取得	
	float RSAngle = GetControllerRightStickAngle();
	float Deg = RadianToDegree(RStickAngle);
	if (mState == TailState::Tail_Idol) {
		float PlusDif_Idol;
		float MinusDif_Idol;
		if (mDirection == Left) {
			//! しっぽの角度を70度にする
			//! プラス、マイナス方向の角度の差を取得
			PlusDif_Idol = GetPlusDifDegree(RadianToDegree(RStickAngle), 70);
			MinusDif_Idol = GetMinusDifDegree(RadianToDegree(RStickAngle), 70);

			if (PlusDif_Idol < MinusDif_Idol) {
				RStickAngle += DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) > 70) {
					RStickAngle = DegreeToRadian(70);
				}
			}
			else {
				RStickAngle -= DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) < 70) {
					RStickAngle = DegreeToRadian(70);
				}
			}
		}
		else {
			//! しっぽの角度を70度にする
			//! プラス、マイナス方向の角度の差を取得
			PlusDif_Idol = GetPlusDifDegree(RadianToDegree(RStickAngle), 110);
			MinusDif_Idol = GetMinusDifDegree(RadianToDegree(RStickAngle), 110);

			if (PlusDif_Idol < MinusDif_Idol) {
				RStickAngle += DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) > 110) {
					RStickAngle = DegreeToRadian(110);
				}
			}
			else {
				RStickAngle -= DegreeToRadian(4);
				if (RadianToDegree(RStickAngle) < 110) {
					RStickAngle = DegreeToRadian(110);
				}
			}
		}
	}
	else if (AttackState == TailAttackState::AttackState_Aim && mAimeAngleSet) {
		//! 0の時は代入しない
		if (RSAngle != 0) { mAimeAngleSet = false; }
		if (mDirection == Right) {
			RStickAngle -= DegreeToRadian(4);
			if (RadianToDegree(RStickAngle) < 10) {
				RStickAngle = DegreeToRadian(10);
			}
		}

		else {
			//! しっぽの角度を110度にする	
			RStickAngle += DegreeToRadian(4);
			if (RadianToDegree(RStickAngle) > 170) {
				RStickAngle = DegreeToRadian(170);
			}	
		}

	}
	else {
		//! 0の時は代入しない
		if (RSAngle != 0) {
			//! プラス、マイナス方向の角度の差を取得
			float PlusDif = GetPlusDifDegree(RadianToDegree(RStickAngle), RadianToDegree(RSAngle));
			float MinusDif = GetMinusDifDegree(RadianToDegree(RStickAngle), RadianToDegree(RSAngle));
			//! 差が小さい方に向かって移動していく
			if (PlusDif < MinusDif) {
				RStickAngle += DegreeToRadian(speed);
				//! 通り過ぎた時
				//! 通り過ぎたとき
				if (AttackState != AttackState_Sting) {
					if (RStickAngle > RSAngle) {
						RStickAngle = RSAngle;
					}
				}
			}
			else {
				RStickAngle -= DegreeToRadian(speed);
				//! 通り過ぎたとき
				if (AttackState != AttackState_Sting) {
					if (RStickAngle < RSAngle) {
						RStickAngle = RSAngle;
					}
				}
			}
		}
	}

	mcVec.x = cos(RStickAngle) * mTailRange + mcTailRoot.x;
	mcVec.y = sin(RStickAngle) * mTailRange + mcTailRoot.y;
	//! しっぽの位置から角度を計算
	mTailAngle = (float)PositionRelationAngle(FLOAT2(mcTailRoot.x, mcTailRoot.y), FLOAT2(mcVec.x, mcVec.y));//! しっぽの角度の取得
}


/* ---------------------------------------------------------------------------------------
// 刺しているオブジェクトに対する処理                                                   //
// しっぽに刺さったまま動かすようなことがあっても対応できるようにしっぽ側で処理をします */
void PlugTail::StingObj()
{
	//! 刺しているオブジェクトが何なのかを取得
	if (mcpStingObj) {
		ObjectTag Tag = ((AnimationHitObject *)mcpStingObj)->GetTag();

		switch (Tag){
		case Tag_Dynamo:
			mOnElectForDynamo = true;
			((Dynamo *)mcpStingObj)->SetChrage(msDisCharge.Hit);

			if (msDisCharge.Hit)
			{
				mOnElectForDynamo = false;
			}
			break;
		case Tag_WeakDynamo:
			((WeakDynamo *)mcpStingObj)->SetChrage(msDisCharge.Hit);
			mOverheat = ((WeakDynamo *)mcpStingObj)->Overheat(); //! オーバーヒートしたかをもらう
			if (!mOverheat)
			{
				mOnElectForDynamo = true;
			}

			if (msDisCharge.Hit)
			{
				mOnElectForDynamo = false;
			}
			break;
		}
	}
}
/* -------------------------------------------
// 電気の槍の処理                          */

void PlugTail::ElectSpear()
{
	//!	超帯電になってから次のエイム状態になったら電気の槍フラグを立てる
	if (ElectState == eElectricity::Elect_Super) {
		msSpear.Activ = true;
	}
	//! 超帯電以外はオフにする
	else {
		msSpear.Activ = false;
	}

	//! 位置と当たり判定の計算は常にする
	//! 電気の槍の位置を求める
	//! 描画位置
	Vector2 SpearPos;
	SpearPos.x = mcVec.x + cosf(mTailAngle) * -msSpear.TailDistance;
	SpearPos.y = mcVec.y + sinf(mTailAngle) * -msSpear.TailDistance;
	msSpear.ElectSting->SetVec(SpearPos);
	//! 当たり判定位置
	msSpear.ColPos.x = SpearPos.x + cosf(mTailAngle) * -0.2f;
	msSpear.ColPos.y = SpearPos.y + sinf(mTailAngle) * -0.2f;
	msSpear.ColRootPos.x = SpearPos.x + cosf(mTailAngle) * 0.14f;
	msSpear.ColRootPos.y = SpearPos.y + sinf(mTailAngle) * 0.14f;

	//! 超帯電のときのみ
	if (msSpear.Activ) {
		if (msSpear.Arufa < 1.0f) {
			msSpear.Arufa += 0.025f;
		}
		else if(msSpear.Flash){
			msSpear.Arufa = 0.3f;
		}
		//! エイム状態になっていたら大きくする
		if (AttackState == TailAttackState::AttackState_Aim || AttackState == TailAttackState::AttackState_Sting) {
			msSpear.ElectSting->SetDrawActiv(true);
			if (msSpear.Size.x < msSpear.DefaultSize.x) {
				msSpear.Size.x += 0.05f;
			}
			if (msSpear.Size.y < msSpear.DefaultSize.y) {
				msSpear.Size.y += 0.05f;
			}
			//! しっぽまでの距離
			if (msSpear.TailDistance < 0.2f) {
				msSpear.TailDistance += 0.025f;
			}
		}
		//! アイドルなら小さくする
		else if (mState == TailState::Tail_Idol) {
			//! アイドル状態のサイズ
			if (msSpear.SmallSize.x < msSpear.Size.x) {
				msSpear.Size.x -= 0.05f;
			}
			if (msSpear.SmallSize.y < msSpear.Size.y) {
				msSpear.Size.y -= 0.05f;
			}
			//! しっぽまでの距離
			if (0.1f < msSpear.TailDistance) {
				msSpear.TailDistance -= 0.025f;
			}
		}

		AnimationSprite * AnimSp = msSpear.ElectSting->GetAnimSprite();
		AnimSp->SetColor(0.5f, 0.5f, 1.0f);
		float DrawRad = mTailAngle + 3.14f;
		AnimSp->SetAngle(DrawRad);

		//! 攻撃中のみ当たり判定をオンにする
		if (Attack_C) {
			msSpear.Col->SetActiv(true);
			msSpear.ColRoot->SetActiv(true);
		}
		else {
			msSpear.Col->SetActiv(false);
			msSpear.ColRoot->SetActiv(false);
		}
	}
	//! 帯電してないとき
	else {
		msSpear.Col->SetActiv(false);
		msSpear.ColRoot->SetActiv(false);
		//! 消えていく
		if (0.0f < msSpear.Arufa) {
			msSpear.Arufa -= 0.025f;
		}
		else {
			msSpear.ElectSting->SetDrawActiv(false);
		}
	}


	

	msSpear.ElectSting->SetSize(msSpear.Size);
	msSpear.ElectSting->GetAnimSprite()->SetArufa(msSpear.Arufa);
}

AnimationSprite * PlugTail::GetElestSpear()
{
	return msSpear.ElectSting->GetAnimSprite();
}

void PlugTail::SetFlash(bool _state)
{
	msSpear.Flash = _state;
}

bool PlugTail::GetOverheat()
{
	if (mOverheat) {
		mOverheat = false;
		return true;
	}
	return false;
}

void PlugTail::SetAttackState(TailAttackState _state)
{
	if (AttackState == AttackState_None) {
		AttackState = _state;
	}
}

//! しっぽ自身の当たり判定のゲッター
Box* PlugTail::GetCol()
{
	return mcpCol;
}

//! 攻撃が発生したときの当たり判定のゲッター
Circle* PlugTail::GetAttackCol()
{
	mcpAttackCircle->SetPos(mcVec.x, mcVec.y);
	return  mcpAttackCircle;
}

Circle PlugTail::GetSpearCol()
{
	return *msSpear.Col;
}

Circle PlugTail::GetSpearColRoot()
{
	return *msSpear.ColRoot;
}

//! 刺す強さをのゲッター
float PlugTail::GetStingPower()
{
	return mStingPower;
}

//! 根元からしっぽまでの距離のゲッター
Vector2 PlugTail::GetTailDistance()
{
	//! 性格な値を返すために返す瞬間にも計算する
	return mcVec - mcTailRoot;
}

//! リアクションを指定する
void PlugTail::SetReaction(TailReaction _reaction, eDirection _direction)
{
	if (mReaction == TailReaction_None) {
		mReaction = _reaction;
		ReactionDerection = _direction;
		//! エフェクトや画面振動をする
		switch (mReaction)
		{
		case TailReaction_Sting:
			CAMERA->StartVibration(3);
			SetControllerVibrationTime(20, 20, 24);
			break;
		case TailReaction_StingDeep:
			CAMERA->StartVibration(4);
			SetControllerVibrationTime(20, 20, 20);
			break;
		case TailReaction_StingStop:
			CAMERA->StartVibration(3);
			SetControllerVibrationTime(20, 20, 20);
			break;
		case TailReaction_Stop:

			//SetControllerVibrationTime(3, 3, 2);
			break;
		case TailReaction_Through:
			CAMERA->StartVibration(4);
			SetControllerVibrationTime(20, 20, 25);
			break;
		case TailReaction_Bounce:
			CAMERA->StartVibration(3);
			SetControllerVibrationTime(13, 13, 30);
			break;
		}
		//mStingPower = 0.0f; //! はじかれるように他の変数に代入すると思う
		mReactionFrameCnt = 0;
		AttackState = AttackState_Reaction; //! リアクションに行く

		//! 仮の処理　刺さったらいるときは帯電する
		if (mReaction != TailReaction_Stop && mReaction != TailReaction_Bounce) {
			//mCharge = true;
		}
	}
}

void PlugTail::TailReturn()
{
	mReaction = TailReaction_End;
	msDisCharge.Able = false; //! 放電不可にする
	mReactionFrameCnt = 0;
	mcpStingObj = nullptr;
}

//! リアクションが終わったことを伝える
bool PlugTail::GetTailRactionState()
{
	if (mReaction == TailReaction_None) {
		return true;
	}
	return false;
}

bool PlugTail::GetAttackState()
{
	//! 攻撃中なら
	if (Attack_C && AttackState != AttackState_None) {
		return true;
	}
	return false;
}

void PlugTail::SetStingObj(GameObject * _stingobj)
{
	//! 発電機に刺さった場合はチャージしないようにする
	if (((AnimationHitObject *)_stingobj)->GetTag() == Tag_Dynamo) {
		mCharge = false;
	}
	mcpStingObj = _stingobj;
}

//! しっぽの中間部分の処理
void PlugTail::Tail()
{
	AnimationSprite * SectionAnimSprite = msSection.Section->GetAnimSprite();
	msSection.OldNum = msSection.Num; //! 前フレームの節の数
	//! 前フレームのしっぽの軌跡として保存する
	for (int i = 0; i < 100; i++) {
		msSection.PrevInf[i] = msSection.Inf[i];
	}
	if (!msBounce.Flg) {
		msSection.Length = fabs(mcVec.PosToPos(mcTailRoot) - 0.02f); //! しっぽから根元の直線距離
		//! 直線距離割るサイズで何個描画したらいいのかを出す		

		msSection.Num = msSection.Length / msSection.Pich;
	}

	//! 個数分座標をセットする
	float DisRemain = 0;

	bool static first = false;
	Vector2	Resistance;				//! 抵抗力
	float AttCoefficient = 1.66f;    //! 減衰係数
	float Coefficient = 0.34f;       //! ばね係数
	float Mass = 1.0f;              //! 質量

	if (!msBounce.Flg) {
		//! 結合点の位置を出す(直線)
		for (int i = 0; i < msSection.Num; i++) {
			//! まず先に根元の位置を計算する
			if (i == 0) {
				msSection.Inf[i].Pos = mcTailRoot;
			}
			else {
				msSection.Inf[i].Pos.x = msSection.Inf[i - 1].Pos.x + cos(RStickAngle) * msSection.Pich;
				msSection.Inf[i].Pos.y = msSection.Inf[i - 1].Pos.y + sin(RStickAngle) * msSection.Pich;
			}
			msSection.Inf[i].Angle = RStickAngle;
			first = true;
		}
	}

	//! 尻尾の先端の結合点を求める
	Vector2 TailAttach;
	TailAttach.x = mcVec.x + cosf(mTailAngle) * 0.02f;
	TailAttach.y = mcVec.y + sinf(mTailAngle) * 0.02f;

	bool Fin = false;
	if (msBounce.Flg) {

		for (int num = 0; num < 15; num++) {
			for (int i = msSection.Num - 1; i > -1; i--) {
				//! ①上側の節から引っ張られる力
				//! 先端
				if (i == msSection.Num - 1) {
					msSection.Inf[i].Tension_Up = Tension(TailAttach, msSection.Inf[i].Pos, Coefficient, msSection.Pich);
				}
				else {
					//! 尻尾から引っ張られる
					msSection.Inf[i].Tension_Up = Tension(msSection.Inf[i + 1].Pos, msSection.Inf[i].Pos, Coefficient, msSection.Pich);
				}

				//! ②下側の節から引っ張られる力
				//! 根本は引っ張られない		
				msSection.Inf[i].Tension_Down = Tension(msSection.Inf[i - 1].Pos, msSection.Inf[i].Pos, Coefficient, msSection.Pich);

				//! ③重力を求める
				msSection.Inf[i].Gravity = Mass * -0.001f;
				msSection.Inf[i].Gravity = 0;

				//! ④抵抗力を求める
				Resistance.x = -msSection.Inf[i].Velocity.x * AttCoefficient;
				Resistance.y = -msSection.Inf[i].Velocity.y * AttCoefficient;

				//! ⑥かかる力を合成
				msSection.Inf[i].Resultant.x = msSection.Inf[i].Tension_Up.x + msSection.Inf[i].Tension_Down.x + Resistance.x;
				msSection.Inf[i].Resultant.y = msSection.Inf[i].Gravity + msSection.Inf[i].Tension_Up.y + msSection.Inf[i].Tension_Down.y + Resistance.y;

				//! ⑦合力と質量から加速度を求める
				msSection.Inf[i].Acceleration.x = msSection.Inf[i].Resultant.x / Mass;
				msSection.Inf[i].Acceleration.y = msSection.Inf[i].Resultant.y / Mass;

				//! ⑧速度に加速度を加える
				msSection.Inf[i].Velocity.x += msSection.Inf[i].Acceleration.x;
				msSection.Inf[i].Velocity.y += msSection.Inf[i].Acceleration.y;

				//! 根元の位置は固定なので全て0にする
				if (i == 0) {
					msSection.Inf[i].Tension_Down = Vector2(0, 0);
					msSection.Inf[i].Tension_Up = Vector2(0, 0);
					msSection.Inf[i].Resultant = Vector2(0, 0);
					msSection.Inf[i].Velocity = Vector2(0, 0);
					msSection.Inf[i].Acceleration = Vector2(0, 0);
					msSection.Inf[i].Gravity = 0;
					msSection.Inf[i].Pos = mcTailRoot;
				}

				//! ⑨速度から座標を移動
				msSection.Inf[i].Pos += msSection.Inf[i].Velocity;

				//! ⑩一つ次の節に対しての角度を求める
				if (i == msSection.Num - 1) {
					msSection.Inf[i].Angle = (float)PositionRelationAngle(FLOAT2(TailAttach.x, TailAttach.y), FLOAT2(msSection.Inf[i].Pos.x, msSection.Inf[i].Pos.y));
				}
				else {
					msSection.Inf[i].Angle = (float)PositionRelationAngle(FLOAT2(msSection.Inf[i + 1].Pos.x, msSection.Inf[i + 1].Pos.y), FLOAT2(msSection.Inf[i].Pos.x, msSection.Inf[i].Pos.y));
				}
			}
		}
	}
	SectionAnimSprite->SetAngle(RStickAngle, 1.0f, 0.5f);

}
