#include "BossHunmer.h"
#include"TextureManager.h"
#include"Angle.h"

BossHunmer::BossHunmer(float _x,float _y)
{
	// 初期値にボスから離れた位置を設定、ハンマーの大きさを設定
	this->mcVec.x = _x;
	this->mcVec.y = _y;
	this->msSize.x = 0.7f;
	this->msSize.y = 0.7f;

	HunmerColiScale.x = 0.4f;
	HunmerColiScale.y = 0.2f;

	mpHunmerColiPos = this->mcVec;

	mpHunmer = new Box(mpHunmerColiPos, HunmerColiScale.x, HunmerColiScale.y);//低く横幅が大きいBox

	mcRodPos.x = -0.2f;
	mcRodPos.y = -0.3f;
	mcRodColiScale.x = 0.2f;
	mcRodColiScale.y = 0.5f;
	mpRod = new Box(mcRodPos, mcRodColiScale.x, mcRodColiScale.y);//細長いBox

	//ハンマーのスプライト読み込み
	LoadTexture(L"assets/BossHunmer_Big.png", &mHunmerTex);
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetTexture(mHunmerTex);
	mcpSprite = mcpAnimsprite;

	mcdebreisScale.x = 0.25f;
	mcdebreisScale.y = 0.25f;
	mcdebreisPos.x = mcVec.x-0.55f;
	mcdebreisPos.y = -1.0f;

	mpdebris = new BoxObject(mcdebreisPos.x, mcdebreisPos.y);
	LoadTexture(L"assets/debris.png", &mdebrisTex);
	mpdebris->GetAnimSprite()->SetAnimtionTable(1,1);
	mpdebris->GetAnimSprite()->SetTexture(mdebrisTex);
	mpdebris->SetSize(mcdebreisScale.x, mcdebreisScale.y);
	mpdebris->SetScale(1.0f,1.0f);
}

BossHunmer::~BossHunmer()
{
	COM_SAFE_RELEASE(mHunmerTex);
	COM_SAFE_RELEASE(mdebrisTex);
}

void BossHunmer::Update(float _x, float _y, int _AtkTime, bool _AtkFlg)
{
	// 親であるAlphaボスの位置情報を受け取ってから、ハンマー自身の処理を開始
	this->mcVec.x = _x;
	this->mcVec.y = _y;

	// がれきの大きさを毎ループ調整
	mpdebris->SetSize(mcdebreisScale.x, mcdebreisScale.y);
	mpdebris->Update();//

	if (_AtkFlg == false)//ハンマー構えの処理
	{
		this->mcpSprite->SetAngle(DegreeToRadian(0), 0.5f, 0.3f);
		this->mcVec.x = _x;
		this->mcVec.y = _y;
		//==================================
		//ハンマー当たり判定の位置設定
		mpHunmerColiPos.x = -0.2f;
		mpHunmerColiPos.y = -0.25f;
		HunmerColiScale.x = 0.5f;
		HunmerColiScale.y = 0.2f;
		mpHunmer->SetSize(HunmerColiScale.x, HunmerColiScale.y);
		//==================================

		//==================================
		//持ち手の当たり判定の位置設定
		mcRodColiScale.x = 0.2f;
		mcRodColiScale.y = 0.4f;
		mcRodPos.x = -0.2f;
		mcRodPos.y = -0.6f;
		mpRod->SetSize(mcRodColiScale.x, mcRodColiScale.y);
		//==================================

		if (mcdebreisPos.y > -1.0f) 
		{ 
			mcdebreisPos.y -= 0.02f;
		}
	}
	else //おろした後のハンマー処理
	{
		this->mcpSprite->SetAngle(DegreeToRadian(90), 0.5f, 0.3f);
		this->mcVec.x = _x-0.2f;
		this->mcVec.y = _y-0.28f;

		//==================================
		//ハンマー当たり判定の位置設定
		HunmerColiScale.x = 0.25f;
		HunmerColiScale.y = 0.5f;
		mpHunmerColiPos.x = -0.575f;
		mpHunmerColiPos.y = -0.6f;
		mpHunmer->SetSize(HunmerColiScale.x, HunmerColiScale.y);
		//==================================

		//==================================
		//持ち手の当たり判定の位置設定
		mcRodColiScale.x = 0.6f;
		mcRodColiScale.y = 0.2f;
		mcRodPos.x = -0.145f;
		mcRodPos.y = -0.6f;
		mpRod->SetSize(mcRodColiScale.x, mcRodColiScale.y);
		//==================================

		if (mcdebreisPos.y < -0.7f)
		{
			mcdebreisPos.y += 0.008f;
		}
	}
	mpdebris->SetVec(mcdebreisPos);
}

void BossHunmer::Draw()
{
	GameObject::Draw();
	mpdebris->Draw();

	//if(Aliving==false)//これでキャラが倒されたときに処理が止まる

	//ハンマーの本体の当たり判定Box描画
	//mcImage.DrawSprite(mpHunmerColiPos.x, mpHunmerColiPos.y, HunmerColiScale.x, HunmerColiScale.y,TexMgr->GetTextuer(Tex_PanelBl),1.0f,1.0f,1.0f,0.5f);
	//ハンマー持ち手のBox描画
	//mcImage.DrawSprite(mcRodPos.x, mcRodPos.y, mcRodColiScale.x, mcRodColiScale.y, TexMgr->GetTextuer(Tex_PanelBl), 0.0f, 1.0f, 1.0f, 0.25f);
	//
}

Box * BossHunmer::GetmpHunmerBox()
{
	return mpHunmer;
}

Box * BossHunmer::GetmpRodBox()
{
	return mpRod;
}

BoxObject * BossHunmer::GetmpDebriesBox()
{
	return mpdebris;
}
