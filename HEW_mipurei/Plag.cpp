#include "Plag.h"
#include"TextureManager.h"
Plag::Plag(float _x, float _y)
{
	//Plag�̏����ʒu
	this->mcVec.x = _x;
	this->mcVec.y = _y;
	this->msSize.x = 0.7f;
	this->msSize.y = 0.7f;

	//�����蔻��̃Z�b�g(�΂����ۂ̃R���Z���g)
	mpPlagColisionPos.x = this->mcVec.x;
	mpPlagColisionPos.y = this->mcVec.y;
	mpPlagCollision = new Box(mpPlagColisionPos, 0.2f, 0.32f);

	//Plag�̃e�N�X�`���ǂݍ���
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
