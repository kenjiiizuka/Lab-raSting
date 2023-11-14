#include "Player.h"
#include "TextureManager.h"
#include "DirectInput8.h"
#include "Time.h"
#include "Angle.h"
#include "Input.h"
#include "Controller.h"
#include "Camerah.h"
#include "WinMain.h"
#include "EffectManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "PlayerSmoke.h"
#include "HPICon.h"
#include "PlayerBattry.h"

//! �R���X�g���N�^
Player::Player()
{
	//! �摜��A�j���[�V�����A�X�e�[�^�X�̐ݒ�
	mTag = Tag_Player;
	mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! �����ۂ̕t�����̈ʒu
	msSize = FLOAT2(0.32f, 0.32f);
	ColSize = Vector2(0.18f, 0.26f);
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);

	mDirection = Right; //! �����̐ݒ�
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Idol));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	mcpAnimsprite->SetSize(msSize.x, msSize.y);
	mcpPlugTail = new PlugTail(mcTailRoot, mcVec, mState, mDirection, mElectState);

	mNumBoruto = mToalBoruto = 0;
	mState = Player_Idol_Walk; //! �v���C���[�̏�Ԃ̐ݒ�
	mElectState = Elect_None;  //! �v���C���[�̑ѓd�̏��
	//! �t���O�̏�����
	AttackFlg = false;
	OnObj = false;
	
	Smoke = new PlayerSmoke;
	msStatus.HP = 5;
	Shive = 0.01f;

	mcpHPIcon = new HPICon(msStatus.HP,-0.17f,0.8f);
	Battery = new PlayerBattery();

	UIFrame = new AnimationHitObject;
	UIFrame->SetCameraActiv(false);
	AnimationSprite * UIFrameSp = UIFrame->GetAnimSprite();
	UIFrameSp->SetTexture(TEXTURE(Tex_UIFrame));
	//UIFrameSp->SetAnimtionTable(13,2);
	UIFrameSp->SetAnimtionTable(1, 1);
	UIFrame->SetSize(1.6f,0.6f);
	UIFrame->SetVec(Vector2(-1.1f,0.7f));
}


Player::Player(float _x, float _y)
{
	//! �摜��A�j���[�V�����A�X�e�[�^�X�̐ݒ�
	mcVec.y = _y;	
	mcVec.x = _x;
	mTag = Tag_Player;
	mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! �����ۂ̕t�����̈ʒu
	msSize = FLOAT2(0.32f, 0.32f);
	ColSize = Vector2(0.18f, 0.26f);
	mcpBoxCol->SetSize(ColSize.x, ColSize.y);
	
	mDirection = Right; //! �����̐ݒ�
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Idol));
	mcpAnimsprite->SetAnimtionTable(6,2);
	mcpAnimsprite->SetSize(msSize.x, msSize.y);
	mcpPlugTail = new PlugTail(mcTailRoot, mcVec, mState,mDirection, mElectState);

	mNumBoruto = mToalBoruto = 0;
	mState = Player_Idol_Walk; //! �v���C���[�̏�Ԃ̐ݒ�
	mElectState = Elect_None;  //! �v���C���[�̑ѓd�̏��
	//! �t���O�̏�����
	AttackFlg = false;
	OnObj = false;
	Smoke = new PlayerSmoke;
	msStatus.HP = 5;
	Shive = 0.01f;
	mcpHPIcon = new HPICon(msStatus.HP, -1.65f, 0.8f);
	Battery = new PlayerBattery();
	UIFrame = new AnimationHitObject;
	UIFrame->SetCameraActiv(false);
	AnimationSprite * UIFrameSp = UIFrame->GetAnimSprite();
	UIFrameSp->SetTexture(TEXTURE(Tex_UIFrame));
	UIFrameSp->SetAnimtionTable(24, 1);
	UIFrame->SetSize(1.55f, 0.54f);
	UIFrame->SetVec(Vector2(-1.1f, 0.75f));
}

//! �f�X�g���N�^
Player::~Player()
{
	delete mcpPlugTail;
	delete mcpHPIcon;
	delete Smoke;
	delete Battery;
	delete UIFrame;
}

