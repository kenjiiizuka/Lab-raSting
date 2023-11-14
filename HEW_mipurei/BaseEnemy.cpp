#include "BaseEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DirectInput8.h"

//! ��{�ƂȂ�G
BaseEnemy::BaseEnemy()
{
	//! �q�b�g�X�g�b�v
	mcpHitStop = new HitStop(this);
	//! �t���O�̏�����
	HitPlayer = false;
	ChaseFlg = false;
	Status.LiveFlg = true;
	Status.MoveDirFlg = false;
	Status.CarryMeFlg = false;
	Elect = false;
	Stinged = Deathed = Death = false;
	
	Reaction = TailReaction_None;
	//! �摜��A�j���[�V�����A�X�e�[�^�X�̐ݒ�
	Count = 0;
	Speed = 0;
	Status.MoveDis = Speed;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! �����蔻��̃T�C�Y�̃Z�b�g
}

BaseEnemy::BaseEnemy(float _x, float _y)
{
	mcVec = Vector2(_x, _y);

	//! �q�b�g�X�g�b�v
	mcpHitStop = new HitStop(this);
	//! �t���O�̏�����
	ChaseFlg = false;
	Status.LiveFlg = true;
	Status.MoveDirFlg = false;
	Status.CarryMeFlg = false;
	Stinged = Deathed = Death = false;
	Elect = false;
	Reaction = TailReaction_None;

	//! �摜��A�j���[�V�����A�X�e�[�^�X�̐ݒ�
	Count = 0;
	Speed = 0;
	Status.MoveDis = Speed;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! �����蔻��̃T�C�Y�̃Z�b�g
}

BaseEnemy::~BaseEnemy()
{
	//! �f���[�g
	delete mcpHitStop;
}

void BaseEnemy::Update()
{
	//! �G���������Ă���ԓ���
	if (mAlive)
	{
		//! �h���[���ƃv���C���[�Ƃ̋��������ɂȂ�����
		float px = mcPlayer->GetVec().x;
		if (fabs(mcVec.x - px) <= 1.8f)
		{
			//! �ǐՃt���O��true�ɂ���
			ChaseFlg = true;
		}

		//! ������Ă���Ԃ͓����Ȃ�
		if (!Status.CarryMeFlg)
		{

			if (ChaseFlg)
			{
				Move();
			}
		}
		else
		{
			SetTouchGround(true);
		}


	}
	//! �N���X�̍X�V����
	Character::Update();

}

void BaseEnemy::Draw()
{
	//! �N���X�̕`�揈��
	GameObject::Draw();
	//Character::Draw();
}

float BaseEnemy::SetMove(float _Speed)
{
	Speed = _Speed;

	return Speed;
}

void BaseEnemy::SetMoveVec(Vector2 _MoveVec)
{
	mcMoveVector = _MoveVec;
}

void BaseEnemy::SetPlayer(Player * _Player)
{
	mcPlayer = _Player;
}

void BaseEnemy::SetCarryFlg(bool _Carryme)
{
	Status.CarryMeFlg = _Carryme;
}


void BaseEnemy::Move()
{
	//! �G�̈ړ����������̏ꍇ
	if (Status.MoveDirFlg)
	{
		mcMoveVector.x += Speed;	//! �������ւ̈ړ�
		Status.MoveDis += Speed;			//! �ړ��ʂ̉��Z
		//! �ړ��ʂ���萔�𒴂����� 
		if (Status.MoveDis >= 0.0f)
		{
			mcMoveVector.x -= Speed;	//! �������ւ̈ړ�
			Status.MoveDis -= Speed;			//! �ړ��ʂ̌��Z
			Status.MoveDirFlg = false;			//! �����ϊ�
		}
	}

	//! �G�̈ړ����������̏ꍇ
	if (!Status.MoveDirFlg)
	{
		mcMoveVector.x -= Speed;	//! �������ւ̈ړ�
		Status.MoveDis -= Speed;			//! �ړ��ʂ̌��Z
		//! �ړ��ʂ���萔�𒴂�����
		if (Status.MoveDis <= -0.85f)
		{
			mcMoveVector.x += Speed;	//! �������ւ̈ړ�
			Status.MoveDis += Speed;			//! �ړ��ʂ̉��Z
			Status.MoveDirFlg = true;			//! �����ϊ�
		}
	}
}

void BaseEnemy::Destroy()
{
	SetHitActiv(false);		//! �����蔻�������
	if (Count <= 50)
	{
		if (!Deathed) {
			Death = true;
		}
		if (Elect)
		{
			if (Count == 10)
			{
				SoundMgr->PlaySE(SE_TaidenAtk, 0.15f);
			}
		}
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
	}
}


bool BaseEnemy::GetDeath()
{
	if (Death && !Deathed && Stinged) {
		Deathed = true;
		return true;
	}
	Stinged = false;
	return false;
}

void BaseEnemy::SetHitPlayer(bool _hit)
{
	HitPlayer = _hit;
}

TailReaction BaseEnemy::SetStingPower(float _Power, bool _Elect)
{
	if (_Elect)
	{
		Elect = _Elect;
	}
	

	if (_Power >= STING_STRONG || _Elect)
	{
		//! ����
		Reaction = TailReaction_Sting;
	}
	else if (_Power >= STING_MIDIUME)
	{
		//! ����
		Reaction = TailReaction_Stop;
	}
	else
	{
		//! �ア
		Reaction = TailReaction_Stop;
	}

	return Reaction;
}

