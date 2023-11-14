#include "Character.h"
#include "Time.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "Camerah.h"
//! �R���X�g���N�^
Character::Character()
{
	ColSize = Vector2(msSize.x,msSize.y);
	mcpBoxCol = new Box(mcVec, ColSize.x, ColSize.y); //! ��`�̓����蔻��̐���
	mcpShape = mcpBoxCol;                              
	mcMoveVector = 0;
	mTouchGraund = true; //! �ŏ��͒n�ʂɂ��Ă�����
	mcpImage = new Image;
	CurrentTime = PrevTime = GravityTime = 0;
}


//! �f�X�g���N�^
Character::~Character()
{
	delete mcpBoxCol;
	delete mcpImage;
}


//! �L�����N�^�[�X�V���� 
//! �� �p����̍X�V�����ł͈�ԍŌ�ɋL�q���Ă��������B
void Character::Update()
{
	/* ����������������������������������������������������������������������
	��  [ �����̗���E�E�E]                                                ��
	�� �p����̃N���X�ňړ��ȂǁA�ړ�����x�N�g���ʊւ��鏈�����������Ƃ�  ��
	�� Character::Update()���ĂԁACharacter::Update()�ňړ��x�N�g���ɏd��  ��
	�� �x�N�g���������A���̃t���[���ł̍ŏI�I�Ȉړ��x�N�g���ʂ��v�Z����A  ��
	�� ���Ɉʒu�x�N�g���Ɉړ��x�N�g�������Z����B�Ō�Ɏ��̃t���[���Ōv�Z  ��
	�� ���邽�߂ɁA�ړ��x�N�g�����O�ɂ���B							       ��
	�� ��������������������������������������������������������������������*/

	if (mAlive) {
		bool Vibe = CAMERA->GetVibration();
		bool OnObj = mcpBoxCol->GetOnObj(); //! �I�u�W�F�N�g�̏�ɂ̂��Ă��邩���擾
		if (OnObj == true) {
			mTouchGraund = true;
		}
		//! ��ʐU�����Ă���Ƃ��͏d�͂������Ȃ�
		if (mTouchGraund == false && Vibe == false) {
			double ElapsedTime = CurrentTime - GravityTime;
			float Gravtiy = -ga * pow(ElapsedTime, 2) / 2.0f; //! �d�͂ɂ�鉺�����̗͂̌v�Z	�~���b�ł̌v�Z�Ȃ̂�1000�Ŋ���
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
		mcMoveVector.SetVector(0, 0);        //! ���̃L�����N�^�[�ɂ������Ă���͂��O�ɂ���
		mcpBoxCol->SetOnObj(false);         //! ��ɂ͏���Ă��Ȃ����Ƃɂ���@������false�ɂ�������Collsion���������肷��̂ł�����false�ɂ��܂�
		//! ��������ɃT�C�Y�Z�b�g
		mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
		AnimationHitObject::Update();
	}
}



//! �����蔻����������Ƃ��p��Draw�ł�
void Character::Draw()
{
	if (mcpBoxCol->GetActiv() == true) {
		mcpImage->DrawSprite(mcVec.x, mcVec.y, ColSize.x * msScale.x, ColSize.y * msScale.y, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
	}
}

//! �^�b�`�O���E���h�̃Z�b�^�[
void Character::SetTouchGround(bool _state)
{
	mTouchGraund = _state;
}

//! ��`�̓����蔻����̃Q�b�^�[
Box * Character::GetBoxCol()
{
	return mcpBoxCol;
}