//! �X�V����
void Player::Update()
{		
	State_Controller();
	Electricity(); //! �ѓd�̏���
	//! �����̕ύX�Ƃ����ۂ̕t�����̈ʒu���o��
	if (mDirection == Left) { //! ��
		mcTailRoot = Vector2(mcVec.x + 0.086f, mcVec.y - 0.046f); //! �����ۂ̕t�����̈ʒu	
	}
	//! �E
	else {
		mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! �����ۂ̕t�����̈ʒu	
	}
	
	mcpPlugTail->Update();    //! �����ۂ̍X�V����
	//! �h�������d�@���I�[�o�[�q�[�g���Ă�����_���[�W���󂯂�
	if (mcpPlugTail->GetOverheat()) {
		msDamage.Overheat = true;
		//! �K���ɔ�����悤�ɂ���
		mcpPlugTail->TailReturn();
	}

	ForceProces();                       //! ���̃t���[���ł��������͂����Z����	
	Battery->Update(msElect.ChargeCnt);  //! �o�b�e���[UI�̍X�V
}

//! �����蔻�菈���̂��Ƃɍs���鏈��
void Player::LastUpdate()
{
	Damage();   //! �_���[�W�̏���������
	Recovary(); //! �񕜂̏���
	mcpHPIcon->Update(msStatus.HP);

	if (mcVec.y < -0.8f) {
		mcVec.y = -0.67f;
	}
}

//! �`�揈��
void Player::Draw()
{
	mcpAnimsprite->SetYSplit(mDirection);
	if (TailDraw) {
		mcpPlugTail->Draw();
	}
	Smoke->Draw();
	GameObject::Draw();
	//! UI�̕`��
	if (UIActiv) {
		UIFrame->Draw();
		mcpHPIcon->Draw();
		Battery->Draw();
	}
}

//! �_���[�W�̃Z�b�^�[
void Player::SetDamege(eDirection _nockback)
{
	if (!msDamage.Flg) {
		msDamage.Flg = true;
		msDamage.NockBackWay = _nockback;
		SoundMgr->PlaySE(SE_Damage,0.1f);
	}
}

//! HP�̃Q�b�^�[UI�Ɏg���Ǝv��
int Player::GetHP()
{
	return msStatus.HP;
}

bool Player::GetCharge()
{
	if (mElectState == eElectricity::Elect_Super) {
		return true;
	}
	return false;
}

void Player::AddBoruto()
{
	mNumBoruto++;
	mToalBoruto++;
	//! 10�E�������
	if (mNumBoruto >= 10) {
		mNumBoruto = 0;
		mRecovery = true;
	}	
}

/* ----------------- 
// �ѓd������֐� */
void Player::AddElect()
{
	msElect.ChargeCnt++;
}

void Player::MoveStop(bool state)
{
	Stop = state;
}

void Player::SetUIActiv(bool _activ)
{
	UIActiv = _activ;
}

/* ------------- 
// �ѓd�̏��� */
void Player::Electricity()
{	
	if (7 <= msElect.ChargeCnt && GetControllerButtonTrigger(Button_LB)) 
	{
		mElectState = Elect_Super;
	}	
	
	switch (mElectState)
	{	
	case Elect_Super:
		//! �ŏ��̈�x�����Đ�
		if (msElect.SuperCnt == 0) {
			EffMgr->PlayFollowEffect(ElectSuper01, mcVec.x, mcVec.y,0.5f,0.5f, true);
			mcpPlugTail->SetFlash(false);
		}	
		msElect.SuperCnt++;
		msElect.UpRate = 1.5f;
		if (msElect.SuperCnt % 180 == 0) {SoundMgr->PlaySE(SE_Taiden, 0.04f);}
		if (msElect.SuperCnt % 150 == 0) {SoundMgr->PlaySE(SE_Taiden, 0.04f);}	


		if (msElect.SuperCnt >= (20 * 60)) {			
			mcpPlugTail->SetFlash(true);
		}

		if (msElect.SuperCnt >= (30 * 60)) {
			mElectState = Elect_None;
			EffMgr->LoopStop(ElectSuper01);
			msElect = SElectricity();
		}
		break;
	case Elect_None:
		break;
	}
}

