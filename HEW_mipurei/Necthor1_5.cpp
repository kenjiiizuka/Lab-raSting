#include "Necthor1_5.h"
#include "Debri.h"
#include "NecthorHammer_InClass.h"
#include "Camerah.h"
#include "ShocoWave.h"
#include "Smoke.h"
#include "Controller.h"
#include "LeapDebri.h"
#include "SoundManager.h"
#include "Collision.h"
#include "TextureManager.h"
#include "Necthor_Allow.h"
//! コンストラクタ
Necthor1_5::Necthor1_5()
{
	for (int i = 0; i < 3; i++) {
		mcpLeapdebri[i] = new LeapDebri;
	}
	HightHP = false;
	HP = 15;
	RushMax = 5;
	ShockWaveCoolTimeMax = 100;
	LeapDebriAtkCnt = 0;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol_Red));
	RushWaveAttack = false;
}

Necthor1_5::Necthor1_5(float _x, float _y)
	: ReNecthor::ReNecthor(_x, _y)
{
	for (int i = 0; i < 3; i++) {
		mcpLeapdebri[i] = new LeapDebri;
	}
	HightHP = false;
	HP = 15;
	RushMax = 5;
	ShockWaveCoolTimeMax = 100;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol_Red));
	RushWaveAttack = true;
	LeapDebriAtkCnt = 0;
}

//! デストラクタ
Necthor1_5::~Necthor1_5()
{
	for (int i = 0; i < 3; i++) {
		delete mcpLeapdebri[i];
	}
}

//! 更新処理
void Necthor1_5::Update()
{
	AnimX = mcpAnimsprite->GetCurrentXSplit(); //! 現在のＸ方向アニメーションの番号をもらう
	ColFix();
	if (BattleActiv) {
		RandamCnt+= (rand() % 4) + 1;
		if (RandamCnt > 100) {
			RandamCnt = 0;
		}
		//! Hpが無くなったら倒れてる状態にいく
		if (HP <= 0 && State != eNecthorState::State_Destroy) {
			if (State != eNecthorState::State_Down) {
				//! がれきを出す
				Vector2 DebriPos;
				DebriPos.x = mcVec.x - 0.7f;
				DebriPos.y = mcVec.y - 0.75f;
				Debri[1].get()->UpStart(DebriPos, true);     //! がれきを出す(描画あり)
				Debri[0].get()->FadeoutStart();
			}
			State = eNecthorState::State_Down;
		}
		//! ステートの処理
		switch (State)
		{
		case ReNecthor::State_Idol:
			Idol();
			break;
		case ReNecthor::State_PressHammer:
			Atk_PressHammer();
			break;
		case ReNecthor::State_ShockWave:
			Atk_ShockWave();
			break;
		case ReNecthor::State_RushWave:
			Atk_RushWave();
			break;
		case ReNecthor::State_LeapDebri:
			Atk_LeapDebri();
			break;
		case ReNecthor::State_Down:
			FallDwoned();
			break;
		case ReNecthor::State_Destroy:
			Destroy();
			break;
		}
	}

	for (int i = 0; i < Debri.size(); i++) {
		Debri[i].get()->Update();
	}
	for (int j = 0; j < Wave.size(); j++) {
		Wave[j].get()->Update();
	}
	for (int k = 0; k < 3; k ++) {
		mcpLeapdebri[k]->Update();
	}
	SmokeUpdate();
	TexChange();
	Allow->Update();
}

//! 描画処理
void Necthor1_5::Draw()
{
	ReNecthor::Draw();
	for (int k = 0; k < 3; k++) {
		mcpLeapdebri[k]->Draw();
	}
}

