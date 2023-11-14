#include "FollowEffect.h"
#include "Camerah.h"
#include "WinMain.h"
#include "Angle.h"

//! �R���X�g���N�^
FollowEffect::FollowEffect(EffectInf _effect, eEffect _effectid, float & _x, float & _y)
	: x(_x), y(_y), Effect(_effect, _effectid)
{

}



//! �X�V����
void FollowEffect::Update()
{
	// �A�j���[�V�������Ō�܂ōs������
	if ((mSplit_y == msEffectInf.Split_y - 1) && (mSplit_x == msEffectInf.Split_x - 1)) {
		mEndflg = true;
	}
	//! ���[�v�t���O�������Ă�����G�t�F�N�g���I���Ȃ��悤�ɂ���
	if (Loop) {
		mEndflg = false;
	}


	VERTEX2D vx[4]; // �l���_�̈ʒu	
	VERTEX2D vertex[6]; // ���_�̐ݒ�@�o�b�t�@�ɑ���p

	// �������ɉ��Ԗڂ̃R�}���v�Z����
	int Index = (mAnimFrameCnt / msEffectInf.AnimSpeed) % msEffectInf.Split_x; // �A�j���[�V�����e�[�u���̓Y����	
	mSplit_x = mpAnimTable[Index];

	//// �������̍Ō�̃R�}�܂ŗ�����c�����̃R�}�ԍ������ɂ��炷
	//if (mAnimFrameCnt == (msEffectInf.Split_x * msEffectInf.AnimSpeed) * (mSplit_y + 1)) {
	//	mSplit_y++;
	//}

	// UV���W���v�Z����
	float uLeft = mSize_u * mSplit_x;
	float uRight = uLeft + mSize_u;
	float vTop = mSize_v * mSplit_y;
	float vBottom = vTop + mSize_v;

	//CAMERA->EffectFix(x, y, mScale_x, mScale_y);
	//! �p�x���ݒ肳��Ă�����
	if (mdAngle != 0) {
		// �����𒆐S�ɉ�]
		double InitAngle = GetAngle(msEffectInf.mSize_x * mScale_x, msEffectInf.mSize_y * mScale_y);
		double LeftTopAngle = mdAngle + (DegreeToRadian(180) - InitAngle); // ���㒸�_�ւ̊p�x 
		double RightTopAngle = mdAngle + InitAngle;
		double LeftDownAngle = RightTopAngle + PI;
		double RightDownAngle = LeftTopAngle + PI;

		vx[LEFTDOWN] = { (x + (float)(cos(LeftDownAngle) * mLength)), (y + (float)(sin(LeftDownAngle) * mLength)),uLeft,vBottom, mColor };
		vx[RIGHTDOWN] = { x + (float)(cos(RightDownAngle) * mLength), (y + (float)(sin(RightDownAngle) * mLength)),uRight,vBottom , mColor };
		vx[LEFTTOP] = { (x + (float)(cos(LeftTopAngle) * mLength)), (y + (float)(sin(LeftTopAngle) *mLength)),uLeft,vTop , mColor };
		vx[RIGHTTOP] = { (x + (float)(cos(RightTopAngle) * mLength)), (y + (float)(sin(RightTopAngle) * mLength)),uRight,vTop, mColor };
	}
	else {
		float left = x - msEffectInf.mSize_x * mScale_x / 2.0f;
		float right = x + msEffectInf.mSize_x * mScale_x / 2.0f;
		float top = y + msEffectInf.mSize_y * mScale_y / 2.0f;
		float bottom = y - msEffectInf.mSize_y * mScale_y / 2.0f;

		vx[LEFTDOWN] = { left,bottom,uLeft,vBottom,mColor };
		vx[RIGHTDOWN] = { right,bottom,uRight,vBottom,mColor };
		vx[LEFTTOP] = { left, top, uLeft, vTop, mColor };
		vx[RIGHTTOP] = { right,top,uRight,vTop,mColor };
	}
	// �|���S���P
	vertex[0] = vx[LEFTTOP];     // ����
	vertex[1] = vx[RIGHTTOP];    // �E��
	vertex[2] = vx[LEFTDOWN];    // ����
	// �|���S���Q
	vertex[3] = vertex[1];       // �E��
	vertex[4] = vx[RIGHTDOWN];   // �E��
	vertex[5] = vertex[2];       // ����

	// DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();
	// ���_�̃f�[�^��VRAM�ɑ���
	d3d->context->UpdateSubresource(mVertexBuffer,//�]����̒��_�o�b�t�@
		0, NULL, vertex,//�]������z��̖��O�i�A�h���X�j
		0, 0);

	mAnimFrameCnt++;
}
