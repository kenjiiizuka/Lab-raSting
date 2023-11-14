#include "Necthor_Allow.h"
#include "TextureManager.h"
#include <math.h>

Necthor_Allow::Necthor_Allow()
{
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Allow));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	SetSize(0.2f,0.2f);
	TotalYAdd = Arufa = 0.0f;
	AddY = 0.003f;	
	SetDrawActiv(false);
}

Necthor_Allow::~Necthor_Allow()
{
}

void Necthor_Allow::Update()
{
	if(AllowActiv) {
		AddArufa = 0.06f;
	}
	else {
		AddArufa = -0.06f;
	}
	Arufa += AddArufa;
	if (Arufa < 0.0f) {
		Arufa = 0.0f;
	}
	else if (Arufa > 1.0f) {
		Arufa = 1.0f;
	}

	//! ‚Ó‚í‚Ó‚í“®‚©‚·
	mcVec.y += AddY;
	TotalYAdd += fabs(AddY);
	if (TotalYAdd > 0.05f) {
		TotalYAdd = 0;
		AddY *= -1;
	}

	mcpAnimsprite->SetArufa(Arufa);
}

void Necthor_Allow::AllowOn(Vector2 _pos)
{
	SetDrawActiv(true);
	AllowActiv = true;
	mcVec = _pos;
}

void Necthor_Allow::AllowOff()
{
	SetDrawActiv(false);
	AllowActiv = false;
}
