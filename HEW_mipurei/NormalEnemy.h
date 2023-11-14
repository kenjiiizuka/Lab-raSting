#pragma once
#include "BaseEnemy.h"
class NormalEnemy :
	public BaseEnemy
{
public:
	NormalEnemy();						//! �R���X�g���N�^
	NormalEnemy(float _x, float _y);	//! �R���X�g���N�^
	~NormalEnemy();						//! �f�X�g���N�^
	void Update();						//! �X�V����
	void Draw();						//! �`�揈��
	TailReaction Reaction;				//! �K���̃��A�N�V�����ϐ�
	TailReaction SetStingPower(float _Power,bool _Elect)override;		//! �K�����h���ꂽ���̋����Ƌ���
private:
	
};

