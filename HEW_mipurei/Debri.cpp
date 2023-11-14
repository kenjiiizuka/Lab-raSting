#include "Debri.h"
#include "TextureManager.h"


//! �R���X�g���N�^
NecthorDebri::NecthorDebri()
{
	mcpBox = new Box(mcVec, 0.2f,0.2f);
	Arufa = totalUp = 0;
	
	SetSize(0.2f,0.2f);
	//! �`��֘A�̐ݒ�
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Debri));
	mcpAnimsprite->SetAnimtionTable(1, 1);

	State = State_None;
	mcpBox->SetActiv(false);
}

//! �f�X�g���N�^
NecthorDebri::~NecthorDebri()
{
	delete mcpBox;
}

//! �X�V����
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


//! �`�揈��
void NecthorDebri::Draw()
{
	mcpAnimsprite->SetArufa(Arufa);
	GameObject::Draw();
}

//! ���ꂫ���o�Ă���֐�
void NecthorDebri::UpStart(Vector2 _initpos, bool _drawstate)
{	
	//! �����Ȃ���o�Ă��邱�Ƃ��͂Ȃ��̂�None�̎�����
	if (State == State_None) {
		State = State_Up;
		mcVec = _initpos;
		SetDrawActiv(_drawstate);
	}
}

//! ���ꂫ��������֐�
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
	//! �����蔻����I��
	mcpBox->SetActiv(true);
	
	Arufa = 1.0f;
	mcVec.y += 0.01f; //! ���ꂫ�Ȃ̂ň�C�ɏ�ɏo�銴���ɂ�����
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
