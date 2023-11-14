#include "ReNecthor.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Camerah.h"
#include "NecthorHammer_InClass.h"
#include "Debri.h"
#include "ShocoWave.h"
#include "Smoke.h"
#include "Necthor_Allow.h"
#include "SoundManager.h"
#include "Collision.h"
#include "EffectManager.h"
//! コンストラクタ
ReNecthor::ReNecthor()
{
	//! 描画関連の設定
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol));
	mcpAnimsprite->SetAnimtionTable(5, 1);
	SetSize(2.4f, 2.4f);

	//! 変数の初期値設定
	State = eNecthorState::State_Idol; //! 初期状態
	HP = 10;
	DamageFrameCnt = TakenDamage = AttackCoolTime = IdolCnt = 0;
	DamageFlg = false;
	//! 当たり判定の生成
	//! ハンマー
	Hammer = new NecthorHammer;
	Hammer->Vec.x = mcVec.x - 0.2f;
	Hammer->Vec.y = mcVec.y - 0.33f;
	//! 本体
	MyCol.Col = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	MyCol.AtkCol = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	//! 弱点の当たり判定
	WeekCol.Col = new Box(WeekCol.Pos, WeekCol.Size.x, WeekCol.Size.y);
	WeekCol.AtkCol = new Box(WeekCol.Pos, WeekCol.Size.x, WeekCol.Size.y);
	ColFix(); //! 本体と弱点位置の当たり判定の調整
	//! がれきの生成
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<NecthorDebri> debri(new NecthorDebri);
		Debri.emplace_back(move(debri));
	}
	//! 衝撃波の生成
	for (int i = 0; i < 4; i++) {
		std::unique_ptr<ShockWave> wave(new ShockWave);
		Wave.emplace_back(move(wave));
	}
	RushFrameCnt = RushCnt = 0;
	AtkSEflg = true;
	//! 仮で戦闘開始状態からスタート 戦闘開始まえの威嚇行動後に戦闘開始
	BattleActiv = true;
}

//! コンストラクタ(引数あり)
ReNecthor::ReNecthor(float _x ,float _y)
{
	//! 描画関連の設定
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol));
	mcpAnimsprite->SetAnimtionTable(5, 1);
	SetSize(1.7f, 1.7f);
	mcVec = Vector2(_x, _y); //! 座標のセット
	//! 変数の初期値設定
	State = eNecthorState::State_Idol; //! 初期状態
	HP = 10;
	AnimX = DamageFrameCnt = TakenDamage = AttackCoolTime = IdolCnt = 0;
	DamageFlg = false;
	//! 当たり判定の生成
	//! ハンマー
	Hammer = new NecthorHammer;
	Hammer->Vec.x = mcVec.x - 0.1;
	Hammer->Vec.y = mcVec.y - 0.44f;

	//! 本体
	MyCol.Col = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	MyCol.AtkCol = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	//! 弱点の当たり判定
	WeekCol.Col = new Box(WeekCol.Pos,WeekCol.Size.x,WeekCol.Size.y);
	WeekCol.AtkCol = new Box(WeekCol.Pos, WeekCol.Size.x, WeekCol.Size.y);

	ColFix(); //! 本体と弱点位置の当たり判定の調整

	//! がれきの生成
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<NecthorDebri> debri(new NecthorDebri);
		Debri.emplace_back(move(debri));
	}	
	//! 衝撃波の生成
	for (int i = 0; i < 6; i++) {
		std::unique_ptr<ShockWave> wave(new ShockWave);
		Wave.emplace_back(move(wave));
	}	
	//! 煙の生成
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<Smoke> smoke(new Smoke);
		Smokes.emplace_back(move(smoke));
	}

	PreparationCnt = RushFrameCnt = RushCnt = 0;
	Shiver = 0.004f;
	//! 仮で戦闘開始状態からスタート 戦闘開始まえの威嚇行動後に戦闘開始
	BattleActiv = false;
	TexState_Prev = TexState = Tex_Idol;
	RushMax = 3;
	ShockWaveCoolTimeMax = 120;
	AtkSEflg = true;
	Allow.reset(new Necthor_Allow);
}


