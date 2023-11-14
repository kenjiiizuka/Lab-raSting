#include "StaticObject.h"

//! �R���X�g���N�^
StaticObject::StaticObject()
{

	mcpSprite = new Sprite(mcVec);	
	msSize = FLOAT2(0.2f, 0.2f);
}

//! �f�X�g���N�^
StaticObject::~StaticObject()
{
	delete mcpSprite;
	
}

//! ���W�̃Z�b�^�[
void StaticObject::SetPos(float _x, float _y)
{
	mcVec.x = _x;
	mcVec.y = _y;
}

void StaticObject::SetX(float _x)
{
	mcVec.x = _x;
}

void StaticObject::SetY(float _y)
{
	mcVec.y = _y;
}
