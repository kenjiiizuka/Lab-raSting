#include "Necthor1_5.h"
#include "Debri.h"
#include "NecthorHammer_InClass.h"
#include "Camerah.h"
#include "ShocoWave.h"
#include "Smoke.h"
#include "Controller.h"
#include "LeapDebri.h"
#include "SoundManager.h"
#include "Collision.h"
#include "TextureManager.h"
#include "Necthor_Allow.h"
//! �R���X�g���N�^
Necthor1_5::Necthor1_5()
{
	for (int i = 0; i < 3; i++) {
		mcpLeapdebri[i] = new LeapDebri;
	}
	HightHP = false;
	HP = 15;
	RushMax = 5;
	ShockWaveCoolTimeMax = 100;
	LeapDebriAtkCnt = 0;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol_Red));
	RushWaveAttack = false;
}

Necthor1_5::Necthor1_5(float _x, float _y)
	: ReNecthor::ReNecthor(_x, _y)
{
	for (int i = 0; i < 3; i++) {
		mcpLeapdebri[i] = new LeapDebri;
	}
	HightHP = false;
	HP = 15;
	RushMax = 5;
	ShockWaveCoolTimeMax = 100;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol_Red));
	RushWaveAttack = true;
	LeapDebriAtkCnt = 0;
}

//! �f�X�g���N�^
Necthor1_5::~Necthor1_5()
{
	for (int i = 0; i < 3; i++) {
		delete mcpLeapdebri[i];
	}
}

//! �X�V����
void Necthor1_5::Update()
{
	AnimX = mcpAnimsprite->GetCurrentXSplit(); //! ���݂̂w�����A�j���[�V�����̔ԍ������炤
	ColFix();
	if (BattleActiv) {
		RandamCnt+= (rand() % 4) + 1;
		if (RandamCnt > 100) {
			RandamCnt = 0;
		}
		//! Hp�������Ȃ�����|��Ă��Ԃɂ���
		if (HP <= 0 && State != eNecthorState::State_Destroy) {
			if (State != eNecthorState::State_Down) {
				//! ���ꂫ���o��
				Vector2 DebriPos;
				DebriPos.x = mcVec.x - 0.7f;
				DebriPos.y = mcVec.y - 0.75f;
				Debri[1].get()->UpStart(DebriPos, true);     //! ���ꂫ���o��(�`�悠��)
				Debri[0].get()->FadeoutStart();
			}
			State = eNecthorState::State_Down;
		}
		//! �X�e�[�g�̏���
		switch (State)
		{
		case ReNecthor::State_Idol:
			Idol();
			break;
		case ReNecthor::State_PressHammer:
			Atk_PressHammer();
			break;
		case ReNecthor::State_ShockWave:
			Atk_ShockWave();
			break;
		case ReNecthor::State_RushWave:
			Atk_RushWave();
			break;
		case ReNecthor::State_LeapDebri:
			Atk_LeapDebri();
			break;
		case ReNecthor::State_Down:
			FallDwoned();
			break;
		case ReNecthor::State_Destroy:
			Destroy();
			break;
		}
	}

	for (int i = 0; i < Debri.size(); i++) {
		Debri[i].get()->Update();
	}
	for (int j = 0; j < Wave.size(); j++) {
		Wave[j].get()->Update();
	}
	for (int k = 0; k < 3; k ++) {
		mcpLeapdebri[k]->Update();
	}
	SmokeUpdate();
	TexChange();
	Allow->Update();
}

//! �`�揈��
void Necthor1_5::Draw()
{
	ReNecthor::Draw();
	for (int k = 0; k < 3; k++) {
		mcpLeapdebri[k]->Draw();
	}
}

