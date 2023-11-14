#include "Image.h"
#include "VERTEX2D.h"
#include <Windows.h>

// �R���X�g���N�^
Image::Image()
{
	//���_�o�b�t�@���쐬
	HRESULT hr; //�����������̌��ʂ��󂯎��^
	DIRECT3D* d3d = Direct3D_Get();

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

	if (FAILED(hr))
	{
		// ���_�o�b�t�@�̍쐬�Ɏ��s�����Ƃ��̏����������ɏ���
		OutputDebugString((L"�G���[�����I\n"));
	}
}


// �f�X�g���N�^
Image::~Image()
{
	COM_SAFE_RELEASE(mVertexBuffer);
}


/*=!�Î~��̕`��!=============================================
===!���� �`����W, �`��T�C�Y, �e�N�X�`��, R, G, B, A(�����x)
============================================================*/
void Image::DrawSprite(float _x,float _y, float _width,float _vertical, ID3D11ShaderResourceView * _Texture, float _r, float _g, float _b, float _a)
{
	DIRECT3D* d3d = Direct3D_Get();

	RGBA color(_r, _g, _b, _a);
	// �I�u�W�F�N�g�̒��S����S���_���v�Z����
	
	float xLeft = _x - _width / 2; //�X�v���C�g�̍��[X
	float xRight = _x + _width / 2; //�X�v���C�g�̉E�[X
	float yTop = _y + _vertical / 2; //�X�v���C�g�̏�[Y
	float yBottom = _y - _vertical / 2; //�X�v���C�g�̉��[Y

	VERTEX2D vx[6];                         // ���_���
	// �|���S���̒��_�����߂�(�w�i01)
	vx[0] = { xLeft,yTop, 0.0f, 0.0f, color };        // { x, y, u, v } ����
	vx[1] = { xRight, yTop, 1.0f, 0.0f, color };      // �E��
	vx[2] = { xRight, yBottom, 1.0f, 1.0f, color };   // �E��
	vx[3] = vx[2];                                    // �E��
	vx[4] = { xLeft, yBottom, 0.0f, 1.0f, color };    // ����
	vx[5] = vx[0];						              // ����

	// ���_�̃f�[�^��VRAM�ɑ���
	d3d->context->UpdateSubresource(mVertexBuffer,//�]����̒��_�o�b�t�@
		0, NULL, vx,//�]������z��̖��O�i�A�h���X�j
		0, 0);

	Draw(_Texture, mVertexBuffer);
}


/*=!�`�b�v��̉摜��`�悷��=================================================================================
===!���� �`����W, �`��T�C�Y, �������̕�����, �c�����̕�����, ���ԖڂȂ̂�, �e�N�X�`��,  R, G, B, A(�����x)
============================================================================================================*/
void Image::DrawDivSprite(float _x, float _y, float _width, float _vertical, int _Divx, int _Divy, int _Num, ID3D11ShaderResourceView * _Texture, float _r , float _g , float _b , float _a )
{
	DIRECT3D* d3d = Direct3D_Get();

	RGBA color(_r, _g, _b, _a);
	// �I�u�W�F�N�g�̒��S����S���_���v�Z����
	float xLeft = _x - _width / 2;    // �X�v���C�g�̍��[X
	float xRight = _x + _width / 2;   // �X�v���C�g�̉E�[X
	float yTop = _y + _vertical / 2;    // �X�v���C�g�̏�[Y
	float yBottom = _y - _vertical / 2; // �X�v���C�g�̉��[Y

	// �P�R�}�̃T�C�Y
	float uvWidth = (1.0f / _Divx);  // U�̒���
	float uvHeight = (1.0f / _Divy); // V�̒���

	// ���Ԗڂ̉摜�Ȃ̂����v�Z����
	int Numx = _Num % _Divx;
	int Numy = _Num / _Divx;

	float uLeft = Numx * uvWidth;    //��
	float uRight = uLeft + uvWidth;  //�E
	float vTop = Numy * uvHeight;    //��
	float vBottom = vTop + uvHeight; //��

	VERTEX2D vertex[6];                         // ���_���
	// �|���S���̒��_�����߂�(�w�i01)
	vertex[0] = { xLeft,yTop, uLeft, vTop,color };          // { x, y, u, v } ����
	vertex[1] = { xRight, yTop, uRight, vTop,color };       // �E��
	vertex[2] = { xRight, yBottom, uRight, vBottom,color }; // �E��
	vertex[3] = vertex[2];                                  // �E��
	vertex[4] = { xLeft, yBottom, uLeft, vBottom ,color };  // ����
	vertex[5] = vertex[0];						            // ����

	// ���_�̃f�[�^��VRAM�ɑ���
	d3d->context->UpdateSubresource(mVertexBuffer,//�]����̒��_�o�b�t�@
		0, NULL, vertex,//�]������z��̖��O�i�A�h���X�j
		0, 0);

	Draw(_Texture, mVertexBuffer);
}



// ���ۂɕ`�悷��֐�
void Image::Draw(ID3D11ShaderResourceView* _texture, ID3D11Buffer* _vertexBuffer)
{
	DIRECT3D* d3d = Direct3D_Get();

	// �|���S���`�揈��
	UINT stride = sizeof(VERTEX2D);
	UINT offset = 0;

	//�s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����Z�b�g����
	d3d->context->PSSetShaderResources(0, 1, &_texture);

	// �s�N�Z���V�F�[�_�[�ɃT���v���[��n��
	d3d->context->PSSetSamplers(0, 1, &d3d->samplerPoint); //�|�C���g�ۊ�

	//�`��Ɏg�����_�o�b�t�@�̑I��
	d3d->context->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);

	//�`�施��
	d3d->context->Draw(6, 0);//�����������_��
}