//! 当たり判定処理
void Necthor1_5::CollisionUpdate()
{
	ReNecthor::CollisionUpdate();

	Box * PlayerBox = mcPlayer->GetBoxCol();
	bool Elect = mcPlayer->GetCharge();
	//! とびだしてくるがれきとの当たり判定
	for (int i = 0; i < 3; i++) {
		//! がれきの当たり判定の取得
		Box * LeapDebriBox = mcpLeapdebri[i]->GetCol();
		Box * LeapDebriAtkBox = mcpLeapdebri[i]->GetAtkCol();
		//! 衝突判定
		BBC(*PlayerBox, *LeapDebriBox);

		//! 攻撃との判定
		if (BBH(*PlayerBox, *LeapDebriAtkBox)) {
			mcPlayer->SetDamege(Left);
		}

		//! 尻尾との当たり判定
		if (Elect) {
			if (BCH(*LeapDebriBox,mcPlayer->GetSpearCol(0)) || BCH(*LeapDebriBox, mcPlayer->GetSpearCol(1))) {
				mcpLeapdebri[i]->Fadeout();
				mcPlayer->SetReaction(TailReaction::TailReaction_Through, Direction_None);
			}
			else if (BCH(*LeapDebriAtkBox, mcPlayer->GetSpearCol(0)) || BCH(*LeapDebriAtkBox, mcPlayer->GetSpearCol(1))) {
				mcpLeapdebri[i]->Fadeout();
				mcPlayer->SetReaction(TailReaction::TailReaction_Through, Direction_None);
			}
		}
		else {
			if (Collision::Box_Circle_Hit(*LeapDebriBox,*mcPlayer->GetAttackCol())) {
				mcpLeapdebri[i]->Fadeout();
				mcPlayer->SetReaction(TailReaction::TailReaction_Through, Direction_None);
			}
		}
	}
}

//1 アイドル状態に時の処理
void Necthor1_5::Idol()
{
	mcpAnimsprite->SetAnimSpeed(8);
	TexState = Tex_Idol;
	//! でぶりを消す
	Debri[0].get()->FadeoutStart();
	Hammer->AtkCol->SetActiv(true);
	mcpAnimsprite->SetStopAnimation(false);
	//! 本体の当たり判定の位置を求める
	ColFix();
	MyCol.AtkCol->SetActiv(true); //! 攻撃の当たり判定をオン

	//! どの攻撃をするか判断
	mcpAnimsprite->SetStopAnimation(false);
	AttackStateMachine();
}

//! どの攻撃をするかを選ぶ処理
void Necthor1_5::AttackStateMachine()
{
	float Px = mcPlayer->GetVec().x;                               //! プレイヤーのX座標
	float ToPx = fabs(mcVec.x - Px);                               //! プレイヤーまでのX方向の距離       
	int Cnt = AtkCnt.Press + AtkCnt.Wave;

	//! 連続衝撃波攻撃 攻撃回数が２になったとき()
	if (HP <= 5 && RushWaveAttack) {							   //! 衝撃波攻撃を二回以上していたら衝撃波連打攻撃をする
		State = eNecthorState::State_RushWave;
		IdolCnt = 100;                                               //! カウントのリセット	 
		RushWaveAttack = false;
		RushMax = 5;
		mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット	
	}
	else if (Cnt >= 4) {
		State = eNecthorState::State_RushWave;
		IdolCnt = 60;                                               //! カウントのリセット	 
		RushWaveAttack = false;
		RushMax = 3;
		mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット	
	}
	else if (IdolCnt >= (60 * 2)) {								   //! 300フレーム経過したら攻撃に行く
		//! プレイヤーがハンマー攻撃の射程ないならふり卸攻撃
		if (ToPx <= 0.8f) {
			State = eNecthorState::State_PressHammer;
			mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
		}
		//! ちょうどいいかんじの位置ならランダム分岐
		else if (ToPx > 0.8f) {
			if ((RandamCnt % 3) == 0) { //! カウントが2の倍数ならハンマー攻撃
				int r = rand() % 100;
				if (r % 3 == 0) {
					State = eNecthorState::State_PressHammer;
					mcpAnimsprite->ResetAnimCnt();   //! アニメーションカウントのリセット 
					AtkCnt.Press++;
				}
				else if(r % 4 == 0) {
					State = eNecthorState::State_ShockWave;
					mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
					AtkCnt.Wave++;
				}
				else if (r % 5 == 0) {
					mcpLeapdebri[0]->Fadeout();
					mcpLeapdebri[1]->Fadeout();
					mcpLeapdebri[2]->Fadeout();
					Shiver = 0.002f;
					State = eNecthorState::State_LeapDebri;
					LeapDebriAtkCnt++;
					mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
				}
			}
			else {
				mcpLeapdebri[0]->Fadeout();
				mcpLeapdebri[1]->Fadeout();
				mcpLeapdebri[2]->Fadeout();
				Shiver = 0.002f;
				State = eNecthorState::State_LeapDebri;
				LeapDebriAtkCnt++;
				mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
			}
		}
		else {mcpLeapdebri[0]->Fadeout();
				mcpLeapdebri[1]->Fadeout();
				mcpLeapdebri[2]->Fadeout();
				Shiver = 0.002f;
				State = eNecthorState::State_LeapDebri;
				LeapDebriAtkCnt++;
				mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
			mcpLeapdebri[0]->Fadeout();
			mcpLeapdebri[1]->Fadeout();
			mcpLeapdebri[2]->Fadeout();
			State = eNecthorState::State_LeapDebri;
			LeapDebriAtkCnt++;
			mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
		}				
		IdolCnt = 0;                                               //! カウントのリセット
	}
	else if (IdolCnt >= (60 * 2) && ToPx >= 1.4) {              //! 三秒経過していてかつボスから離れていたら
		if (!ShockWaved) {
			State = eNecthorState::State_ShockWave;
			mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
			Shiver = 0.002f;
			ShockWaved = true;                                     //! この攻撃をしたフラグを立てる
			AtkCnt.Wave++;                                         //! 何回この攻撃をしたかを数える
		}
		else {													   //! クールタイムが経過したらまたこの攻撃をできるようにする
			ShockWaveCoolTime++;
			if (ShockWaveCoolTime >= ShockWaveCoolTimeMax) {
				ShockWaved = false;
			}
		}
	}

	mcpAnimsprite->SetStopAnimation(false);
	IdolCnt++;
}

