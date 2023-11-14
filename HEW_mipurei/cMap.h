#pragma once
#include "Image.h"
#include "FLOAT2.h"
#include <string>
#include "Vector2.h"
#include "Character.h"
#include "StaticObject.h"
#include "CheckPoint.h"
#include "Log.h"
#include <vector>
#include <memory>

//�@���@���쒆 �@�@�I�J�����̏����𔽉f�����Ă��܂���!

/*************************************************************
* Map�N���X                                                  *
* �@�\   : Map��`�悵�AMap�Ƃ̓����蔻�������Ă���܂�    *
* ����� : �ђ� ���i                                         *
*************************************************************/

class Map
{
	//! �`�b�v���Ƃ̏��̍\����
	typedef struct {
		Vector2 mcPos; //! ���̃`�b�v�̍��W
		int Number;    //! ���̃`�b�v�̔ԍ��@�e�N�X�`����ł̔ԍ�
		int Tag;       //! ���̃`�b�v��Tag�@�n�ʂȂ̂��A��ڐG�̂��̂Ȃ̂��𔻒f���邽�߂̂���
		bool Drawed;   //! �`�悳�ꂽ���𔻒f����@�`�悳��Ă��Ȃ��Ƃ��͓����蔻������Ȃ��悤�ɂ���
	}MapTip;

public:
	Map(std::string _filename, std::string _itemfile, ID3D11ShaderResourceView * _maptiptex); //! �R���X�g���N�^	
	~Map();
	virtual void Update();
	virtual void Draw();
	void SetPos(Vector2 _pos);      //! ���W�̃Z�b�^�[
	virtual bool CollisionUpdate(Character * _chra);
	void ResetMap();                //! Map�̈ʒu�������̈ʒu�ɖ߂�
	void SetDrawBg(bool _state);    //! �w�i��`��
	Vector2 GetPos();               //! Map�̍��W�̃Q�b�^�[  
protected:
	bool Collision(Character * _char); //! ��`�̃L�����Ƃ̓����蔻��
	bool ActivItem;                         //! Item��`�悷�邩���Ȃ���
	Vector2 mcPos;                          //! ���̃}�b�v�̒��S���W
	Vector2 mcMapSize;                      //! ���̃}�b�v�̃T�C�Y
	MapTip ** mspMaptip;                    //! �}�b�v�`�b�v�̏����i�[����
	MapTip ** mspItem;                      //! ����Map�ɂ���A�C�e���̏��
	FLOAT2 msTipSize = { 0.1f,0.1f };       //! �}�b�v�`�b�v1�̃T�C�Y
	int mTipNumX;                           //! �}�b�v�̉��̃T�C�Y
	int mTipNumY;		                    //! �}�b�v�̏c�̃T�C�Y	
	int mMaxGimmick;                        //! ����Map�ɂ���M�~�b�N�̐�
	bool DrawBg;                            //! �w�i��`�悷�邩���Ȃ����̃t���O
	StaticObject * mcpBG[3];                //! �w�i�`��
	void BgUpdate(StaticObject * Left, StaticObject * center, StaticObject * Right, float speed);
	std::vector<std::unique_ptr<StaticObject>> BG01; //! �w�i�`��p�I�u�W�F�N�g�̕`��
	std::vector<std::unique_ptr<StaticObject>> BG02; //! �w�i�`��p�I�u�W�F�N�g�̕`��
	std::vector<std::unique_ptr<StaticObject>> BG03; //! �w�i�`��p�I�u�W�F�N�g�̕`��
	
	bool Effflg;  //! �����̃}�b�v�`�b�v�ɓ����ɓ������ăG�t�F�N�g��������Đ������̂�h��

private:		
	int mSplitx, mSplity;                   //! �}�b�v�`�b�v�̕�����
	FLOAT2 msScale;                         //! �g��k����	
	StaticObject * mcpMapTip;               //! �}�b�v�`�b�v�`��p�I�u�W�F�N�g
	AnimationHitObject * mcpItem;           //! �}�b�v�`�b�v�`��p�I�u�W�F�N�g
	
	bool first = true;
};

