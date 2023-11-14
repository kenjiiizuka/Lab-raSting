#include "NormalEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

/* -----------
// �R���X�g���N�^�@*/
NormalEnemy::NormalEnemy()
{
	//! �A�j���[�V�����֌W
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! �G�l�~�[�摜�̃Z�b�g

	//! �U������H
	mcpShape->SetAttack(true);
	//! �^�O
	mTag = Tag_Enemy_Tinpillar;
	//! �X�s�[�h�̏����l�ݒ�
	BaseEnemy::SetMove(0.004);

	ColSize.x = ColSize.y = 0.28;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// �R���X�g���N�^ */
NormalEnemy::NormalEnemy(float _x,float _y)
{
	//! �����ʒu�̐ݒ�
	mcVec = Vector2(_x, _y);
	//! �A�j���[�V�����֌W
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! �G�l�~�[�摜�̃Z�b�g

	//! �U������H
	mcpShape->SetAttack(true);
	//! �^�O
	mTag = Tag_Enemy_Tinpillar;
	//! �X�s�[�h�̏����l�ݒ�
	BaseEnemy::SetMove(0.004);

	ColSize.x = ColSize.y = 0.28;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// �f�X�g���N�^ */
NormalEnemy::~NormalEnemy()
{
	//! ���ɏ������ƂȂ�
}

/* -----------
// �X�V���� */
void NormalEnemy::Update()
{
	//! �{�̂̍X�V
	BaseEnemy::Update();

	//! ���񂾂Ƃ��̏���
	if (!mAlive)
	{
		//! ��
		BaseEnemy::Destroy();
	}
	
}

/* -----------
// �`�揈�� */
void NormalEnemy::Draw()
{
	//! �{�̂̕`��
	if (!Status.MoveDirFlg)
	{
		mcpAnimsprite->SetYSplit(eDirection::Right);
	}
	if (Status.MoveDirFlg)
	{
		mcpAnimsprite->SetYSplit(eDirection::Left);
	}
	BaseEnemy::Draw();
}

/* -----------
// �K���Ŏh���ꂽ�Ƃ��̋����Ə��� */
TailReaction NormalEnemy::SetStingPower(float _Power ,bool _Elect)
{
	Reaction = TailReaction_None;
	//! �G���G�͕��ʈȏ�Ŏ���(��)
	if (_Elect) {
		Stinged = true;
		mAlive = false;
		Reaction = TailReaction::TailReaction_Through;
		SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.07);
		EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.7f,0.7f));
	}
	else {
		if (_Power >= STING_STRONG)
		{
			//! ����
			Reaction = TailReaction_StingStop;
			Stinged = true;
			mAlive = false;
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
			//! �h���ꂽ��
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
		}
		else if (_Power >= STING_MIDIUME)
		{
			//! ����
			Reaction = TailReaction_StingStop;
			mAlive = false;
			Stinged = true;
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
			//! �h���ꂽ��
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
		}
	}
	return Reaction;
}