/* ---------------------------------------
// �R���g���[���[�̎��̏�Ԃɉ��������� */
void Player::State_Controller()
{
	//! ��Ԃ̍X�V
	if (msStatus.HP <= 0) {
		mState = Player_Down;
	}
	else if (!GetControllerButtonPress(Button_LT)) {
		if (mcpPlugTail->GetTailRactionState()) {	
			if (mcpPlugTail->SetState(TailState::Tail_Idol)) {
				mState = Player_Idol_Walk;
				KamaeSE = true;
			}
		}
	}
	else {
		MoveReady();
		//! �Ր�Ԑ�	
		mState = Player_Attack;
		mcpPlugTail->SetState(TailState::Tail_Attack);
		//! �摜�̐؂�ւ�
		mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Aim));
		if (KamaeSE) {
			SoundMgr->PlaySE(SE_Kamae,0.25f);
			KamaeSE = false;
		}
		mcpPlugTail->SetAttackState(TailAttackState::AttackState_Aim);
		msStatus.MoveAble = true; //! �W�����v���ɃG�C�������Ƃ��ɓ���̃A�j���[�V�������ɃG�C���ɂ����ƕ����Ȃ��Ȃ�̂ł����ŁA������悤�ɂ���
		msJump.Doing = false;
		msJump.End = false;
		msJump.Up = false;
		msJump.Jump = false;
		mcpAnimsprite->SetStopAnimation(false);		
	}

	//! ��Ԃɉ���������
	switch (mState)
	{
	case Player_Idol_Walk:
		Move_Controller();	
		break;
	case Player_Attack:	
		break;
	case Player_Down:
		Destroy();
		break;
	}
}

//! �v���C���[�����W�����v�Ȃǂ́A���̃L�����N�^�[�Ƃ͈Ⴄ�����������Ȃ�Ɨ\�z�����̂ŁA���̊֐����ŏd�͂̏�����A���������͂̉��Z�Ȃǂ��s���܂�
void Player::ForceProces()
{
	if (!ChangeDestroy) {
		bool Vibe = CAMERA->GetVibration();
		OnObj = mcpBoxCol->GetOnObj();

		//!��ʐU�������Ă��炸�A�n�ʂɐG��Ă��Ȃ��Ƃ��A�܂��̓W�����v���ɏd�͂�������
		if (OnObj == false && mTouchGraund == false && Vibe == false || msJump.Doing) {
			double ElapsedTime = CurrentTime - GravityTime;
			float Gravtiy = -ga * pow(ElapsedTime, 2) / 2.0f; //! �d�͂ɂ�鉺�����̗͂̌v�Z
			//! �d�͂̉e���̍ő�l�𒴂��Ȃ��悤�ɂ���
			if (Gravtiy >= 0.02f) {
				Gravtiy = 0.02f;
			}
			mcMoveVector.y += Gravtiy; //! �d�̗͂͂����Z
		}
		else {
			GravityTime = CurrentTime; //! �b�P�ʂ̍��̎��Ԃ��擾����
		}
		CurrentTime += (1.0f / 60.0f);  //! �o�ߎ��Ԃ𑝂₷
		mcpBoxCol->SetPrevVec(mcVec);       //! �O�t���[���̍��W�Ƃ��ĕۑ�����
		mcVec += mcMoveVector;              //! ���̃L�����N�^�[�ɂ������Ă���͂𑫂�
		mcpShape->SetMoveVec(mcMoveVector); //! �����蔻��Ɏg�����߂̏����Z�b�g
		CameraMoveMent = mcMoveVector;
		mcMoveVector.SetVector(0, 0);       //! ���̃L�����N�^�[�ɂ������Ă���͂��O�ɂ���
		mcpBoxCol->SetOnObj(false);
		//! ��������ɃT�C�Y�Z�b�g
		mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
		AnimationHitObject::Update();
	}
}


