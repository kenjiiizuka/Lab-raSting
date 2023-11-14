#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include "Player.h"
/* --------------------------------------------------------------
// �J�����N���X                                                //
// ���C���ƂȂ�J�����ł�                                      //
// ����� : �ђ� ���i                                          */

#define CAMERA Camera::GetIns()

class Camera
{
public:
	static Camera * GetIns();
	static void Create();
	static void Destroy();

	void Update();                                 //! �X�V����
	Vector2 GetCameraPos();                        //! �J�����̍��W�̃Q�b�^�[
	Vector2 GetCameraMove();                       //! �J�����̈ړ��ʂ̃Q�b�^�[
	FLOAT2 GetScale();                             //! �J�����̊g��k�����̃Q�b�^�[
	void Reset();                                  //! �J�����̈ʒu�����Z�b�g����
	void CameraFix(GameObject * _gameobj);         //! �J�����̂Ō����Ƃ��̈ʒu�g�嗦�����Ă������I�u�W�F�N�g�ɔ��f����
	void EffectFix(float & _x, float & _y , float & scale_x,float & _scale_y);                              //! �J�����ŃG�t�F�N�g�������Ƃ��̈ʒu�ɒ�������
	void SetZoom(float _x, float _y);              //! �g��k�����̃Z�b�^�[
	void FollowObj(GameObject * _followobj, float _followthresholdX = 0, float _followthresholdY = 0);    //! �w�肵���I�u�W�F�N�g��Ǐ]����悤�ɂ���֐�
	void FollowPlayer(Player * _player, float _followthresholdX = 0, float _followthresholdY = 0);
	void StartVibration(int _vibepower); //! ��ʐU���֐�(�J�����������݂ɓ������ĐU�����Ă���悤�Ɍ����܂�)
	bool GetVibration(); //! �U�����Ă��邩��Ԃ��֐�
	//! �J�������~�߂�֐�
	void MoveLeft(bool _state);
	void MoveRight(bool _state);
	void MoveTop(bool _state);
	void MoveDown(bool _state);
	bool GetRightMove();
	void SetFollowWay(bool _x, bool _y); //! �Ǐ]���Ăق��������̃Z�b�^�[
	void MoveCamera(Vector2 _move);      //!�J�����𓮂����֐�
private:
	Camera();  //! �R���X�g���N�^
	~Camera(); //! �f�X�g���N�^
	void Vibration(); //! ��ʐU���֐�

	static Camera * mcpIns;
	Vector2 mcPos;             //! �J�����̈ʒu
	Vector2 mcOldPos;          //! �J�����̈ʒu
	Vector2 mcMovement;        //! �J�����̈ړ���
	GameObject * mcpFollowObj; //! �Ǐ]����I�u�W�F�N�g�̃|�C���^
	Player * mcpFollowPlayer;  //! �Ǐ]����v���C���[�̃|�C���^
	Vector2 FollowObjOldVec;   //! �Ǐ]����I�u�W�F�N�g�̑O�t���[���̍��W
	float mZoomX;              //! �g��k����
	float mZoomY;              //! �g��k����
	FLOAT2 msFollowThreshold;  //! �Ǐ]����ʒu

	//! ��ʐU���Ɏg���ϐ�
	int FrameCnt;     //! ��ʐU�����J�n���Ă���o�߂����t���[���𐔂���
	Vector2 VibeMent; //! ��ʐU�����ĐU��������
	int mVibePower;    //! ��ʐU���̋���
	//! ���ꂼ��̕����̈ړ��\�����f�t���O
	bool mLeftMove;
	bool mRightMove;
	bool mTopMove;
	bool mDownMove;
	bool mFollowPlayer; //! �v���C���[��Ǐ]���Ă��邩
	bool mFollowObj;    //! �I�u�W�F�N�g��Ǐ]���Ă��邩(�v���C���[�͂̂���)
	bool mVibration;    //! ��ʐU�����邩�ǂ����̔��f
	bool Follow_y;      //! y�̕����ɒǏ]���邩���Ȃ������f����
	bool Follow_x;		//! x�̕����ɒǏ]���邩���Ȃ������f����

};


