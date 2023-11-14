#include "Command.h"
#include "TextureManager.h"
#include "Collision.h"
#include "SoundManager.h"

//! �R���X�g���N�^
Command::Command()
{
	GameObject::SetSize(0.4f, 0.2f);
	Arufa = 0;
	DefaultSize = msSize;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_PanelBl));
	mcpAnimsprite->SetArufa(Arufa);
	mcpAnimsprite->SetAnimtionTable(1, 1);
	CurrentHit = PrevHit = false;

	//! �����蔻��̐���
	mcpBox = new Box(mcVec,msSize.x, 0.3f);
	mcpShape = mcpBox;

	Bg = new AnimationHitObject;
	Bg->GetAnimSprite()->SetTexture(TEXTURE(Tex_CommmandOpen)); //! �摜�̃Z�b�g
	Bg->GetAnimSprite()->SetAnimtionTable(8, 1);
	Bg->SetSize(0.7f, 0.25f);
	Bg->GetAnimSprite()->SetNoStopObj(true);
	
}

//! ��������R���X�g���N�^
Command::Command(ID3D11ShaderResourceView * _tex)
{
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetTexture(_tex);
	GameObject::SetSize(0.6f, 0.3f);
	DefaultSize = msSize;
	//! �����蔻��̐���
	mcpBox = new Box(mcVec, msSize.x, msSize.y);
	mcpShape = mcpBox;

	Bg = new AnimationHitObject;
	Bg->GetAnimSprite()->SetTexture(TEXTURE(Tex_CommmandOpen)); //! �摜�̃Z�b�g
	Bg->GetAnimSprite()->SetAnimtionTable(6,1);
	Bg->SetSize(1.6f,1.0f);
	Bg->GetAnimSprite()->SetNoStopObj(true);


}

//! �f�X�g���N�^
Command::~Command()
{
	delete mcpBox;
	delete Bg;
}

//! �X�V����
void Command::Update()
{
	AnimationSprite * Sp = Bg->GetAnimSprite();
	Bg->SetVec(mcVec);
	int AnimX = Sp->GetCurrentXSplit();
	if (AnimX == 7) {
		Bg->GetAnimSprite()->SetNoStopObj(false);
		Bg->GetAnimSprite()->SetStopAnimation(true);
		//Opned = true;
	}
	if (AnimX == 5) {
		Opned = true;
	}
	
	if (Close) {
		if (AnimX == 7) {
			Bg->GetAnimSprite()->SetNoStopObj(false);
			Bg->GetAnimSprite()->SetStopAnimation(true);
			Closed = true;
		}
	}

	//! �Ђ炫�؂�����R�}���h�̖��x���グ��
	if (Opned) {
		if (Arufa < 1.0f) {
			Arufa += 0.05f;
		}
		else {
			Opned = false;
		}
	}
	if (Close) {
		if (Arufa > 0.0f) {
			Arufa -= 0.2f;
		}
	}
	mcpAnimsprite->SetArufa(Arufa);

	//! �J�[�\�����G��Ă��邩�ǂ����𔻒f����		
	PBH(*mcpCursol->GetShape(), *mcpBox, CurrentHit);
	
	if (CurrentHit) {
		if (!PrevHit) { //! �O�t���[���ɓ������Ă��Ȃ�������
			SoundMgr->PlaySE(SE_Button01,0.2f);
		}
		if (msSize.x < DefaultSize.x + 0.03f) {
			msSize.x += 0.01f;
		}
		if (msSize.y < DefaultSize.y + 0.02f) {
			msSize.y += 0.006f;
		}
	}
	else {
		if (msSize.x > DefaultSize.x) {
			msSize.x -= 0.01f;
		}
		if (msSize.y > DefaultSize.y) {
			msSize.y -= 0.006f;
		}
	}
	PrevHit = CurrentHit;
}

void Command::Draw()
{
	Bg->Draw();
	GameObject::Draw();
}

bool Command::Selected()
{
	if (CurrentHit && mcpCursol->Select()) {
		//! �����Ō��艹��炷
		return true;
	}
	return false;
}

void Command::SetVec(Vector2 _vec)
{
	Bg->SetVec(_vec);
	mcVec = _vec;
}

void Command::SetCursol(Cursol * _cursol)
{
	mcpCursol = _cursol;
}

void Command::SetSize(float _x, float _y)
{
	msSize = { _x, _y };
	DefaultSize = msSize;
}

void Command::SetClose(bool _close)
{
	//! ���ݕ��Ă��Ȃ��āA����悤�ɃZ�b�g���ꂽ��摜�̐؂�ւ��A�A�j���[�V�����̃��Z�b�g
	if (!Close && _close) {
		Close = _close;
		Bg->GetAnimSprite()->SetTexture(TEXTURE(Tex_CommmandClose));
		Bg->GetAnimSprite()->ResetAnimCnt();
		Bg->GetAnimSprite()->SetNoStopObj(true);
		Bg->GetAnimSprite()->SetStopAnimation(false);
	}	
}

bool Command::GetClosed()
{
	return Closed;
}

Vector2 Command::GetNextCommandPos()
{
	return Vector2(mcVec.x,mcVec.y - msSize.y - 0.05f);
}

AnimationHitObject * Command::GetFrame()
{
	return Bg;
}
