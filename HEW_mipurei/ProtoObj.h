#pragma once
#include "Character.h"
#include"Box.h"
//====================================================//
/*
�v���g�^�C�v�Ń}�b�v�̓����蔻��p�Ɏg���L�����N�^�[�ł�
�쐬�ҁF����r��
*/
//====================================================//
class ProtoObj :
	public Character
{
public:
	ProtoObj();
	~ProtoObj();
	void Update() override;
	void Draw() override;
	//Vector2* GetVec2();//mcpvec��Ԃ����߂̊֐�(�����蔻��p)
	void AddVec2(float _x, float _y);//float�^�ňʒu���w�肷��
	Box* GetmpBox();
private:
	Box* mpBox;
};

