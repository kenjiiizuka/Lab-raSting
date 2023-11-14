#pragma once
#include "Vector2.h"

/* -------------------------------------------------------------------
// Shape�N���X                                                      //
// �`�̏������N���X�ł��B                                       //
// �����蔻������������I�u�W�F�N�g�Ɏ������ď���ݒ肵�Ă������� */
class Shape
{
public:
	Shape(Vector2 & _pos); //! �R���X�g���N�^
	
	Vector2 GetVec();
	void SetMoveVec(Vector2 _movevec);
	Vector2 GetMoveVec();
	void SetActiv(bool _state);     //! �����蔻��̐؂�ւ��̃Z�b�^�[
	bool GetActiv();                //! �����蔻��̐؂�ւ��̃Q�b�^�[
	void SetAttack(bool _state);    //! �U������t���O�̃Z�b�^�[ 
	bool GetAttack();               //! �U������t���O�̃Q�b�^�[
	void SetPrevVec(Vector2 _vec);  //! �O�t���[���̍��W�̃Z�b�^�[
	Vector2 GetPrevVec();           //! �O�t���[���̍��W�̃Z�b�^�[

	void SetPenetration(float _x, float _y);
	void AddPenetration(float _x, float _y);
	Vector2 GetPetration();

	//! ���W�̃Z�b�^�[�@�����蔻��֌W�ł̂ݎg��
	void SetPos(float _x, float _y);
	void SetX(float _x);
	void SetY(float _y);
	void SetOnObj(bool _state);
	bool GetOnObj();
	//! ���g�̃A�h���X��Ԃ�
	Shape * Getthis();
protected:
	Vector2 & mcPos;     //! ���W
	Vector2 mPrevPos;    //! �O�t���[���̍��W
	Vector2 mcMoveVec;   //! ���̃N���X�����A�I�u�W�F�N�g�̈ړ��� 
	Vector2 Penetration; //! �߂荞��ł���C�������
	bool Attack;         //! �U���̔���Ȃ̂��𔻒f���� �������ꂢ���
	bool Activ;          //! �����蔻��̃I���I�t�؂�ւ�
	bool mOnObj;      //! �����ɏ���Ă��邩(Character�̃^�b�`�O���E���h�̎Q�Ƃɂ���Ƃ�������)
};

