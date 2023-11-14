#pragma once
#include "AnimationHitObject.h"
#include "Log.h"
#include "Box.h"
#include "Shape.h"
#include "Image.h"

/* =================================================================================================================================== 
// �L�����N�^�[�N���X�@���̃N���X�����ɂ��āA�G��v���C���[������ĉ�����														    //
// �L�����N�^�[�S�̂ɋ��ʂ���d�l���܂Ō��܂��Ă��Ȃ����߁A�܂��������ł��B�d�l�ɍ��킹�ĕύX���₷���悤�Ɍp����ŋC��t���ĉ����� // 
// ����� : �ђ� ���i*/


//! �L�����N�^�[�͊�{�I�ɋ�`�œ����蔻�����낤�Ǝv���܂��@
//! �ꍇ�ɂ���Ă͉~�̃L����������Ǝv���̂ł��̏ꍇ�́A���̃N���X�ŐV����Circle�N���X�𐶐����A����̃Q�b�^�[��K�v�ȏ��������Ă�������

//! �d�͂Ȃǂ��̃L�����N�^�[�ɂ������Ă���͂̌v�Z�����܂�
class Character :
	public AnimationHitObject
{
public:
	Character();  //! �R���X�g���N�^	
	~Character(); //! �f�X�g���N�^
	void Update() override; //! �X�V����
	virtual void Draw() override;
	void SetTouchGround(bool _state);   //! �^�b�`�O���E���h�̃Z�b�^�[
	virtual Box * GetBoxCol();                   //! ��`�̓����蔻����̃Q�b�^�[
protected:
	Vector2 mcMoveVector;      //! �ړ�����ʁ@���̒l�����g��Pos�ɉ��Z���Ĉړ��Ȃǂ�����悤�ɂ���\��
	bool mTouchGraund;          //! �n�ʂɂ��邩���Ȃ������f����
	double mSecond;             //! �n�ʂɂ��Ă���Ԍ��݂̎��Ԃ��擾����	
	Box * mcpBoxCol;            //! ��`�̓����蔻��
	Vector2 ColSize;            //! �����蔻��̃T�C
	double CurrentTime;         //! ���̃L�����N�^�[����������Ă���̌o�ߎ��� 
	double PrevTime;            //! ���̃L�����N�^�[����������Ă���̑O�t���[���̌o�ߎ���
	double GravityTime;         //! �d�͂̉e�����󂯎n�߂�����
private:
	Log * CharDeLog;
	Image * mcpImage;           //! �����蔻����������Ƃ��Ɏg���Ă�������
};

