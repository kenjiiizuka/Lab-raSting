
#include "Enemy.h"
#include "TextureManager.h"
#include "DirectInput8.h"

//! �R���X�g���N�^
EnemyProt::EnemyProt()
{
	//! �q�b�g�X�g�b�v
	mcpHitStop = new HitStop(this);
	//! �t���O�̏�����
	LiveFlg = true;
	MoveDirFlg = true;
	GetAttack = false;

	//! �摜��A�j���[�V�����A�X�e�[�^�X�̐ݒ�
	MoveDis = 0.001f;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! �����蔻��̃T�C�Y�̃Z�b�g
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! �G�l�~�[�摜�̃Z�b�g
}

EnemyProt::EnemyProt(float _x, float _y)
{
	mcVec = Vector2(_x, _y);

	//! �q�b�g�X�g�b�v
	mcpHitStop = new HitStop(this);
	//! �t���O�̏�����
	LiveFlg = true;
	MoveDirFlg = true;
	GetAttack = false;

	//! �摜��A�j���[�V�����A�X�e�[�^�X�̐ݒ�
	MoveDis = 0.001f;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! �����蔻��̃T�C�Y�̃Z�b�g
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! �G�l�~�[�摜�̃Z�b�g
}

//! �f�X�g���N�^
EnemyProt::~EnemyProt()
{
	//! �f���[�g
	delete mcpHitStop;
}

//! �X�V����
void EnemyProt::Update()
{

	//! �G���������Ă���ԓ���
	if (LiveFlg == true)
	{
		//! ��U�̃G���^�[�L�[�Ńq�b�g�X�g�b�v�@�������͂܂��ς���
		if (DI8->mKeyBoard->GetKeyTrigger(DIK_RETURN))
		{

			mcpHitStop->HitStopStart(50);		//! �q�b�g�X�g�b�v�t���O���I���ɂ���

		}

		//! �q�b�g�X�g�b�v�t���O���I���̏ꍇ

		mcpHitStop->HitStoptime();	//! �����ŕb������


		//! �q�b�g�X�g�b�v���N�����Ă��Ȃ��ԓ���
		if (mcpHitStop->HitStopFlg == false)
		{
			Move();
		}

	}

	//! �N���X�̍X�V����
	Character::Update();
}

//! �`�揈��
void EnemyProt::Draw()
{
	//! �N���X�̕`�揈��
	GameObject::Draw();
	Character::Draw();
}

void EnemyProt::Move()
{
	
	//! �G�̈ړ����������̏ꍇ
	if (MoveDirFlg == true)
	{
		mcMoveVector.x += 0.005f;	//! �������ւ̈ړ�
		MoveDis += 0.005f;			//! �ړ��ʂ̉��Z
		//! �ړ��ʂ���萔�𒴂����� 
		if (MoveDis >= 0.8f)
		{
			mcMoveVector.x -= 0.003f;	//! �������ւ̈ړ�
			MoveDis -= 0.003f;			//! �ړ��ʂ̌��Z
			MoveDirFlg = false;			//! �����ϊ�
		}
	}

	//! �G�̈ړ����������̏ꍇ
	if (MoveDirFlg == false)
	{
		mcMoveVector.x -= 0.005f;	//! �������ւ̈ړ�
		MoveDis -= 0.005f;			//! �ړ��ʂ̌��Z
		//! �ړ��ʂ���萔�𒴂�����
		if (MoveDis <= 0.0f)
		{
			mcMoveVector.x += 0.005f;	//! �������ւ̈ړ�
			MoveDis += 0.005f;			//! �ړ��ʂ̉��Z
			MoveDirFlg = true;			//! �����ϊ�
		}
	}

}
