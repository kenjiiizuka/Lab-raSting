#pragma once
#include "AnimationHitObject.h"
#include "Player.h"
#include <vector>
#include <memory>

//! �l�N�g�[��������

class NecthorHammer;
class NecthorDebri;
class ShockWave;
class Smoke;
class Necthor_Allow;

class ReNecthor :
	public AnimationHitObject
{
protected:
	//! ���g�̏��
	enum eNecthorState {
		State_Idol,
		State_PressHammer,
		State_ShockWave,
		State_RushWave,
		State_LeapDebri,  //! �P�|�T�̃l�N�g�[���p�̍U���@���ꂫ����яオ���i�{���{���X�̓����������̎��o��D�U���݂����ȁj
		State_Down,   //!�|��Ă���
		State_Destroy
	};

	enum Texture_State {
		Tex_Idol,
		Tex_Attack,
		Tex_Attack2
	};

	//! �����蔻��Ɏg���ϐ����܂Ƃ߂��\����
	//! �{�X�͓����蔻��𕪂��Ă��ĕ�������̂ō\���̂ɂ܂Ƃ߂܂���
	struct sCol {
		Box * Col;
		Box * AtkCol;                                           //! �U������
		Vector2 Pos;	                                        
		Vector2 Size;	                                        
		bool TailHited;                                         //! �U�������Ă�ꂽ���𔻒f����
		int Cnt;                                                //! ���Ă��Ă��琔�t���[���͍U���Ƃ̓����蔻������Ȃ��A���̃t���[���𐔂���
	};

	//! �e�U����������
	struct AttackCnt {
		int Press;
		int Wave;
		int Ruch;
	};

public:
	ReNecthor();                                               //! �R���X�g���N�^
	ReNecthor(float _x, float _y);                             //! ��������R���X�g���N�^
	~ReNecthor();                                              //! �f�X�g���N�^
											                   
	void Update();							                   
	void Draw();							                   
	void CollisionUpdate();                                    //! �����蔻��̏���
	void LastUpdate();                                         //! �ŏI�X�V����
	void SetPlayer(Player * _player);                          //! �v���C���[���Z�b�g����
	void BattleStart();                                        //! �{�X�𓮂���
	bool GetDestroyed();                                       //! ���g���|���ꂽ���Ƃ�������֐� 
protected:
	virtual void Idol();                                       //! Idol�̏���
	virtual void Atk_PressHammer();                            //! �n���}�[��@������U��(���ꂫ���o�܂�)
	virtual void Atk_ShockWave();                              //! �Ռ��g�U��
	virtual void AttackStateMachine();                         //! �ǂ̍U�������邩�����߂�
	virtual void Atk_RushWave();                               //! �A���Ռ��g�U��
	void FallDwoned();                                         //! �|���ꂽ���̏���
	void Destroy();                                            //! �Ƃǂ߂��h���ꂽ�Ƃ��̂����@
	void ColFix();                                             //! ���g�̓����蔻��̈ʒu�̒����֐�
	void Damage();                                             //! �_���[�W�̏���
	virtual void SmokeUpdate();                                        //! �X���[�N�̍X�V����
	void TexChange();                                          //! �e�N�X�`���̏�Ԃɍ��킹�ĕύX���Ă����

	//! ���@�����o�ϐ��@��
	eNecthorState State;                                       //! ���
	int IdolCnt;                                               //! �A�C�h����Ԃ̃t���[���J�E���g(�U���J�n�̔��f�Ɏg��)
	int AttackCoolTime;                                        //! �U�����̃A�j���[�V�����̃t���[���𐔂���
	Player * mcPlayer;                                         //! �O���œ����蔻������̂��߂�ǂ������̂Ńv���C���[�̃A�h���X��������Ă����ł��܂�
	sCol MyCol;												   //! �{�̂̓����蔻��
	sCol WeekCol;											   //! ��_�̓����蔻��
	float HP;												   //! �̗�10     (�����Q�[�W�����邱�ƂɂȂ����Ƃ��̂��߂Ƀt���[�g�^�ɂ��Ă���)
	float TakenDamage;										   //! ��_���[�W (�����Q�[�W�����邱�ƂɂȂ����Ƃ��̂��߂Ƀt���[�g�^�ɂ��Ă���)
	int DamageFrameCnt;										   //! �_���[�W�ɏ����Ɏg���ϐ�
	bool DamageFlg;											   //! �_���[�W���������邩���f����t���O
	bool BattleActiv = false;                                  //! �퓬�t���O
	bool ShockWaved = false;                                   //! �Ռ��g�U�����������ǂ���
	AttackCnt AtkCnt;                                          //! �e�U����������
	int RushCnt;                                               //! ���b�V���U�����ɉ���U���������𐔂���
	int RushMax;                                               //! �A�ł̍ő��
	int RushFrameCnt;                                          //! ���b�V���U���̗��ߎ���
	bool RushPreparation = false;                              //! ���b�V���U���̗\������
	int PreparationCnt;                                        //! �\������̃t���[���𐔂���
	float Shiver;                                                //! �\������Ők����l
	int ShockWaveCoolTime;                                     //! �Ռ��g�U���̃N�[���^�C�� 
	int ShockWaveCoolTimeMax;                                  //! �Ռ��g�U���̃N�[���^�C���ɕK�v�Ȏ���
	NecthorHammer * Hammer;                                    //! �n���}�[
	std::vector < std::unique_ptr<NecthorDebri>> Debri;        //! ���ꂫ
	std::vector<std::unique_ptr<ShockWave>> Wave;              //! �Ռ��g    
	std::vector<std::unique_ptr<Smoke>> Smokes;                //! ��
	std::unique_ptr<Necthor_Allow> Allow;         //! �n���}�[�ɏ��Ƃ���̂₶�邵
	bool LeftSmoke, RightSmoke, NomalSmoke;                    //! �����o���t���O
	int AnimX;                                                 //! �A�j���[�V������X�����̌��݂̔ԍ�
	Texture_State TexState;                                    //! ���̂ǂ̃e�N�X�`��Ȃ̂�
	Texture_State TexState_Prev;                               //! �ߋ��t���[���̂ǂ̃e�N�X�`��Ȃ̂�
	bool mDestroy = false;                                     //! �|���Ƃ��̉��o���S�ďI��芮�S�ɓ����Ȃ��Ȃ������t���O
	int DestroyCnt = 0;                                        //! �Ō�̉��o�̎��ɃG�t�F�N�g���o���^�C�~���O�𒲐����邽�߂̕ϐ�
	float Arufa = 1.0f;
	bool HightHP = true;

	bool AtkSEflg;
	//! �f�o�b�O�p
	Image image;
	
};