void Necthor1_5::SmokeUpdate()
{
	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->Update();
	}
	//! 煙のフラグを立てる
	int AttackNum = AtkCnt.Press + AtkCnt.Wave + LeapDebriAtkCnt;
	if (AttackNum == 2) {
		LeftSmoke = true;
	}
	if (AttackNum == 4) {
		RightSmoke = true;
	}

	Vector2 SmokePos[3]; //! 0 真ん中 1 右 2 左
	//! 各煙の座標の計算
	if (TexState == Tex_Idol) {
		SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
		SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
		SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
	}
	else if (TexState == Tex_Attack || TexState == Tex_Attack2) {
		if (AnimX == 0) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
		else if (AnimX == 1) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
		else if (AnimX == 2 || AnimX == 3) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
		else if (AnimX == 4 || AnimX == 5 || AnimX == 6) {
			SmokePos[0] = Vector2(mcVec.x + 0.04f, mcVec.y + 0.3f);
			SmokePos[1] = Vector2(mcVec.x + 0.2, mcVec.y - 0.06f);
			SmokePos[2] = Vector2(mcVec.x - 0.12f, mcVec.y - 0.06f);
		}
		else if (AnimX == 7) {
			SmokePos[0] = Vector2(mcVec.x + 0.1f, mcVec.y + 0.56f);
			SmokePos[1] = Vector2(mcVec.x + 0.28f, mcVec.y + 0.13f);
			SmokePos[2] = Vector2(mcVec.x - 0.04f, mcVec.y + 0.13f);
		}
		else if (AnimX == 8) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
	}

	if (NomalSmoke) {
		Smokes[0].get()->NomalSmokeRagular(SmokePos[0]);
	}
	else {
		Smokes[0].get()->SmokeOff();
	}

	if (RightSmoke) {
		Smokes[1].get()->RightSmokeSmall(SmokePos[1]);
	}
	else {
		Smokes[1].get()->SmokeOff();
	}

	if (LeftSmoke) {
		Smokes[2].get()->LeftSmokeSmall(SmokePos[2]);
	}
	else {
		Smokes[2].get()->SmokeOff();
	}
}

