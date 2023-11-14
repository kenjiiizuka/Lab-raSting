#pragma once
#include "BaseEnemy.h"
#include "SplitUpperEnemy.h"

//! Splitter�i�ʏ̕��􂷂�G���j���������قږ{��
class SplitLowerEnemy :
	public BaseEnemy
{
public:
	SplitLowerEnemy();					  //! �R���X�g���N�^
	SplitLowerEnemy(float _x, float _y);  //! �R���X�g���N�^
	~SplitLowerEnemy();					  //! �f�X�g���N�^

	void Update();						  //! �X�V����
	void Draw();						  //! �`�揈��
	void LastUpdate() override;			  //! �ŏI�X�V����
										  
	void SetInitVec(Vector2 _vec);		  //! �����ʒu�̃Z�b�^�[
	SplitUpperEnemy * GetUpperEnemy();	  //! ��ɂ���G�l�~�[�̃Q�b�^�[
	Box * GetBoxCol() override;			  //! �����蔻��̏��
	bool GetDeath();                      //! ���ꂽ�Ƃ��Ɉ�x�������ꂽ���Ƃ�Ԃ��֐�
	TailReaction SetStingPower(float _Power, bool _Elect) override;		//! �K�����h���ꂽ���̋����Ƌ���
	void SetFollow(bool _state);
private:
	void ForceProces();			//! �d�͂̏���
	void Walk();				//! �ړ��̏���
	SplitUpperEnemy * mcpSpltterUP; //! ��ɂ�����
	Box * mcpCombiCol;     //! ��������O�̓����蔻��
	Box * mcpSplitedCol;   //! ������̓����蔻��
	Vector2 mcCombiPos;    //! �������Ă��Ԃł̓�����̒��S���W
	Vector2 mcSplitedColPos; //! �@�����̓����蔻��̒��S���W
	Vector2 mcCombColSize; //! �������Ă��Ԃł̓�����̃T�C�Y
	void Destroy();  //! �|���Ƃ��̊֐�
	bool Combi;      //! �������Ă邩���f����t���O
	float TotalMove; //! �ړ�����
	float mfSpeed;   //! �X�s�[�h
	bool Follow = true; //! �v���C���[�Ɉ�x������܂ŒǏ]����
	int Count;
	int MutekiCount;  //!�����O�ɂ����ꂽ�炵�΂炭���G(�A���q�b�g������邽�߂�)
	float FollowMove;
 
};

