#include "Player.h"
#include "TextureManager.h"
#include "DirectInput8.h"
#include "Time.h"
#include "Angle.h"
#include "Input.h"
#include "Controller.h"
#include "Camerah.h"
#include "WinMain.h"
#include "EffectManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "PlayerSmoke.h"
#include "HPICon.h"
#include "PlayerBattry.h"

//! コンストラクタ
Player::Player()
{
	//! 画像やアニメーション、ステータスの設定
	mTag = Tag_Player;
	mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! しっぽの付け根の位置
	msSize = FLOAT2(0.32f, 0.32f);
	ColSize = Vector2(0.18f, 0.26f);
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);

	mDirection = Right; //! 向きの設定
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Idol));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetSize(msSize.x, msSize.y);
	mcpPlugTail = new PlugTail(mcTailRoot, mcVec, mState, mDirection, mElectState);

	mNumBoruto = mToalBoruto = 0;
	mState = Player_Idol_Walk; //! プレイヤーの状態の設定
	mElectState = Elect_None;  //! プレイヤーの帯電の状態
	//! フラグの初期化
	AttackFlg = false;
	OnObj = false;
	
	Smoke = new PlayerSmoke;
	msStatus.HP = 5;
	Shive = 0.01f;

	mcpHPIcon = new HPICon(msStatus.HP,-0.17f,0.8f);
	Battery = new PlayerBattery();

	UIFrame = new AnimationHitObject;
	UIFrame->SetCameraActiv(false);
	AnimationSprite * UIFrameSp = UIFrame->GetAnimSprite();
	UIFrameSp->SetTexture(TEXTURE(Tex_UIFrame));
	//UIFrameSp->SetAnimtionTable(13,2);
	UIFrameSp->SetAnimtionTable(1, 1);
	UIFrame->SetSize(1.6f,0.6f);
	UIFrame->SetVec(Vector2(-1.1f,0.7f));
}


Player::Player(float _x, float _y)
{
	//! 画像やアニメーション、ステータスの設定
	mcVec.y = _y;	
	mcVec.x = _x;
	mTag = Tag_Player;
	mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! しっぽの付け根の位置
	msSize = FLOAT2(0.32f, 0.32f);
	ColSize = Vector2(0.18f, 0.26f);
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
	
	mDirection = Right; //! 向きの設定
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Idol));
	mcpAnimsprite->SetAnimtionTable(6,2);
	mcpAnimsprite->SetSize(msSize.x, msSize.y);
	mcpPlugTail = new PlugTail(mcTailRoot, mcVec, mState,mDirection, mElectState);

	mNumBoruto = mToalBoruto = 0;
	mState = Player_Idol_Walk; //! プレイヤーの状態の設定
	mElectState = Elect_None;  //! プレイヤーの帯電の状態
	//! フラグの初期化
	AttackFlg = false;
	OnObj = false;
	Smoke = new PlayerSmoke;
	msStatus.HP = 5;
	Shive = 0.01f;
	mcpHPIcon = new HPICon(msStatus.HP, -1.65f, 0.8f);
	Battery = new PlayerBattery();
	UIFrame = new AnimationHitObject;
	UIFrame->SetCameraActiv(false);
	AnimationSprite * UIFrameSp = UIFrame->GetAnimSprite();
	UIFrameSp->SetTexture(TEXTURE(Tex_UIFrame));
	UIFrameSp->SetAnimtionTable(24, 1);
	UIFrame->SetSize(1.55f, 0.54f);
	UIFrame->SetVec(Vector2(-1.1f, 0.75f));
}

//! デストラクタ
Player::~Player()
{
	delete mcpPlugTail;
	delete mcpHPIcon;
	delete Smoke;
	delete Battery;
	delete UIFrame;
}

//! 更新処理
void Player::Update()
{		
	State_Controller();
	Electricity(); //! 帯電の処理
	//! 向きの変更としっぽの付け根の位置を出す
	if (mDirection == Left) { //! 左
		mcTailRoot = Vector2(mcVec.x + 0.086f, mcVec.y - 0.046f); //! しっぽの付け根の位置	
	}
	//! 右
	else {
		mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! しっぽの付け根の位置	
	}
	
	mcpPlugTail->Update();    //! しっぽの更新処理
	//! 刺した発電機がオーバーヒートしていたらダメージを受ける
	if (mcpPlugTail->GetOverheat()) {
		msDamage.Overheat = true;
		//! 尻尾に抜けるようにする
		mcpPlugTail->TailReturn();
	}

	ForceProces();                       //! このフレームでかかった力を加算する	
	Battery->Update(msElect.ChargeCnt);  //! バッテリーUIの更新
}