void Necthor1_5::Atk_PressHammer()
{
	//! 攻撃用のテクスチャに変更
	TexState = Tex_Attack;

	//! ハンマーが叩きつけられたら画面振動	
	if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk);
			AtkSEflg = false;
		}
		CAMERA->StartVibration(4);
		Hammer->Slamed = true;
		//! ハンマーの当たり判定の位置の調整
		MyCol.AtkCol->SetActiv(false); //! 攻撃の当たり判定をオフ
		//! ここでがれきを出す
		//! がれきの座標の計算
		Vector2 DebriPos;
		DebriPos.x = Hammer->Vec.x - 0.26f;
		DebriPos.y = Hammer->Vec.y - 0.3f;
		Debri[0].get()->UpStart(DebriPos);     //! がれきを出す

		//! 矢印を出す
		Vector2 AllowPos;
		AllowPos.x = Hammer->Vec.x - 0.3f;
		AllowPos.y = Hammer->Vec.y + 0.2f;
		Allow->AllowOn(AllowPos);
	}
	else if (AnimX == 6) {
		mcpAnimsprite->SetStopAnimation(true);
		//! ハンマーの攻撃判定をオフにする
		Hammer->AtkCol->SetActiv(false);

		//! 弱点に攻撃をくらったら起き上がる
		if (WeekCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}
		if (MyCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}
		//! 数秒間待機後にIdol状態に戻る
		if (AttackCoolTime >= (60 * 6)) {
			mcpAnimsprite->SetStopAnimation(false);
		}
		AttackCoolTime++;
	}
	else if (AnimX == 7) {
		Debri[0].get()->FadeoutStart();
		Allow->AllowOff();
	}
	else if (AnimX == 8) {
		AtkSEflg = true;
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		mcpAnimsprite->ResetAnimCnt(); //! アニメーションカウントのリセット
	}
}

void Necthor1_5::Atk_ShockWave()
{
	//! 攻撃用のテクスチャに変更
	TexState = Tex_Attack2;

	//! アニメーションのそくどを遅くする
	mcpAnimsprite->SetAnimSpeed(4);

	//! ハンマーが叩きつけられたら画面振動
	if (AnimX <= 3) {
		Hammer->Slamed = false;
		//! ハンマーの当たり判定の調整
	}
	if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk);
			AtkSEflg = false;
		}
		Hammer->Slamed = true;
		CAMERA->StartVibration(4);
		MyCol.AtkCol->SetActiv(false); //! 攻撃の当たり判定をオフ

		//! 衝撃波を出す
		Vector2 WavePos;
		WavePos.x = Hammer->Vec.x - 0.1f;
		WavePos.y = Hammer->Vec.y;
		Wave[0].get()->ShockWaveStart(WavePos);
	}
	else if (AnimX == 6) {
		mcpAnimsprite->SetStopAnimation(true);
		//! ハンマーの攻撃判定をオフにする
		Hammer->AtkCol->SetActiv(false);

		//! 数秒間待機後にIdol状態に戻る
		if (AttackCoolTime >= (60 * 2)) {
			mcpAnimsprite->SetStopAnimation(false);
		}
		AttackCoolTime++;
	}
	else if (AnimX == 8) {
		AtkSEflg = true;
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		mcpAnimsprite->ResetAnimCnt(); //! アニメーションカウントのリセット
	}
}

