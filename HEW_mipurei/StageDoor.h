#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "TextureManager.h"

/* --------------------------------- 
// �X�e�[�W�Z���N�g��ʂ̎��ɂ��� */
class StageDoor :
	public AnimationHitObject
{
public:
	StageDoor();
	
	~StageDoor();

	void Update();
	void Draw();
	Box * GetBoxCol();
	void SetColSize(float _x, float _y); 
	void SetHit(bool _state); 
	bool GetHit();

private:

	enum DoorState{
		Door_Open,  //! �J���Ă�r��
		Door_Close, //! ���Ă�r��
		Door_Opned, //! �J�����������
		Door_Closed //! ���؂������
	};

	
	DoorState State;   //! ���
	Vector2 ColSize;   //! �����蔻��̃T�C�Y
	Box * mcpBox;
	AnimationHitObject * AbuttonObj;
	bool CurrentHit;   //! ���݃v���C���[���h�A�̑O�ɂ���̂��𔻒f����t���O
	int FrameCnt;      //! �t���[���𐔂���
	int CloseFrameCnt; //! ����Ƃ��p�̃t���[���J�E���g
	bool Open;         //! �����󂢂Ă邩�󂢂ĂȂ���
	bool Sound = false;
	bool Abutton;        //! A�{�^���`��t���O

};

