#include "DirectInput8.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "BaseDrone.h"
#include "EffectManager.h"

/* -----------
// �R���X�g���N�^ */
BaseDrone::BaseDrone()
{
	mTag = ObjectTag::Tag_Drone;
	//! �����蔻��̑傫���Z�b�g
	ColSize = Vector2(0.3f, 0.3f);

	//! �A�j���[�V�����e�[�u��
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));	//! �G�l�~�[�摜�̃Z�b�g

	//! �t���O�֌W
	CarryFlg = true;	//! �^���t���O

	//! �����l�̐ݒ�
	mfSpeed = 0.008f;	//! �X�s�[�h�̏����l�ݒ�
	TotalMove = 0.0f;	//! ���ړ������̏����l
}

/* -----------
// �R���X�g���N�^ */
BaseDrone::BaseDrone(float _x, float _y)
{
	//! ���W�̃Z�b�g
	mcVec = Vector2(_x, _y);
	//! �����蔻��̑傫���Z�b�g
	ColSize = Vector2(0.3f, 0.3f);

	//! �A�j���[�V�����e�[�u��
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));	//! �G�l�~�[�摜�̃Z�b�g

	//! �t���O�֌W
	CarryFlg = true;	//! �^���t���O

	//! �����l�̐ݒ�
	mfSpeed = 0.008f;	//! �X�s�[�h�̏����l�ݒ�
	TotalMove = 0.0f;	//! ���ړ������̏����l
}
/* -----------
// �f�X�g���N�^ */
BaseDrone::~BaseDrone()
{

}
/* -----------
// �X�V���� */
void BaseDrone::Update()
{
	Fly();						//! ��s�ړ�
	mcpBoxCol->SetPrevVec(mcVec);       //! �O�t���[���̍��W�Ƃ��ĕۑ�����
	mcpShape->SetMoveVec(mcMoveVector); //! �����蔻��Ɏg�����߂̏����Z�b�g
	EnemyBase();						//! �G�̌Ăяo��
	mcMoveVector.SetVector(0, 0);        //! ���̃L�����N�^�[�ɂ������Ă���͂��O�ɂ���
	//! ��������ɃT�C�Y�Z�b�g
	mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
}

/* -----------
// �`�揈���@*/
void BaseDrone::Draw()
{
	GameObject::Draw();
}
/* -----------
// �G�̃Z�b�^�[ */
void BaseDrone::SetEnemy(BaseEnemy * _EnemyNo)
{
	//! �G�̃Z�b�g
	mcpEnemy = _EnemyNo;
	//! ������Ă����Ԃɂ���
	mcpEnemy->SetCarryFlg(true);
}

/* -----------
// ������Ă���G�̏��� */
void BaseDrone::EnemyBase()
{
	//! ������Ă����
	if (CarryFlg)
	{
		if (!mAlive)
		{
			mcMoveVector.x = 0;
		}
		//! �h���[���Ɠ�������������
		mcpEnemy->SetMoveVec(mcMoveVector);
	}
}

/* -----------
// �h���[���̈ړ��ƍs���̏��� */
void BaseDrone::Fly()
{
	//! �h���[���ƃv���C���[�Ƃ̋��������ɂȂ�����
	float px = mcPlayer->GetVec().x;
	if (fabs(mcVec.x - px) <= 1.9f)
	{
		//! �ǐՃt���O��true�ɂ���
		ChaseFlg = true;
	}

	//! �ǐՃt���O��true�̏ꍇ
	if (ChaseFlg)
	{
		mcMoveVector.x -= mfSpeed;	//! �X�s�[�h�̌��Z
		TotalMove -= fabs(mfSpeed);	//! ���ړ������̌��Z
		if (mAlive) {
			mcVec += mcMoveVector;		//! �ʒu�̈ړ�
		}
		//! �������ړ��@�^���t���Otrue �h���[�������t���Otrue�@�̏ꍇ
		if (TotalMove < -1.0f && CarryFlg && mAlive) {

			mfSpeed *= -1;		//! �ړ��ʂ𔽓]������	
			TotalMove = 0;		//! ���ړ������̏�����
			CarryFlg = false;	//! �����Ă��邩�ǂ����̃t���O��false��
			ChaseFlg = false;
			mcpEnemy->SetCarryFlg(false);	//! ��ɓ���
			
			//! �������o�O���������̂ŏC�����Ă����܂�
			//SetHitActiv(false); //! �߂�Ƃ��ɑ��̃h���[���Ȃǂɓ�����Ȃ��悤�ɂ��邽�߂ɓ����蔻����Ȃ����܂�
		}
		
		//if (TotalMove < -1.5f && !CarryFlg)
		//{
		//	//! ������0�ɂ��Ă��܂��Ǝ��ʂƂ��̏����ɖ��t���[������Ȃ��ł�
		//	//TotalMove = 0;		//! ���ړ������̏�����
		//	//���ʏ���
		//	BaseEnemy::Destroy();

		//}		
		//! ��������
		if (!mAlive)
		{
			if (CarryFlg)
			{
				BaseEnemy::Destroy();	//! �h���[���{�̂̏���
				mcpEnemy->Destroy();	//! ������Ă���G�̏���
			}
			else
			{
				BaseEnemy::Destroy();	//! �h���[���{�̂̏���
			}
			
		}
	}
}

bool BaseDrone::GetCarryFlg()
{
	return CarryFlg;
}

/* -----------
// �K���̎h�������擾�֐� */
TailReaction BaseDrone::SetStingPower(float _Power, bool _Elect)
{
	//! �h���[���͋���֌W�Ȃ��Ɏ���
	Reaction = TailReaction_None;
	if (mAlive) {
		if (_Elect) {
			//! ����
			Reaction = TailReaction_Through;
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
			EffMgr->PlayEffect(HitEffect02,mcVec,Vector2(0.7f,0.7f));
			mAlive = false;
			Stinged = true;
			mcpBoxCol->SetActiv(false);
		}
		else {
			if (_Power >= STING_STRONG)
			{
				//! ����
				Reaction = TailReaction_StingStop;
				SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
				mAlive = false;
				Stinged = true;
				mcpBoxCol->SetActiv(false);
			}
			else if (_Power >= STING_MIDIUME)
			{
				//! ����
				Reaction = TailReaction_StingStop;
				SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.1f);
				EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.7f, 0.7f));
				mAlive = false;
				Stinged = true;
				mcpBoxCol->SetActiv(false);
			}
		}
	}
	//! ���A�N�V������Ԃ�
	return Reaction;
}