void Necthor1_5::Atk_RushWave()
{
	//! 予備動作
	if (!RushPreparation) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_AtkSig);
			AtkSEflg = false;
		}
		TexState = Tex_Idol;
		NomalSmoke = true;
		//! 震える		
		if (PreparationCnt % 3 == 0) { //! 3フレーム毎に震える方向を帰る
			Shiver *= -1;
		}
		mcVec.x += Shiver;
		if (PreparationCnt >= 120) {
			RushPreparation = true;
			PreparationCnt = 0;
			AtkSEflg = true;
			mcpAnimsprite->ResetAnimCnt();
			
		}
		PreparationCnt++;
	}
	//! 攻撃開始
	else {
		//! 仮で攻撃の画像をセットしています
		TexState = Tex_Attack2;
		//! アニメーションのそくどを遅くする
		mcpAnimsprite->SetAnimSpeed(4);
		//! 地面にハンマーがついたらアニメーションを止める	
		if (RushCnt < RushMax) {
			mcpAnimsprite->SetStopAnimation(false);
			if (AnimX <= 3) {
				Hammer->Slamed = false;
			}
			//! ハンマーが叩きつけられたら画面振動
			if (AnimX == 5) {
				if (AtkSEflg) {
					SoundMgr->PlaySE(SE_Necthor_Atk,0.2f);
				}
				Hammer->Slamed = true;
				CAMERA->StartVibration(4);
				MyCol.AtkCol->SetActiv(false); //! 攻撃の当たり判定をオフ

				//! 衝撃波を出す
				Vector2 WavePos;
				WavePos.x = Hammer->Vec.x - 0.1f;
				WavePos.y = Hammer->Vec.y;
				Wave[RushCnt].get()->ShockWaveStart(WavePos);
			}
			else if (AnimX == 6) {
				mcpAnimsprite->SetStopAnimation(true);
				//! ハンマーの攻撃判定をオフにする
				Hammer->AtkCol->SetActiv(false);

				//! 数秒間待機後にIdol状態に戻る
				if (AttackCoolTime >= (30)) {
					mcpAnimsprite->SetStopAnimation(false);
				}

				AttackCoolTime++;
			}
			else if (AnimX == 8) {
				AttackCoolTime = 0;
				AtkSEflg = true;
				RushCnt++;
				mcpAnimsprite->ResetAnimCnt(); //! アニメーションカウントのリセット	
			}
		}

		//! 4回目にクソでか衝撃波を出す
		else {
			TexState = Tex_Attack;
			if (AnimX <= 3) {
				Hammer->Slamed = false;
			}
			if (AnimX == 3) {
				mcpAnimsprite->SetStopAnimation(true);
				if (RushFrameCnt >= 30) {
					mcpAnimsprite->SetStopAnimation(false);
				}
				RushFrameCnt++;
			}
			else if (AnimX == 5) {
				if (AtkSEflg) {
					SoundMgr->PlaySE(SE_Necthor_Atk, 0.4f);
				}
				CAMERA->StartVibration(4);
				//! ハンマーの当たり判定の位置の調整
				MyCol.AtkCol->SetActiv(false); //! 攻撃の当たり判定をオフ

				Hammer->Slamed = true;

				//! 衝撃波を出す
				Vector2 WavePos;
				WavePos.x = Hammer->Vec.x - 0.1f;
				WavePos.y = Hammer->Vec.y;
				// 本来はでかい衝撃波
				Wave[RushCnt].get()->ShockWaveStart(WavePos);

				Vector2 AllowPos;
				AllowPos.x = Hammer->Vec.x - 0.3f;
				AllowPos.y = Hammer->Vec.y + 0.2f;
				Allow->AllowOn(AllowPos);

				//! がれきの座標の計算
				Vector2 DebriPos;
				DebriPos.x = Hammer->Vec.x - 0.26f;
				DebriPos.y = Hammer->Vec.y - 0.3f;
				Debri[0].get()->UpStart(DebriPos);     //! がれきを出す
			}
			else if (AnimX == 6) {
				mcpAnimsprite->SetStopAnimation(true);
				//! ハンマーの攻撃判定をオフにする
				Hammer->AtkCol->SetActiv(false);

				//! 数秒間待機後にIdol状態に戻る
				if (AttackCoolTime >= (160)) {
					NomalSmoke = RightSmoke = LeftSmoke = false; //! スモークをオフにする
					AtkCnt.Wave = AtkCnt.Press = 0;			//! カウントリセット 

					if (!Smokes[0].get()->GetSmokeActiv()) {    //! 全てのスモークがオフになったらもとに戻る	
						mcpAnimsprite->SetStopAnimation(false);
						//! がれきを消す
						Debri[0].get()->FadeoutStart();
						Allow->AllowOff();
					}
				}
				AttackCoolTime++;
			}
			else if (AnimX == 8) {
				AtkSEflg = true;
				State = eNecthorState::State_Idol;      //! アイドル状態に戻す
				mcpAnimsprite->ResetAnimCnt();          //! アニメーションカウントのリセット	
				RushPreparation = 0;
				AttackCoolTime = 0;
				RushCnt = 0;
				RushFrameCnt = 0;
				IdolCnt = 0;
			}
		}
	}
}

