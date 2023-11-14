#include "ReNecthor.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Camerah.h"
#include "NecthorHammer_InClass.h"
#include "Debri.h"
#include "ShocoWave.h"
#include "Smoke.h"
#include "Necthor_Allow.h"
#include "SoundManager.h"
#include "Collision.h"
#include "EffectManager.h"
//! �R���X�g���N�^
ReNecthor::ReNecthor()
{
	//! �`��֘A�̐ݒ�
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol));
	mcpAnimsprite->SetAnimtionTable(5, 1);
	SetSize(2.4f, 2.4f);

	//! �ϐ��̏����l�ݒ�
	State = eNecthorState::State_Idol; //! �������
	HP = 10;
	DamageFrameCnt = TakenDamage = AttackCoolTime = IdolCnt = 0;
	DamageFlg = false;
	//! �����蔻��̐���
	//! �n���}�[
	Hammer = new NecthorHammer;
	Hammer->Vec.x = mcVec.x - 0.2f;
	Hammer->Vec.y = mcVec.y - 0.33f;
	//! �{��
	MyCol.Col = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	MyCol.AtkCol = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	//! ��_�̓����蔻��
	WeekCol.Col = new Box(WeekCol.Pos, WeekCol.Size.x, WeekCol.Size.y);
	WeekCol.AtkCol = new Box(WeekCol.Pos, WeekCol.Size.x, WeekCol.Size.y);
	ColFix(); //! �{�̂Ǝ�_�ʒu�̓����蔻��̒���
	//! ���ꂫ�̐���
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<NecthorDebri> debri(new NecthorDebri);
		Debri.emplace_back(move(debri));
	}
	//! �Ռ��g�̐���
	for (int i = 0; i < 4; i++) {
		std::unique_ptr<ShockWave> wave(new ShockWave);
		Wave.emplace_back(move(wave));
	}
	RushFrameCnt = RushCnt = 0;
	AtkSEflg = true;
	//! ���Ő퓬�J�n��Ԃ���X�^�[�g �퓬�J�n�܂��̈Њd�s����ɐ퓬�J�n
	BattleActiv = true;
}

//! �R���X�g���N�^(��������)
ReNecthor::ReNecthor(float _x ,float _y)
{
	//! �`��֘A�̐ݒ�
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol));
	mcpAnimsprite->SetAnimtionTable(5, 1);
	SetSize(1.7f, 1.7f);
	mcVec = Vector2(_x, _y); //! ���W�̃Z�b�g
	//! �ϐ��̏����l�ݒ�
	State = eNecthorState::State_Idol; //! �������
	HP = 10;
	AnimX = DamageFrameCnt = TakenDamage = AttackCoolTime = IdolCnt = 0;
	DamageFlg = false;
	//! �����蔻��̐���
	//! �n���}�[
	Hammer = new NecthorHammer;
	Hammer->Vec.x = mcVec.x - 0.1;
	Hammer->Vec.y = mcVec.y - 0.44f;

	//! �{��
	MyCol.Col = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	MyCol.AtkCol = new Box(MyCol.Pos, MyCol.Size.x, MyCol.Size.y);
	//! ��_�̓����蔻��
	WeekCol.Col = new Box(WeekCol.Pos,WeekCol.Size.x,WeekCol.Size.y);
	WeekCol.AtkCol = new Box(WeekCol.Pos, WeekCol.Size.x, WeekCol.Size.y);

	ColFix(); //! �{�̂Ǝ�_�ʒu�̓����蔻��̒���

	//! ���ꂫ�̐���
	for (int i = 0; i < 2; i++) {
		std::unique_ptr<NecthorDebri> debri(new NecthorDebri);
		Debri.emplace_back(move(debri));
	}	
	//! �Ռ��g�̐���
	for (int i = 0; i < 6; i++) {
		std::unique_ptr<ShockWave> wave(new ShockWave);
		Wave.emplace_back(move(wave));
	}	
	//! ���̐���
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<Smoke> smoke(new Smoke);
		Smokes.emplace_back(move(smoke));
	}

	PreparationCnt = RushFrameCnt = RushCnt = 0;
	Shiver = 0.004f;
	//! ���Ő퓬�J�n��Ԃ���X�^�[�g �퓬�J�n�܂��̈Њd�s����ɐ퓬�J�n
	BattleActiv = false;
	TexState_Prev = TexState = Tex_Idol;
	RushMax = 3;
	ShockWaveCoolTimeMax = 120;
	AtkSEflg = true;
	Allow.reset(new Necthor_Allow);
}


