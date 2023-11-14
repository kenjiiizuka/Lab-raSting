#include "TestChar.h"
#include "TextureManager.h"
#include "DirectInput8.h"

TestChar::TestChar()
{
	mcVec.x = -0.8f;
	//mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_nuko02));
	mcpAnimsprite->SetAnimtionTable(1, 1);
}

TestChar::~TestChar()
{

}

void TestChar::Update()
{
	static float speed;
	speed = 0.005f;
	if (DI8->mKeyBoard->GetKeyPress(DIK_CAPSLOCK)) {
		speed = 0.009f;
	}
	
	if (DI8->mKeyBoard->GetKeyPress(DIK_H)) {
		mcMoveVector.x -= speed;
	}
	if (DI8->mKeyBoard->GetKeyPress(DIK_K)) {
		mcMoveVector.x += speed;
	}

	if (DI8->mKeyBoard->GetKeyPress(DIK_U)) {
		mcMoveVector.y += speed;
	}
	if (DI8->mKeyBoard->GetKeyPress(DIK_J)) {
		mcMoveVector.y -= speed;
	}


	Character::Update();

}

void TestChar::Draw()
{
	GameObject::Draw();
	Character::Draw();	
}

void TestChar::FixUpdate()
{
	mcVec += mcpShape->GetPetration();
	mcpShape->SetPenetration(0,0);
	
}