//! デストラクタ
ReNecthor::~ReNecthor()
{	
	delete MyCol.AtkCol;
	delete MyCol.Col;
	delete WeekCol.AtkCol;
	delete WeekCol.Col;
	delete Hammer;
}

//! 更新処理
void ReNecthor::Update()
{	
	AnimX = mcpAnimsprite->GetCurrentXSplit(); //! 現在のＸ方向アニメーションの番号をもらう
	ColFix();
	if (BattleActiv) {
		//! Hpが無くなったら倒れてる状態にいく
		if (HP <= 0 && State != eNecthorState::State_Destroy) {
			if (State != eNecthorState::State_Down) {
				//! がれきを出す
				Vector2 DebriPos;
				DebriPos.x = mcVec.x - 0.7f;
				DebriPos.y = mcVec.y - 0.75f;
				Debri[1].get()->UpStart(DebriPos,true);     //! がれきを出す(描画あり)
				Debri[0].get()->FadeoutStart();
			}
			State = eNecthorState::State_Down;	
		}
		//! HPが少なくなったら
		if (HP <= 5 && HightHP && State == eNecthorState::State_Idol) {
			RushMax = 5;
			ShockWaveCoolTimeMax = 100;
			IdolCnt = 50;
			HightHP = false;
		}

		//! 状態の更新処理
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

		case eNecthorState::State_Down:
			FallDwoned();
			break;
		case eNecthorState::State_Destroy:
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
	SmokeUpdate();
	Allow->Update();
	TexChange();
	//ColFix();
}

//! 描画処理
void ReNecthor::Draw()
{
	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->Draw();
	}
	GameObject::Draw();
	for (int i = 0; i < Debri.size(); i++) {
		Debri[i].get()->Draw();
	}
	for (int j = 0; j < Wave.size(); j++) {
		Wave[j].get()->Draw();
	}
	
	Allow->Draw();
	//image.DrawSprite(Hammer->Vec.x,Hammer->Vec.y,Hammer->ColSize.x,Hammer->ColSize.y,TEXTURE(Tex_PanelBl),1,1,1,0.5f);
	////! デバッグようボスHPの表示
	//Vector2 HpPos = Vector2(mcVec.x, mcVec.y + 0.4f);
	//for (int i = 0; i < HP; i++) {
	//	image.DrawSprite(HpPos.x + (i * 0.12f), HpPos.y, 0.1, 0.1, TEXTURE(Tex_MapTip01));
	//}
}