//! �f�X�g���N�^
ReNecthor::~ReNecthor()
{	
	delete MyCol.AtkCol;
	delete MyCol.Col;
	delete WeekCol.AtkCol;
	delete WeekCol.Col;
	delete Hammer;
}

//! �X�V����
void ReNecthor::Update()
{	
	AnimX = mcpAnimsprite->GetCurrentXSplit(); //! ���݂̂w�����A�j���[�V�����̔ԍ������炤
	ColFix();
	if (BattleActiv) {
		//! Hp�������Ȃ�����|��Ă��Ԃɂ���
		if (HP <= 0 && State != eNecthorState::State_Destroy) {
			if (State != eNecthorState::State_Down) {
				//! ���ꂫ���o��
				Vector2 DebriPos;
				DebriPos.x = mcVec.x - 0.7f;
				DebriPos.y = mcVec.y - 0.75f;
				Debri[1].get()->UpStart(DebriPos,true);     //! ���ꂫ���o��(�`�悠��)
				Debri[0].get()->FadeoutStart();
			}
			State = eNecthorState::State_Down;	
		}
		//! HP�����Ȃ��Ȃ�����
		if (HP <= 5 && HightHP && State == eNecthorState::State_Idol) {
			RushMax = 5;
			ShockWaveCoolTimeMax = 100;
			IdolCnt = 50;
			HightHP = false;
		}

		//! ��Ԃ̍X�V����
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

		case eNecthorState::State_Down:
			FallDwoned();
			break;
		case eNecthorState::State_Destroy:
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
	SmokeUpdate();
	Allow->Update();
	TexChange();
	//ColFix();
}

//! �`�揈��
void ReNecthor::Draw()
{
	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->Draw();
	}
	GameObject::Draw();
	for (int i = 0; i < Debri.size(); i++) {
		Debri[i].get()->Draw();
	}
	for (int j = 0; j < Wave.size(); j++) {
		Wave[j].get()->Draw();
	}
	
	Allow->Draw();
	//image.DrawSprite(Hammer->Vec.x,Hammer->Vec.y,Hammer->ColSize.x,Hammer->ColSize.y,TEXTURE(Tex_PanelBl),1,1,1,0.5f);
	////! �f�o�b�O�悤�{�XHP�̕\��
	//Vector2 HpPos = Vector2(mcVec.x, mcVec.y + 0.4f);
	//for (int i = 0; i < HP; i++) {
	//	image.DrawSprite(HpPos.x + (i * 0.12f), HpPos.y, 0.1, 0.1, TEXTURE(Tex_MapTip01));
	//}
}


