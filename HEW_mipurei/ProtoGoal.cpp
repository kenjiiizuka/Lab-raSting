#include "ProtoGoal.h"
#include"TextureManager.h"
ProtoGoal::ProtoGoal()
{
	LoadTexture(L"assets/Goal.png", &GoalTex);
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetTexture(GoalTex);
	msSize = { 0.6f,0.6f };
	mcpSprite = mcpAnimsprite;
	this->mcVec.x = 0.0f;
	this->mcVec.y = 0.0f;
	GoalColiPos = this->mcVec;
	GoalColiPos.y = GoalColiPos.y - 0.18f;
	mpGoalCollisionBox = new Box(GoalColiPos, 0.3f, 0.1f);
	FirstStabFlg = false;
	SecondStabFlg = false;
}
ProtoGoal::ProtoGoal(float _X,float _Y)
{
	LoadTexture(L"assets/Goal.png", &GoalTex);
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetTexture(GoalTex);
	msSize = { 0.6f,0.6f };
	mcpSprite = mcpAnimsprite;
	this->mcVec.x = _X;
	this->mcVec.y = _Y;
	GoalColiPos = this->mcVec;
	GoalColiPos.y = GoalColiPos.y - 0.18f;
	mpGoalCollisionBox = new Box(GoalColiPos,0.3f,0.1f);
	FirstStabFlg = false;
	SecondStabFlg = false;
}

ProtoGoal::~ProtoGoal()
{
	COM_SAFE_RELEASE(GoalTex);
	delete mpGoalCollisionBox;
}

void ProtoGoal::Update()
{
}

void ProtoGoal::Draw()
{
	GameObject::Draw();
	mcImage.DrawSprite(GoalColiPos.x, GoalColiPos.y, 0.3f, 0.1f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.8f);

}

Box * ProtoGoal::GetmpGoalBox()
{
	return mpGoalCollisionBox;
}

bool ProtoGoal::GetFirstStabFlg()
{
	return FirstStabFlg;
}

void ProtoGoal::SetFirstStabFlg(bool _Flg)
{
	FirstStabFlg = _Flg;
}

bool ProtoGoal::GetSecondStabFlg()
{
	return SecondStabFlg;
}

void ProtoGoal::SetSecondStabFlg(bool _Flg)
{
	SecondStabFlg = _Flg;
}