//! 当たり判定の処理
void ReNecthor::CollisionUpdate()
{
	//! ダメージを加算にしているのは帯電状態の時にうまくさしたら2パンできるようにしてます(たぶん)
	Box * PlayerBox = mcPlayer->GetBoxCol();
	//! プレイヤーからの攻撃の当たり判定
	Circle* PlayerAtk;
	PlayerAtk = mcPlayer->GetAttackCol();
	Circle * SpearCol[2];
	int ColNum = 0;
	//! 攻撃の当たり判定をもらう
	bool Elect = mcPlayer->GetCharge();
	
//* ハンマー ------------------------------------------------------------------
	//! ハンマーの攻撃判定との当たり判定
	if (BBH(*PlayerBox, *Hammer->AtkCol)) {
		mcPlayer->SetDamege(Left); //! ボスは右側にいるので、必ず左側にはじかれるようにする(右にノックバックすると本体とハンマーに挟まって即死する)
	}	
	//! ハンマーとの衝突判定
	BBC(*PlayerBox,*Hammer->Col);

	//! ハンマーとしっぽの当たり判定
	if (Elect) {  //! 帯電時
		for ( ColNum = 0; ColNum < 2; ColNum++) {
			if (BCH(*Hammer->Col, mcPlayer->GetSpearCol(ColNum)) && !Hammer->TailHited) {
				mcPlayer->SetReaction(TailReaction_Bounce, Left);
				SoundMgr->PlaySE(SE_Timpiller_Sasaru);;
				Hammer->TailHited = true;
			}
		}
	}
	else {   //! 非帯電
		if (BCH(*Hammer->Col, *PlayerAtk) && !Hammer->TailHited) {
			SoundMgr->PlaySE(SE_Necthor_Haziku);
			if (mcPlayer->GetVec().x < Hammer->Vec.x) {
				mcPlayer->SetReaction(TailReaction_Bounce, Left);
			}
			else {
				mcPlayer->SetReaction(TailReaction_Bounce, Right);
			}
			TakenDamage += 0;
			Hammer->TailHited = true;
		}
	}

//! 本体 ---------------------------------------------------------------------------------
	//! 本体とプレイヤーの当たり判定
	//! 衝突判定
	BBC(*PlayerBox, *MyCol.Col);

	//! 尻尾との当たり判定
	if (Elect) {
		for (ColNum = 0; ColNum < 2; ColNum++) {	
			if (BCH(*MyCol.Col, mcPlayer->GetSpearCol(ColNum)) && !MyCol.TailHited) {
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.2f);
				mcPlayer->SetReaction(TailReaction_Stop, Direction_None);
				TakenDamage += 1;
				MyCol.TailHited = true;
			}
		}
	}
	else {
		if (BCH(*MyCol.Col, *PlayerAtk) && !MyCol.TailHited) {
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.2f);
			mcPlayer->SetReaction(TailReaction_Stop, Direction_None);
			TakenDamage += 1;
			MyCol.TailHited = true;
		}
	}

	//! 攻撃判定
	if (BBH(*PlayerBox, *MyCol.AtkCol)) {
		mcPlayer->SetDamege(Left); //! ボスは右側にいるので、必ず左側にはじかれるようにする(右にノックバックすると本体とハンマーに挟まって即死する)
	}

//! 弱点 -------------------------------------------------------------------------------------
	//! 弱点との当たり判定
	//! 衝突判定
	BBC(*PlayerBox,*WeekCol.Col);

	if (BBH(*PlayerBox,*WeekCol.AtkCol)) {
		mcPlayer->SetDamege(Left); //! ボスは右側にいるので、必ず左側にはじかれるようにする(右にノックバックすると本体とハンマーに挟まって即死する)
	}

	//! 尻尾との当たり判定
	if (Elect) {
		for (ColNum = 0; ColNum < 2; ColNum++) {
			if (BCH(*WeekCol.Col,mcPlayer->GetSpearCol(ColNum)) && !WeekCol.TailHited) {
				//! とどめを刺されたらデストロイにいく
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.4f);
				if (State == eNecthorState::State_Down) {
					State = eNecthorState::State_Destroy;
				}
				WeekCol.TailHited = true;
				mcPlayer->SetReaction(TailReaction_Through, Direction_None);
				TakenDamage += 2;
			}
		}
	}
	else {
		if (BCH(*WeekCol.Col, *PlayerAtk) && !WeekCol.TailHited) {
			SoundMgr->PlaySE(SE_Timpiller_Sasaru,0.4f);
			WeekCol.TailHited = true;
			mcPlayer->SetReaction(TailReaction_StingStop, Direction_None);
			TakenDamage += 2;
			//! ダウンしているときに弱点に刺されたらデストロイ状態に行く
			if (State == eNecthorState::State_Down) {
				State = eNecthorState::State_Destroy;
			}
		}
	}

//! がれき -----------------------------------------------------------------------------------
	for (int i = 0; i < Debri.size(); i++) {
		Box * DebriCol = Debri[i].get()->GetCol();
		BBC(*PlayerBox, *DebriCol);

		//! がれきと尻尾の当たり判定
		if (Elect) {	
			for (ColNum = 0; ColNum < 2; ColNum++) {
				if (BCH(*DebriCol, mcPlayer->GetSpearCol(ColNum))) {
					SoundMgr->PlaySE(SE_Splitter_Haziku, 0.2f);
					mcPlayer->SetReaction(TailReaction_Bounce, Left);	
				}
			}
		}
		else {
			if (BCH(*DebriCol, *PlayerAtk)) {
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.2f);
				mcPlayer->SetReaction(TailReaction_Bounce, Left);
				
			}
		}
	}