//! �����蔻�菈��
void Necthor1_5::CollisionUpdate()
{
	ReNecthor::CollisionUpdate();

	Box * PlayerBox = mcPlayer->GetBoxCol();
	bool Elect = mcPlayer->GetCharge();
	//! �Ƃт����Ă��邪�ꂫ�Ƃ̓����蔻��
	for (int i = 0; i < 3; i++) {
		//! ���ꂫ�̓����蔻��̎擾
		Box * LeapDebriBox = mcpLeapdebri[i]->GetCol();
		Box * LeapDebriAtkBox = mcpLeapdebri[i]->GetAtkCol();
		//! �Փ˔���
		BBC(*PlayerBox, *LeapDebriBox);

		//! �U���Ƃ̔���
		if (BBH(*PlayerBox, *LeapDebriAtkBox)) {
			mcPlayer->SetDamege(Left);
		}

		//! �K���Ƃ̓����蔻��
		if (Elect) {
			if (BCH(*LeapDebriBox,mcPlayer->GetSpearCol(0)) || BCH(*LeapDebriBox, mcPlayer->GetSpearCol(1))) {
				mcpLeapdebri[i]->Fadeout();
				mcPlayer->SetReaction(TailReaction::TailReaction_Through, Direction_None);
			}
			else if (BCH(*LeapDebriAtkBox, mcPlayer->GetSpearCol(0)) || BCH(*LeapDebriAtkBox, mcPlayer->GetSpearCol(1))) {
				mcpLeapdebri[i]->Fadeout();
				mcPlayer->SetReaction(TailReaction::TailReaction_Through, Direction_None);
			}
		}
		else {
			if (Collision::Box_Circle_Hit(*LeapDebriBox,*mcPlayer->GetAttackCol())) {
				mcpLeapdebri[i]->Fadeout();
				mcPlayer->SetReaction(TailReaction::TailReaction_Through, Direction_None);
			}
		}
	}
}

//1 �A�C�h����ԂɎ��̏���
void Necthor1_5::Idol()
{
	mcpAnimsprite->SetAnimSpeed(8);
	TexState = Tex_Idol;
	//! �łԂ������
	Debri[0].get()->FadeoutStart();
	Hammer->AtkCol->SetActiv(true);
	mcpAnimsprite->SetStopAnimation(false);
	//! �{�̂̓����蔻��̈ʒu�����߂�
	ColFix();
	MyCol.AtkCol->SetActiv(true); //! �U���̓����蔻����I��

	//! �ǂ̍U�������邩���f
	mcpAnimsprite->SetStopAnimation(false);
	AttackStateMachine();
}

//! �ǂ̍U�������邩��I�ԏ���
void Necthor1_5::AttackStateMachine()
{
	float Px = mcPlayer->GetVec().x;                               //! �v���C���[��X���W
	float ToPx = fabs(mcVec.x - Px);                               //! �v���C���[�܂ł�X�����̋���       
	int Cnt = AtkCnt.Press + AtkCnt.Wave;

	//! �A���Ռ��g�U�� �U���񐔂��Q�ɂȂ����Ƃ�()
	if (HP <= 5 && RushWaveAttack) {							   //! �Ռ��g�U������ȏサ�Ă�����Ռ��g�A�ōU��������
		State = eNecthorState::State_RushWave;
		IdolCnt = 100;                                               //! �J�E���g�̃��Z�b�g	 
		RushWaveAttack = false;
		RushMax = 5;
		mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g	
	}
	else if (Cnt >= 4) {
		State = eNecthorState::State_RushWave;
		IdolCnt = 60;                                               //! �J�E���g�̃��Z�b�g	 
		RushWaveAttack = false;
		RushMax = 3;
		mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g	
	}
	else if (IdolCnt >= (60 * 2)) {								   //! 300�t���[���o�߂�����U���ɍs��
		//! �v���C���[���n���}�[�U���̎˒��Ȃ��Ȃ�ӂ艵�U��
		if (ToPx <= 0.8f) {
			State = eNecthorState::State_PressHammer;
			mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
		}
		//! ���傤�ǂ������񂶂̈ʒu�Ȃ烉���_������
		else if (ToPx > 0.8f) {
			if ((RandamCnt % 3) == 0) { //! �J�E���g��2�̔{���Ȃ�n���}�[�U��
				int r = rand() % 100;
				if (r % 3 == 0) {
					State = eNecthorState::State_PressHammer;
					mcpAnimsprite->ResetAnimCnt();   //! �A�j���[�V�����J�E���g�̃��Z�b�g 
					AtkCnt.Press++;
				}
				else if(r % 4 == 0) {
					State = eNecthorState::State_ShockWave;
					mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
					AtkCnt.Wave++;
				}
				else if (r % 5 == 0) {
					mcpLeapdebri[0]->Fadeout();
					mcpLeapdebri[1]->Fadeout();
					mcpLeapdebri[2]->Fadeout();
					Shiver = 0.002f;
					State = eNecthorState::State_LeapDebri;
					LeapDebriAtkCnt++;
					mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
				}
			}
			else {
				mcpLeapdebri[0]->Fadeout();
				mcpLeapdebri[1]->Fadeout();
				mcpLeapdebri[2]->Fadeout();
				Shiver = 0.002f;
				State = eNecthorState::State_LeapDebri;
				LeapDebriAtkCnt++;
				mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
			}
		}
		else {mcpLeapdebri[0]->Fadeout();
				mcpLeapdebri[1]->Fadeout();
				mcpLeapdebri[2]->Fadeout();
				Shiver = 0.002f;
				State = eNecthorState::State_LeapDebri;
				LeapDebriAtkCnt++;
				mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
			mcpLeapdebri[0]->Fadeout();
			mcpLeapdebri[1]->Fadeout();
			mcpLeapdebri[2]->Fadeout();
			State = eNecthorState::State_LeapDebri;
			LeapDebriAtkCnt++;
			mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
		}				
		IdolCnt = 0;                                               //! �J�E���g�̃��Z�b�g
	}
	else if (IdolCnt >= (60 * 2) && ToPx >= 1.4) {              //! �O�b�o�߂��Ă��Ă��{�X���痣��Ă�����
		if (!ShockWaved) {
			State = eNecthorState::State_ShockWave;
			mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
			Shiver = 0.002f;
			ShockWaved = true;                                     //! ���̍U���������t���O�𗧂Ă�
			AtkCnt.Wave++;                                         //! ���񂱂̍U�����������𐔂���
		}
		else {													   //! �N�[���^�C�����o�߂�����܂����̍U�����ł���悤�ɂ���
			ShockWaveCoolTime++;
			if (ShockWaveCoolTime >= ShockWaveCoolTimeMax) {
				ShockWaved = false;
			}
		}
	}

	mcpAnimsprite->SetStopAnimation(false);
	IdolCnt++;
}

