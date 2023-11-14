#include "PlayerSmoke.h"
#include "TextureManager.h"


PlayerSmoke::PlayerSmoke()
{
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_Smoke));
	mcpAnimsprite->SetAnimtionTable(10,1);
	SetSize(0.5,0.5);
	SetDrawActiv(false);
}

PlayerSmoke::~PlayerSmoke()
{

}

void PlayerSmoke::Update()
{

}

void PlayerSmoke::Draw()
{
	GameObject::Draw();
}

void PlayerSmoke::SmokeStart(Vector2 _pos)
{
	mcVec = _pos;
	SetDrawActiv(true);
}

void PlayerSmoke::SmokeStop()
{
	SetDrawActiv(false);
}