//! 衝撃波 -------------------------------------------------------------------------------------
	for (int i = 0; i < Wave.size(); i++) {
		Box * WaveCol = Wave[i].get()->GetCol();
		//! プレイヤーとの当たり判定
		if (BBH(*WaveCol, *PlayerBox)) {
			mcPlayer->SetDamege(Left);
		}
		//! 尻尾との当たり判定
		if (Elect) {
			for (ColNum = 0; ColNum < 2; ColNum++) {
				if (BCH(*WaveCol, mcPlayer->GetSpearCol(ColNum))) {
					SoundMgr->PlaySE(SE_Timpiller_Sasaru,0.1);
					Wave[i].get()->SetHit(true);
					mcPlayer->SetReaction(TailReaction_Through, Direction_None);
					break;
				}
			}
		}
		else {
			if (BCH(*WaveCol, *PlayerAtk)) {
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1);
				Wave[i].get()->SetHit(true);
				mcPlayer->SetReaction(TailReaction_Through, Direction_None);
			}
		}
	}

	//! 一度尻尾の攻撃に当たったら30フレームは攻撃には当たらない
	if (WeekCol.TailHited) {
		WeekCol.Cnt++;
		if (WeekCol.Cnt >= 30) {
			WeekCol.Cnt = 0;
			WeekCol.TailHited = false;
		}
	}
	if (MyCol.TailHited) {
		MyCol.Cnt++;
		if (MyCol.Cnt >= 30) {
			MyCol.Cnt = 0;
			MyCol.TailHited = false;
		}
	}
	if (Hammer->TailHited) {
		Hammer->Cnt++;
		if (Hammer->Cnt >= 30) {
			Hammer->Cnt = 0;
			Hammer->TailHited = false;
		}
	}
}

void ReNecthor::LastUpdate()
{
	Damage();
}

void ReNecthor::SetPlayer(Player * _player)
{
	mcPlayer = _player;
}

void ReNecthor::BattleStart()
{
	BattleActiv = true;
}

bool ReNecthor::GetDestroyed()
{
	return mDestroy;
}

//! アイドル状態の処理
void ReNecthor::Idol()
{
	mcpAnimsprite->SetAnimSpeed(8);
	TexState = Tex_Idol;
	
	//! でぶりを消す
	Debri[0].get()->FadeoutStart();

	Hammer->AtkCol->SetActiv(true);
	
	//! 本体の当たり判定の位置を求める
	ColFix();
	
	MyCol.AtkCol->SetActiv(true); //! 攻撃の当たり判定をオン
	Hammer->Slamed = false;
	AttackStateMachine();	
}