void Necthor1_5::SmokeUpdate()
{
	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->Update();
	}
	//! ���̃t���O�𗧂Ă�
	int AttackNum = AtkCnt.Press + AtkCnt.Wave + LeapDebriAtkCnt;
	if (AttackNum == 2) {
		LeftSmoke = true;
	}
	if (AttackNum == 4) {
		RightSmoke = true;
	}

	Vector2 SmokePos[3]; //! 0 �^�� 1 �E 2 ��
	//! �e���̍��W�̌v�Z
	if (TexState == Tex_Idol) {
		SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
		SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
		SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
	}
	else if (TexState == Tex_Attack || TexState == Tex_Attack2) {
		if (AnimX == 0) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
		else if (AnimX == 1) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
		else if (AnimX == 2 || AnimX == 3) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
		else if (AnimX == 4 || AnimX == 5 || AnimX == 6) {
			SmokePos[0] = Vector2(mcVec.x + 0.04f, mcVec.y + 0.3f);
			SmokePos[1] = Vector2(mcVec.x + 0.2, mcVec.y - 0.06f);
			SmokePos[2] = Vector2(mcVec.x - 0.12f, mcVec.y - 0.06f);
		}
		else if (AnimX == 7) {
			SmokePos[0] = Vector2(mcVec.x + 0.1f, mcVec.y + 0.56f);
			SmokePos[1] = Vector2(mcVec.x + 0.28f, mcVec.y + 0.13f);
			SmokePos[2] = Vector2(mcVec.x - 0.04f, mcVec.y + 0.13f);
		}
		else if (AnimX == 8) {
			SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
			SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
			SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);
		}
	}

	if (NomalSmoke) {
		Smokes[0].get()->NomalSmokeRagular(SmokePos[0]);
	}
	else {
		Smokes[0].get()->SmokeOff();
	}

	if (RightSmoke) {
		Smokes[1].get()->RightSmokeSmall(SmokePos[1]);
	}
	else {
		Smokes[1].get()->SmokeOff();
	}

	if (LeftSmoke) {
		Smokes[2].get()->LeftSmokeSmall(SmokePos[2]);
	}
	else {
		Smokes[2].get()->SmokeOff();
	}
}

