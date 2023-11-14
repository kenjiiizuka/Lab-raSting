#pragma once
#include "Character.h"
#include "PlugTail.h"
#include "Log.h"
#include "PlayerState.h"

//! ���Ƃŏꏊ�ړ������܂�

class PlayerSmoke;
class HPICon;
class PlayerBattery;

class Player :
	public Character
{
public:
	Player();                    //! �R���X�g���N�^�@�v���C���[�̃X�e�[�^�X���t�@�C������ǂݍ���Œ����ł���悤�ɂ���
	Player(float _x, float _y);  //! ���W�ݒ��
	~Player();	                 //!  �f�X�g���N�^
	void Update() override;
	void LastUpdate() override;              //! �����蔻�菈���̌�ɍs������
	void Draw() override;
	void SetDamege(eDirection _nockback);    //! �_���[�W�͂P�Œ�ł�
	int GetHP();                             //! HP�̃Q�b�^�[(UI�ɏ���n�����߂ɕK�v)
	bool GetCharge();                        //! �ѓd�̏�Ԃ�Ԃ�
	void AddBoruto();
	void AddElect();                         //! �ѓd����֐�
	void MoveStop(bool _state);              //! �A�C�h���ɂȂ��Ē�~����֐�
	void SetUIActiv(bool _activ);            //! UI�`��̐؂�ւ��֐�
	//! ���Ԃ�񕜂�����
private:
	//! �����o�֐�
	void Electricity();           //! �ѓd�̓x���ɉ���������������
	void State_Controller();      //! �R���g���[���[����̎��̏�Ԃɉ���������
	void ForceProces();           //! �v���C���[�����W�����v�Ȃǂ́A���̃L�����N�^�[�Ƃ͈Ⴄ�����������Ȃ�Ɨ\�z�����̂ŁA���̊֐����ŏd�͂̏�����A���������͂̉��Z�Ȃǂ��s���܂�
	void Move_Mouse();            //! �ړ��֐� �}�E�X
	void Move_Controller();       //! �ړ��֐� �R���g���[���[
	void MoveReady();
	void Jump();                  //! �W�����v�֐�
	void Damage();                //! �_���[�W���󂯂��Ƃ��̏���
	void Recovary();              //! �񕜂��鎞�̏���
	void Destroy();               //! Hp��0�ɂȂ������̏���
	
	//! �����o�ϐ�

	bool UIActiv = true;         //! UI�̕\����\���̐؂��
	bool KamaeSE = true;
	PlayerStatus msStatus;	      //! �X�e�[�^�X
	eDirection mDirection;        //! ����
	ePlayerState mState;          //! ���
	eElectricity mElectState;     //! �ѓd�̏��
	SJump msJump;                 //! �W�����v�\����
	SDamage msDamage;             //! �_���[�W�\����
	SElectricity msElect;         //! �ѓd�\����
	AnimationHitObject * UIFrame; //! UI�̘g
	int mNumBoruto;               //! �{���g���E������
	int mToalBoruto;              //! �{���g���E�������v
	bool mRecovery;               //! �񕜃t���O(�{���g����萔�E������񕜂���)
	bool Stop = false;
	//! �v���C���[�̂����ۂɊւ���ϐ�
	PlugTail * mcpPlugTail;       //! ������
	Vector2 mcTailRoot;           //! �����ۂ̕t�����̈ʒu
	Vector2 BeforColPos;          //! �����蔻�菈�����s���O�̍��W�@�����蔻�菈�����s������ɂ����ۂ̈ʒu���C�����邽�߂ɕK�v
	
	//! �t���O�֘A
	bool AttackFlg;               //! �U���t���O
	bool OnObj;                   //! �I�u�W�F�N�g�̏�ɏ���Ă��邩
	bool Destroyed = false;         //! HP���O�ɂȂ�_�E�����o���I������ɗ��Ă�t���O
	bool ChangeDestroy = false;
	int DestroyCnt = 0;

	bool TailDraw = true;
	float Shive;                  //! Hp���[���ɂȂ������ɐk���鎞�̒l
	bool Death = false;           //! Hp���[���ɂȂ����痧�Ă�
	PlayerSmoke * Smoke;          //! Hp�������Ȃ������̃X���[�N
	float TailArufa = 0.0f;
	HPICon * mcpHPIcon;           //! HP�`��pUI
	PlayerBattery * Battery;      //! �ѓd��UI
	Vector2 CameraMoveMent;  //! �J�����ɂ��̃t���[���ɂǂꂾ���ړ���������n�����߂̕ϐ�
public: //! �Z�b�^�[�A�Q�b�^�[
	void SetVec(Vector2 _vec) override;               //! �v���C���[�̍��W���Z�b�g����Ƃ����ۂ̍����̈ʒu���Z�b�g���Ă��玟�̃t���[���̍X�V�����܂ł��ꂪ���܂��̂ŁA��p�ɂ���
	Box    *   GetTailCol();                          //! �����ۂ́@�����蔻��̃Q�b�^�[
	Circle*    GetAttackCol();                        //! �U���̓����蔻��̃Q�b�^�[
	Circle     GetSpearCol(int _index);               //! �d�C�̑��̓����蔻��̃Q�b�^�[(�����ō��{����[���I�ׂ�)
	bool       GetAttackFlg();                        //! �U�����������Ă��邩�̃Q�b�^�[
	float      GetStingPower();                       //! �h�������̃Q�b�^�[
	Vector2    GetTailRoot();                         //! �����ۂ̍��{�̍��W�̃Q�b�^�[
	Vector2    GetCameraMovement();
	bool       GetDeath();                            //! �v���C���[��HP���O�ɂȂ����t���O
	void       SetReaction(TailReaction _reaction, eDirection _direction);   //! �h�����Ƃ��̃��A�N�V�����̃Z�b�^�[
	PlugTail * GetTail();                             //! �����ۂ̃Q�b�^�[ �J�����ɓn���悤
};