//! �����蔻��̏���
void ReNecthor::CollisionUpdate()
{
	//! �_���[�W�����Z�ɂ��Ă���̂͑ѓd��Ԃ̎��ɂ��܂���������2�p���ł���悤�ɂ��Ă܂�(���Ԃ�)
	Box * PlayerBox = mcPlayer->GetBoxCol();
	//! �v���C���[����̍U���̓����蔻��
	Circle* PlayerAtk;
	PlayerAtk = mcPlayer->GetAttackCol();
	Circle * SpearCol[2];
	int ColNum = 0;
	//! �U���̓����蔻������炤
	bool Elect = mcPlayer->GetCharge();
	
//* �n���}�[ ------------------------------------------------------------------
	//! �n���}�[�̍U������Ƃ̓����蔻��
	if (BBH(*PlayerBox, *Hammer->AtkCol)) {
		mcPlayer->SetDamege(Left); //! �{�X�͉E���ɂ���̂ŁA�K�������ɂ͂������悤�ɂ���(�E�Ƀm�b�N�o�b�N����Ɩ{�̂ƃn���}�[�ɋ��܂��đ�������)
	}	
	//! �n���}�[�Ƃ̏Փ˔���
	BBC(*PlayerBox,*Hammer->Col);

	//! �n���}�[�Ƃ����ۂ̓����蔻��
	if (Elect) {  //! �ѓd��
		for ( ColNum = 0; ColNum < 2; ColNum++) {
			if (BCH(*Hammer->Col, mcPlayer->GetSpearCol(ColNum)) && !Hammer->TailHited) {
				mcPlayer->SetReaction(TailReaction_Bounce, Left);
				SoundMgr->PlaySE(SE_Timpiller_Sasaru);;
				Hammer->TailHited = true;
			}
		}
	}
	else {   //! ��ѓd
		if (BCH(*Hammer->Col, *PlayerAtk) && !Hammer->TailHited) {
			SoundMgr->PlaySE(SE_Necthor_Haziku);
			if (mcPlayer->GetVec().x < Hammer->Vec.x) {
				mcPlayer->SetReaction(TailReaction_Bounce, Left);
			}
			else {
				mcPlayer->SetReaction(TailReaction_Bounce, Right);
			}
			TakenDamage += 0;
			Hammer->TailHited = true;
		}
	}

//! �{�� ---------------------------------------------------------------------------------
	//! �{�̂ƃv���C���[�̓����蔻��
	//! �Փ˔���
	BBC(*PlayerBox, *MyCol.Col);

	//! �K���Ƃ̓����蔻��
	if (Elect) {
		for (ColNum = 0; ColNum < 2; ColNum++) {	
			if (BCH(*MyCol.Col, mcPlayer->GetSpearCol(ColNum)) && !MyCol.TailHited) {
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.2f);
				mcPlayer->SetReaction(TailReaction_Stop, Direction_None);
				TakenDamage += 1;
				MyCol.TailHited = true;
			}
		}
	}
	else {
		if (BCH(*MyCol.Col, *PlayerAtk) && !MyCol.TailHited) {
			SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.2f);
			mcPlayer->SetReaction(TailReaction_Stop, Direction_None);
			TakenDamage += 1;
			MyCol.TailHited = true;
		}
	}

	//! �U������
	if (BBH(*PlayerBox, *MyCol.AtkCol)) {
		mcPlayer->SetDamege(Left); //! �{�X�͉E���ɂ���̂ŁA�K�������ɂ͂������悤�ɂ���(�E�Ƀm�b�N�o�b�N����Ɩ{�̂ƃn���}�[�ɋ��܂��đ�������)
	}

//! ��_ -------------------------------------------------------------------------------------
	//! ��_�Ƃ̓����蔻��
	//! �Փ˔���
	BBC(*PlayerBox,*WeekCol.Col);

	if (BBH(*PlayerBox,*WeekCol.AtkCol)) {
		mcPlayer->SetDamege(Left); //! �{�X�͉E���ɂ���̂ŁA�K�������ɂ͂������悤�ɂ���(�E�Ƀm�b�N�o�b�N����Ɩ{�̂ƃn���}�[�ɋ��܂��đ�������)
	}

	//! �K���Ƃ̓����蔻��
	if (Elect) {
		for (ColNum = 0; ColNum < 2; ColNum++) {
			if (BCH(*WeekCol.Col,mcPlayer->GetSpearCol(ColNum)) && !WeekCol.TailHited) {
				//! �Ƃǂ߂��h���ꂽ��f�X�g���C�ɂ���
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.4f);
				if (State == eNecthorState::State_Down) {
					State = eNecthorState::State_Destroy;
				}
				WeekCol.TailHited = true;
				mcPlayer->SetReaction(TailReaction_Through, Direction_None);
				TakenDamage += 2;
			}
		}
	}
	else {
		if (BCH(*WeekCol.Col, *PlayerAtk) && !WeekCol.TailHited) {
			SoundMgr->PlaySE(SE_Timpiller_Sasaru,0.4f);
			WeekCol.TailHited = true;
			mcPlayer->SetReaction(TailReaction_StingStop, Direction_None);
			TakenDamage += 2;
			//! �_�E�����Ă���Ƃ��Ɏ�_�Ɏh���ꂽ��f�X�g���C��Ԃɍs��
			if (State == eNecthorState::State_Down) {
				State = eNecthorState::State_Destroy;
			}
		}
	}

