#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "DrawValue.h"
#include "ObjTag.h"
/* =============================================
** GameObject�N���X�@�@�@�@�@�@�@�@�@�@�@     **�@�@�@
** GameObject�̊��N���X�ł��@               **
** ����� : �ђ� ���i                         **
** ========================================== */

class GameObject
{
public:
	virtual void Draw();

	void SetDrawActiv(bool _drawState);         //! �`��̃I���I�t�؂�ւ��p�̃Z�b�^�[	
	virtual Vector2  GetVec();                          //! ���W�̃Q�b�^�[
	virtual void SetVec(Vector2 _vec);          //! ���W�̃Z�b�^�[
	void SetScale(float _x, float _y);          //! �g��k����
	virtual void SetSize(float _widht, float _hieght);  //! �T�C�X�̃Z�b�^�[
	virtual void SetSize(Vector2 _size);        //! �T�C�Y�̃Z�b�^�[
	Sprite * GetSprite();                       //! �X�v���C�g�N���X�̃Q�b�^�[
	bool GetAlive();                            //! �����t���O�̃Q�b�^�[
	void SetCameraActiv(bool _state);           //! �J���������f����邩�ǂ����̃Z�b�^�[
	ObjectTag GetTag();                 //! �^�O�̃Q�b�^�[

protected:
	Sprite * mcpSprite;                         //! �`��@�\
	Vector2 mcVec;                              //! �I�u�W�F�N�g�̍��W
	FLOAT2 msSize = { 0.2f ,0.2f};              //! ���̃I�u�W�F�N�g�̃T�C�Y
	FLOAT2 msScale = {1.0f,1.0f};               //! �g��k����
	bool mAlive = true;                         //! �����t���O
	ObjectTag mTag = ObjectTag::Tag_None;
private:
	bool mDrawActiv = true;                     //! �`��̃I���I�t�؂�ւ�	
	bool mCameraActiv = true;                   //! �J�����̏����𔽉f�h���邩�����Ȃ����̃I���I�t     
};

