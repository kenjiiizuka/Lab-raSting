#pragma once
#include "BaseEnemy.h"
#include <vector>

class Fordon :
	public BaseEnemy
{
public:
	Fordon(); 
	~Fordon();
	void Update();
	void Draw();
	void CreateMenber(int _num);

	int GetNumMenber(); //! �����o�[�̐���Ԃ�
	TailReaction SetStingPower(float _Power, bool _Elect);  //! �h����ă��A�N�V������Ԃ��֐�
	Fordon * GetMenber(int _index);                         //! �����o�[�̎擾�֐� �����͉��Ԗڂ̃����o�[
	void SetInitVec(Vector2 _vec);
	void SetVec(Vector2 _vec);
	Vector2 GetVec() override;
private:
	Fordon(bool _state, int _formation);                    //! �����o�[�𐶐�����Ƃ��Ɏg���R���X�g���N�^
	void Update_Top();                      //! �擪�̍X�V����
	void Update_Member(Vector2 _pos);       //! �����o�[�̍X�V����

	void Move();                            //! �ړ��֐�
	void ForceProces();                     //! ���W���ړ�������֐�
	void Move_Menber(Vector2 _destination); //! �����o�[�̎��̈ړ�

	Vector2 Movevec; //!�@�����o�[�ɓn���p�̍��W�i�|���ꂽ��������������߁j
	std::vector<std::unique_ptr<Fordon>> Member;        //! ����̃����o�[
	bool Top;										    //! �擪�ɂ��邩�ǂ���
	int AtkIntervalCnt = 0;                             //! �U���܂ł̃C���^�[�o��
	int ReturnCnt = 0;                                  //! �U���̂��Ƃ��ǂ鎞�̃J�E���g�Ȃɂ��ɂ��������Ƃ��悤
	bool Atk = false;                                   //! �U���t���O
	bool AtkRetrun = false;                             //! �U�����I�����Ĉ��̍��x�܂Ŗ߂�
 	float Speed = 0.008f;                               //! ���[�u�X�s�[�h
	float AtkSpeed = 0.01f;
	float TotalMove = 0;                                //! �ړ����v
	float MoveDeg   = 30;                               //! �ړ���x
	float Totaldeg  = 0;                                //! �p�x�̕ψʂ�����
	float MoveRad   = 0;                                //! �ړ��̊p�x(�ʓx�@)
	float Add       = -0.5f;                            //! �p�x�̕ψʂ����
	int FormaionNum;                                    //! ����̐�
	bool Moved      = false;                            //! �f�o�b�O�p�ϐ�
};

