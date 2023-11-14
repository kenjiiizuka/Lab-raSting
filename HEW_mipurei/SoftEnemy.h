#pragma once
#include "BaseEnemy.h"

//! Hooder�i�ʏ̂��炩���G�j
class SoftEnemy :
	public BaseEnemy
{
public:
	SoftEnemy();		//! �R���X�g���N�^
	SoftEnemy(float _x,float _y);	//! �f�X�g���N�^
	~SoftEnemy();		//! �R���X�g���N�^
	void Update();		//! �X�V����
	void Draw();		//!	�`�揈��
	TailReaction Reaction;	//! �K���̃��A�N�V�����̕ϐ�
	TailReaction SetStingPower(float _Power, bool _Elect)override;	//! �K���Ŏh���ꂽ���̋����Ƌ���
private:
	int mMidHitcount = 0;

	int AnimFrm;
	bool Stop;
};

