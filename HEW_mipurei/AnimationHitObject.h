#pragma once
#include "GameObject.h"
#include "AnimationSprite.h"
#include "Shape.h"
#include "ObjTag.h"
/* =========================================================== 
** AnimationHitObject�N���X                                 **
** �A�j���[�V�����Ɠ����蔻��@�\���������I�u�W�F�N�g�N���X **
** ���̃N���X���p�����ăL�����N�^�[���̃N���X�����\��@�@ **
** ����� : �ђ� ���i                                       **
** ======================================================== */


class AnimationHitObject :
	public GameObject
{
public:
	AnimationHitObject();               //! �R���X�g���N�^
	virtual ~AnimationHitObject();      //! �f�X�g���N�^
	virtual void Update();              //! �X�V����
    virtual void LastUpdate();          //! �����蔻�菈���̌�ɂ���X�V����
	void SetHit(bool _state);           //! �q�b�g�t���O�̃Z�b�^�[
	void SetHitActiv(bool _state);      //! �����蔻��̃I���I�t�؂�ւ��̃Z�b�^�[
	AnimationSprite * GetAnimSprite();	//! �X�v���C�g�N���X�̃Q�b�^�[
	
protected:	
	AnimationSprite* mcpAnimsprite;     //! �A�j���[�V�����X�v���C�g�N���X
	Shape * mcpShape;                   //! ���̃I�u�W�F�N�g�̌`������
	
private:							    

	bool mHitFlg;                       //! HitFlg
};