//! ���ꂫ -----------------------------------------------------------------------------------
	for (int i = 0; i < Debri.size(); i++) {
		Box * DebriCol = Debri[i].get()->GetCol();
		BBC(*PlayerBox, *DebriCol);

		//! ���ꂫ�ƐK���̓����蔻��
		if (Elect) {	
			for (ColNum = 0; ColNum < 2; ColNum++) {
				if (BCH(*DebriCol, mcPlayer->GetSpearCol(ColNum))) {
					SoundMgr->PlaySE(SE_Splitter_Haziku, 0.2f);
					mcPlayer->SetReaction(TailReaction_Bounce, Left);	
				}
			}
		}
		else {
			if (BCH(*DebriCol, *PlayerAtk)) {
				SoundMgr->PlaySE(SE_Splitter_Haziku, 0.2f);
				mcPlayer->SetReaction(TailReaction_Bounce, Left);
				
			}
		}
	}

//! �Ռ��g -------------------------------------------------------------------------------------
	for (int i = 0; i < Wave.size(); i++) {
		Box * WaveCol = Wave[i].get()->GetCol();
		//! �v���C���[�Ƃ̓����蔻��
		if (BBH(*WaveCol, *PlayerBox)) {
			mcPlayer->SetDamege(Left);
		}
		//! �K���Ƃ̓����蔻��
		if (Elect) {
			for (ColNum = 0; ColNum < 2; ColNum++) {
				if (BCH(*WaveCol, mcPlayer->GetSpearCol(ColNum))) {
					SoundMgr->PlaySE(SE_Timpiller_Sasaru,0.1);
					Wave[i].get()->SetHit(true);
					mcPlayer->SetReaction(TailReaction_Through, Direction_None);
					break;
				}
			}
		}
		else {
			if (BCH(*WaveCol, *PlayerAtk)) {
				SoundMgr->PlaySE(SE_Timpiller_Sasaru, 0.1);
				Wave[i].get()->SetHit(true);
				mcPlayer->SetReaction(TailReaction_Through, Direction_None);
			}
		}
	}

	//! ��x�K���̍U���ɓ���������30�t���[���͍U���ɂ͓�����Ȃ�
	if (WeekCol.TailHited) {
		WeekCol.Cnt++;
		if (WeekCol.Cnt >= 30) {
			WeekCol.Cnt = 0;
			WeekCol.TailHited = false;
		}
	}
	if (MyCol.TailHited) {
		MyCol.Cnt++;
		if (MyCol.Cnt >= 30) {
			MyCol.Cnt = 0;
			MyCol.TailHited = false;
		}
	}
	if (Hammer->TailHited) {
		Hammer->Cnt++;
		if (Hammer->Cnt >= 30) {
			Hammer->Cnt = 0;
			Hammer->TailHited = false;
		}
	}
}

void ReNecthor::LastUpdate()
{
	Damage();
}

void ReNecthor::SetPlayer(Player * _player)
{
	mcPlayer = _player;
}

void ReNecthor::BattleStart()
{
	BattleActiv = true;
}

bool ReNecthor::GetDestroyed()
{
	return mDestroy;
}

//! �A�C�h����Ԃ̏���
void ReNecthor::Idol()
{
	mcpAnimsprite->SetAnimSpeed(8);
	TexState = Tex_Idol;
	
	//! �łԂ������
	Debri[0].get()->FadeoutStart();

	Hammer->AtkCol->SetActiv(true);
	
	//! �{�̂̓����蔻��̈ʒu�����߂�
	ColFix();
	
	MyCol.AtkCol->SetActiv(true); //! �U���̓����蔻����I��
	Hammer->Slamed = false;
	AttackStateMachine();	
}

