#include "Debri.h"
#include "TextureManager.h"


//! コンストラクタ
NecthorDebri::NecthorDebri()
{
	mcpBox = new Box(mcVec, 0.2f,0.2f);
	Arufa = totalUp = 0;
	
	SetSize(0.2f,0.2f);
	//! 描画関連の設定
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Debri));
	mcpAnimsprite->SetAnimtionTable(1, 1);

	State = State_None;
	mcpBox->SetActiv(false);
}

//! デストラクタ
NecthorDebri::~NecthorDebri()
{
	delete mcpBox;
}

//! 更新処理
void NecthorDebri::Update()
{
	switch (State)
	{
	case NecthorDebri::State_Up:
		Up();
		break;
	case NecthorDebri::State_Fadeout:
		Fadeout();
		break;
	case NecthorDebri::State_None:
	
		break;		
	}
}


//! 描画処理
void NecthorDebri::Draw()
{
	mcpAnimsprite->SetArufa(Arufa);
	GameObject::Draw();
}

//! がれきが出てくる関数
void NecthorDebri::UpStart(Vector2 _initpos, bool _drawstate)
{	
	//! 消えながら出てくることをはないのでNoneの時だけ
	if (State == State_None) {
		State = State_Up;
		mcVec = _initpos;
		SetDrawActiv(_drawstate);
	}
}

//! がれきが消える関数
void NecthorDebri::FadeoutStart()
{
	State = State_Fadeout;
}

Box * NecthorDebri::GetCol()
{
	return mcpBox;
}

void NecthorDebri::Up()
{
	//! 当たり判定をオン
	mcpBox->SetActiv(true);
	
	Arufa = 1.0f;
	mcVec.y += 0.01f; //! がれきなので一気に上に出る感じにしたい
	totalUp += 0.01f;
	if (totalUp >= 0.2f) {
		State = State_None;
		totalUp = 0;
	}	
}

void NecthorDebri::Fadeout()
{
	mcpBox->SetActiv(false);
	Arufa -= 0.02f;
	if (Arufa <= 0) {
		State = State_None;
	}

}