/* -----------------------------------------
// �}�E�X���쎞�̈ړ��ƃW�����v�̏������� */
void Player::Move_Mouse()
{
	//! ���E�ړ� �L�[
	if (!msJump.Up) {
		if (!DI8->mKeyBoard->GetKeyPress(DIK_LSHIFT) && !DI8->mKeyBoard->GetKeyPress(DIK_LCONTROL)) {
			if (DI8->mKeyBoard->GetKeyPress(DIK_LEFT) || DI8->mKeyBoard->GetKeyPress(DIK_A)) {
				mcMoveVector.x += -msStatus.MoveSpeed;
				mDirection = Left;
			}
			if (DI8->mKeyBoard->GetKeyPress(DIK_RIGHT) || DI8->mKeyBoard->GetKeyPress(DIK_D)) {
				mcMoveVector.x += msStatus.MoveSpeed;
				mDirection = Right;
			}
		}
	}

	Jump(); //! �W�����v�֐�
	//! �f�o�b�O�p�̏���
	if (DI8->mKeyBoard->GetKeyTrigger(DIK_RETURN)) {
		msJump.Doing = false;
		msJump.End = false;
		msJump.Up = false;

		mTouchGraund = true;
		mcVec.SetVector(0, -0.4f);
	}
}


/* -------------------------------------------------
// �R���g���[���[���쎞�̈ړ��ƃW�����v�̏������� */
void Player::Move_Controller()
{
	//! ���E�ړ��@�R���g���[���[
	Vector2 LeftStick = GetControllerLeftStick() * 1.0f;
	//! �W�����v�̗��ߒ���
	if (msStatus.MoveAble) {
		mcMoveVector.x += (LeftStick.x) * msElect.UpRate;
	}

	//! �摜�ƌ����̕ύX
	//! �ړ����ĂȂ���
	if (LeftStick.x == 0) {
		if (!msJump.Jump) {
			mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Idol));
			mcpAnimsprite->SetAnimSpeed(8);
		}
	}
	else {	
		//! �ړ����Ă��鎞���AJump���Ă��Ȃ��Ƃ�
		if (!msJump.Jump) {
			mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Run));
			mcpAnimsprite->SetAnimSpeed(6);
			int AnimX = mcpAnimsprite->GetCurrentXSplit();
			if (AnimX == 5) {
				mcpAnimsprite->SetXSplit(0);
			}
		}
		else {
			mcpAnimsprite->SetAnimSpeed(8);
		}

		if (LeftStick.x < 0) {
			mDirection = Left;
		}
		else {
			mDirection = Right;
		}		
	}
	Jump(); //! �W�����v�֐�
}

void Player::MoveReady()
{
	if (msStatus.MoveAble) 
	{
		Vector2 LeftStick = GetControllerLeftStick() * 0.1f;
		mcMoveVector.x += (LeftStick.x) * msElect.UpRate;
	}
}