void ReNecthor::AttackStateMachine()
{
	float Px = mcPlayer->GetVec().x;                               //! �v���C���[��X���W
	float ToPx = fabs(mcVec.x - Px);                               //! �v���C���[�܂ł�X�����̋���       
	int TotalAtk = AtkCnt.Press + AtkCnt.Wave;                     //! �Ռ��g�ƃv���X�U����������

	if (TotalAtk >= 2) {									       //! �Ռ��g�U������ȏサ�Ă�����Ռ��g�A�ōU��������
		State = eNecthorState::State_RushWave;
		IdolCnt = 0;                                               //! �J�E���g�̃��Z�b�g	 
		mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g	
	}
	else if (IdolCnt >= (60 * 4)) {								   //! 300�t���[���o�߂�����U���ɍs��		  	                  	                      
		State = eNecthorState::State_PressHammer;
		IdolCnt = 0;                                               //! �J�E���g�̃��Z�b�g
		mcpAnimsprite->ResetAnimCnt();                             //! �A�j���[�V�����J�E���g�̃��Z�b�g
		AtkCnt.Press++;
	}
	else if (IdolCnt >= (60 * 3) && ToPx >= 1.4) {              //! �O�b�o�߂��Ă��Ă��{�X���痣��Ă�����
		if (!ShockWaved) {
			State = eNecthorState::State_ShockWave;
			mcpAnimsprite->ResetAnimCnt();                         //! �A�j���[�V�����J�E���g�̃��Z�b�g	
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
	IdolCnt++;
}

//! �U���̏���
void ReNecthor::Atk_PressHammer()
{
	//! �U���p�̃e�N�X�`���ɕύX
	TexState = Tex_Attack;
	
	//! �n���}�[���@������ꂽ���ʐU��	
	if (AnimX == 5) {
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_Atk, 0.2f);
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

		//! ��������
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
		if (WeekCol.TailHited || MyCol.TailHited) {
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

void ReNecthor::Atk_ShockWave()
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
			SoundMgr->PlaySE(SE_Necthor_Atk, 0.1f);
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
		AttackCoolTime = 0;
		State = eNecthorState::State_Idol;
		AtkSEflg = true;
		mcpAnimsprite->ResetAnimCnt(); //! �A�j���[�V�����J�E���g�̃��Z�b�g
	}
}

//! �A���Ռ��g�U��
void ReNecthor::Atk_RushWave()
{	
	//! �\������
	if (!RushPreparation) {	
		if (AtkSEflg) {
			SoundMgr->PlaySE(SE_Necthor_AtkSig, 0.1f);
			AtkSEflg = false;
		}
		TexState = Tex_Idol;
		NomalSmoke = true;
		//! �Ԃ��Ȃ�Ȃ���k����		
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
					SoundMgr->PlaySE(SE_Necthor_Atk, 0.2f);
					AtkSEflg = false;
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
				AtkSEflg = true;
				AttackCoolTime = 0;
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
					SoundMgr->PlaySE(SE_Necthor_SPAtk, 0.3f);
					AtkSEflg = false;
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

				//! ���ꂫ�̍��W�̌v�Z
				Vector2 DebriPos;
				DebriPos.x = Hammer->Vec.x - 0.26f;
				DebriPos.y = Hammer->Vec.y - 0.3f;
				Debri[0].get()->UpStart(DebriPos);     //! ���ꂫ���o��

				//! ��������
				Vector2 AllowPos;
				AllowPos.x = Hammer->Vec.x - 0.3f;
				AllowPos.y = Hammer->Vec.y + 0.2f;
				Allow->AllowOn(AllowPos);
			}
			else if (AnimX == 6) {
				mcpAnimsprite->SetStopAnimation(true);
				//! �n���}�[�̍U��������I�t�ɂ���
				Hammer->AtkCol->SetActiv(false);
				
				if (WeekCol.TailHited || MyCol.TailHited) {
					AttackCoolTime = 160;
				}
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
				State = eNecthorState::State_Idol;      //! �A�C�h����Ԃɖ߂�
				mcpAnimsprite->ResetAnimCnt();          //! �A�j���[�V�����J�E���g�̃��Z�b�g	
				RushPreparation = 0;
				AttackCoolTime = 0;
				RushCnt = 0;
				RushFrameCnt = 0;
				IdolCnt = 0;	
				AtkSEflg = true;
			}
		}
	}
}

