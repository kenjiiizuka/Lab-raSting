#include "ProtoAnimObj.h"
#include"TextureManager.h"
ProtoAnimObj::ProtoAnimObj()
{
	//mcpSprite->SetTexture(TexMgr->GetTextuer(Tex_Teki));
	
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpSprite = mcpAnimsprite;
	mcVec.x = 0.7f;
	mcVec.y = 0.0f;
	mcpSprite->SetSize(1.5f, 1.0f);
	mpCircle = new Circle(mcVec, 0.6f);
}

ProtoAnimObj::~ProtoAnimObj()
{
	delete mpCircle;
}

void ProtoAnimObj::Update()
{
	//‰~‚ð‘I‚Ô

}

void ProtoAnimObj::Draw()
{
	GameObject::Draw();
}

Circle * ProtoAnimObj::GetmpCircle()
{
	return mpCircle;
}
