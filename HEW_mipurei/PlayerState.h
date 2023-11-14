#pragma once
#include "Vector2.h"
#include "eDirection.h"
#define STING_STRONG 0.12f
#define STING_MIDIUME 0.06f
//! �h�������̎�͒��ȉ��ɂŔ��f�ł���̂Œ�`�͂��܂���


//! �v���C���[�{�̂Ɏg��enum�ƍ\����---------------------------------------------------------
/* -------------------------------
// �v���C���[�̏�Ԃ̗񋓌^�ł� //
// ����� : �ђ� ���i           */
enum ePlayerState {
	Player_Idol_Walk,  //! �ʏ�
	Player_Walk,       //! ����
	Player_Attack,     //! �U����
	Player_Down        //! HP�������Ȃ�����
	//Player_Reaction, //! �U�������Ƃ��̃��A�N�V�����������ԁA
};

enum eElectricity {
	Elect_None,     //! �ѓd���Ă��Ȃ�
	Elect_Small,    //! ���ѓd
	Elect_Midiume,  //! ���ѓd
	Elect_Large,    //! ��ѓd
	Elect_Super,    //! ���ѓd
};

//! �v���C���[�̃X�e�[�^�X�\���̂ł�
struct PlayerStatus {
	float MoveSpeed;     //! �ړ����x
	float InitJumpPower; //! �W�����v�� ����������Ďg��
	float TmpJumpPower;  //! ���ۂɏ����Ɏg���p�ϐ�
	int HP;              //! �̗�
	bool MoveAble;       //! �ړ��\�t���O
	PlayerStatus();
};

//! �W�����v�Ɏg���ϐ����܂Ƃ߂��\����
struct SJump {
	int FrameCnt; //! �W�����v���̃t���[���J�E���g
	int AnimCnt;  //! �W�����v���̃A�j���[�V�����J�E���g
	bool Doing;   //! �W�����v(�󒆂ɂ��邩)���̃t���O
	bool Up;      //! �W�����v�O�̏����A���ߎ���
	bool End;     //! �W�����v���Ē��n�����t���O
	bool Jump;    //! �W�����v�����ǂ���
	SJump();
};

//! �_���[�W���o�Ɏg���\����
struct SDamage {
	int Cnt;                //! �t���[���J�E���g
	bool Flg;               //! �_���[�W���󂯂��t���O
	bool Effect;            //! �_���[�W�G�t�F�N�g�t���O(��荇����30�t���[���_��)
	bool NockBack;          //! �m�b�N�o�b�N�t���O
	bool Overheat;          //! �I�[�o�[�q�[�g�ɂ��_���[�W
	eDirection NockBackWay; //! �m�b�N�o�b�N�̕���
	SDamage();
};

//! �ѓd�Ɋւ���ϐ����܂Ƃ߂��\����
struct SElectricity {
	int ChargeCnt;  //! �ѓd�̃J�E���g�@���̐��l�ɂ���đѓd�̏�Ԃ��ς��
	int SuperCnt;   //! ���ѓd�̎��̃t���[���𐔂���
	float UpRate;   //! �X�e�[�^�X�̏㏸�{��
	bool EndSuper;  //! ���ѓd�I���t���O
	bool Super;     //! ���ѓd���̃t���O
	SElectricity();
};

//! �����ۂɎg���\���̂Ɨ񋓌^----------------------------------------------------------------
//! �����ۂ̈ʒu�Ɗp�x������\����
struct TailSectionInf {
	Vector2 Pos;
	float Width; //! ����
	float Angle;
	Vector2 Velocity;     //! �ړ���
	float Gravity;        //! �d��
	Vector2 Acceleration; //! �����x
	Vector2 Tension_Up;   //! �ォ������������
	Vector2 Tension_Down; //! ����������������
	Vector2 Resultant;    //! ����
	bool Fin;             
};

//! �����ۂ̏��
enum TailState {
	Tail_Idol,
	Tail_Attack,
};

//! �����ۂ��h�����Ƃ��̃��A�N�V�����̗񋓌^�ł�
//! �ǂ�ȃ��A�N�V����������̂���Ԃ����Ɏg���܂�
enum TailReaction {
	TailReaction_None,      //! �Ȃɂ��Ă��Ȃ����
	TailReaction_Bounce,    //! �͂������
	TailReaction_Stop,      //! �~�܂� �h����Ȃ�(��΂ɂ�����Ȃ�����Map�ȂǂɎh�����Ƃ��p)
	TailReaction_StingStop, //! �h�����Ď~�܂�
	TailReaction_Through,   //! �т�
	TailReaction_Sting,     //! �h����
	TailReaction_StingDeep, //! �[���h����
	TailReaction_End        //! ���A�N�V�����̏I��
};

// �U�����̏��
enum TailAttackState {
	AttackState_None,
	AttackState_Aim,      //! �_���Ă��鎞
	AttackState_Sting,    //! �h���Ă���iRT�������Ă��牽���ɓ����邩�U���������܂Łj
	AttackState_Reaction, //! �U����̃��A�N�V����
	AttackState_End       //! �U���I��
};

