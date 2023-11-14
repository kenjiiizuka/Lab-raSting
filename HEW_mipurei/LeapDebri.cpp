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
	Vector2 Pos(0,0); //! �����^������0����̈ʒu
	float Gravtiy = 0;
	float ySpeed = 0;
	switch (State)
	{
	case State_Leap:
		SetDrawActiv(true);
		//! �ړ��̏���
		//! �d�̗͂͂̌v�Z
		Gravtiy = -ga * pow(PrevTime, 2) / 2.0f; //! �d�͂ɂ�鉺�����̗͂̌v�Z	�~���b�ł̌v�Z�Ȃ̂�1000�Ŋ���
		if (Gravtiy >= 0.02f) {
			Gravtiy = 0.02f;
		}	
		//! �d�͂̉e���̍ő�l�𒴂��Ȃ��悤�ɂ���
		if (Gravtiy >= 0.02f) {
			Gravtiy = 0.02f;
		}	
		mcVec.x -= Speed.x;
		ySpeed = Speed.y + Gravtiy;
		mcVec.y += ySpeed;
		PrevTime += (1.0f / 60.0f);
		//! �ō����B�_�ɂȂ����瓖���蔻��I��
		if (ySpeed <= 0) {
			AtkCol->SetActiv(true); //! �U���̔�����I��
		}
		if (mcVec.y <= -0.72f && ySpeed <= 0) {
			State = State_Ground;
			mcVec.y = -0.70f;
		}
		
		break;
	case State_Ground:
		Col->SetActiv(true);    //! �Փ˂̔�����I��
		AtkCol->SetActiv(false); //! �U���̔�����I�t
		//! �����ŏ�����܂ł̃J�E���g
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
