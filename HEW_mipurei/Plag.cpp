#include "Plag.h"
#include"TextureManager.h"
Plag::Plag(float _x, float _y)
{
	//Plagの初期位置
	this->mcVec.x = _x;
	this->mcVec.y = _y;
	this->msSize.x = 0.7f;
	this->msSize.y = 0.7f;

	//当たり判定のセット(対しっぽのコンセント)
	mpPlagColisionPos.x = this->mcVec.x;
	mpPlagColisionPos.y = this->mcVec.y;
	mpPlagCollision = new Box(mpPlagColisionPos, 0.2f, 0.32f);

	//Plagのテクスチャ読み込み
	LoadTexture(L"assets/AlphaPlag.png", &mPlagTex);
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetTexture(mPlagTex);
	mcpSprite = mcpAnimsprite;
}

Plag::~Plag()
{
}

void Plag::Update()
{
	
}

void Plag::Draw()
{
	GameObject::Draw();
	mcImage.DrawSprite(mpPlagColisionPos.x, mpPlagColisionPos.y, 
		mpPlagCollision->GetSize().x, mpPlagCollision->GetSize().y, TexMgr->GetTextuer(Tex_PanelBl),
		0.0f, 1.0f, 1.0f, 0.25f);

}

Box * Plag::GetPlagCollision()
{
	return mpPlagCollision;
}
