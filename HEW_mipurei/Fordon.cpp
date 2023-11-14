#include "Fordon.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Angle.h"
#include "EffectManager.h"

//! �R���X�g���N�^
Fordon::Fordon()
{
	mTag = Tag_Fordon;
	Top = true;
	FormaionNum = 0;
	Movevec = mcVec;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));
	mcpAnimsprite->SetAnimtionTable(6,2);
	MoveRad = DegreeToRadian(MoveDeg);
}

//! �f�X�g���N�^
Fordon::~Fordon()
{
	if (Top) {
		for (int i = 0; 9 < Member.size(); i++) {
			Member[i].reset();
		}
		Member.clear();
	}
}

//! �X�V����
void Fordon::Update()
{
	float distance = 0.0f;
	//! �擪�ɂ���z�̏���	
	Update_Top();
	for (int i = 0; i < FormaionNum; i++) {
		if (i == 0) {
			distance = Member[i]->Movevec.PosToPos(Movevec);
			//! ������Ɨ���Ă���ړ�����
			if (distance > 0.138f) {
				float Angle = PositionRelationAngle(Member[i]->Movevec, Movevec);
				if (Atk) {
					Member[i]->mcMoveVector.x += cosf(Angle) * -AtkSpeed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -AtkSpeed;
				}
				else {
					Member[i]->mcMoveVector.x += cosf(Angle) * -Speed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -Speed;
				}
			}
			Member[i]->ForceProces();
		}
		else {
			distance = Member[i]->Movevec.PosToPos(Member[i - 1]->Movevec);
			//! ������Ɨ���Ă���ړ�����
			if (distance > 0.138f) {
				float Angle = PositionRelationAngle(Member[i]->Movevec, Member[i - 1]->Movevec);
				if (Atk) {
					Member[i]->mcMoveVector.x += cosf(Angle) * -AtkSpeed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -AtkSpeed;
				}
				else {
					Member[i]->mcMoveVector.x += cosf(Angle) * -Speed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -Speed;
				}
			}
			Member[i]->ForceProces();
		}
		if (!Member[i]->mAlive) {
			Member[i]->Destroy();
		}
	}
	if (!mAlive) {
		Destroy();
	}

}

void Fordon::Draw()
{	
	GameObject::Draw();
	if (Top) {
		mcpAnimsprite->SetColor(1.0f,0.5f,1.0f);
		for (int i = 0; i < FormaionNum; i++) {
			Member[i]->Draw();
		}
	}
}

void Fordon::CreateMenber(int _num)
{
	FormaionNum = _num;
	for (int i = 0; i < _num; i++) {
		std::unique_ptr<Fordon> member(new Fordon(false,FormaionNum));
		member->Top = false;
		member->SetVec(Vector2(mcVec.x + (0.14f * (i + 1)), mcVec.y));
		Member.emplace_back(std::move(member));
	}
}

int Fordon::GetNumMenber()
{
	return FormaionNum;
}

//! ���A�N�V������Ԃ��֐�
TailReaction Fordon::SetStingPower(float _Power, bool _Elect)
{
	TailReaction Reaction = TailReaction_None;

	if (_Elect) {
		Reaction = TailReaction_Through;
		SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.11f);
		mAlive = false;
		Stinged = true;	
		EffMgr->PlayEffect(HitEffect02, mcVec, Vector2(0.3f,0.3f));
	}
	else {
		if (_Power >= STING_STRONG) {
			Reaction = TailReaction_Through;
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.11f);
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.3f, 0.3f));
			mAlive = false;
			Stinged = true;
		}
		else if (_Power > STING_MIDIUME) {
			Reaction = TailReaction_Through;
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.11f);
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.3f, 0.3f));
			mAlive = false;
			Stinged = true;
		}
	}
	return Reaction;
}


Fordon * Fordon::GetMenber(int _index)
{
	return Member[_index].get();
}

void Fordon::SetInitVec(Vector2 _vec)
{
	SetVec(_vec);
	Movevec = mcVec;
	if (Top) {
		for (int i = 0; i < Member.size(); i++) {
			Member[i]->SetVec(Vector2(mcVec.x + (0.14f * (i + 1)), mcVec.y));
		}
	}
}

void Fordon::SetVec(Vector2 _vec)
{
	Vector2 dif = mcVec - _vec;
	mcVec = _vec;
	Movevec = _vec;
}

Vector2 Fordon::GetVec()
{
	if (mAlive) {
		return mcVec;
	}
	return Movevec;

}


//! ��������R���X�g���N�^
//! �����o�[�𐶐�����Ƃ��p�̃��m
Fordon::Fordon(bool _state , int _formation)
{
	Top = false;
	Moved = false;
	FormaionNum = _formation;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	MoveRad = DegreeToRadian(MoveDeg);
}


