#include "PlayerBattry.h"
#include "TextureManager.h"

//! �R���X�g���N�^
PlayerBattery::PlayerBattery()
{
	Battery.reset(new AnimationHitObject);
	Battery->SetVec(Vector2(-1.4f, 0.64f));
	Battery->SetSize(0.7f,0.47f);
	Battery->SetCameraActiv(false);
	AnimationSprite *  Sp = Battery->GetAnimSprite(); //! �A�j���[�V�����X�v���C�g�̎擾
	Sp->SetTexture(TEXTURE(Tex_Battery));
	Sp->SetAnimtionTable(8, 2);	
	Sp->SetStopAnimation(true);

	NumBattryDraw = NowCharge = 0;
	DifCharge = WaitFrameCnt = 0;
	Wait = false;
	WaitFrameLow = 30;
}

//! �f�X�g���N�^
PlayerBattery::~PlayerBattery()
{
}

//! �X�V����
void PlayerBattery::Update(int _charge)
{
	NowCharge = _charge;                   //! ���݂Ƀ`���[�W�ɑ��
	if (!Wait) {
		//! �������������ɕ\�����P�i�߂�
		if (NowCharge > NumBattryDraw) {
			NumBattryDraw++;
			if (NumBattryDraw > 7) {
				NumBattryDraw = 7;
			}	
			Wait = true;
		}
		else if(NowCharge < NumBattryDraw){
			NumBattryDraw--;
			if (NumBattryDraw < 0) {
				NumBattryDraw = 0;
			}
			//Down = true;
			Wait = true;
		}
		
	}
	else {	
		//! 3�t���[���҂�
		if (WaitFrameCnt >= 10) {
			Wait = false;
			WaitFrameCnt = 0;
		}
		WaitFrameCnt++;
	}
	AnimationSprite *  Sp = Battery->GetAnimSprite(); //! �A�j���[�V�����X�v���C�g�̎擾
	Sp->SetXSplit(NumBattryDraw);
}

//! �`�揈��
void PlayerBattery::Draw()
{
	Battery->Draw();
}
