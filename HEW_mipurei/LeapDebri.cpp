#include "LeapDebri.h"
#include <math.h>
#include "WinMain.h"
#include "TextureManager.h"
#include <Windows.h>

LeapDebri::LeapDebri()
{
	Col = new Box(mcVec,0.2f,0.2f);
	AtkCol = new Box(mcVec, 0.2f, 0.2f);
	AliveCnt = PrevTime = 0;
	SetSize(0.2f,0.2f);
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Debri));
	mcpAnimsprite->SetAnimtionTable(1,1);	
	TotalMoveMent_Y = 0;
}

LeapDebri::~LeapDebri()
{
	delete Col;
	delete AtkCol;
}

void LeapDebri::Update()
{
	Vector2 Pos(0,0); //! 放物運動中の0からの位置
	float Gravtiy = 0;
	float ySpeed = 0;
	switch (State)
	{
	case State_Leap:
		SetDrawActiv(true);
		//! 移動の処理
		//! 重力の力の計算
		Gravtiy = -ga * pow(PrevTime, 2) / 2.0f; //! 重力による下方向の力の計算	ミリ秒での計算なので1000で割る
		if (Gravtiy >= 0.02f) {
			Gravtiy = 0.02f;
		}	
		//! 重力の影響の最大値を超えないようにする
		if (Gravtiy >= 0.02f) {
			Gravtiy = 0.02f;
		}	
		mcVec.x -= Speed.x;
		ySpeed = Speed.y + Gravtiy;
		mcVec.y += ySpeed;
		PrevTime += (1.0f / 60.0f);
		//! 最高到達点になったら当たり判定オン
		if (ySpeed <= 0) {
			AtkCol->SetActiv(true); //! 攻撃の判定をオン
		}
		if (mcVec.y <= -0.72f && ySpeed <= 0) {
			State = State_Ground;
			mcVec.y = -0.70f;
		}
		
		break;
	case State_Ground:
		Col->SetActiv(true);    //! 衝突の判定をオン
		AtkCol->SetActiv(false); //! 攻撃の判定をオフ
		//! 自動で消えるまでのカウント
		AliveCnt++;
		if (AliveCnt >= 300) {State = State_None;}
		break;

	case State_None:
		if (Arufa > 0) {
			Arufa -= 0.01f;
		}
		AliveCnt = 0;
		PrevTime = 0;
		Col->SetActiv(false);
		AtkCol->SetActiv(false);
		SetDrawActiv(false);
		break;
	}

}

void LeapDebri::Draw()
{
	mcpAnimsprite->SetArufa(Arufa);
	GameObject::Draw();
}

void LeapDebri::Leap(Vector2 _InitPos, Vector2 _power)
{
	if (State == State_None) {
		State = State_Leap;
		mcVec = _InitPos;
		Arufa = 1.0f;
		Speed = _power;
		PrevTime = 0;	
		SetDrawActiv(true);
	}
}

void LeapDebri::Fadeout()
{
	State = State_None;
	Col->SetActiv(false);
	AtkCol->SetActiv(false);
	SetDrawActiv(false);
}

Box * LeapDebri::GetCol()
{
	return Col;
}

Box * LeapDebri::GetAtkCol()
{
	return AtkCol;
}
