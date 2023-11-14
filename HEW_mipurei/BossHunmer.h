#pragma once
#include"Box.h"
#include"BoxObject.h"
#include"Sprite.h"
#include"AnimationHitObject.h"
#include "Image.h"
/*
���Ń{�X���g���n���}�[�̃N���X�ł��B
���Ń{�X�Ƃ̈ʒu�֌W�́A�e�q�֌W�ɂ���\��ł��B(�ђˌN�̍�����L�ƃv���O�̊���)
�Ȃ̂ŁA���̃N���X��AlphaBoss���Ő������āA���̃N���X�̊֐��Ȃǂ��Ăт܂�
�U�艺�낳�ꂽ��̃n���}�[�͑���Ƃ��ė��p�ł��܂�
*/
class BossHunmer :
	public AnimationHitObject
{
public:
	BossHunmer(float _x, float _y);//��Ƀ{�X�̎�ɂ������悤�Ɉʒu��ݒ肷��
	~BossHunmer();
	void Update(float _x, float _y,int _AtkTime,bool _AtkFlg);
	void Draw();
	Box* GetmpHunmerBox();
	Box* GetmpRodBox();
	BoxObject* GetmpDebriesBox();
private:
	ID3D11ShaderResourceView * mHunmerTex;//�U�艺�낷�O�A�U�艺�낵����̃n���}�[�̃e�N�X�`���p��2�p�ӂ���

	/*
	�����蔻��2�p��(��[�Ǝ����Ă̕���)
	�E�U�����n���}�[���T�C�h�ɍU���p����̊ۂ�p�ӂ���
	*/
	Image mcImage;
	//�n���}�[�̖{�̂̓����蔻��֘A�̕ϐ�
	Box* mpHunmer;//�n���}�[�ɏ�鎞�̓����蔻��(�l�p�`)
	Vector2 mpHunmerColiPos;//�����蔻��̈ʒu
	Vector2 HunmerColiScale;//�����蔻��̑傫��

	//�n���}�[�̎�����̓����蔻��֘A�̕ϐ�
	Box* mpRod;//������̓����蔻��(�l�p�`)
	Vector2 mcRodPos; //! ������p�̍��W
	Vector2 mcRodColiScale;//������̓����蔻��̑傫��

	//���ꂫ Box�N���X���g�p����A��ʉ����琶���Ă���
	BoxObject* mpdebris;
	AnimationSprite* tmpdbrisAnimSprite;
	ID3D11ShaderResourceView* mdebrisTex;
	Vector2 mcdebreisPos;//���ꂫ�̍��W
	Vector2 mcdebreisScale;
};