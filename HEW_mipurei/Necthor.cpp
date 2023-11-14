#include "Necthor.h"
#include"TextureManager.h"
#include"DirectInput8.h"

Necthor::Necthor(float _X, float _Y)
{
	mAttackCoolTime = 60 * StopTime;
	mLife = ResistDef;//
	mChargeTime = 60 * AtkCharge;//60(1秒)*停止してほしいループ数(1以上の整数)
	mDamageCoolTime = 60 * 3;//仮で60秒＊３ループ＝180秒耐えるようにする

	this->mcVec.x = _X;
	this->mcVec.y = _Y;
	msSize = { 1.0f,1.0f };
	LoadTexture(L"assets/idol2.png", &mTmpTex);
	LoadTexture(L"assets/attack2.png", &mAtkTex);
	mcpAnimsprite->SetTexture(mTmpTex);
	mcpAnimsprite->SetAnimtionTable(5, 1);

	//体の当たり判定設定
	mpBodyColisionPos.x = this->mcVec.x + 0.15f;
	mpBodyColisionPos.y = this->mcVec.y - 0.25f;
	mpBodyCollision = new Box(mpBodyColisionPos, 0.4f, 0.32f);

	//頭の当たり判定設定
	mpHeadCollisionPos.x = this->mcVec.x + 0.16f;
	mpHeadCollisionPos.y = this->mcVec.y + 0.1f;
	mpHeadCollision = new Box(mpHeadCollisionPos, 0.22f, 0.25f);

	//ハンマー当たり判定設定
	mpHunmerCollisionPos.x = this->mcVec.x - 0.16f;
	mpHunmerCollisionPos.y = this->mcVec.y - 0.19f;
	mpHunmerCollision = new Box(mpHunmerCollisionPos, 0.3f, 0.25f);
	//トドメのプラグ生成
	mpPlag = new Plag(this->mcVec.x + 0.35f, this->mcVec.y + 0.1f);
	mpPlag->SetSize(0.25f, 0.25f);
	mBossDownFlg = false;

	//ハンマー振り下ろし時に飛ばす衝撃波の初期設定
	mpWaves = new BoxObject();
	LoadTexture(L"assets/ShockWave.png", &mWavesTex);
	mpWaves->GetAnimSprite()->SetAnimtionTable(1, 1);
	mpWaves->GetAnimSprite()->SetTexture(mWavesTex);
	mpWaves->SetDrawActiv(false);
	//衝撃波の位置、拡縮の初期設定
	mcWavesScale.x = 0.25f;
	mcWavesScale.y = 0.18f;
	mcWavesPos.x = mcVec.x - 0.2f;
	mcWavesPos.y = -0.7f;
	mpWaves->SetSize(mcWavesScale.x, mcWavesScale.y);
	//mpWaves->SetScale(0.2f,0.2f);
	WaveMoveFlg = false;



	//地面から生えるがれきを生成
	mpdebris = new BoxObject();
	//がれきのテクスチャを設定
	LoadTexture(L"assets/debris.png", &mdebrisTex);
	mpdebris->GetAnimSprite()->SetAnimtionTable(1, 1);
	mpdebris->GetAnimSprite()->SetTexture(mdebrisTex);
	mpdebris->SetDrawActiv(false);
	//がれきの位置、拡縮の初期設定
	mcdebreisScale.x = 0.25f;
	mcdebreisScale.y = 0.25f;
	mcdebreisPos.x = mcVec.x - 0.55f;
	mcdebreisPos.y = -1.0f;
	mpdebris->SetSize(mcdebreisScale.x, mcdebreisScale.y);
	mpdebris->SetScale(1.0f, 1.0f);

	mSwingFlg = false;

	ShakeTime = 0;

	AliveFlg = true;

	//ボスの点滅処理に関する初期化
	DamageFlg = false;//Setterでtrue→点滅処理終了時にfalseに戻す
	AlphaFlg = false;
	mCtrShakeFlg = 0;
	Alpha = 0.0f;
	AlphaCnt = 8;//点滅した回数
}

Necthor::~Necthor()
{
	delete mpdebris;
	delete mpPlag;
	delete mpBodyCollision;
	delete mpHeadCollision;
	delete mpHunmerCollision;
	
	if (mpWaves != nullptr) 
	{
		delete mpWaves;
	}
	COM_SAFE_RELEASE(mTmpTex);
	COM_SAFE_RELEASE(mAtkTex);
	COM_SAFE_RELEASE(mWavesTex);
}