void ReNecthor::AttackStateMachine()
{
	float Px = mcPlayer->GetVec().x;                               //! プレイヤーのX座標
	float ToPx = fabs(mcVec.x - Px);                               //! プレイヤーまでのX方向の距離       
	int TotalAtk = AtkCnt.Press + AtkCnt.Wave;                     //! 衝撃波とプレス攻撃をした回数

	if (TotalAtk >= 2) {									       //! 衝撃波攻撃を二回以上していたら衝撃波連打攻撃をする
		State = eNecthorState::State_RushWave;
		IdolCnt = 0;                                               //! カウントのリセット	 
		mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット	
	}
	else if (IdolCnt >= (60 * 4)) {								   //! 300フレーム経過したら攻撃に行く		  	                  	                      
		State = eNecthorState::State_PressHammer;
		IdolCnt = 0;                                               //! カウントのリセット
		mcpAnimsprite->ResetAnimCnt();                             //! アニメーションカウントのリセット
		AtkCnt.Press++;
	}
	else if (IdolCnt >= (60 * 3) && ToPx >= 1.4) {              //! 三秒経過していてかつボスから離れていたら
		if (!ShockWaved) {
			State = eNecthorState::State_ShockWave;
			mcpAnimsprite->ResetAnimCnt();                         //! アニメーションカウントのリセット	
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
	IdolCnt++;
}

//! 攻撃の処理
void ReNecthor::Atk_PressHammer()
{
	//! 攻撃用のテクスチャに変更
	TexState = Tex_Attack;
	
	//! ハンマーが叩きつけられたら画面振動	
	if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk, 0.2f);
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

		//! 矢印をだす
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
		if (WeekCol.TailHited || MyCol.TailHited) {
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

void ReNecthor::Atk_ShockWave()
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
			SoundMgr->PlaySE(SE_Necthor_Atk, 0.1f);
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
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		AtkSEflg = true;
		mcpAnimsprite->ResetAnimCnt(); //! アニメーションカウントのリセット
	}
}

//! 連続衝撃波攻撃
void ReNecthor::Atk_RushWave()
{	
	//! 予備動作
	if (!RushPreparation) {	
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_AtkSig, 0.1f);
			AtkSEflg = false;
		}
		TexState = Tex_Idol;
		NomalSmoke = true;
		//! 赤くなりながら震える		
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
					SoundMgr->PlaySE(SE_Necthor_Atk, 0.2f);
					AtkSEflg = false;
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
				AtkSEflg = true;
				AttackCoolTime = 0;
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
					SoundMgr->PlaySE(SE_Necthor_SPAtk, 0.3f);
					AtkSEflg = false;
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

				//! がれきの座標の計算
				Vector2 DebriPos;
				DebriPos.x = Hammer->Vec.x - 0.26f;
				DebriPos.y = Hammer->Vec.y - 0.3f;
				Debri[0].get()->UpStart(DebriPos);     //! がれきを出す

				//! 矢印をだす
				Vector2 AllowPos;
				AllowPos.x = Hammer->Vec.x - 0.3f;
				AllowPos.y = Hammer->Vec.y + 0.2f;
				Allow->AllowOn(AllowPos);
			}
			else if (AnimX == 6) {
				mcpAnimsprite->SetStopAnimation(true);
				//! ハンマーの攻撃判定をオフにする
				Hammer->AtkCol->SetActiv(false);
				
				if (WeekCol.TailHited || MyCol.TailHited) {
					AttackCoolTime = 160;
				}
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
				State = eNecthorState::State_Idol;      //! アイドル状態に戻す
				mcpAnimsprite->ResetAnimCnt();          //! アニメーションカウントのリセット	
				RushPreparation = 0;
				AttackCoolTime = 0;
				RushCnt = 0;
				RushFrameCnt = 0;
				IdolCnt = 0;	
				AtkSEflg = true;
			}
		}
	}
}

//! 倒れているときの処理
void ReNecthor::FallDwoned()
{
	//! 仮で攻撃の画像をセットしています
	TexState = Tex_Attack2;
	mcpAnimsprite->SetXSplit(6); //! 最後のコマにセットする
	//! 画像の色を暗くする
	mcpAnimsprite->SetColor(0.5f, 0.5f, 0.5f);

	Allow->AllowOn(Vector2(WeekCol.Pos.x, WeekCol.Pos.y + 0.1f));

	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->SmokeOff();
	}

	Hammer->AtkCol->SetActiv(false);
	MyCol.AtkCol->SetActiv(false);	
}

