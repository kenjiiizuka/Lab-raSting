#pragma once
#include "BossBase.h"
#include "AnimationHitObject.h"
#include"BoxObject.h"
#include"Plag.h"
#include "Image.h"
#include"Camerah.h"
/*
����ҁF����r��
�n���}�[��U�艺�낷�{�X�A�l�N�^�[�̃N���X�ł��B
*/


//�{�X�̏����Ɋւ���Define
#define ResistDef 6 //�v���C���[����̍U����ς����
#define AtkCharge 6 //��j2�b�Ȃ�2�Ƃ���Define�ɐݒ肵�Ă��炦�΁A���̎��Ԃ̌�Ƀn���}�[���낵�܂�
#define StopTime  9 //�U�艺�낵�Ă���~�܂鎞��

class Necthor :
	public BossBase
{
public:
	Necthor(float _X, float _Y);
	~Necthor();
	void Update();
	void Draw();
	int GetChargeTime();

	/*�{�X�̓����蔻��֘A�̊֐�*/
	//�{�X���̓����蔻����擾
	Box* GetBossBodyCollision();
	//�{�X�̑̂̓����蔻����擾
	Box* GetBossHeadCollision();
	//�{�X���U�艺�낷�n���}�[�̓����蔻����擾
	Box* GetBossHunmerCollision();
	//�v���O�̎擾
	Plag* GetPlag();

	//�����̒l��ChargeTime�ϐ��ɒ��ڑ������֐�
	void SetChargeTime(int _Time);
	//�����̒l��ChargeTime�ϐ��ɉ��Z����֐�
	void AddChargeTime(int _Time);
	//�{�X�̃��C�t�������Z����֐�
	void AddLife(int _Life);
	//�{�X���_�E�����Ă��邩�ǂ�������
	bool GetDownFlg();
	//�_���[�W�̃N�[���^�C�����擾
	unsigned int GetmDamageCoolTime();
	void SetmDamageCoolTime(unsigned int _Time);
	bool GetAliveFlg();
	void SetAliveFlg(bool _Flg);
	//Necthor���������邪�ꂫ�ƏՌ��g���擾���鏈��
	BoxObject* GetmpDebriesBox();
	BoxObject* GetmpWavesBox();
	void SetDamageFlg(bool _Flg);
	//�R���g���[���[�U���p�Ƀn���}�[�����낵���t���O���擾����֐�
	unsigned int GetCtrShakeFlg();

private:

	Plag* mpPlag;                       //�g�h���������Ƃ��ɍU������v���O�̕ϐ�
	unsigned int mAttackCoolTime;       //�n���}�[�U�艺�낵��̍d������
	unsigned int mLife;	                //�v���C���[�̂Ԃ������ɑς����
	unsigned int mDamageCoolTime;        //�_���[�W�̃N�[���^�C��
	ID3D11ShaderResourceView * mTmpTex;
	ID3D11ShaderResourceView * mPlagTex;//�g�h���ɂԂ������v���O�̃e�N�X�`��
	ID3D11ShaderResourceView * mAtkTex;//���C�t���Ȃ��Ȃ����Ƃ��̃e�N�X�`��
	bool mBossDownFlg;                  //�e�N�X�`����؂�ւ���Ƃ��̃t���O
	float NoDamageTime;                 //�A���_���[�W�h�~�p�̖��G����
	//�{�X�̑̂̓����蔻��
	Box* mpBodyCollision;
	Vector2 mpBodyColisionPos;
	//�{�X�̓��̓����蔻��@�@//Tail���A�N�V�����^�֐������APlayerState�ɓ����Ă�
	Box* mpHeadCollision;
	Vector2 mpHeadCollisionPos;
	//�n���}�[�̓����蔻��
	Box* mpHunmerCollision;
	Vector2 mpHunmerCollisionPos;
	//�����蔻��m�F�p�摜
	Image mcImage;

	//�U�艺�낵�܂ł̎���
	int mChargeTime;

	//�n���}�[��U�艺�낷�t���O
	bool mSwingFlg = false;

	//�R���g���[���[��U��������t���O
	unsigned int mCtrShakeFlg = false;

	//�����Ă��邩�ǂ�������
	bool AliveFlg = true;
	//��ʐU���p�̎��Ԍv���ϐ�
	unsigned int ShakeTime = 0;

	//�_���[�W���󂯂����̓_�ŗp�ϐ�
	bool DamageFlg = false;//Setter��true���_�ŏ����I������false�ɖ߂�
	bool AlphaFlg = false;
	float Alpha = 0.0f;//SetAlpha�֐��œn���p�̕ϐ�
	int AlphaCnt = 8;//�_�ł�����

	//���ꂫ Box�N���X���g�p����A��ʉ����琶���Ă���
	BoxObject* mpdebris;
	AnimationSprite* tmpdbrisAnimSprite;
	ID3D11ShaderResourceView* mdebrisTex;
	Vector2 mcdebreisPos;//���ꂫ�̍��W
	Vector2 mcdebreisScale;
	bool WaveMoveFlg;

	//�Ռ��g BoxObject�N���X���g�p
	BoxObject* mpWaves;
	AnimationSprite* mpWavesAnimSprite;
	ID3D11ShaderResourceView* mWavesTex;
	Vector2 mcWavesPos;//���ꂫ�̍��W
	Vector2 mcWavesScale;
	Box* mpWavesCollision;//���ꂫ�̓����蔻��

};

