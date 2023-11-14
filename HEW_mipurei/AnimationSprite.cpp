#include "AnimationSprite.h"
#include "VERTEX2D.h"
#include "Angle.h"
#include <math.h>
#include "WinMain.h"
#include "GameManager.h"

//! �R���X�g���N�^
AnimationSprite::AnimationSprite(Vector2 & _pos) : Sprite::Sprite(_pos)
{
	mAnimSpeed = 8;
	mAnimCnt = 0;
	mYSplit = mCurrentXsplit = 0;
	mAnimTableElemnt = 4;
	StopAnimation = false;
	//! �A�j���[�V�����e�[�u���̏����l�ݒ�@���R�����A�c�S�����@���Q�[���̑f�ނň�ԑ��������ɍ��킹�Đݒ肷��悤�ɂ���Ɨǂ�
    mpAnimTable = new int[mAnimTableElemnt];
	mpAnimTable[0] = 0;
	mpAnimTable[1] = 1;
	mpAnimTable[2] = 2;
	mpAnimTable[3] = 1;

	//! �P�R�}��UV�T�C�Y
	mSizeU = (1.0f / 3.0f);
	mSizeV = (1.0f / 4.0f);	
}


//! �f�X�g���N�^
AnimationSprite::~AnimationSprite()
{	
	delete[] mpAnimTable;
	mpAnimTable = nullptr;
}


//! �X�V����
void AnimationSprite::Update()
{	
	VERTEX2D vx[4];     //! �l���_�̈ʒu	
	VERTEX2D vertex[6]; //! ���_�̐ݒ�@�o�b�t�@�ɑ���p

	int XSplit;
	//! UV���W���v�Z����
	if (mAnimTableElemnt != 0) 
	{
		int Index = (mAnimCnt / mAnimSpeed) % mAnimTableElemnt; // �A�j���[�V�����e�[�u���̓Y����	
		XSplit = mpAnimTable[Index];
		mCurrentXsplit = XSplit;
	}
	else 
	{
		XSplit = 0;
	}

	float uLeft = mSizeU * XSplit;
	float uRight = uLeft + mSizeU;
	float vTop = mSizeV * mYSplit;
	float vBottom = vTop + mSizeV;

	//! �p�x��ݒ肵�Ă��Ȃ��ꍇ
	if (mAngle == 0.0f) {
		vx[LEFTDOWN] = { msPos.x - msSize.x / 2.0f , msPos.y - msSize.y / 2.0f ,uLeft,vBottom, msColor };
		vx[RIGHTDOWN] = { msPos.x + msSize.x / 2.0f , msPos.y - msSize.y / 2.0f ,uRight,vBottom, msColor };
		vx[LEFTTOP] = { msPos.x - msSize.x / 2.0f , msPos.y + msSize.y / 2.0f ,uLeft,vTop, msColor };
		vx[RIGHTTOP] = { msPos.x + msSize.x / 2.0f , msPos.y + msSize.y / 2.0f ,uRight,vTop, msColor };

	}
	else {
		float  Hypotenuse; //! �Ε�
		double Rad;        //! ���W�A��
		//! �E��
		Hypotenuse = (float)sqrt(pow(msSize.x * (1 - mCenterX), 2.0f) + pow(msSize.y * (1 - mCenterY), 2.0f));
		Rad = GetAngle(msSize.x * (1 - mCenterX), msSize.y * (1 - mCenterY)) + mAngle;
		vx[RIGHTTOP] = { (msPos.x + (float)(cos(Rad) * Hypotenuse)), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uRight,vTop, msColor };

		//! ����
		Hypotenuse = (float)sqrt(pow(msSize.x * mCenterX, 2.0f) + pow(msSize.y * (1 - mCenterY), 2.0f));
		Rad = PI - GetAngle(msSize.x * mCenterX, msSize.y * (1 - mCenterY)) + mAngle;
		vx[LEFTTOP] = { (msPos.x + (float)(cos(Rad) * Hypotenuse)), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uLeft,vTop, msColor };

		//! ����
		Hypotenuse = (float)sqrt(pow(msSize.x * mCenterX, 2.0f) + pow(msSize.y * mCenterY, 2.0f));
		Rad = GetAngle(msSize.x * mCenterX, msSize.y * mCenterY) + PI + mAngle;
		vx[LEFTDOWN] = { (msPos.x + (float)(cos(Rad) * Hypotenuse)), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uLeft,vBottom, msColor };

		//! �E��
		Hypotenuse = (float)sqrt(pow(msSize.x * (1 - mCenterX), 2.0f) + pow(msSize.y * mCenterY, 2.0f));
		Rad = (PI * 2) - GetAngle(msSize.x * (1 - mCenterX), msSize.y * mCenterY) + mAngle;
		vx[RIGHTDOWN] = { msPos.x + (float)(cos(Rad) * Hypotenuse), (msPos.y + (float)(sin(Rad) * Hypotenuse)),uRight,vBottom, msColor };

	}
	//! �|���S���P
	vertex[0] = vx[LEFTTOP];     //! ����
	vertex[1] = vx[RIGHTTOP];    //! �E��
	vertex[2] = vx[LEFTDOWN];    //! ����
	//! �|���S���Q
	vertex[3] = vertex[1];       //! �E��
	vertex[4] = vx[RIGHTDOWN];   //! �E��
	vertex[5] = vertex[2];       //! ����

	//! DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	//! ���_�̃f�[�^��VRAM�ɑ���
	d3d->context->UpdateSubresource(mVertexBuffer,//! �]����̒��_�o�b�t�@
		0, NULL, vertex,//! �]������z��̖��O�i�A�h���X�j
		0, 0);

	if (NoStopObj) {
		mAnimCnt++;
	}
	else if (GameMgr->GetAnimation()) {
		if (!StopAnimation) {
			mAnimCnt += 1; //! �A�j���[�V�����J�E���g��i�߂�
		}
	}
}