void Necthor::Update()
{
	//==ボス自身の処理=========================================
	if (mBossDownFlg == false)//ボスの体力が残ってる状態ならハンマー振り下ろし処理を行う
	{
		if (mChargeTime > 0)
		{
			mChargeTime -= 1;//振り下ろしまでの時間を減らしていく
		}

		if (mChargeTime <= 0)//ハンマーを振り下ろす
		{

			if (mSwingFlg == false)
			{
				mSwingFlg = true;
				mcpAnimsprite->SetTexture(mAtkTex);
				mcpAnimsprite->SetAnimtionTable(9, 1);
				mcpAnimsprite->ResetAnimCnt();
				mChargeTime = 0;
			}
			else
			{
				if (mAttackCoolTime > 0)
				{
					mAttackCoolTime--;//振り下ろし後の硬直時間減少
					if (mAttackCoolTime < 492)
					{
						mCtrShakeFlg = 0;
						mpWaves->SetDrawActiv(true);
						WaveMoveFlg = true;
						mcpAnimsprite->SetStopAnimation(true);
						mpHeadCollisionPos.y = this->mcVec.y - 0.05f;

						//ハンマー振り下ろし時に画面を数秒揺らす
						if (mAttackCoolTime > 484)
						{
							CAMERA->StartVibration(1);
							mCtrShakeFlg = 1;
						}

					}
			

					//がれきが隆起する処理
					if (mcdebreisPos.y < -0.7f)
					{
						mcdebreisPos.x = mcVec.x - 0.55f;
						mpdebris->SetDrawActiv(true);						
						mcdebreisPos.y += 0.008f;
					}

					mpHunmerCollisionPos.x = this->mcVec.x - 0.22f;
					mpHunmerCollisionPos.y = this->mcVec.y - 0.22f;
				}
				else if (mAttackCoolTime <= 0)
				{
					mSwingFlg = false;
					mChargeTime = 60 * AtkCharge;//攻撃ため時間の値リセット
					mAttackCoolTime = 60 * StopTime;//硬直時間が無くなったので、初期値を代入
					mcpAnimsprite->ResetAnimCnt();
					mcdebreisPos.y -= 1.0f;//がれきを地中に戻す
					mpdebris->SetDrawActiv(false);


					//待機アニメーションに戻す、衝撃波を初期状態にリセット
					mcpAnimsprite->SetTexture(mTmpTex);
					mcpAnimsprite->SetAnimtionTable(5, 1);
					mcpAnimsprite->SetStopAnimation(false);
					WaveMoveFlg = false;
					mcWavesPos.x = mcVec.x - 0.13f;
					mpWaves->SetDrawActiv(false);

					mpHeadCollisionPos.y = this->mcVec.y + 0.1f;
				}
			}
		}
	}
	//=========================================================

	//=========================================================
	//ダメージを受けた時の処理
	if (mDamageCoolTime < 180 && mDamageCoolTime > 0)
	{
		mDamageCoolTime--;
	}

	if (mDamageCoolTime <= 0)
	{
		mDamageCoolTime = 180;
	}

	//ライフがなくなった時の処理
	if (mLife <= 0)
	{
		mLife = 0;//unsignedなので、負の数を取ることはないが、念のため0を代入
		if (mBossDownFlg == false)
		{
			this->mcpSprite->SetTexture(mTmpTex);
			mcpAnimsprite->SetAnimtionTable(5, 1);
			mcpAnimsprite->SetStopAnimation(true);
			mBossDownFlg = true;
			mSwingFlg = true;//ダウンしたので、ハンマーをおろしっぱなしにする
			mpHeadCollisionPos.x = this->mcVec.x + 0.09f;//頭の当たり判定を下に移動する
			mpHeadCollisionPos.y = this->mcVec.y - 0.035f;//頭の当たり判定を下に移動する

			mpHunmerCollisionPos.y = this->mcVec.y - 0.27f;
			mpdebris->SetDrawActiv(true);

			//当たり判定を縮め、位置調整
			mpBodyColisionPos.y = mpBodyColisionPos.y -= 0.03f;
			mpBodyCollision->SetSize(0.4f, 0.25f);

			mpHeadCollisionPos.y = mpHeadCollisionPos.y -= 0.02f;
			mpHeadCollision->SetSize(0.5f, 0.325f);
		}
		else
		{
			mpdebris->SetDrawActiv(false);

			if (mcdebreisPos.y <= -0.7f)
				mcdebreisPos.y += 0.1f;
		}
	}

	//ダメージを受けた時の点滅処理
	
	if (DamageFlg == true)
	{
		if (AlphaFlg == false)
			Alpha -= 0.2f;
		if (AlphaFlg == true)
			Alpha += 0.2f;

		if (Alpha <= 0.0f)
		{
			Alpha = 0;
			AlphaFlg = true;
		}
		if (Alpha >= 1.0f)
		{
			Alpha = 1.0f;
			AlphaFlg = false;
			AlphaCnt--;
		}

		mcpAnimsprite->SetArufa(Alpha);

		if (AlphaCnt < 0)//点滅処理の終了
		{
			DamageFlg = false;
			AlphaCnt = 8;
			Alpha = 1.0f;
		}
	}

	//=========================================================

	//=========================================================
	//がれきの処理
	//がれきの大きさを毎ループ調整
	mpdebris->SetSize(mcdebreisScale.x, mcdebreisScale.y);
	mpdebris->Update();
	mpdebris->SetVec(mcdebreisPos);
	//=========================================================

	//=========================================================
	//衝撃波の処理
	if (mpWaves != nullptr)
	{
		mpWaves->Update();
		mpWaves->SetSize(mcWavesScale.x, mcWavesScale.y);
		if (WaveMoveFlg == true) 
		{
			mcWavesPos.x -= 0.025f;
		}
		mpWaves->SetVec(mcWavesPos);
	}
	//=========================================================

	mpPlag->Update();

	//とどめを刺された時の振動処理
	if (!AliveFlg)
	{
		ShakeTime++;
		if (ShakeTime < 180)
		{
			CAMERA->StartVibration(2);
		}
		else if (ShakeTime > 180)
		{
			ShakeTime = 180;
		}
	}
}