//! �|��Ă���Ƃ��̏���
void ReNecthor::FallDwoned()
{
	//! ���ōU���̉摜���Z�b�g���Ă��܂�
	TexState = Tex_Attack2;
	mcpAnimsprite->SetXSplit(6); //! �Ō�̃R�}�ɃZ�b�g����
	//! �摜�̐F���Â�����
	mcpAnimsprite->SetColor(0.5f, 0.5f, 0.5f);

	Allow->AllowOn(Vector2(WeekCol.Pos.x, WeekCol.Pos.y + 0.1f));

	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->SmokeOff();
	}

	Hammer->AtkCol->SetActiv(false);
	MyCol.AtkCol->SetActiv(false);	
}

//! �Ƃǂ߂��h����Ĕj�󂳂�鎞�̏���
void ReNecthor::Destroy()
{
	//! ���ōU���̉摜���Z�b�g���Ă��܂�
	TexState = Tex_Attack2;
	mcpAnimsprite->SetXSplit(6); //! �Ō�̃R�}�ɃZ�b�g����
	mcpAnimsprite->SetColor(0.5,0.5,0.5);
	Allow->AllowOff();
	//! �X���[�N������
	Smokes[0]->SmokeOff();
	Smokes[1]->SmokeOff();
	Smokes[2]->SmokeOff();
	Allow->AllowOff();
	//! �����x�������Ă���
	if (Arufa > 0) {
		Arufa -= 0.01f;
	}
	else {
		mDestroy = true;
	}

	mcpAnimsprite->SetArufa(Arufa);
	//! ���j�G�t�F�N�g���o��
	if (DestroyCnt == 3) {
		SoundMgr->PlaySE(SE_Necthor_Bakuhatu,0.15f);
		EffMgr->PlayEffect(Explosion02,mcVec.x,mcVec.y - 0.2f,0.4f,0.4f,10);
	}
	else if (DestroyCnt == 10) {
		EffMgr->PlayEffect(Explosion02, mcVec.x + 0.2f, mcVec.y - 0.3f, 1.0f, 1.0f,12);
	}
	else if (DestroyCnt == 15) {
		EffMgr->PlayEffect(Explosion02, mcVec.x - 0.14f, mcVec.y - 0.33f, 0.6f, 0.6f,10);
	}
	else if (DestroyCnt == 18) {
		EffMgr->PlayEffect(Explosion02, mcVec.x - 0.1f, mcVec.y - 0.27f, 0.5f, 0.5f,14);
	}
	else if (DestroyCnt == 20) {
		EffMgr->PlayEffect(Explosion02, WeekCol.Pos.x, WeekCol.Pos.y,0.5f, 0.5f,10);
	}
	else if (DestroyCnt == 24) {
		EffMgr->PlayEffect(Explosion02, Hammer->Vec.x, Hammer->Vec.y, 0.9f, 0.9f,10);
	}
	else if (DestroyCnt == 26) {
		EffMgr->PlayEffect(Explosion02, MyCol.Pos.x, MyCol.Pos.y, 1.0f, 1.0f,10);
	}
	//! �n���}�[
	//! �{��
	//! �K���ȂƂ���

	DestroyCnt++;

	//! �S�Ă̓����蔻����I�t�ɂ���
	MyCol.AtkCol->SetActiv(false);
	MyCol.Col->SetActiv(false);
	WeekCol.AtkCol->SetActiv(false);
	WeekCol.Col->SetActiv(false);
	Hammer->AtkCol->SetActiv(false);
	Hammer->Col->SetActiv(false);
}

