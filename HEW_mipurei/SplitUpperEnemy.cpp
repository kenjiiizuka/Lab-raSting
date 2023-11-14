#include "SplitUpperEnemy.h"
#include "SoundManager.h"
#include "EffectManager.h"
#include "TextureManager.h"

//! �R���X�g���N�^
SplitUpperEnemy::SplitUpperEnemy(Vector2 _vec ,bool & _combi)
	: Combi(_combi)
{
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Splitter_Body));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcVec = Vector2(_vec.x, mcVec.y + 0.2f); //! �����ʒu�̐ݒ�
	mTag = Tag_Enemy_SplitU;
	SetSize(0.5f, 0.6f);
	Count = 0;
	ColSize = Vector2(0.25f, 0.24f);

	MyCol = new Box(SplitedColPos,ColSize.x,ColSize.y);
}

//! �f�X�g���N�^
SplitUpperEnemy::~SplitUpperEnemy()
{
	delete MyCol;
}

//! �X�V����
void SplitUpperEnemy::Update()
{
	//! �������Ă鎞�͎��g�̓����蔻������Ȃ�
	if (Combi) {
		MyCol->SetActiv(false);
		mTouchGraund = true;
	}
	else {
		MyCol->SetActiv(true);		
	}

	SplitedColPos.x = mcVec.x;
	SplitedColPos.y = mcVec.y + 0.03f;
	Character::Update();

	if (!mAlive) {
		BaseEnemy::Destroy();
		MyCol->SetActiv(false);
	}
}

//! �`�揈��
void SplitUpperEnemy::Draw()
{
	GameObject::Draw();	
}

void SplitUpperEnemy::SetMoveVec(Vector2 _move)
{
	mcMoveVector = _move;
}

void SplitUpperEnemy::FixVec(Vector2 _vec)
{
	mcVec = _vec;
}

Box * SplitUpperEnemy::GetBoxCol()
{
	return MyCol;
}

TailReaction SplitUpperEnemy::SetStingPower(float _Power, bool _Elect)
{
	if(!Combi){
		if (_Elect) {
			Reaction = TailReaction_Through;
			//! �h���ꂽ��
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02, Vector2(mcVec.x, mcVec.y + 0.05f), Vector2(0.5f,0.5f));
			mAlive = false;
			Stinged = true;
		}
		else {	
			if (_Power > STING_STRONG) {
				Reaction = TailReaction::TailReaction_StingStop;
				//! �h���ꂽ��
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, Vector2(mcVec.x, mcVec.y + 0.05f), Vector2(0.5f, 0.5f));
				mAlive = false;
				Stinged = true;
			}
			else if (_Power > STING_MIDIUME) {
				Reaction = TailReaction::TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.08f);
				EffMgr->PlayEffect(Hibana, Vector2(mcVec.x, mcVec.y + 0.05f), Vector2(0.4f, 0.4f));
			}
		}
	}
	return Reaction;
}

void SplitUpperEnemy::Destroy()
{
	SetHitActiv(false);		//! �����蔻�������
	if (Count <= 50)
	{
		//! �_�ł�����
		if ((Count % 20) <= 10) {
			SetDrawActiv(false);
		}
		else {
			mcpAnimsprite->SetColor(1.0f, 0.0f, 0.0f);
			SetDrawActiv(true);
		}
		Count++;
	}
	else
	{
		SetDrawActiv(false);	//! �摜������
		SetHitActiv(false);		//! �����蔻�������
	}
}



