#include "Effect.h"
#include "direct3d.h"
#include "VERTEX2D.h"
#include "Angle.h"
#include <math.h>
#include "WinMain.h"
#include "Camerah.h"

// �R���X�g���N�^
Effect::Effect(EffectInf _effect,eEffect _effectid)
{
	//���_�o�b�t�@���쐬
	HRESULT hr; //�����������̌��ʂ��󂯎��^
	DIRECT3D* d3d = Direct3D_Get(); // �܂�DIRECT3D�\���̂ɃA�N�Z�X
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(VERTEX2D) * 6; // VRAM�Ɋm�ۂ���f�[�^�T�C�Y�B�ʏ�͍����瑗�钸�_�f�[�^�̃T�C�Y�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���_�o�b�t�@�쐬�������Ŏw��B
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// �o�b�t�@�쐬�֐��i�f�o�C�X�N���X�̃����o�֐��j���Ăяo��
	hr = d3d->device->CreateBuffer(&bufferDesc, NULL,
		&mVertexBuffer); //��������_�o�b�t�@�͂����Ŏw�肵���ϐ��ɕۑ������

	if (FAILED(hr)) {
		// ���_�o�b�t�@�̍쐬�Ɏ��s�����Ƃ��̏����������ɏ���
		OutputDebugString((L"�G���[�����I\n"));
	}

	mEndflg = false;	
	mEffectID = _effectid;
	mAnimFrameCnt = 0;	
	mSplit_y = mSplit_x = 0;;	
	mColor = { 1.0f,1.0f,1.0f,1.0f };
	msEffectInf = _effect;
	mScale_x = mScale_y = 1.0f;
	mdAngle = _effect.Angle;
	// �`��T�C�Y�̌v�Z
	mLength = sqrt((msEffectInf.mSize_x /2 * msEffectInf.mSize_x / 2) + (msEffectInf.mSize_y / 2 * msEffectInf.mSize_y / 2));

	// UV�T�C�Y�̌v�Z
	mSize_u = (1.0f / (float)msEffectInf.Split_x);
	mSize_v = (1.0f / (float)msEffectInf.Split_y);

	// �A�j���[�V�����e�[�u���𐶐�
	mpAnimTable = new int[msEffectInf.Split_x];
	for (int num = 0; num < msEffectInf.Split_x; num++) {
		mpAnimTable[num] = num;
	}
}


// �f�X�g���N�^
Effect::~Effect()
{
	delete[] mpAnimTable;
	COM_SAFE_RELEASE(mVertexBuffer);
}


// �G�t�F�N�g�̍X�V���� 
void Effect::Update()
{	
	// �A�j���[�V�������Ō�܂ōs������
	if ((mSplit_y == msEffectInf.Split_y -1) && (mSplit_x == msEffectInf.Split_x - 1)) {
		mEndflg = true;
	}

	VERTEX2D vx[4]; // �l���_�̈ʒu	
	VERTEX2D vertex[6]; // ���_�̐ݒ�@�o�b�t�@�ɑ���p

	// �������ɉ��Ԗڂ̃R�}���v�Z����
	int Index = (mAnimFrameCnt / msEffectInf.AnimSpeed) % msEffectInf.Split_x; // �A�j���[�V�����e�[�u���̓Y����	
	mSplit_x = mpAnimTable[Index];
	
	// �������̍Ō�̃R�}�܂ŗ�����c�����̃R�}�ԍ������ɂ��炷
	if (mAnimFrameCnt == (msEffectInf.Split_x * msEffectInf.AnimSpeed) * (mSplit_y + 1)) {
		mSplit_y++;
	}

	// UV���W���v�Z����
	float uLeft = mSize_u * mSplit_x;
	float uRight = uLeft + mSize_u;
	float vTop = mSize_v * mSplit_y;
	float vBottom = vTop + mSize_v;
	
	CAMERA->EffectFix(msEffectInf.pos_x,msEffectInf.pos_y,mScale_x,mScale_y);
	//! �p�x���ݒ肳��Ă�����
	if (mdAngle != 0) {

		// �����𒆐S�ɉ�]
		double InitAngle = GetAngle(msEffectInf.mSize_x * mScale_x, msEffectInf.mSize_y * mScale_y);
		double LeftTopAngle = mdAngle + (DegreeToRadian(180) - InitAngle); // ���㒸�_�ւ̊p�x 
		double RightTopAngle = mdAngle + InitAngle;
		double LeftDownAngle = RightTopAngle + PI;
		double RightDownAngle = LeftTopAngle + PI;

		vx[LEFTDOWN] = { (msEffectInf.pos_x + (float)(cos(LeftDownAngle) * mLength)), (msEffectInf.pos_y + (float)(sin(LeftDownAngle) * mLength)),uLeft,vBottom, mColor };
		vx[RIGHTDOWN] = { msEffectInf.pos_x + (float)(cos(RightDownAngle) * mLength), (msEffectInf.pos_y + (float)(sin(RightDownAngle) * mLength)),uRight,vBottom , mColor };
		vx[LEFTTOP] = { (msEffectInf.pos_x + (float)(cos(LeftTopAngle) * mLength)), (msEffectInf.pos_y + (float)(sin(LeftTopAngle) *mLength)),uLeft,vTop , mColor };
		vx[RIGHTTOP] = { (msEffectInf.pos_x + (float)(cos(RightTopAngle) * mLength)), (msEffectInf.pos_y + (float)(sin(RightTopAngle) * mLength)),uRight,vTop, mColor };
	}
	else {
		float left = msEffectInf.pos_x - msEffectInf.mSize_x * mScale_x / 2.0f;
		float right = msEffectInf.pos_x + msEffectInf.mSize_x * mScale_x / 2.0f;
		float top = msEffectInf.pos_y + msEffectInf.mSize_y * mScale_y / 2.0f;
		float bottom = msEffectInf.pos_y - msEffectInf.mSize_y * mScale_y / 2.0f;

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


// �G�t�F�N�g�̕`�揈��
void Effect::Draw()
{
	//DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();

	// �|���S���`�揈��
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//�s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����Z�b�g����
	d3d->context->PSSetShaderResources(0, 1, &msEffectInf.mTexture);

	// �s�N�Z���V�F�[�_�[�ɃT���v���[��n��
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint); //�|�C���g�ۊ�

	//�`��Ɏg�����_�o�b�t�@�̑I��
	d3d->context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//�`�施��
	d3d->context->Draw(NUM_VERTEX, 0);//�����������_��
}

void Effect::SetPos(float _x, float _y)
{
	//! ���W�̃Z�b�g
	msEffectInf.pos_x = _x;
	msEffectInf.pos_x = _y;
}

//! ���̃G�t�F�N�g���I�����������f����t���O��Ԃ�
bool Effect::GetEndFlg()
{
	return mEndflg;
}

eEffect Effect::GetEffectID()
{
	return mEffectID;
}
