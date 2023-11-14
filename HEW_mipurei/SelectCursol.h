// �R�}���h�I���ɗp����J�[�\���N���X
// �c�����ɂ̂ݑΉ���

#pragma once

#include "Image.h"
#include "FLOAT2.h"

class SelectCursol
{
public:
	int Update(); // �߂�l�ɂ���񂾃R�}���h��Ԃ� �Ȃɂ��I��ł��Ȃ�����-1������
	void Draw();
	~SelectCursol();
	SelectCursol(int num, float xPos, float yPos, float Interval, float width); // �R�}���h�̐��ƍŏ��̃R�}���h�̍��W��n�� 
private:
	int mNumComnd; //�R�}���h�̐�
	int mSelectComand;  // ���ǂ̃R�}���h�������ł��邩
	int mOldSelectComand; // �O�t���[���ɑI��ł����R�}���h
	float mInterval;
	// �R�}���h�̈ړ������Ɏg��
	float mComnadTopPos; // ��ԏ�̃R�}���h��Y���W
	float mComnadUnderPos; // ��ԉ��̃R�}���h��X���W
	Image *mpcImage;
	FLOAT2* mpComandPos;
	FLOAT2 msPos;
	FLOAT2 msOldPos;

	// �󂯎�����R�}���h�̐��ƍ��W���炻�ꂼ��̂��܂�ǂ̈ʒu���v�Z����
};