//! 当たり判定処理のあとに行われる処理
void Player::LastUpdate()
{
	Damage();   //! ダメージの処理をする
	Recovary(); //! 回復の処理
	mcpHPIcon->Update(msStatus.HP);

	if (mcVec.y < -0.8f) {
		mcVec.y = -0.67f;
	}
}

//! 描画処理
void Player::Draw()
{
	mcpAnimsprite->SetYSplit(mDirection);
	if (TailDraw) {
		mcpPlugTail->Draw();
	}
	Smoke->Draw();
	GameObject::Draw();
	//! UIの描画
	if (UIActiv) {
		UIFrame->Draw();
		mcpHPIcon->Draw();
		Battery->Draw();
	}
}

//! ダメージのセッター
void Player::SetDamege(eDirection _nockback)
{
	if (!msDamage.Flg) {
		msDamage.Flg = true;
		msDamage.NockBackWay = _nockback;
		SoundMgr->PlaySE(SE_Damage,0.1f);
	}
}

//! HPのゲッターUIに使うと思う
int Player::GetHP()
{
	return msStatus.HP;
}

bool Player::GetCharge()
{
	if (mElectState == eElectricity::Elect_Super) {
		return true;
	}
	return false;
}

void Player::AddBoruto()
{
	mNumBoruto++;
	mToalBoruto++;
	//! 10個拾ったら回復
	if (mNumBoruto >= 10) {
		mNumBoruto = 0;
		mRecovery = true;
	}	
}

/* ----------------- 
// 帯電をする関数 */
void Player::AddElect()
{
	msElect.ChargeCnt++;
}

void Player::MoveStop(bool state)
{
	Stop = state;
}

void Player::SetUIActiv(bool _activ)
{
	UIActiv = _activ;
}

/* ------------- 
// 帯電の処理 */
void Player::Electricity()
{	
	if (7 <= msElect.ChargeCnt && GetControllerButtonTrigger(Button_LB)) 
	{
		mElectState = Elect_Super;
	}	
	
	switch (mElectState)
	{	
	case Elect_Super:
		//! 最初の一度だけ再生
		if (msElect.SuperCnt == 0) {
			EffMgr->PlayFollowEffect(ElectSuper01, mcVec.x, mcVec.y,0.5f,0.5f, true);
			mcpPlugTail->SetFlash(false);
		}	
		msElect.SuperCnt++;
		msElect.UpRate = 1.5f;
		if (msElect.SuperCnt % 180 == 0) {SoundMgr->PlaySE(SE_Taiden, 0.04f);}
		if (msElect.SuperCnt % 150 == 0) {SoundMgr->PlaySE(SE_Taiden, 0.04f);}	


		if (msElect.SuperCnt >= (20 * 60)) {			
			mcpPlugTail->SetFlash(true);
		}

		if (msElect.SuperCnt >= (30 * 60)) {
			mElectState = Elect_None;
			EffMgr->LoopStop(ElectSuper01);
			msElect = SElectricity();
		}
		break;
	case Elect_None:
		break;
	}
}

/* ---------------------------------------
// コントローラーの時の状態に応じた処理 */
void Player::State_Controller()
{
	//! 状態の更新
	if (msStatus.HP <= 0) {
		mState = Player_Down;
	}
	else if (!GetControllerButtonPress(Button_LT)) {
		if (mcpPlugTail->GetTailRactionState()) {	
			if (mcpPlugTail->SetState(TailState::Tail_Idol)) {
				mState = Player_Idol_Walk;
				KamaeSE = true;
			}
		}
	}
	else {
		MoveReady();
		//! 臨戦態勢	
		mState = Player_Attack;
		mcpPlugTail->SetState(TailState::Tail_Attack);
		//! 画像の切り替え
		mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Aim));
		if (KamaeSE) {
			SoundMgr->PlaySE(SE_Kamae,0.25f);
			KamaeSE = false;
		}
		mcpPlugTail->SetAttackState(TailAttackState::AttackState_Aim);
		msStatus.MoveAble = true; //! ジャンプ中にエイムしたときに特定のアニメーション中にエイムにいくと歩けなくなるのでここで、歩けるようにする
		msJump.Doing = false;
		msJump.End = false;
		msJump.Up = false;
		msJump.Jump = false;
		mcpAnimsprite->SetStopAnimation(false);		
	}

	//! 状態に応じた処理
	switch (mState)
	{
	case Player_Idol_Walk:
		Move_Controller();	
		break;
	case Player_Attack:	
		break;
	case Player_Down:
		Destroy();
		break;
	}
}

