#include "CheackBox.h"
#include "Collision.h"
#include "TextureManager.h"

//! コンストラクタ
CheackBox::CheackBox(Vector2 _pos,Vector2 _size)
{
	mcpSprite = new Sprite(mcVec);
	SetDrawActiv(false);
	mcVec = _pos;
	SetSize(_size.x, _size.y);
	MyHit = new Box(mcVec,_size.x, _size.y);
	mcpSprite->SetTexture(TEXTURE(Tex_PanelBl));
}


//! デストラクタ
CheackBox::~CheackBox()
{
	delete MyHit;
}

bool CheackBox::HitCheack(Character * object)
{
	if (BBH(*object->GetBoxCol(),*MyHit)) {
		return true;
	}
	return false;
}

void CheackBox::Collision(Character * obj)
{
	BBC(*obj->GetBoxCol(),*MyHit);
}