void Necthor::Draw()
{
	//トドメのプラグに刺すまでは、Necthor関連の描画を行う
	if (AliveFlg == true)
	{
		GameObject::Draw();
		mpPlag->Draw();
		//体の当たり判定描画
		mcImage.DrawSprite(mpBodyColisionPos.x, mpBodyColisionPos.y, 0.4f, 0.32f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
		//頭の当たり判定描画
		mcImage.DrawSprite(mpHeadCollisionPos.x, mpHeadCollisionPos.y, 0.22f, 0.25f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
		//ハンマーの当たり判定描画
		mcImage.DrawSprite(mpHunmerCollisionPos.x, mpHunmerCollisionPos.y, 0.3f, 0.25f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
		//衝撃波の当たり判定
		mcImage.DrawSprite(mcWavesPos.x, mcWavesPos.y, mcWavesScale.x, mcWavesScale.y, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
	}
	//がれきの描画
	mpdebris->Draw();

	if (mpWaves != nullptr)
	{
		mpWaves->Draw();
	}

}

int Necthor::GetChargeTime()
{
	return mChargeTime;
}

Box * Necthor::GetBossBodyCollision()
{
	return mpBodyCollision;
}

Box * Necthor::GetBossHeadCollision()
{
	return mpHeadCollision;
}

Box * Necthor::GetBossHunmerCollision()
{
	return mpHunmerCollision;
}

Plag * Necthor::GetPlag()
{
	return mpPlag;
}

void Necthor::SetChargeTime(int _Time)
{
	mChargeTime = _Time;
}

void Necthor::AddChargeTime(int _Time)
{
	mChargeTime += _Time;
}

void Necthor::AddLife(int _Life)
{
	mLife += _Life;
}

bool Necthor::GetDownFlg()
{
	return mBossDownFlg;
}

unsigned int Necthor::GetmDamageCoolTime()
{
	return mDamageCoolTime;
}

void Necthor::SetmDamageCoolTime(unsigned int _Time)
{
	mDamageCoolTime = _Time;
}

bool Necthor::GetAliveFlg()
{
	return AliveFlg;
}

void Necthor::SetAliveFlg(bool _Flg)
{
	AliveFlg = _Flg;
}

BoxObject * Necthor::GetmpDebriesBox()
{
	return mpdebris;
}

BoxObject * Necthor::GetmpWavesBox()
{
	return mpWaves;
}

void Necthor::SetDamageFlg(bool _Flg)
{
	DamageFlg = _Flg;
}

unsigned int Necthor::GetCtrShakeFlg()
{
	return mCtrShakeFlg;
}