//! �{�̂̓����蔻��̒����֐�
void ReNecthor::ColFix()
{
	if (TexState == Tex_Idol) {
		MyCol.Pos.x = mcVec.x + 0.32f;
		MyCol.Pos.y = mcVec.y - 0.26f;
		MyCol.Size.x = 0.46f;
		MyCol.Size.y = 0.66f;
		MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
		MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

		//! ��_�̓����蔻��̈ʒu����
		WeekCol.Pos.x = mcVec.x + 0.34f;
		WeekCol.Pos.y = mcVec.y + 0.2f;
		WeekCol.Size.x = 0.2f;
		WeekCol.Size.y = 0.16f;
		WeekCol.AtkCol->SetActiv(true);
		WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
		WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

		//! �n���}�[�̓����蔻��̈ʒu���v�Z����
		Hammer->Vec.x = mcVec.x - 0.1;
		Hammer->Vec.y = mcVec.y - 0.44f;
	}
	else if (TexState == Tex_Attack || Tex_Attack2) {
		if (AnimX == 0) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! ��_�̓����蔻��̈ʒu����
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! �n���}�[�̓����蔻��̈ʒu���v�Z����
			Hammer->Vec.x = mcVec.x - 0.1;
			Hammer->Vec.y = mcVec.y - 0.44f;
		}
		else if (AnimX == 1) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! ��_�̓����蔻��̈ʒu����
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);
		}
		else if (AnimX == 2 || AnimX == 3) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! ��_�̓����蔻��̈ʒu����
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			Hammer->Vec.x = mcVec.x - 0.2f;
			Hammer->Vec.y = mcVec.y + 0.48f;
			Hammer->ColSize.x = 0.6f;
			Hammer->ColSize.y = 0.2f;

		}
		else if (AnimX == 4 || AnimX == 5 || AnimX == 6) {
			//! �{�̂̓����蔻��̈ʒu�̒���
			MyCol.Pos.x = mcVec.x + 0.05f;
			MyCol.Pos.y = mcVec.y - 0.4f;
			MyCol.Size.x = 0.4f;
			MyCol.Size.y = 0.4f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! ��_�̓����蔻��̈ʒu����
			WeekCol.Pos.x = mcVec.x + 0.1f;
			WeekCol.Pos.y = mcVec.y - 0.1f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(false);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! �n���}�[�̓����蔻��̈ʒu�̒���
			Hammer->Vec.x = mcVec.x - 0.40f;
			Hammer->Vec.y = mcVec.y - 0.5f;
			//! �n���}�[�̑傫�����Ƃɖ߂�
			Hammer->ColSize.x = 0.44f;
			Hammer->ColSize.y = 0.5f;
			Hammer->AtkCol->SetSize(0.44, 0.5f);
		
		}
		else if (AnimX == 7) {
			MyCol.Pos.x = mcVec.x + 0.18f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.58f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! ��_�̓����蔻��̈ʒu����
			WeekCol.Pos.x = mcVec.x + 0.18f;
			WeekCol.Pos.y = mcVec.y + 0.1f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! �n���}�[�̓����蔻��̈ʒu���v�Z����
			Hammer->Vec.x = mcVec.x - 0.28f;
			Hammer->Vec.y = mcVec.y - 0.44f;
		}
		else if (AnimX == 8) {
			MyCol.Pos.x = mcVec.x + 0.32f;
			MyCol.Pos.y = mcVec.y - 0.26f;
			MyCol.Size.x = 0.46f;
			MyCol.Size.y = 0.66f;
			MyCol.Col->SetSize(MyCol.Size.x, MyCol.Size.y);
			MyCol.AtkCol->SetSize(MyCol.Size.x, MyCol.Size.y);

			//! ��_�̓����蔻��̈ʒu����
			WeekCol.Pos.x = mcVec.x + 0.34f;
			WeekCol.Pos.y = mcVec.y + 0.2f;
			WeekCol.Size.x = 0.2f;
			WeekCol.Size.y = 0.16f;
			WeekCol.AtkCol->SetActiv(true);
			WeekCol.AtkCol->SetSize(WeekCol.Size.x, WeekCol.Size.y);
			WeekCol.Col->SetSize(WeekCol.Size.x, WeekCol.Size.y);

			//! �n���}�[�̓����蔻��̈ʒu���v�Z����
			Hammer->Vec.x = mcVec.x - 0.1f;
			Hammer->Vec.y = mcVec.y - 0.44f;
		}
	}
	Hammer->Col->SetSize(Hammer->ColSize.x, Hammer->ColSize.y);
}