void Necthor1_5::Atk_PressHammer()
{
	//! �U���p�̃e�N�X�`���ɕύX
	TexState = Tex_Attack;

	//! �n���}�[���@������ꂽ���ʐU��	
	if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk);
			AtkSEflg = false;
		}
		CAMERA->StartVibration(4);
		Hammer->Slamed = true;
		//! �n���}�[�̓����蔻��̈ʒu�̒���
		MyCol.AtkCol->SetActiv(false); //! �U���̓����蔻����I�t
		//! �����ł��ꂫ���o��
		//! ���ꂫ�̍��W�̌v�Z
		Vector2 DebriPos;
		DebriPos.x = Hammer->Vec.x - 0.26f;
		DebriPos.y = Hammer->Vec.y - 0.3f;
		Debri[0].get()->UpStart(DebriPos);     //! ���ꂫ���o��

		//! �����o��
		Vector2 AllowPos;
		AllowPos.x = Hammer->Vec.x - 0.3f;
		AllowPos.y = Hammer->Vec.y + 0.2f;
		Allow->AllowOn(AllowPos);
	}
	else if (AnimX == 6) {
		mcpAnimsprite->SetStopAnimation(true);
		//! �n���}�[�̍U��������I�t�ɂ���
		Hammer->AtkCol->SetActiv(false);

		//! ��_�ɍU�������������N���オ��
		if (WeekCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}
		if (MyCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}
		//! ���b�ԑҋ@���Idol��Ԃɖ߂�
		if (AttackCoolTime >= (60 * 6)) {
			mcpAnimsprite->SetStopAnimation(false);
		}
		AttackCoolTime++;
	}
	else if (AnimX == 7) {
		Debri[0].get()->FadeoutStart();
		Allow->AllowOff();
	}
	else if (AnimX == 8) {
		AtkSEflg = true;
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		mcpAnimsprite->ResetAnimCnt(); //! �A�j���[�V�����J�E���g�̃��Z�b�g
	}
}

void Necthor1_5::Atk_ShockWave()
{
	//! �U���p�̃e�N�X�`���ɕύX
	TexState = Tex_Attack2;

	//! �A�j���[�V�����̂����ǂ�x������
	mcpAnimsprite->SetAnimSpeed(4);

	//! �n���}�[���@������ꂽ���ʐU��
	if (AnimX <= 3) {
		Hammer->Slamed = false;
		//! �n���}�[�̓����蔻��̒���
	}
	if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk);
			AtkSEflg = false;
		}
		Hammer->Slamed = true;
		CAMERA->StartVibration(4);
		MyCol.AtkCol->SetActiv(false); //! �U���̓����蔻����I�t

		//! �Ռ��g���o��
		Vector2 WavePos;
		WavePos.x = Hammer->Vec.x - 0.1f;
		WavePos.y = Hammer->Vec.y;
		Wave[0].get()->ShockWaveStart(WavePos);
	}
	else if (AnimX == 6) {
		mcpAnimsprite->SetStopAnimation(true);
		//! �n���}�[�̍U��������I�t�ɂ���
		Hammer->AtkCol->SetActiv(false);

		//! ���b�ԑҋ@���Idol��Ԃɖ߂�
		if (AttackCoolTime >= (60 * 2)) {
			mcpAnimsprite->SetStopAnimation(false);
		}
		AttackCoolTime++;
	}
	else if (AnimX == 8) {
		AtkSEflg = true;
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		mcpAnimsprite->ResetAnimCnt(); //! �A�j���[�V�����J�E���g�̃��Z�b�g
	}
}