//! プレイヤーだけジャンプなどの、他のキャラクターとは違う部分が多くなると予想されるので、この関数内で重力の処理や、かかった力の加算などを行います
void Player::ForceProces()
{
	if (!ChangeDestroy) {
		bool Vibe = CAMERA->GetVibration();
		OnObj = mcpBoxCol->GetOnObj();

		//!画面振動をしておらず、地面に触れていないとき、またはジャンプ中に重力をかける
		if (OnObj == false && mTouchGraund == false && Vibe == false || msJump.Doing) {
			double ElapsedTime = CurrentTime - GravityTime;
			float Gravtiy = -ga * pow(ElapsedTime, 2) / 2.0f; //! 重力による下方向の力の計算
			//! 重力の影響の最大値を超えないようにする
			if (Gravtiy >= 0.02f) {
				Gravtiy = 0.02f;
			}
			mcMoveVector.y += Gravtiy; //! 重力の力を加算
		}
		else {
			GravityTime = CurrentTime; //! 秒単位の今の時間を取得する
		}
		CurrentTime += (1.0f / 60.0f);  //! 経過時間を増やす
		mcpBoxCol->SetPrevVec(mcVec);       //! 前フレームの座標として保存する
		mcVec += mcMoveVector;              //! このキャラクターにかかっている力を足す
		mcpShape->SetMoveVec(mcMoveVector); //! 当たり判定に使うための情報をセット
		CameraMoveMent = mcMoveVector;
		mcMoveVector.SetVector(0, 0);       //! このキャラクターにかかっている力を０にする
		mcpBoxCol->SetOnObj(false);
		//! 当たり情報にサイズセット
		mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
		AnimationHitObject::Update();
	}
}


/* -----------------------------------------
// マウス操作時の移動とジャンプの処理処理 */
void Player::Move_Mouse()
{
	//! 左右移動 キー
	if (!msJump.Up) {
		if (!DI8->mKeyBoard->GetKeyPress(DIK_LSHIFT) && !DI8->mKeyBoard->GetKeyPress(DIK_LCONTROL)) {
			if (DI8->mKeyBoard->GetKeyPress(DIK_LEFT) || DI8->mKeyBoard->GetKeyPress(DIK_A)) {
				mcMoveVector.x += -msStatus.MoveSpeed;
				mDirection = Left;
			}
			if (DI8->mKeyBoard->GetKeyPress(DIK_RIGHT) || DI8->mKeyBoard->GetKeyPress(DIK_D)) {
				mcMoveVector.x += msStatus.MoveSpeed;
				mDirection = Right;
			}
		}
	}

	Jump(); //! ジャンプ関数
	//! デバッグ用の処理
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_RETURN)) {
		msJump.Doing = false;
		msJump.End = false;
		msJump.Up = false;

		mTouchGraund = true;
		mcVec.SetVector(0, -0.4f);
	}
}


/* -------------------------------------------------
// コントローラー操作時の移動とジャンプの処理処理 */
void Player::Move_Controller()
{
	//! 左右移動　コントローラー
	Vector2 LeftStick = GetControllerLeftStick() * 1.0f;
	//! ジャンプの溜め中と
	if (msStatus.MoveAble) {
		mcMoveVector.x += (LeftStick.x) * msElect.UpRate;
	}

	//! 画像と向きの変更
	//! 移動してない時
	if (LeftStick.x == 0) {
		if (!msJump.Jump) {
			mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Idol));
			mcpAnimsprite->SetAnimSpeed(8);
		}
	}
	else {	
		//! 移動している時かつ、Jumpしていないとき
		if (!msJump.Jump) {
			mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Run));
			mcpAnimsprite->SetAnimSpeed(6);
			int AnimX = mcpAnimsprite->GetCurrentXSplit();
			if (AnimX == 5) {
				mcpAnimsprite->SetXSplit(0);
			}
		}
		else {
			mcpAnimsprite->SetAnimSpeed(8);
		}

		if (LeftStick.x < 0) {
			mDirection = Left;
		}
		else {
			mDirection = Right;
		}		
	}
	Jump(); //! ジャンプ関数
}

