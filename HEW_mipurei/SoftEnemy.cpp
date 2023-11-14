#include "SoftEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

/* -----------
// �R���X�g���N�^ */
SoftEnemy::SoftEnemy()
{
	//! �A�j���[�V�����֌W
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetAnimSpeed(12);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Soft));	//! �G�l�~�[�摜�̃Z�b�g
	//! �U������H
	mcpShape->SetAttack(true);
	//! �^�O
	mTag = Tag_Enemy_Soft;
	//! �X�s�[�h�̏����l�ݒ�
	BaseEnemy::SetMove(0.001);

	AnimFrm = 0;
	ColSize.x = 0.26f;
	ColSize.y = 0.34f;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// �R���X�g���N�^ */
SoftEnemy::SoftEnemy(float _x, float _y)
{
	//! �����ʒu�̐ݒ�
	mcVec = Vector2(_x, _y);
	//! �A�j���[�V�����֌W
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetAnimSpeed(12);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Soft));	//! �G�l�~�[�摜�̃Z�b�g
	//! �U������H
	mcpShape->SetAttack(true);
	//! �^�O
	mTag = Tag_Enemy_Soft;
	//! �X�s�[�h�̏����l�ݒ�
	BaseEnemy::SetMove(0.0015);

	AnimFrm = 0;
	ColSize.x = 0.26f;
	ColSize.y = 0.34f;
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
}

/* -----------
// �f�X�g���N�^ */
SoftEnemy::~SoftEnemy()
{
	//! ���ɏ������ƂȂ�
}

/* -----------
// �X�V���� */
void SoftEnemy::Update()
{
	//! �{�̂̍X�V
	BaseEnemy::Update();
	int AnimX = mcpAnimsprite->GetCurrentXSplit();
	if (AnimX == 5) {
		Stop = true;
		
	}
	//! �~�܂��Ă��鎞
	if (Stop) {
		AnimFrm++;
		mcpAnimsprite->SetStopAnimation(true);

		//! 5�b�~�܂�
		if (AnimFrm >= 30) {
			Stop = false;
			AnimFrm = 0;
			mcpAnimsprite->SetStopAnimation(false);
			mcpAnimsprite->ResetAnimCnt();
		}
	}

	//! ����ł��邩�̔��f
	if (!mAlive)
	{
		BaseEnemy::Destroy();
	}
}

/* -----------
// �`�揈�� */
void SoftEnemy::Draw()
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
	//! �{�̂̕`��
	BaseEnemy::Draw();
}

/* -----------
// �K���Ŏh���ꂽ�Ƃ��̋����Ə��� */
TailReaction SoftEnemy::SetStingPower(float _Power, bool _Elect)
{
	
	//!	���炩���G�͎キ�h���ꂽ���Ɏ���
	if (_Elect) {
		Reaction = TailReaction_Through;
		mAlive = false;		//! ��
		Stinged = true;
		SoundMgr->PlaySE(SE_Hoder_Sasaru, 0.1f);
		EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.7f,0.7f));
	}
	else if (mcpAnimsprite->GetCurrentXSplit() == 2 ||
		mcpAnimsprite->GetCurrentXSplit() == 3 || mcpAnimsprite->GetCurrentXSplit() == 4)
	{
		Reaction = TailReaction_Through;
		mAlive = false;		//! ��
		Stinged = true;
		SoundMgr->PlaySE(SE_Hoder_Sasaru, 0.1f);
		EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
	}

	else {
		if (_Power >= STING_STRONG)
		{
			//! ����
			Reaction = TailReaction_Bounce;
			SoundMgr->PlaySE(SE_Hoder_Haziku,0.07f);
			EffMgr->PlayEffect(Hibana, mcVec, Vector2(0.7f, 0.7f));
		}
		else if (_Power >= STING_MIDIUME)
		{
			//! ����
			mMidHitcount++;
			if (mMidHitcount < 2) {
				Reaction = TailReaction_Bounce;
				SoundMgr->PlaySE(SE_Hoder_Haziku, 0.07f);
				EffMgr->PlayEffect(Hibana, mcVec, Vector2(0.7f, 0.7f));
			}
			else {
				Reaction = TailReaction_Through;
				mAlive = false;		//! ��
				Stinged = true;
				SoundMgr->PlaySE(SE_Hoder_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
			}
		}	
	}

	//! �ア�ȊO�Ŏh���ꂽ�璵�˕Ԃ�

	return Reaction;

}