/* ------------------------------------------------------------
// �W�����v�֐�                                              //
// ����̃{�^�����Ⴄ�����Ȃ̂łǂ���̑���ł������֐��ōs��*/
void Player::Jump()
{
	//! �W�����v���Ă��Ȃ��Ƃ�
	if (!msJump.Jump) {
		//mcpAnimsprite->SetAnimSpeed(8);
		msJump.AnimCnt = 0;
		msJump.FrameCnt = 0;
		msJump.End = false;
		msJump.Jump = false;
	}

	//! �W�����v���I�����Ă�����
	if (msJump.End) {
		msJump.AnimCnt++;
		//! �Ō�̒��n�̊G��`�悷��܂ő҂�
		if (msJump.AnimCnt >= 4) {
			mcpAnimsprite->ResetAnimCnt();
			mcpAnimsprite->SetAnimSpeed(8);	
			msJump.AnimCnt = 0;
			msJump.FrameCnt = 0;
			msJump.End = false;
			msJump.Jump = false;
		}
	}
	//! �{�^���������ꂽ��W�����v�̂��߂ɓ���
	if (msJump.End == false && msJump.Doing == false && msJump.Up == false) {
		if (DI8->mKeyBoard->GetKeyTrigger(DIK_SPACE) || GetControllerButtonTrigger(Button_A)) {
			msJump.Up = true;
			msStatus.MoveAble = false; //! �ړ��s��
			msJump.Jump = true;
			//! �W�����v�p�̉摜�ɐ؂�ւ���
			mcpAnimsprite->ResetAnimCnt();
			float UpLate = msElect.UpRate;
			if (UpLate > 1.2f) {
				UpLate = 1.2f;
			}
			msStatus.TmpJumpPower = msStatus.InitJumpPower * UpLate; //! �W�����v�̗͂�ݒ肷��
			mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Player_Jump));
		}
	}
	//! �W�����v�̗��߃��[�V����
	else if (msJump.Up) {
		//! �A�j���[�V�����p�̃J�E���g��i�߂�
		msJump.AnimCnt++;
		//! ���߂Ă���摜���t���[�����o�߂�����Jump�J�n
		if (msJump.AnimCnt >= 6) {		
			SoundMgr->PlaySE(SE_Jump, 0.05f); //! �W�����vSE
			msJump.Doing = true; //! �W�����v���ɂȂ�
			msJump.Up = false; //! ���߂���߂�
			msStatus.MoveAble = true;
			//! �n�ʂ��痣���
			mTouchGraund = false;
			OnObj = false;
			mcpBoxCol->SetOnObj(false);
		}
	}
	
	//! �ō����B�_�����߂Ă����čō����B�_�ɂȂ�܂ŁA���߂̓W�����v�̗͂��傫�����񂾂񏬂����Ȃ�悤�ɂ���
	//! �W�����v���̏���		
	if (msJump.Doing) {	
		mcMoveVector.y += msStatus.TmpJumpPower * sin(DegreeToRadian(90));
		if (mcMoveVector.x > 0.0f) {
			mcMoveVector.x += 0.002f;
		}
		else if (mcMoveVector.x < 0.0f) {
			mcMoveVector.x += -0.002f;
		}
		if (msJump.FrameCnt >= 3 && msJump.FrameCnt <= 6) {
			msStatus.TmpJumpPower -= 0.004f; //���񂾂�W�����v�͂����炵�čs��
		}
		//! ���_�ɂ�����@�W�����v�̃A�j���[�V�����J�E���g��40�`43�̊�
		if (msJump.AnimCnt >= 40 && msJump.AnimCnt <= 41) {
			mcpAnimsprite->SetStopAnimation(true); //! �A�j���[�V�������~�߂�
		}
		//! �������n�߂���A�j���[�V������i�߂�
		else if (msJump.AnimCnt >= 42) {
			mcpAnimsprite->SetStopAnimation(false); //! �A�j���[�V������i�߂�
		}
		msJump.FrameCnt++; //�W�����v�p�̃J�E���g
		msJump.AnimCnt++; //! �W�����v�p�̃A�j���[�V�����J�E���g
	}

	//! �W�����v���Ēn�ʂɒ��n������W�����v�I���ɂ���
	if ((mTouchGraund && msJump.Doing) || (OnObj && msJump.Doing)) {
		msJump.Doing = false;
		msJump.End = true; //! �W�����v�I��
		mcMoveVector.y = 0;
		msJump.AnimCnt = 0;
		mcpAnimsprite->SetStopAnimation(false);
	}
}

