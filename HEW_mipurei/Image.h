#pragma once
#include "direct3d.h"


class Image
{
public:
	Image();
	~Image();
	// �Î~��
	void DrawSprite(float _x, float _y, float _width, float _vertical, ID3D11ShaderResourceView* _Texture, float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f); // ���S���W�@�c���̃T�C�Y,�摜
	// �`�b�v�n�@�L�����`�b�v�Ȃǂ̕`�� 
	void DrawDivSprite(float _x, float _y, float _width, float _vertical, int _Divx, int _Divy, int _Num, ID3D11ShaderResourceView* _Texture , float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f); // ���S���W�@�c���@������X�AY�A���Ԗڂ̉摜,�@�摜

private:
	ID3D11Buffer* mVertexBuffer;    // ���̃X�v���C�g�Ŏg�����_�o�b�t�@
	void Draw(ID3D11ShaderResourceView*, ID3D11Buffer*);	

};

