#include "Cursol.h"
#include "TextureManager.h"
#include "Controller.h"

Cursol::Cursol()
{
	mcpShape = new Shape(mcVec);
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Cursol));
	mcpAnimsprite->SetAnimtionTable(1, 1);
	SetSize(0.2f,0.2f);
}

Cursol::~Cursol()
{
	delete mcpShape;
}

void Cursol::Update()
{
	Vector2 Left = GetControllerLeftStick() * 1.4f;
	mcVec += Left;
}

Vector2 Cursol::GetSelectPos()
{
	if (GetControllerButtonTrigger(Button_A)) {
		return mcVec;
	}
	return Vector2(9000, 9000); //! Œˆ’è‚³‚ê‚Ä‚¢‚È‚¢‚Í‚ ‚Ù‚İ‚½‚¢‚È”’l‚ğ•Ô‚µƒ}ƒX
}

Shape * Cursol::GetShape()
{
	return mcpShape;
}

bool Cursol::Select()
{
	if (GetControllerButtonTrigger(Button_A)) {
		return true;
	}
	return false;
}