/* ----------------------------- 
// �_���[�W���󂯂��Ƃ��̏���*/
void Player::Damage()
{
	if (msDamage.Flg) {
		//! �G�t�F�N�g���J�n����O�Ɉ�x����HP�����炷
		if (!msDamage.Effect) {
			msStatus.HP -= 1; //! HP�����炷
			//! HP���[���Ȃ�_���[�W���o�͂��Ȃ�
			if (msStatus.HP <= 0) {
				msStatus.MoveAble = false; //! �m�b�N�o�b�N���I���܂ňړ��s��
				msDamage.Flg = false;      
				// EffMgr->PlayFollowEffect(PlayerSmoke,mcVec.x,mcVec.x,true);
			}
			else {
				msDamage.Effect = true;
				msDamage.NockBack = true;
				msStatus.MoveAble = false; //! �m�b�N�o�b�N���I���܂ňړ��s��
			}	
		}
		else {
			//! �m�b�N�o�b�N
			if (msDamage.NockBackWay == Left) { //! ��
				if (msDamage.Cnt < 10) {
					mcMoveVector.y += 0.014f;
					mcMoveVector.x += -0.01f;
				}
				else if(msDamage.Cnt < 16){	
					mcMoveVector.x += -0.012f; 	
				}
				else if (msDamage.Cnt >= 26) {
					msDamage.NockBack = false;
					msStatus.MoveAble = true;
				}
			}
			else if(msDamage.NockBackWay == Right){ //! �E				
				if (msDamage.Cnt < 10) {
					mcMoveVector.y += 0.014f;
					mcMoveVector.x += 0.01f;
				}
				else if (msDamage.Cnt < 16) {
					mcMoveVector.x += 0.012f;
				}
				else if(msDamage.Cnt >= 26){
					msDamage.NockBack = false;
					msStatus.MoveAble = true;
				}
			}
			//! �_�ł�����
			if ((msDamage.Cnt % 20) <= 10) {
				SetDrawActiv(false);
				TailDraw = false;
			}
			else {
				SetDrawActiv(true);
				TailDraw = true;
			}
			msDamage.Cnt++;
		}
		//! 60�t���[���𒴂�����
		if (msDamage.Cnt > 120) {
			SetDrawActiv(true);
			TailDraw = true;
			msDamage.Flg = false;
			msDamage.Effect = false;
			msDamage.Cnt = 0;
			msDamage.NockBack = false;
		}
	}

	if (msDamage.Overheat) {
		if (!msDamage.Effect) {
			msStatus.HP -= 1; //! HP�����炷
			msDamage.Effect = true;
		}
		else {
			//! �_�ł�����
			if ((msDamage.Cnt % 20) <= 10) {
				SetDrawActiv(false);
				TailDraw = false;
			}
			else {
				SetDrawActiv(true);
				TailDraw = true;
			}

			if (msDamage.Cnt < 10) {
				mcMoveVector.y += 0.014f;
				mcMoveVector.x += -0.01f;
			}
			else if (msDamage.Cnt < 16) {
				mcMoveVector.x += -0.012f;
			}
			else if (msDamage.Cnt >= 26) {
				msDamage.NockBack = false;
				//msStatus.MoveAble = true;
			}

			msDamage.Cnt++;
		}
		//! 30�t���[����������
		if (msDamage.Cnt > 50) {
			SetDrawActiv(true);
			TailDraw = true;
			msDamage.Overheat = false;
			msDamage.Effect = false;
			msDamage.Cnt = 0;
		}
	}
}
/* --------------------- 
// �񕜂���Ƃ��̏��� */
void Player::Recovary()
{
	/*if (GetControllerButtonTrigger(Button_B)) {
		mRecovery = true;
	}*/

	if (mRecovery) {
		SoundMgr->PlaySE(SE_Heal,0.08f);
		//! HP���ő�ł͂Ȃ��Ƃ��̂݉񕜂���
		if (msStatus.HP <= 4) {
			msStatus.HP += 1;
		}
		mRecovery = false;
		//! ������ւ�ŉ񕜃G�t�F�N�g���o��
		EffMgr->PlayFollowEffect(eEffect::Recovery, mcVec.x, mcVec.y,0.2f,0.2f);
		EffMgr->PlayFollowEffect(eEffect::Hp_Recvery, mcVec.x, mcVec.y, 0.2f, 0.2f);
	}
}