void Necthor1_5::Atk_RushWave()
{
	//! �\������
	if (!RushPreparation) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_AtkSig);
			AtkSEflg = false;
		}
		TexState = Tex_Idol;
		NomalSmoke = true;
		//! �k����		
		if (PreparationCnt % 3 == 0) { //! 3�t���[�����ɐk����������A��
			Shiver *= -1;
		}
		mcVec.x += Shiver;
		if (PreparationCnt >= 120) {
			RushPreparation = true;
			PreparationCnt = 0;
			AtkSEflg = true;
			mcpAnimsprite->ResetAnimCnt();
			
		}
		PreparationCnt++;
	}
	//! �U���J�n
	else {
		//! ���ōU���̉摜���Z�b�g���Ă��܂�
		TexState = Tex_Attack2;
		//! �A�j���[�V�����̂����ǂ�x������
		mcpAnimsprite->SetAnimSpeed(4);
		//! �n�ʂɃn���}�[��������A�j���[�V�������~�߂�	
		if (RushCnt < RushMax) {
			mcpAnimsprite->SetStopAnimation(false);
			if (AnimX <= 3) {
				Hammer->Slamed = false;
			}
			//! �n���}�[���@������ꂽ���ʐU��
			if (AnimX == 5) {
				if (AtkSEflg) {
					SoundMgr->PlaySE(SE_Necthor_Atk,0.2f);
				}
				Hammer->Slamed = true;
				CAMERA->StartVibration(4);
				MyCol.AtkCol->SetActiv(false); //! �U���̓����蔻����I�t

				//! �Ռ��g���o��
				Vector2 WavePos;
				WavePos.x = Hammer->Vec.x - 0.1f;
				WavePos.y = Hammer->Vec.y;
				Wave[RushCnt].get()->ShockWaveStart(WavePos);
			}
			else if (AnimX == 6) {
				mcpAnimsprite->SetStopAnimation(true);
				//! �n���}�[�̍U��������I�t�ɂ���
				Hammer->AtkCol->SetActiv(false);

				//! ���b�ԑҋ@���Idol��Ԃɖ߂�
				if (AttackCoolTime >= (30)) {
					mcpAnimsprite->SetStopAnimation(false);
				}

				AttackCoolTime++;
			}
			else if (AnimX == 8) {
				AttackCoolTime = 0;
				AtkSEflg = true;
				RushCnt++;
				mcpAnimsprite->ResetAnimCnt(); //! �A�j���[�V�����J�E���g�̃��Z�b�g	
			}
		}

		//! 4��ڂɃN�\�ł��Ռ��g���o��
		else {
			TexState = Tex_Attack;
			if (AnimX <= 3) {
				Hammer->Slamed = false;
			}
			if (AnimX == 3) {
				mcpAnimsprite->SetStopAnimation(true);
				if (RushFrameCnt >= 30) {
					mcpAnimsprite->SetStopAnimation(false);
				}
				RushFrameCnt++;
			}
			else if (AnimX == 5) {
				if (AtkSEflg) {
					SoundMgr->PlaySE(SE_Necthor_Atk, 0.4f);
				}
				CAMERA->StartVibration(4);
				//! �n���}�[�̓����蔻��̈ʒu�̒���
				MyCol.AtkCol->SetActiv(false); //! �U���̓����蔻����I�t

				Hammer->Slamed = true;

				//! �Ռ��g���o��
				Vector2 WavePos;
				WavePos.x = Hammer->Vec.x - 0.1f;
				WavePos.y = Hammer->Vec.y;
				// �{���͂ł����Ռ��g
				Wave[RushCnt].get()->ShockWaveStart(WavePos);

				Vector2 AllowPos;
				AllowPos.x = Hammer->Vec.x - 0.3f;
				AllowPos.y = Hammer->Vec.y + 0.2f;
				Allow->AllowOn(AllowPos);

				//! ���ꂫ�̍��W�̌v�Z
				Vector2 DebriPos;
				DebriPos.x = Hammer->Vec.x - 0.26f;
				DebriPos.y = Hammer->Vec.y - 0.3f;
				Debri[0].get()->UpStart(DebriPos);     //! ���ꂫ���o��
			}
			else if (AnimX == 6) {
				mcpAnimsprite->SetStopAnimation(true);
				//! �n���}�[�̍U��������I�t�ɂ���
				Hammer->AtkCol->SetActiv(false);

				//! ���b�ԑҋ@���Idol��Ԃɖ߂�
				if (AttackCoolTime >= (160)) {
					NomalSmoke = RightSmoke = LeftSmoke = false; //! �X���[�N���I�t�ɂ���
					AtkCnt.Wave = AtkCnt.Press = 0;			//! �J�E���g���Z�b�g 

					if (!Smokes[0].get()->GetSmokeActiv()) {    //! �S�ẴX���[�N���I�t�ɂȂ�������Ƃɖ߂�	
						mcpAnimsprite->SetStopAnimation(false);
						//! ���ꂫ������
						Debri[0].get()->FadeoutStart();
						Allow->AllowOff();
					}
				}
				AttackCoolTime++;
			}
			else if (AnimX == 8) {
				AtkSEflg = true;
				State = eNecthorState::State_Idol;      //! �A�C�h����Ԃɖ߂�
				mcpAnimsprite->ResetAnimCnt();          //! �A�j���[�V�����J�E���g�̃��Z�b�g	
				RushPreparation = 0;
				AttackCoolTime = 0;
				RushCnt = 0;
				RushFrameCnt = 0;
				IdolCnt = 0;
			}
		}
	}
}

