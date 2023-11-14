#pragma once
#include "Sprite.h"

//! �A�j���[�V�����X�v���C�g�N���X�@
//! UV���W������(0,0)�ɑΉ����Ă��܂�

class AnimationSprite :
	public Sprite
{
public:	
	AnimationSprite(Vector2 & _pos);
	~AnimationSprite();
	void Update() override;
	void SetAnimtionTable(int _xsplit, int _ysplit); //! �A�j���[�V�������̃Z�b�^�[(���̃e�N�X�`���̏c���̕�����)
	void SetAnimSpeed(int _animspeed);               //! �A�j���[�V�����X�s�[�h�̃Z�b�^�[   
	void SetYSplit(int _ysplit);                     //! �c�����̃A�j���[�V�����̃R�}�ԍ��̃Z�b�^�[
	void SetXSplit(int _xsplit);                     //! X�����̃A�j���[�V�����̃R�}�ԍ��̃Z�b�^�[
	void ResetAnimCnt();
	void SetStopAnimation(bool _state);              //! �A�j���[�V�������~�߂邽�߂̂������[
	void SetNoStopObj(bool _state);              
	int GetCurrentXSplit();             //! ���Đ����Ă���A�j���[�V�������������ŉ��ԖڂȂ̂���Ԃ�

private:
	int* mpAnimTable;      //! �A�񃁁[�V�����e�[�u��
	int mAnimTableElemnt;  //! �A�j���[�V�����e�[�u���̗v�f��
	int mAnimSpeed;        //! �A�j���[�V�����X�s�[�h
	int mAnimCnt;          //! �A�j���[�V�����J�E���g
	int mYSplit;           //! Y�����̈ʒu
	int mCurrentXsplit;    //! ����X�����̈ʒu
	bool StopAnimation;    //! �A�j���[�V�������~�߂�

	bool NoStopObj = false;        //! �|�[�Y��ʗp�̃A�j���[�V�������Ƃ܂�Ȃ��I�u�W�F�N�g�ł�
};

