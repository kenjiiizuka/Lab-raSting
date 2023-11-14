#include "BoxObject.h"
#include "TextureManager.h"

//!  �R���X�g���N�^
BoxObject::BoxObject()
{
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpBoxCol = new Box(mcVec,msSize.x, msSize.y);
	mcpShape = mcpBoxCol;
}

//! �R���X�g���N�^�@��������
BoxObject::BoxObject(float _x, float _y)
{
	mcVec.x = _x;
	mcVec.y = _y;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpBoxCol = new Box(mcVec, msSize.x, msSize.y);
	mcpShape = mcpBoxCol;
}

BoxObject::~BoxObject()
{
	delete mcpBoxCol;
}

//! �X�V����
void BoxObject::Update()
{
	mcpBoxCol->SetSize(msSize.x * msScale.x, msSize.y * msScale.y);
}


//! ��`�̓�����̃Q�b�^�[
Box * BoxObject::GetBoxCol()
{
	return mcpBoxCol;
}