//! とどめを刺されて破壊される時の処理
void ReNecthor::Destroy()
{
	//! 仮で攻撃の画像をセットしています
	TexState = Tex_Attack2;
	mcpAnimsprite->SetXSplit(6); //! 最後のコマにセットする
	mcpAnimsprite->SetColor(0.5,0.5,0.5);
	Allow->AllowOff();
	//! スモークを消す
	Smokes[0]->SmokeOff();
	Smokes[1]->SmokeOff();
	Smokes[2]->SmokeOff();
	Allow->AllowOff();
	//! 透明度を下げていく
	if (Arufa > 0) {
		Arufa -= 0.01f;
	}
	else {
		mDestroy = true;
	}

	mcpAnimsprite->SetArufa(Arufa);
	//! 爆破エフェクトを出す
	if (DestroyCnt == 3) {
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu,0.15f);
		EffMgr->PlayEffect(Explosion02,mcVec.x,mcVec.y - 0.2f,0.4f,0.4f,10);
	}
	else if (DestroyCnt == 10) {
		EffMgr->PlayEffect(Explosion02, mcVec.x + 0.2f, mcVec.y - 0.3f, 1.0f, 1.0f,12);
	}
	else if (DestroyCnt == 15) {
		EffMgr->PlayEffect(Explosion02, mcVec.x - 0.14f, mcVec.y - 0.33f, 0.6f, 0.6f,10);
	}
	else if (DestroyCnt == 18) {
		EffMgr->PlayEffect(Explosion02, mcVec.x - 0.1f, mcVec.y - 0.27f, 0.5f, 0.5f,14);
	}
	else if (DestroyCnt == 20) {
		EffMgr->PlayEffect(Explosion02, WeekCol.Pos.x, WeekCol.Pos.y,0.5f, 0.5f,10);
	}
	else if (DestroyCnt == 24) {
		EffMgr->PlayEffect(Explosion02, Hammer->Vec.x, Hammer->Vec.y, 0.9f, 0.9f,10);
	}
	else if (DestroyCnt == 26) {
		EffMgr->PlayEffect(Explosion02, MyCol.Pos.x, MyCol.Pos.y, 1.0f, 1.0f,10);
	}
	//! ハンマー
	//! 本体
	//! 適当なところ

	DestroyCnt++;

	//! 全ての当たり判定をオフにする
	MyCol.AtkCol->SetActiv(false);
	MyCol.Col->SetActiv(false);
	WeekCol.AtkCol->SetActiv(false);
	WeekCol.Col->SetActiv(false);
	Hammer->AtkCol->SetActiv(false);
	Hammer->Col->SetActiv(false);
}

//! 本体の当たり判定の調整関数
void ReNecthor::ColFix()
{
	if (TexState == Tex_Idol) {
		MyCol.Pos.x = mcVec.x + 0.32f;
		MyCol.Pos.y = mcVec.y - 0.26f;
		MyCol.Size.x = 0.46f;
		MyCol.Size.y = 0.66f;
		MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
		MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

		//! 弱点の当たり判定の位置調整
		WeekCol.Pos.x = mcVec.x + 0.34f;
		WeekCol.Pos.y = mcVec.y + 0.2f;
		WeekCol.Size.x = 0.2f;
		WeekCol.Size.y = 0.16f;
		WeekCol.AtkCol->SetActiv(true);
		WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
		WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

		//! ハンマーの当たり判定の位置を計算する
		Hammer->Vec.x = mcVec.x - 0.1;
		Hammer->Vec.y = mcVec.y - 0.44f;
	}
	else if (TexState == Tex_Attack || Tex_Attack2) {
		if (AnimX == 0) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! 弱点の当たり判定の位置調整
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! ハンマーの当たり判定の位置を計算する
			Hammer->Vec.x = mcVec.x - 0.1;
			Hammer->Vec.y = mcVec.y - 0.44f;
		}
		else if (AnimX == 1) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! 弱点の当たり判定の位置調整
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);
		}
		else if (AnimX == 2 || AnimX == 3) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! 弱点の当たり判定の位置調整
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			Hammer->Vec.x = mcVec.x - 0.2f;
			Hammer->Vec.y = mcVec.y + 0.48f;
			Hammer->ColSize.x = 0.6f;
			Hammer->ColSize.y = 0.2f;

		}
		else if (AnimX == 4 || AnimX == 5 || AnimX == 6) {
			//! 本体の当たり判定の位置の調整
			MyCol.Pos.x = mcVec.x + 0.05f;
			MyCol.Pos.y = mcVec.y - 0.4f;
			MyCol.Size.x = 0.4f;
			MyCol.Size.y = 0.4f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! 弱点の当たり判定の位置調整
			WeekCol.Pos.x = mcVec.x + 0.1f;
			WeekCol.Pos.y = mcVec.y - 0.1f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(false);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! ハンマーの当たり判定の位置の調整
			Hammer->Vec.x = mcVec.x - 0.40f;
			Hammer->Vec.y = mcVec.y - 0.5f;
			//! ハンマーの大きさもとに戻す
			Hammer->ColSize.x = 0.44f;
			Hammer->ColSize.y = 0.5f;
			Hammer->AtkCol->SetSize(0.44, 0.5f);
		
		}
		else if (AnimX == 7) {
			MyCol.Pos.x = mcVec.x + 0.18f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.58f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! 弱点の当たり判定の位置調整
			WeekCol.Pos.x = mcVec.x + 0.18f;
			WeekCol.Pos.y = mcVec.y + 0.1f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! ハンマーの当たり判定の位置を計算する
			Hammer->Vec.x = mcVec.x - 0.28f;
			Hammer->Vec.y = mcVec.y - 0.44f;
		}
		else if (AnimX == 8) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! 弱点の当たり判定の位置調整
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! ハンマーの当たり判定の位置を計算する
			Hammer->Vec.x = mcVec.x - 0.1f;
			Hammer->Vec.y = mcVec.y - 0.44f;
		}
	}
	Hammer->Col->SetSize(Hammer->ColSize.x, Hammer->ColSize.y);
}