void ReNecthor::Damage()
{
	//! ��_��������Ώ������J�n����
	if (TakenDamage != 0 && State != eNecthorState::State_Down) {
		DamageFlg = true;
		HP -= TakenDamage;
		if (State == State_Idol) {
			IdolCnt += 40;
		}
		TakenDamage = 0;
		DamageFrameCnt = 0;
	}

	//! �_���[�W�������Ă�����60�t���[���_�ł���
	if (DamageFlg) {
		if (HP > 0) {
			//! �_�ł�����
			if (DamageFrameCnt >= 60) {
				DamageFlg = false;
				SetDrawActiv(true); //! �Ō�ɕ`������ď������I���
			}
			else if ((DamageFrameCnt % 20) <= 10) {
				SetDrawActiv(false);
			}
			else { SetDrawActiv(true); }
			DamageFrameCnt++;
		}
		else {
			//! �_�ł�����
			if (DamageFrameCnt >= 96) {
				DamageFlg = false;
				SetDrawActiv(true); //! �Ō�ɕ`������ď������I���
			}
			else if ((DamageFrameCnt % 12) <= 4) {
				SetDrawActiv(false);
			}
			else { SetDrawActiv(true); }
			DamageFrameCnt++;
		}
	}
}

//! ���̍X�V����
void ReNecthor::SmokeUpdate()
{
	for (int i = 0; i < Smokes.size(); i++) {
		Smokes[i].get()->Update();
	}
	//! ���̃t���O�𗧂Ă�
	int AttackNum = AtkCnt.Press + AtkCnt.Wave;
	if (AttackNum == 1) {
		LeftSmoke = true;
	}
	if (AttackNum == 2) {
		RightSmoke = true;
	}
	
	Vector2 SmokePos[3]; //! 0 �^�� 1 �E 2 ��
	//! �e���̍��W�̌v�Z
	if (TexState == Tex_Idol) {	
		SmokePos[0] = Vector2(mcVec.x + 0.34f, mcVec.y + 0.68f);
		SmokePos[1] = Vector2(mcVec.x + 0.5f, mcVec.y + 0.2f);
		SmokePos[2] = Vector2(mcVec.x + 0.14f, mcVec.y + 0.2f);	
	}
	else if (TexState == Tex_Attack || TexState == Tex_Attack2){
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
			SmokePos[2] = Vector2(mcVec.x - 0.12f, mcVec.y -0.06f);
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

//! �e�N�X�`�������̏�Ԃɍ��킹�ĕύX����֐�
void ReNecthor::TexChange()
{
	//! �O�t���[���ƃe�N�X�`�����ς���Ă�����A�j���[�V�����J�E���g�����Z�b�g���ăe�N�X�`����ύX����
	if (TexState != TexState_Prev) {
		mcpAnimsprite->ResetAnimCnt();
		if (TexState == Tex_Idol) {
			mcpAnimsprite->SetAnimtionTable(5, 1);
			if (HightHP) {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol));
			}
			else {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Idol_Red));
			}
		}
		else if (TexState == Tex_Attack) {
			mcpAnimsprite->SetAnimtionTable(9, 1);
			if (HightHP) {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack));
			}
			else {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack_Red));
			}
		}
		else if (Tex_Attack2) {
			mcpAnimsprite->SetAnimtionTable(9, 1);
			if (HightHP) {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack2));
			}
			else {
				mcpAnimsprite->SetTexture(TEXTURE(Tex_Necthor_Attack2_Red));
			}
		}
	}
	TexState_Prev = TexState;


}