void Necthor1_5::Atk_LeapDebri()
{
	//! �U���p�̃e�N�X�`���ɕύX
	TexState = Tex_Attack;	
	//! ���߃��[�V����
	if (AnimX == 0 || AnimX == 1 || AnimX == 2) {
		mcpAnimsprite->SetStopAnimation(false);
	}
	else if (AnimX == 3) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_SPAtk,0.4f);
			AtkSEflg = false;
		}	
		//! �k����		
		mcpAnimsprite->SetStopAnimation(true);	
		if (LeapDebriPreparation % 3 == 0) { //! 3�t���[�����ɐk����������A��
			Shiver *= -1;
		}
		//mcVec.x += Shiver;

		//! �R�b�ӂ邦����U���J�n
		if (MyCol.TailHited) {
			LeapDebriPreparation = 100;
		}
		if (LeapDebriPreparation > 100) {
			AtkSEflg = true;
			mcpAnimsprite->SetStopAnimation(false);
		}
		LeapDebriPreparation++;
	}
	//! �n���}�[���@������ꂽ���ʐU��
	else if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk,0.2f);
			AtkSEflg = false;
		}
		CAMERA->StartVibration(6);
		Hammer->Slamed = true;
		//! �n���}�[�̓����蔻��̈ʒu�̒���
		MyCol.AtkCol->SetActiv(false); //! �U���̓����蔻����I�t
		
		//! ���ꂫ�̍��W�̌v�Z
		Vector2 DebriPos;
		DebriPos.x = Hammer->Vec.x - 0.26f;
		DebriPos.y = Hammer->Vec.y - 0.3f;
		Debri[0].get()->UpStart(DebriPos);     //! ���ꂫ���o��

		//! �ƂԂ��ꂫ���o��
		//! ��Ԑ���
		Vector2 LeapDebriPos;
		LeapDebriPos.x = Hammer->Vec.x - 0.1f;
		LeapDebriPos.y = Hammer->Vec.y - 0.1f;
		//! ���ꂼ��򋗗���L�΂�
		for (int i = 0; i < LeapDebriAtkCnt; i++) {	
			if (i == 0) {
				mcpLeapdebri[i]->Leap(LeapDebriPos, Vector2(0.014f, 0.029f));
			}
			else if (i == 1) {
				mcpLeapdebri[i]->Leap(LeapDebriPos, Vector2(0.026f, 0.034f));
			}
			else if(i == 2){
				mcpLeapdebri[i]->Leap(LeapDebriPos, Vector2(0.04f, 0.039f));
			}
		}
		//! �����o��
		Vector2 AllowPos;
		AllowPos.x = Hammer->Vec.x - 0.3f;
		AllowPos.y = Hammer->Vec.y + 0.2f;
		Allow->AllowOn(AllowPos);

	}
	else if (AnimX == 6) {
		mcpAnimsprite->SetStopAnimation(true);
		//! �n���}�[�̍U��������I�t�ɂ���
		Hammer->AtkCol->SetActiv(false);

		//! ��_�ɍU�������������N���オ��
		if (WeekCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}
		if (MyCol.TailHited) {
			AttackCoolTime = (60 * 6);
		}

		//! ���b�ԑҋ@���Idol��Ԃɖ߂�
		if (AttackCoolTime >= (60 * 6)) {
			mcpAnimsprite->SetStopAnimation(false);
		}
		AttackCoolTime++;
	}
	else if (AnimX == 7) {
		Debri[0].get()->FadeoutStart();
		Allow->AllowOff();
	}
	else if (AnimX == 8) {
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		LeapDebriPreparation = 0;
		AtkSEflg = true;
		mcpAnimsprite->ResetAnimCnt(); //! �A�j���[�V�����J�E���g�̃��Z�b�g
		if (LeapDebriAtkCnt == 3) {
			LeapDebriAtkCnt = 0;
		}
	}
}