void Fordon::Update_Top()
{
	Move();
	ForceProces();
}

void Fordon::Update_Member(Vector2 _pos)
{
	
}


/* ----------
// �ړ��֐� */
void Fordon::Move()
{	
	Vector2 PlayerPos = mcPlayer->GetVec(); //!�v���C���[�̍��W�̎擾
	float Distance = fabs(PlayerPos.x - mcVec.x); //! �v���C���[�Ƃ̋������v�Z����
	//! ��������肢�Ȃ��Ȃ�A�ˌ��܂ł̎��Ԃ𐔂���(7�b�������炢)
	if (Distance < 1.6) {
		AtkIntervalCnt++;
		Atk = false;
		if (AtkIntervalCnt >= (4 * 60)) {
			Atk = true;
		}
	}

	//! �ˌ��J�n(�v���C���[�߂����Ĉړ���)
	if(Atk){
		float AngleToPlayer = PositionRelationAngle(PlayerPos, mcVec); //! �v���C���[�ɑ΂��Ă̊p�x�����߂�
		mcMoveVector.x += cosf(AngleToPlayer) * AtkSpeed;
		mcMoveVector.y += sinf(AngleToPlayer) * AtkSpeed;
		TotalMove += fabs((cosf(AngleToPlayer) * AtkSpeed) + (sinf(AngleToPlayer) * AtkSpeed));
		//! �Ȃɂ��ɓ���������ˌ�����߂�

		bool HitAny = false; //! �����ɓ����������͂񂾂񂷂�t���O
		//! �擪���Ȃɂ��ɂ����������𔻒f
		if (HitPlayer || mTouchGraund) {
			HitAny = true;
		}
		//! �擪���������Ă��Ȃ������烁���o�[���Ȃɂ��ɓ������Ă��Ȃ����𔻒f����
		else {
			for (int i = 0; i < FormaionNum; i++) {
				if (Member[i]->HitPlayer || Member[i]->mTouchGraund) {
					HitAny = true;
					break;
				}
			}
		}

		//! �����ɓ������Ă��Ȃ������f����
		if (TotalMove >= 2.0f || HitAny) {
			TotalMove = 0;
			AtkIntervalCnt = 0;
			AtkRetrun = true;
		} 
	}

	//! �ˌ����ƂɈ��̍��x�ɂȂ�܂Ŗ߂�
	else if (AtkRetrun) {
		AtkIntervalCnt = 0; //! �߂��Ă�r���̓J�E���g��i�߂Ȃ�
		ReturnCnt++;
		if (Movevec.y <= 0.5f) {
			mcMoveVector.y += sinf(DegreeToRadian(90)) * Speed;
		}
		else {
			AtkRetrun = false;
			ReturnCnt = 0;
		}		

		if (ReturnCnt > 140) {
			AtkRetrun = false;
			ReturnCnt = 0;
		}
	}

	else {	
		//! ��{�͂��邮��Ɖ~��`���悤�ɓ���
		mcMoveVector.x = cosf(MoveRad) * -Speed;
		mcMoveVector.y = sinf(MoveRad) * -Speed;		
		MoveDeg += Add;
		Totaldeg += fabs(Add);
		if (Totaldeg >= 70) {
			if (MoveDeg >= 140) {
				MoveDeg = 30;
			}
			else {
				MoveDeg = 210;
			}
			Totaldeg = 0;
		}
		MoveRad = DegreeToRadian(MoveDeg);
	}
}

//! �ړ��ʂ𑫂�����
void Fordon::ForceProces()
{
	CurrentTime += (1.0f / 60.0f);		 //! �o�ߎ��Ԃ𑝂₷
	mcpBoxCol->SetPrevVec(mcVec);        //! �O�t���[���̍��W�Ƃ��ĕۑ�����
	
	Movevec += mcMoveVector;
	if (mAlive) {
		mcVec += mcMoveVector;               //! ���̃L�����N�^�[�ɂ������Ă���͂𑫂�
		Movevec = mcVec;
	}
	mcpShape->SetMoveVec(mcMoveVector);  //! �����蔻��Ɏg�����߂̏����Z�b�g
	mcMoveVector.SetVector(0, 0);        //! ���̃L�����N�^�[�ɂ������Ă���͂��O�ɂ���
	mcpBoxCol->SetOnObj(false);          //! ��ɂ͏���Ă��Ȃ����Ƃɂ���@������false�ɂ�������Collsion���������肷��̂ł�����false�ɂ��܂�
	//! ��������ɃT�C�Y�Z�b�g
	mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
}


//! �����o�[�̈ړ��֐�
void Fordon::Move_Menber(Vector2 _destination)
{
	
}