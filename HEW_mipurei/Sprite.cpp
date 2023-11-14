#include "Sprite.h"
#include "direct3d.h"
#include "Angle.h"
#include <math.h>
#include "WinMain.h"


//! �R���X�g���N�^
Sprite::Sprite(Vector2 & _pos) : msPos(_pos)
{
	//! ���_�o�b�t�@���쐬
	HRESULT hr;                             
	DIRECT3D* d3d = Direct3D_Get();              //! DIRECT3D�\���̂ɃA�N�Z�X
	D3D11_BUFFER_DESC bufferDesc;                
	bufferDesc.ByteWidth = sizeof(VERTEX2D) * 6; //! VRAM�Ɋm�ۂ���f�[�^�T�C�Y�B�ʏ�͍����瑗�钸�_�f�[�^�̃T�C�Y�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //! ���_�o�b�t�@�쐬�������Ŏw��B
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// �o�b�t�@�쐬�֐��i�f�o�C�X�N���X�̃����o�֐��j���Ăяo��
	hr = d3d->device->CreateBuffer(&bufferDesc, NULL,
		&mVertexBuffer); //��������_�o�b�t�@�͂����Ŏw�肵���ϐ��ɕۑ������

	if (FAILED(hr))	{
		// ���_�o�b�t�@�̍쐬�Ɏ��s�����Ƃ��̏����������ɏ���
		OutputDebugString((L"�G���[�����I\n"));
	}

	mPosU = mPosV = 0.5f;
	mSizeU = mSizeV = 1.0f;
	mAngle = 0;
	msColor = {1.0f,1.0f,1.0f,1.0f};
	mCenterX = mCenterY = 0.5f;
	mTexture = NULL;
	SplitDraw = false;
}

//! �f�X�g���N�^
Sprite::~Sprite()
{
	COM_SAFE_RELEASE(mVertexBuffer);
}

//! �X�V����
void Sprite::Update()
{	
	VERTEX2D vx[4]; //! �l���_�̈ʒu

	//! ���_�̐ݒ�@�o�b�t�@�ɑ���p
	VERTEX2D vertex[6];

	float uLeft;
	float uRight;
	float vTop;
	float vBottom;
	//! �e�N�X�`����̍��W�����߂�
	if(SplitDraw){
		// �P�R�}�̃T�C�Y
		float uvWidth = (1.0f / XSplit);  // U�̒���
		float uvHeight = (1.0f / YSplit); // V�̒���

		// ���Ԗڂ̉摜�Ȃ̂����v�Z����
		int Numx = TexNum % XSplit;
		int Numy = TexNum / XSplit;

		uLeft = Numx * uvWidth;    //��
		uRight = uLeft + uvWidth;  //�E
		vTop = Numy * uvHeight;    //��
		vBottom = vTop + uvHeight; //��
	}
	else {
		uLeft = mPosU - (mSizeU / 2);
		uRight = mPosU + (mSizeU / 2);
		vTop = mPosV - (mSizeV / 2);
		vBottom = mPosV + (mSizeV / 2);
	}


	//! �p�x���ݒ肢�Ȃ��ꍇ
	if (mAngle == 0.0f) {
		vx[LEFTDOWN] = { msPos.x - msSize.x / 2.0f , msPos.y - msSize.y / 2.0f ,uLeft,vBottom, msColor};
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
		0, NULL, vertex, //! �]������z��̖��O�i�A�h���X�j
		0, 0);

}

//! �`�揈��
void Sprite::Draw()
{
	//! DIRECT3D�\���̂ɃA�N�Z�X����
	DIRECT3D* d3d = Direct3D_Get();

	//! �|���S���`�揈��
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//! �s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����Z�b�g����
	d3d->context->PSSetShaderResources(0, 1, &mTexture);

	//! �s�N�Z���V�F�[�_�[�ɃT���v���[��n��
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint); //�|�C���g�ۊ�

	//! �`��Ɏg�����_�o�b�t�@�̑I��
	d3d->context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//! �`�施��
	d3d->context->Draw(NUM_VERTEX, 0);//�����������_��

}

//! �e�N�X�`���̃Z�b�^�[
void Sprite::SetTexture(ID3D11ShaderResourceView * _texture)
{
	mTexture = _texture;
}

//! ���̃X�v���C�g�̃T�C�Y�̃Z�b�^�[ 
void Sprite::SetSize(float _width, float _vertical)
{
	msSize.x = _width;
	msSize.y = _vertical;
}


//! �`����̃Z�b�^�[�@UV���W�AUV�T�C�Y
void Sprite::SetUVSpriteInf(int _num, int _xsplit, int _ysplit, bool _state)
{
	TexNum = _num;
	XSplit = _xsplit;
	YSplit = _ysplit;
	SplitDraw = _state;
}

//! �p�x�̃Z�b�^�[
void Sprite::SetAngle(double _angle, float _centerx, float _centery)
{
	mAngle = _angle;
	mCenterX = _centerx;
	mCenterY = _centery;
}

//! �F���̃Z�b�^�[
void Sprite::SetColor(float _r, float _g, float _b)
{
	msColor.r = _r;
	msColor.g = _g;
	msColor.b = _b;

}

//! �����x�̃Z�b�^�[
void Sprite::SetArufa(float _a)
{
	msColor.a = _a;
}