/*===================================================================================================================**
**  �A�j���[�V�����ɕK�v�ȏ��̃Z�b�^�[�@                                                                            *
**  ���� :  �A�j���[�V�����e�[�u���̐擪�̃|�C���^ , �A�j���[�V�����e�[�u���̗v�f�� , �������̕����� ,�c�����̕������@*
**===================================================================================================================*/
void AnimationSprite::SetAnimtionTable(int _xsplit, int _ysplit)
{

	//! �T�C�Y�̌v�Z
	float U = (1.0f / _xsplit);
	float V = (1.0f / _ysplit);
	//! UV�T�C�Y������Ă����珈��������
	if (U != mSizeU || mSizeV != V) {

		//! �T�C�Y�̌v�Z
		mSizeU = U;
		mSizeV = V;


		//! ��ɓ����Ă����A�j���[�V�����e�[�u����j������
		delete mpAnimTable;
		mpAnimTable = nullptr;

		//! �A�j���[�V�����e�[�u���̗v�f���̐ݒ�
		mAnimTableElemnt = _xsplit + (_xsplit - 2);

		if (mAnimTableElemnt != 0) {
			//! �A�j���[�V�����e�[�u���̐���
			mpAnimTable = new int[mAnimTableElemnt];

			//! �A�j���[�V�����e�[�u���ɒl��ݒ�@_xSplit-1�Ԗڂ܂�
			for (int num = 0; num < _xsplit; num++) {
				mpAnimTable[num] = num;
			}

			//! �A�j���[�V�����e�[�u���ɒl��ݒ�@_XSpliti�ȍ~����Ō�܂�
			int work = 1;
			for (int num = _xsplit; num < mAnimTableElemnt; num++) {
				mpAnimTable[num] = mpAnimTable[_xsplit - 1] - work;
				work++;
			}
		}

	}
}


/*====================================**
** �A�j���[�V�����X�s�[�h�̃Z�b�^�[    *
** �����@�A�j���[�V�����X�s�[�h �@�@�@ *
**====================================*/
void AnimationSprite::SetAnimSpeed(int _animspeed)
{
	mAnimSpeed = _animspeed;
}

/*===========================** 
** Y�����̃R�}�ԍ��̃Z�b�^�[ **
** �����@Y�����̃R�}�ԍ�     **
**===========================*/
void AnimationSprite::SetYSplit(int _ysplit)
{
	mYSplit = _ysplit;
}

/*===========================**
** X�����̃R�}�ԍ��̃Z�b�^�[ **
** �����@X�����̃R�}�ԍ�     **
**===========================*/
void AnimationSprite::SetXSplit(int _xsplit)
{
	//! ������Index�������ɂȂ�܂ŃA�j���[�V�����J�E���g��i�߂�
	for (int i = 0; i < (mAnimTableElemnt * mAnimSpeed) + 32; i++) { //! �Q�[�����~�܂�Ȃ��悤�ɂ���
		int Index = (mAnimCnt / mAnimSpeed) % mAnimTableElemnt;
		if (mpAnimTable[Index] == _xsplit) {
			break;
		}
		else {
			mAnimCnt++;
		}
	}
}

//! �A�j���[�V�����J�E���g�̃��Z�b�g�֐�
void AnimationSprite::ResetAnimCnt()
{
	mAnimCnt = 0;
}

void AnimationSprite::SetStopAnimation(bool _state)
{
	StopAnimation = _state;
}

void AnimationSprite::SetNoStopObj(bool _state)
{
	NoStopObj = _state;
}

int AnimationSprite::GetCurrentXSplit()
{
	return mCurrentXsplit;
}