void Player::MoveReady()
{
	if (msStatus.MoveAble) 
	{
		Vector2 LeftStick = GetControllerLeftStick() * 0.1f;
		mcMoveVector.x += (LeftStick.x) * msElect.UpRate;
	}
}

/* ------------------------------------------------------------
// ジャンプ関数                                              //
// 操作のボタンが違うだけなのでどちらの操作でも同じ関数で行う*/
void Player::Jump()
{
	//! ジャンプしていないとき
	if (!msJump.Jump) {
		//mcpAnimsprite->SetAnimSpeed(8);
		msJump.AnimCnt = 0;
		msJump.FrameCnt = 0;
		msJump.End = false;
		msJump.Jump = false;
	}

	//! ジャンプが終了していたら
	if (msJump.End) {
		msJump.AnimCnt++;
		//! 最後の着地の絵を描画するまで待つ
		if (msJump.AnimCnt >= 4) {
			mcpAnimsprite->ResetAnimCnt();
			mcpAnimsprite->SetAnimSpeed(8);	
			msJump.AnimCnt = 0;
			msJump.FrameCnt = 0;
			msJump.End = false;
			msJump.Jump = false;
		}
	}
	//! ボタンが押されたらジャンプのために入る
	if (msJump.End == false && msJump.Doing == false && msJump.Up == false) {
		if (DI8->mKeyBoard->GetKeyTrigger(DIK_SPACE) || GetControllerButtonTrigger(Button_A)) {
			msJump.Up = true;
			msStatus.MoveAble = false; //! 移動不可
			msJump.Jump = true;
			//! ジャンプ用の画像に切り替える
			mcpAnimsprite->ResetAnimCnt();
			float UpLate = msElect.UpRate;
			if (UpLate > 1.2f) {
				UpLate = 1.2f;
			}
			msStatus.TmpJumpPower = msStatus.InitJumpPower * UpLate; //! ジャンプの力を設定する
			mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Jump));
		}
	}
	//! ジャンプの溜めモーション
	else if (msJump.Up) {
		//! アニメーション用のカウントを進める
		msJump.AnimCnt++;
		//! 溜めている画像分フレームが経過したらJump開始
		if (msJump.AnimCnt >= 6) {		
			SoundMgr->PlaySE(SE_Jump, 0.05f); //! ジャンプSE
			msJump.Doing = true; //! ジャンプ中になる
			msJump.Up = false; //! 溜めをやめる
			msStatus.MoveAble = true;
			//! 地面から離れる
			mTouchGraund = false;
			OnObj = false;
			mcpBoxCol->SetOnObj(false);
		}
	}
	
	//! 最高到達点を決めておいて最高到達点になるまで、初めはジャンプの力が大きくだんだん小さくなるようにする
	//! ジャンプ中の処理		
	if (msJump.Doing) {	
		mcMoveVector.y += msStatus.TmpJumpPower * sin(DegreeToRadian(90));
		if (mcMoveVector.x > 0.0f) {
			mcMoveVector.x += 0.002f;
		}
		else if (mcMoveVector.x < 0.0f) {
			mcMoveVector.x += -0.002f;
		}
		if (msJump.FrameCnt >= 3 && msJump.FrameCnt <= 6) {
			msStatus.TmpJumpPower -= 0.004f; //だんだんジャンプ力を減らして行く
		}
		//! 頂点についたら　ジャンプのアニメーションカウントが40～43の間
		if (msJump.AnimCnt >= 40 && msJump.AnimCnt <= 41) {
			mcpAnimsprite->SetStopAnimation(true); //! アニメーションを止める
		}
		//! 落下し始めたらアニメーションを進める
		else if (msJump.AnimCnt >= 42) {
			mcpAnimsprite->SetStopAnimation(false); //! アニメーションを進める
		}
		msJump.FrameCnt++; //ジャンプ用のカウント
		msJump.AnimCnt++; //! ジャンプ用のアニメーションカウント
	}

	//! ジャンプして地面に着地したらジャンプ終了にいく
	if ((mTouchGraund && msJump.Doing) || (OnObj && msJump.Doing)) {
		msJump.Doing = false;
		msJump.End = true; //! ジャンプ終了
		mcMoveVector.y = 0;
		msJump.AnimCnt = 0;
		mcpAnimsprite->SetStopAnimation(false);
	}
}