void ReNecthor::Damage()
{
	//! 被ダメがあれば処理を開始する
	if (TakenDamage != 0 && State != eNecthorState::State_Down) {
		DamageFlg = true;
		HP -= TakenDamage;
		if (State == State_Idol) {
			IdolCnt += 40;
		}
		TakenDamage = 0;
		DamageFrameCnt = 0;
	}

	//! ダメージをうけていたら60フレーム点滅する
	if (DamageFlg) {
		if (HP > 0) {
			//! 点滅させる
			if (DamageFrameCnt >= 60) {
				DamageFlg = false;
				SetDrawActiv(true); //! 最後に描画をして処理を終わる
			}
			else if ((DamageFrameCnt % 20) <= 10) {
				SetDrawActiv(false);
			}
			else { SetDrawActiv(true); }
			DamageFrameCnt++;
		}
		else {
			//! 点滅させる
			if (DamageFrameCnt >= 96) {
				DamageFlg = false;
				SetDrawActiv(true); //! 最後に描画をして処理を終わる
			}
			else if ((DamageFrameCnt % 12) <= 4) {
				SetDrawActiv(false);
			}
			else { SetDrawActiv(true); }
			DamageFrameCnt++;
		}
	}
}

//! 煙の更新処理
void ReNecthor::SmokeUpdate()
{
	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->Update();
	}
	//! 煙のフラグを立てる
	int AttackNum = AtkCnt.Press + AtkCnt.Wave;
	if (AttackNum == 1) {
		LeftSmoke = true;
	}
	if (AttackNum == 2) {
		RightSmoke = true;
	}
	
	Vector2 SmokePos[3]; //! 0 真ん中 1 右 2 左
	//! 各煙の座標の計算
	if (TexState == Tex_Idol) {	
		SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
		SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
		SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);	
	}
	else if (TexState == Tex_Attack || TexState == Tex_Attack2){
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
			SmokePos[2] = Vector2(mcVec.x - 0.12f, mcVec.y -0.06f);
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

//! テクスチャを今の状態に合わせて変更する関数
void ReNecthor::TexChange()
{
	//! 前フレームとテクスチャが変わっていたらアニメーションカウントをリセットしてテクスチャを変更する
	if (TexState != TexState_Prev) {
		mcpAnimsprite->ResetAnimCnt();
		if (TexState == Tex_Idol) {
			mcpAnimsprite->SetAnimtionTable(5, 1);
			if (HightHP) {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol));
			}
			else {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol_Red));
			}
		}
		else if (TexState == Tex_Attack) {
			mcpAnimsprite->SetAnimtionTable(9, 1);
			if (HightHP) {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack));
			}
			else {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack_Red));
			}
		}
		else if (Tex_Attack2) {
			mcpAnimsprite->SetAnimtionTable(9, 1);
			if (HightHP) {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack2));
			}
			else {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack2_Red));
			}
		}
	}
	TexState_Prev = TexState;


}
