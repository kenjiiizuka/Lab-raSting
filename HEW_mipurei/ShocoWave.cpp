#include "ShocoWave.h"
#include "TextureManager.h"


//! コンストラクタ
ShockWave::ShockWave()
{
	ColSize = Vector2(0.16f,0.1f);
	mcpBox = new Box(ColPos, ColSize.x, ColSize.y);
	SetSize(0.4f,0.4f);
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_ShockWave));
	mcpAnimsprite->SetAnimtionTable(1, 1);

	//! 最初は描画しない
	SetDrawActiv(false);
	ColPos.x = mcVec.x;
	ColPos.y = mcVec.y - 0.1f;
}

//! デストラクタ
ShockWave::~ShockWave()
{
	delete mcpBox;
}

void ShockWave::Update()
{
	if (Act) {
		SetDrawActiv(true);
		mcVec.x -= speed;
		float dis = fabs(mcVec.x - InitPos.x);

		//! ある程度すすんだら透明にしていく
		if (dis > 1.0f) {
			Arufa -= 0.05f;
			speed -= 0.0001f;
		}

		if (TailHit) {
			Act = false;
		}
		if (dis > 1.4f) {
			Act = false;
		}

		//! 当たり判定をオン
		ColPos.x = mcVec.x;
		ColPos.y = mcVec.y - 0.1f;
		if (Arufa >= 0.2f) {
			mcpBox->SetActiv(true);
		}
		else {
			mcpBox->SetActiv(false);
		}
	}
	else {
		TailHit = false;
		SetDrawActiv(false);
		mcpBox->SetActiv(false);
	}
}

void ShockWave::Draw()
{
	mcpAnimsprite->SetArufa(Arufa);
	GameObject::Draw();
	//gImage.DrawSprite(ColPos.x,ColPos.y,ColSize.x, ColSize.y,TEXTURE(Tex_PanelBl),1,1,1,0.5f);
}

void ShockWave::ShockWaveStart(Vector2 _pos)
{
	if (!Act) {
		Act = true;
		InitPos = mcVec = _pos;
		Arufa = 1.0f;
		speed = 0.02f;
	}
}

void ShockWave::SetHit(bool _hit)
{
	TailHit = _hit;
}

Box * ShockWave::GetCol()
{
	return mcpBox;
}
