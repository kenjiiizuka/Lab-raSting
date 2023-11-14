#include "Smoke.h"
#include "TextureManager.h"

//! コンストラクタ
Smoke::Smoke()
{
	State = SmokeState::State_None;
	Arufa = 0;

	SetSize(0.3f, 0.3f);
	mcpAnimsprite->SetAnimtionTable(3,4);
}

//! デストラクタ
Smoke::~Smoke()
{

}

//! 更新
void Smoke::Update()
{
	switch (State)
	{
	case State_FadeIn:
		Arufa += 0.02f;
		if (Arufa >= 1.0f) {
			Arufa = 1.0f;
			State = State_None;
		}
		SmokeActiv = true;
		break;

	case State_FadeOut:
		Arufa -= 0.01f;
		if (Arufa <= 0.0f) {
			Arufa = 0.0f;
			State = State_None;
			SmokeActiv = false;
			SetDrawActiv(false);
		}	
		break;
	case State_None:
		break;
	}

	mcpAnimsprite->SetArufa(Arufa); //! 透明度をセットする
}

//! 描画
void Smoke::Draw()
{
	GameObject::Draw();
}


void Smoke::NomalSmokeSmall(Vector2 _pos)
{
	mcVec = _pos;
	State = State_FadeIn;
	SetSize(0.3f, 0.3f);
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Smoke01));
	mcpAnimsprite->SetYSplit(2);
	SetDrawActiv(true);
}

void Smoke::LeftSmokeSmall(Vector2 _pos)
{
	mcVec = _pos;
	SetSize(0.3f, 0.3f);
	State = State_FadeIn;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Smoke02));
	mcpAnimsprite->SetYSplit(2);
	SetDrawActiv(true);
}

void Smoke::RightSmokeSmall(Vector2 _pos)
{
	mcVec = _pos;
	SetSize(0.3f, 0.3f);
	State = State_FadeIn;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Smoke03));
	mcpAnimsprite->SetYSplit(2);
	SetDrawActiv(true);
}

void Smoke::NomalSmokeRagular(Vector2 _pos)
{
	mcVec = _pos;
	SetSize(0.3f,1.0f);
	State = State_FadeIn;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Smoke01));
	mcpAnimsprite->SetYSplit(1);
	SetDrawActiv(true);
}

//! 煙を消す関数
void Smoke::SmokeOff()
{
	State = State_FadeOut;
	//mcpAnimsprite->SetYSplit(2);
}

bool Smoke::GetSmokeActiv()
{
	return SmokeActiv;
}