/* ----------------------------- 
// ダメージを受けたときの処理*/
void Player::Damage()
{
	if (msDamage.Flg) {
		//! エフェクトが開始する前に一度だけHPを減らす
		if (!msDamage.Effect) {
			msStatus.HP -= 1; //! HPを減らす
			//! HPがゼロならダメージ演出はしない
			if (msStatus.HP <= 0) {
				msStatus.MoveAble = false; //! ノックバックが終わるまで移動不可
				msDamage.Flg = false;      
				// EffMgr->PlayFollowEffect(PlayerSmoke,mcVec.x,mcVec.x,true);
			}
			else {
				msDamage.Effect = true;
				msDamage.NockBack = true;
				msStatus.MoveAble = false; //! ノックバックが終わるまで移動不可
			}	
		}
		else {
			//! ノックバック
			if (msDamage.NockBackWay == Left) { //! 左
				if (msDamage.Cnt < 10) {
					mcMoveVector.y += 0.014f;
					mcMoveVector.x += -0.01f;
				}
				else if(msDamage.Cnt < 16){	
					mcMoveVector.x += -0.012f; 	
				}
				else if (msDamage.Cnt >= 26) {
					msDamage.NockBack = false;
					msStatus.MoveAble = true;
				}
			}
			else if(msDamage.NockBackWay == Right){ //! 右				
				if (msDamage.Cnt < 10) {
					mcMoveVector.y += 0.014f;
					mcMoveVector.x += 0.01f;
				}
				else if (msDamage.Cnt < 16) {
					mcMoveVector.x += 0.012f;
				}
				else if(msDamage.Cnt >= 26){
					msDamage.NockBack = false;
					msStatus.MoveAble = true;
				}
			}
			//! 点滅させる
			if ((msDamage.Cnt % 20) <= 10) {
				SetDrawActiv(false);
				TailDraw = false;
			}
			else {
				SetDrawActiv(true);
				TailDraw = true;
			}
			msDamage.Cnt++;
		}
		//! 60フレームを超えたら
		if (msDamage.Cnt > 120) {
			SetDrawActiv(true);
			TailDraw = true;
			msDamage.Flg = false;
			msDamage.Effect = false;
			msDamage.Cnt = 0;
			msDamage.NockBack = false;
		}
	}

	if (msDamage.Overheat) {
		if (!msDamage.Effect) {
			msStatus.HP -= 1; //! HPを減らす
			msDamage.Effect = true;
		}
		else {
			//! 点滅させる
			if ((msDamage.Cnt % 20) <= 10) {
				SetDrawActiv(false);
				TailDraw = false;
			}
			else {
				SetDrawActiv(true);
				TailDraw = true;
			}

			if (msDamage.Cnt < 10) {
				mcMoveVector.y += 0.014f;
				mcMoveVector.x += -0.01f;
			}
			else if (msDamage.Cnt < 16) {
				mcMoveVector.x += -0.012f;
			}
			else if (msDamage.Cnt >= 26) {
				msDamage.NockBack = false;
				//msStatus.MoveAble = true;
			}

			msDamage.Cnt++;
		}
		//! 30フレーム超えたら
		if (msDamage.Cnt > 50) {
			SetDrawActiv(true);
			TailDraw = true;
			msDamage.Overheat = false;
			msDamage.Effect = false;
			msDamage.Cnt = 0;
		}
	}
}
/* --------------------- 
// 回復するときの処理 */
void Player::Recovary()
{
	/*if (GetControllerButtonTrigger(Button_B)) {
		mRecovery = true;
	}*/

	if (mRecovery) {
		SoundMgr->PlaySE(SE_Heal,0.08f);
		//! HPが最大ではないときのみ回復する
		if (msStatus.HP <= 4) {
			msStatus.HP += 1;
		}
		mRecovery = false;
		//! ここらへんで回復エフェクトを出す
		EffMgr->PlayFollowEffect(eEffect::Recovery, mcVec.x, mcVec.y,0.2f,0.2f);
		EffMgr->PlayFollowEffect(eEffect::Hp_Recvery, mcVec.x, mcVec.y, 0.2f, 0.2f);
	}
}


