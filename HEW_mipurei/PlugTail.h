#pragma once
#include "AnimationHitObject.h"
#include "PlayerState.h"
#include "Box.h"
#include "eDirection.h"
#include "Circle.h"
#include "Image.h"
#include "Log.h"

/* ==================================================================== 
// PlugTaile�N���X �v���C���[�̂����ۃN���X�@�@�@�@�@�@�@�@�@�@�@�@  //
// ����� : �ђ� ���i�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@  */

//! �����ۂ̃X�e�[�^�X���v���C���[�̏�Ԃɂ���ĕω�����̂Ńv���C���[������l��ύX���₷���悤�ɂ���������������

//! �v���C���[�̈ʒu��������Ă��̒l���炵���ۂ̈ʒu�����߂�
//! �����ۂ̓}�E�X�ƘA�����ē���

class PlugTail :
	public AnimationHitObject
{
public:
	PlugTail(Vector2 & _Tailvec, Vector2 & _movevec, ePlayerState & _state, eDirection & _direction, eElectricity & _electstate); //! �R���X�g���N�^
	~PlugTail(); //! �f�X�g���N�^

	void Update() override;
	void LastUpdate() override;           //! �v���C���[�������蔻�菈�����s������ɍ��W���C�����鏈��
	void Draw() override;
	bool SetState(TailState _state);      //! ��Ԃ̃Z�b�g�֐�
	void Destroy();                       //! �v���C���[��HP��0�ɂȂ������̏���
	bool GetChrage();                     //! �h�����đѓd����邩
	AnimationSprite * GetElestSpear();
	void SetFlash(bool _state);           //! �_�ł������̃Z�b�^�[
private:
	//! �����o�֐�
	void Idol_Controller();               //! Idol��Ԃ̊֐� �R���g���[���[	
	void Attack_Controller();             //! �U����Ԃ̊֐� �R���g���[���[
	void State();                         //! ��Ԃɉ���������
	void Tail();						  //! �����ۂ̒��ԕ����̏���
	void Aim_Controller();                //! �G�C�� �R���g���[���[
	void Reaction_Controller();           //! �U����̃��A�N�V�����̏���
	void AttackPosture_Controller();      //! �}�E�X�ő��삵�Ă��鎞�̍U���Ԑ��֐�
	void Bounce();                        //! �����ۂ��h���Ă͂������Ƃ��̃��A�N�V����
	void Stop();                          //! �h���炸�Ɏ~�܂鎞
	void StingStop_Controller();          //! �����ۂ��h������Ɏ~�܂郊�A�N�V���� �R���g���[���[
	void Through();                       //! �����ۂ��h������Ɋт�����
	void Sting_Controller();              //! �h���鎞�̏���
	void StingDeep_Controller();          //! �[���h����Ƃ��̏���
	void ReturnTail();                    //! �����ۂ��h������Ɏh���O�̈ʒu�ɖ߂鏈��
	void DisCharge();                     //! ���d
	void MoveLimit(int _speed  =12);      //! �ړ������֐�
	void StingObj();                      //! �h���Ă���I�u�W�F�N�g�ɂ������鏈��
	void ElectSpear();                    //! �d�C�̑��̏���


	//! ���d�Ɏg���ϐ����܂Ƃ߂��\����
	struct SDisCharge{
		bool Able;          //! ���d�\���𔻒f����t���O
		bool Doing;         //! ���d���̃t���O 
		bool End;           //! ���d�I���̃t���O
		int Cnt ;           //! ���d���Ƀt���[���𐔂���		
		bool Hit;           //! ���d���h���Ă�Ώۂɓ����邩�ǂ���
		int EffectNum;      //! ���d�̃G�t�F�N�g���o����
		int DrawEffectNum;  //! ���ڂ̃G�t�F�N�g�Ȃ̂�
		int EffectCnt;      //! ���ɃG�t�F�N�g�������܂ł̃J�E���g
		bool EffectDraw;    //! �G�t�F�N�g�`��t���O
	};

	//! �����ۂ̐�
	struct SSection {
		AnimationHitObject * Section;    //! �����ۂ̒��ԕ���	
		TailSectionInf Inf[100];         //! �����ۂ̒��ԕ����̍��W
		TailSectionInf PrevInf[100];     //! �����ۂ̒��ԕ����̍��W(�����ۂ̋O�ՂƂ��ĕۑ�����)
		FLOAT2 Size;                     //! �����ۂ̒��ԕ����̃T�C�Y
		FLOAT2 DefaultSize;              //! �����ۂ̒��ԕ����̒ʏ�T�C�Y
		FLOAT2 AimSize;                  //! �G�C�����̃T�C�Y
		float Length;                    //! �����ۂ̒���
		float PichDefault;               //! �����ۂ̂ӂ��̊Ԋu �ʏ펞
		float Pich;                      //! �Ԋu
		float PichAim;                   //! �G�C�����ƍU�����̂����ۂ̊Ԋu
		int Num;                         //! �����ۂ̐߂����`�悷��̂�
		int OldNum;                      //! �����ۂ̑O�t���[���̐߂̐�
	};

	struct SBounce {
		int TotalAngle;   //! ���Z�����p�x
		float TotalMove;  //! �ړ�������
		float speed;      //! �͂������X�s�[�h
		bool ReTail;      //! �K����߂��t���O
		bool Flg;         //! �͂�����Ă���t���O
		int Cnt;          //! �t���[���𐔂���
	};

	SBounce msBounce;                     //! �͂������Ƃ��̃��A�N�V�����Ɏg���\����
	TailState mState;                     //! ���g�̃X�e�[�g
	Vector2 mcDefaultSize;                //! �ʏ펞�̃T�C�Y
	Vector2 mcAimeSize;                   //! �G�C�����Ă�Ƃ��̃T�C�Y
	TailAttackState AttackState;          //! �U���̏��
	TailReaction mReaction;               //! �����ۂ��͂����ꂽ�Ƃ��Ȃǂ̃��A�N�V�������ǂꂩ�𔻒f����
	int mReactionFrameCnt;                //! �t���[���𐔂���
	ePlayerState & mPlayerState;          //! �v���C���[�̏��	
	Vector2 & mcPlayerVec;                //! �v���C���[�̈ʒu
	eDirection & mDirection;              //! �v���C���[�̌����Ă����
	eDirection PrevDirection;             //! �v���C���[�̌����Ă����(�O�t���[��)
	Vector2 & mcTailRoot;                 //! �����ۂ̕t����	
	Vector2 mcOldPlayerVec;               //! �v���C���[�̑O�t���[���̈ʒu	

	Vector2 mcTailDistance;               //! �����ۂ̕t��������̋����@�������ς�������ɑΉ��ł���悤�ɋ����������Ă���
	Vector2 mRightStick_C;                //! �E�X�e�B�b�N�̓|��Ă����
	
	float mTailAngle;                     //! �����ۂ̊p�x
	float DrawTailAngle;                  //! �`��p�̐K���̊p�x
	float mTailRange;                     //! �����ۂ̓�������͈�...�͂��͈�
	float mAtkSpeed;                      //! �U���̑��x(�����ۂ̓�������)
	float mDownAtkSpeed;                  //! �G���т����牺�~�␳��������
	float mReturnSpeed;                   //! �U����ɂ����ۂ���̈ʒu�ɖ߂鎞�̃X�s�[�h 
	bool AtkStop;                         //! �h���Ď~�܂������𔻒f����t���O
	bool TameSE = true;

	float RStickAngle;                    //! �E�X�e�B�b�N�̃A���O��
	eDirection ReactionDerection;         //! ���A�N�V�����̎��ɓG�ɑ΂��Ăǂ̕����ɂ��邩

	bool mOverheat;                       //! �h�������d�@���I�[�o�[�q�[�g���������f����t���O
	bool mAimeAngleSet;                   //! �G�C���ɍs�����Ƃ��ɂ����ۂ̌������Z�b�g����t���O

	SDisCharge msDisCharge;               //! ���d�\����
	SSection msSection;                   //! �����ۂ̐�
	eElectricity & ElectState;            //! �ѓd�̏��
	bool mCharge;                         //! �`���[�W�t���O
	//! �R���g���[���[����̂��߂̕ϐ�
	bool TriggerStart_C;                   //! �g���K�[�̌v���J�n�t���O
	bool Attack_C;                         //! �U���J�n�t���O
	float AttackInitSpeed;			       //! �U���̏���
	int MaxTrigger_C;                      //! �g���K�[�̍ő�l	                      
	float mStingPower;                     //! �h������(�U���̋���)

	Box * mcpCol;                          //! ���g�̓����蔻��������N���X	
	Circle * mcpAttackCircle;              //! �U���p�l����	
	Vector2 mcAttackPos;                   //! �U��������������W, �����ۂ̐�[����
	float AttackRadius;                    //! �U���̔��a
	FLOAT2 msColSize;                      //! �����蔻��̃T�C�Y
	                         
	bool mOnElectForDynamo = false;

	//! �d�C�̂��
	struct S_ElectSting{                    
		bool Activ = false; 
		bool First = false;                 //! �ѓd��ԂɂȂ����u��(�ŏ��ɂł񂫂̂�肪�o�Ă��鎞)
		AnimationHitObject * ElectSting;    
		Vector2 ColPos;						//! �����蔻��̈ʒu
		Vector2 ColRootPos;                 //! �����̓����蔻��̈ʒu
		Circle * Col;                       //! �d�C�̑��̓����蔻��(��[)
		Circle * ColRoot;                   //! ���{
		Vector2 DefaultSize;                //! ���������Ȃ������̃T�C�Y
		Vector2 SmallSize;                  //! �������Ƃ��̃T�C�Y
		Vector2 Size;                       //! �����݂̃T�C�Y
		float Arufa;                        //! �����x
		float TailDistance;                 //! �K������̋��� (���̂Ȃ����ňʒu�����܂�)
		bool Flash = false;
	};

	S_ElectSting msSpear;

	//! �h���Ă���I�u�W�F�N�g
	GameObject * mcpStingObj;
	//! �f�o�b�O�p

	Image mImage;
	bool Red;
	bool Yellow;
	bool Blue;
	bool Nomal;
public: //! �Q�b�^�[�A�Z�b�^�[
	bool GetOverheat();                           //! �I�[�o�[�q�[�g���������炤�Q�b�^�[
	void SetAttackState(TailAttackState _state);  //! �U���̏�Ԃ̃Z�b�^�[
	Box * GetCol();                               //! ���g�̓����蔻��Ɏg�����̃Q�b�^�[
	Circle* GetAttackCol();                       //! �U���̓����蔻��̃Q�b�^�[
	Circle GetSpearCol();                         //! �d�C�̑��̓����蔻��
	Circle GetSpearColRoot();                     //! �d�C�̑��̍����̓����蔻��
	float GetStingPower();                        //! �h�������Q�b�^�[
	Vector2 GetTailDistance();                    //! �����ۂ̋����̃Q�b�^�[�@
	void SetReaction(TailReaction _reaction ,eDirection _direction);     //! �����ۂ̎h������̃��A�N�V�����Z�b�^�[
	void TailReturn();                            //! �K���𔲂��֐�(�ǂ�ȏ�Ԃ���ł������܂�)
	bool GetTailRactionState();                   //! �����ۂ̏�Ԃ�Ԃ�
	bool GetAttackState();                        //! �U���̏�Ԃ�Ԃ��@true�Ȃ�U���� 
	void SetStingObj(GameObject * _stingobj);     //! �h���Ă�I�u�W�F�N�g�̃Z�b�^�[


};

