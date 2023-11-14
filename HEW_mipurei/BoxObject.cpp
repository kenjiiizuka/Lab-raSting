#include "BoxObject.h"
#include "TextureManager.h"

//!  コンストラクタ
BoxObject::BoxObject()
{
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpBoxCol = new Box(mcVec,msSize.x, msSize.y);
	mcpShape = mcpBoxCol;
}

//! コンストラクタ　引数あり
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

//! 更新処理
void BoxObject::Update()
{
	mcpBoxCol->SetSize(msSize.x * msScale.x, msSize.y * msScale.y);
}


//! 矩形の当たりのゲッター
Box * BoxObject::GetBoxCol()
{
	return mcpBoxCol;
}