/* ------------------------ 
// HP��0�ɂȂ������̏��� */
void Player::Destroy()
{
	mcpAnimsprite->SetStopAnimation(false); //! �A�j���[�V�����̂��Ƃ܂��Ă���ꍇ����̂�
	//! �摜�̃Z�b�g
	if (!ChangeDestroy) {	
		mcpAnimsprite->ResetAnimCnt();
		mcpAnimsprite->SetAnimtionTable(6, 2);
		SetControllerVibrationTime(20,20,30);
		ChangeDestroy = true;
		mcpBoxCol->SetActiv(false);
		mElectState = eElectricity::Elect_None;	
		EffMgr->LoopStop(ElectSuper02);
		SoundMgr->PlaySE(SE_Damage, 0.3f);
		Death = true;
	}

	msStatus.MoveAble = false;
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_Down));

	//! �������_�ł��ĉ����G�t�F�N�g���o���Ȃ���
	if (DestroyCnt < 120) {
		if ((DestroyCnt % 20) <= 10) {
			SetDrawActiv(false);
			TailDraw = false;
		}
		else {
			SetDrawActiv(true);
			TailDraw = true;
		}
	}
	else {
		SetDrawActiv(true);
		TailDraw = true;

		//! �X���[�N���o��
		if (mDirection == Left) {
			Smoke->SmokeStart(Vector2(mcVec.x - 0.01f, mcVec.y + 0.1f));
		}
		else {
			Smoke->SmokeStart(Vector2(mcVec.x + 0.01f, mcVec.y + 0.1f));
		}
	}
	int XFrame = mcpAnimsprite->GetCurrentXSplit();

	if (XFrame == 5) { //! �A�j���[�V�������~�߂�
		mcpAnimsprite->SetStopAnimation(true);
		//! �����݂ɐk����
		mcMoveVector.x += Shive;
		if ((DestroyCnt / 4) == 0) {
			Shive *= -1;
		}
	}

	if (DestroyCnt >= (60 * 5)) {
		Destroyed = true;
	}

	DestroyCnt++;

	if (Destroyed) {
		SetDrawActiv(false);
		SetHitActiv(false);
		mcpPlugTail->Destroy(); //! �����ۂ��j������
		mAlive = false;         //! �����t���O�܂�
	}
}

//! �ȉ��Z�b�^�[�A�Q�b�^�[ ������������������������������������������������������������������������������������������������������������������������
//! �v���C���[�p�̍��W�̃Z�b�^�[
//! �X�V�����̌�ɃZ�b�g���Ă��܂��ƁA���̍X�V�����܂ŕt�����̈ʒu���Â�Ă��܂��̂Ŗh�~�̂��߂ɐ�p�ɍ��
void Player::SetVec(Vector2 _vec)
{
	mcVec = _vec;
	if (mDirection == Left) {
		mcTailRoot = Vector2(mcVec.x + 0.086f, mcVec.y - 0.046f); //! �����ۂ̕t�����̈ʒu	
	}
	else {
		mcTailRoot = Vector2(mcVec.x - 0.08f, mcVec.y - 0.046f); //! �����ۂ̕t�����̈ʒu
	}
}

//! �����ۂ̓����蔻��̃Q�b�^�[
Box * Player::GetTailCol()
{
	return mcpPlugTail->GetCol();
}

//! �U���̓����蔻��̃Q�b�^�[
Circle* Player::GetAttackCol()
{
	return mcpPlugTail->GetAttackCol();
}

Circle Player::GetSpearCol(int _index)
{	
	if (_index == 0) {
		return mcpPlugTail->GetSpearCol();
	}
	return mcpPlugTail->GetSpearColRoot();	
}

//! �U�����Ă邩�̃Q�b�^�[
bool Player::GetAttackFlg()
{
	return AttackFlg;
}

//! �h�������̃Q�b�^�[
float Player::GetStingPower()
{
	return mcpPlugTail->GetStingPower();
}

//! �����ۂ̍����̃Q�b�^�[
Vector2 Player::GetTailRoot()
{
	return mcTailRoot;
}

Vector2 Player::GetCameraMovement()
{
	return CameraMoveMent;
}

bool Player::GetDeath()
{
	return Death;
}

//! �����ۂ̎h������̃��A�N�V�����̃Z�b�^�[
void Player::SetReaction(TailReaction _reaction ,eDirection _direction)
{	
	mcpPlugTail->SetReaction(_reaction, _direction);
}

//! �����ۂ̃Q�b�^�[
PlugTail * Player::GetTail()
{
	return mcpPlugTail;
}