/* ------------------------ 
// HPが0になった時の処理 */
void Player::Destroy()
{
	mcpAnimsprite->SetStopAnimation(false); //! アニメーションのがとまっている場合あるので
	//! 画像のセット
	if (!ChangeDestroy) {	
		mcpAnimsprite->ResetAnimCnt();
		mcpAnimsprite->SetAnimtionTable(6, 2);
		SetControllerVibrationTime(20,20,30);
		ChangeDestroy = true;
		mcpBoxCol->SetActiv(false);
		mElectState = eElectricity::Elect_None;	
		EffMgr->LoopStop(ElectSuper02);
		SoundMgr->PlaySE(SE_Damage, 0.3f);
		Death = true;
	}

	msStatus.MoveAble = false;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_Down));

	//! すこし点滅して煙をエフェクトを出しながら
	if (DestroyCnt < 120) {
		if ((DestroyCnt % 20) <= 10) {
			SetDrawActiv(false);
			TailDraw = false;
		}
		else {
			SetDrawActiv(true);
			TailDraw = true;
		}
	}
	else {
		SetDrawActiv(true);
		TailDraw = true;

		//! スモークを出す
		if (mDirection == Left) {
			Smoke->SmokeStart(Vector2(mcVec.x - 0.01f, mcVec.y + 0.1f));
		}
		else {
			Smoke->SmokeStart(Vector2(mcVec.x + 0.01f, mcVec.y + 0.1f));
		}
	}
	int XFrame = mcpAnimsprite->GetCurrentXSplit();

	if (XFrame == 5) { //! アニメーションを止める
		mcpAnimsprite->SetStopAnimation(true);
		//! 小刻みに震える
		mcMoveVector.x += Shive;
		if ((DestroyCnt / 4) == 0) {
			Shive *= -1;
		}
	}

	if (DestroyCnt >= (60 * 5)) {
		Destroyed = true;
	}

	DestroyCnt++;

	if (Destroyed) {
		SetDrawActiv(false);
		SetHitActiv(false);
		mcpPlugTail->Destroy(); //! しっぽも破棄する
		mAlive = false;         //! 生存フラグ折る
	}
}

//! 以下セッター、ゲッター ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
//! プレイヤー用の座標のセッター
//! 更新処理の後にセットしてしまうと、次の更新処理まで付け根の位置がづれてしまうので防止のために専用に作る
void Player::SetVec(Vector2 _vec)
{
	mcVec = _vec;
	if (mDirection == Left) {
		mcTailRoot = Vector2(mcVec.x + 0.086f, mcVec.y - 0.046f); //! しっぽの付け根の位置	
	}
	else {
		mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! しっぽの付け根の位置
	}
}

//! しっぽの当たり判定のゲッター
Box * Player::GetTailCol()
{
	return mcpPlugTail->GetCol();
}

//! 攻撃の当たり判定のゲッター
Circle* Player::GetAttackCol()
{
	return mcpPlugTail->GetAttackCol();
}

Circle Player::GetSpearCol(int _index)
{	
	if (_index == 0) {
		return mcpPlugTail->GetSpearCol();
	}
	return mcpPlugTail->GetSpearColRoot();	
}

//! 攻撃してるかのゲッター
bool Player::GetAttackFlg()
{
	return AttackFlg;
}

//! 刺す強さのゲッター
float Player::GetStingPower()
{
	return mcpPlugTail->GetStingPower();
}

//! しっぽの根元のゲッター
Vector2 Player::GetTailRoot()
{
	return mcTailRoot;
}

Vector2 Player::GetCameraMovement()
{
	return CameraMoveMent;
}

bool Player::GetDeath()
{
	return Death;
}

//! しっぽの刺した後のリアクションのセッター
void Player::SetReaction(TailReaction _reaction ,eDirection _direction)
{	
	mcpPlugTail->SetReaction(_reaction, _direction);
}

//! しっぽのゲッター
PlugTail * Player::GetTail()
{
	return mcpPlugTail;
}