void Necthor1_5::Atk_LeapDebri()
{
	//! 攻撃用のテクスチャに変更
	TexState = Tex_Attack;	
	//! 溜めモーション
	if (AnimX == 0 || AnimX == 1 || AnimX == 2) {
		mcpAnimsprite->SetStopAnimation(false);
	}
	else if (AnimX == 3) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_SPAtk,0.4f);
			AtkSEflg = false;
		}	
		//! 震える		
		mcpAnimsprite->SetStopAnimation(true);	
		if (LeapDebriPreparation % 3 == 0) { //! 3フレーム毎に震える方向を帰る
			Shiver *= -1;
		}
		//mcVec.x += Shiver;

		//! ３秒ふるえたら攻撃開始
		if (MyCol.TailHited) {
			LeapDebriPreparation = 100;
		}
		if (LeapDebriPreparation > 100) {
			AtkSEflg = true;
			mcpAnimsprite->SetStopAnimation(false);
		}
		LeapDebriPreparation++;
	}
	//! ハンマーが叩きつけられたら画面振動
	else if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk,0.2f);
			AtkSEflg = false;
		}
		CAMERA->StartVibration(6);
		Hammer->Slamed = true;
		//! ハンマーの当たり判定の位置の調整
		MyCol.AtkCol->SetActiv(false); //! 攻撃の当たり判定をオフ
		
		//! がれきの座標の計算
		Vector2 DebriPos;
		DebriPos.x = Hammer->Vec.x - 0.26f;
		DebriPos.y = Hammer->Vec.y - 0.3f;
		Debri[0].get()->UpStart(DebriPos);     //! がれきを出す

		//! とぶがれきを出す
		//! 飛ぶ勢い
		Vector2 LeapDebriPos;
		LeapDebriPos.x = Hammer->Vec.x - 0.1f;
		LeapDebriPos.y = Hammer->Vec.y - 0.1f;
		//! それぞれ飛距離を伸ばす
		for (int i = 0; i < LeapDebriAtkCnt; i++) {	
			if (i == 0) {
				mcpLeapdebri[i]->Leap(LeapDebriPos, Vector2(0.014f, 0.029f));
			}
			else if (i == 1) {
				mcpLeapdebri[i]->Leap(LeapDebriPos, Vector2(0.026f, 0.034f));
			}
			else if(i == 2){
				mcpLeapdebri[i]->Leap(LeapDebriPos, Vector2(0.04f, 0.039f));
			}
		}
		//! 矢印を出す
		Vector2 AllowPos;
		AllowPos.x = Hammer->Vec.x - 0.3f;
		AllowPos.y = Hammer->Vec.y + 0.2f;
		Allow->AllowOn(AllowPos);

	}
	else if (AnimX == 6) {
		mcpAnimsprite->SetStopAnimation(true);
		//! ハンマーの攻撃判定をオフにする
		Hammer->AtkCol->SetActiv(false);

		//! 弱点に攻撃をくらったら起き上がる
		if (WeekCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}
		if (MyCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}

		//! 数秒間待機後にIdol状態に戻る
		if (AttackCoolTime >= (60 * 6)) {
			mcpAnimsprite->SetStopAnimation(false);
		}
		AttackCoolTime++;
	}
	else if (AnimX == 7) {
		Debri[0].get()->FadeoutStart();
		Allow->AllowOff();
	}
	else if (AnimX == 8) {
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		LeapDebriPreparation = 0;
		AtkSEflg = true;
		mcpAnimsprite->ResetAnimCnt(); //! アニメーションカウントのリセット
		if (LeapDebriAtkCnt == 3) {
			LeapDebriAtkCnt = 0;
		}
	}
}

