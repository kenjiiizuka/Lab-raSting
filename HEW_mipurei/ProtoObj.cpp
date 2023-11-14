#include "ProtoObj.h"
#include"TextureManager.h"
#include"Input.h"
ProtoObj::ProtoObj()
{
	mcVec.x = -1.0f, mcVec.y = -0.74f;//キャラの位置初期値設定
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_ProtoChara));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetSize(0.5f, 0.5f);
	mpBox = new Box(mcVec,0.25f,0.2f);
}

ProtoObj::~ProtoObj()
{
	delete mpBox;
}

void ProtoObj::Update()
{
	//プレイヤー移動
	if (In->GetKeyDownPress(VK_RIGHT) == TRUE)
	{
		mcVec.x += 0.015f;
	}
	else if (In->GetKeyDownPress(VK_LEFT) == TRUE)
	{
		mcVec.x -= 0.015f;
	}
	//UPとDownはselectcursorクラスで使ってるので、のちに修正する
	else if (In->GetKeyDownPress(VK_UP) == TRUE)
	{
		mcVec.y += 0.015f;
	}
	else if (In->GetKeyDownPress(VK_DOWN) == TRUE)
	{
		mcVec.y -= 0.015f;
	}
}

void ProtoObj::Draw()
{
	GameObject::Draw();
	Character::Draw();//コリジョンボックス表示
}

//Vector2* ProtoObj::GetVec2()
//{
//	return &mcVec;
//}

void ProtoObj::AddVec2(float _x, float _y)
{
	mcVec.x += _x;
	mcVec.y += _y;
}

Box * ProtoObj::GetmpBox()
{
	return mpBox;
}
