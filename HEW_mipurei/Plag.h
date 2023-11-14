#pragma once
#include "AnimationHitObject.h"
#include"Box.h"

/*
�n���}�[���������{�X�̃g�h���������Ƃ��ɁA
�U�����镔���̃N���X�ł��B
*/
class Plag :
	public AnimationHitObject
{
public:
	Plag(float _x, float _y);
	~Plag();
	void Update();
	void Draw();
	//�v���C���[�̂����ۂƓ����蔻������邽�߂̊֐�
	Box* GetPlagCollision();
private:
	ID3D11ShaderResourceView * mPlagTex;
	Box* mpPlagCollision;
	Vector2 mpPlagColisionPos;
	//�����蔻��m�F�p�摜
	Image mcImage;
};

