#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "cMap.h"
//! �G�̃C���N���[�h
#include "SplitLowerEnemy.h"
#include "NormalEnemy.h"
#include "SoftEnemy.h"
#include "BaseDrone.h"
#include "Fordon.h"

using namespace std;
class EnemyManager
{
public:
	EnemyManager(string _filename, Player & _player, Map & _map); //! �R���X�g���N�^
	~EnemyManager();

	void Update();             //! �X�V����
	void LastUpdate();	       //! �����蔻���ɂ���X�V����
	void CollisionUpdate();    //! �����蔻�菈��
	void Draw();

	void AddX(float _x);               //! �S�Ă̓G��X���W���Z����
private:

	//! �Y�����Ɏg���\����
	struct EnemyIndex{
		int Tinpiller;
		int Splitter;
		int Hooder;
		int Aunper;
		int Fodon;
	};

	Map & mcMap;       //! ���̃V�[���̃}�b�v
	Player & mcPlayer; //! �v���C���[

	SoftEnemy * mcpHooder;         // �z�[�_�[
	SplitLowerEnemy * mcpSplitter; //! �X�v���b�^�[
	BaseDrone * mcpAunper;         //! �A�E���p�[
	NormalEnemy * mcpTinpiller;    //! �`���s���[  �`���s���[�͓�̂̓G�����􂷂�̂Ŕz��ɓ��ꂸ�ɏ������s��
	Fordon * mcpFordon;            //! �t�H�[�h��

	vector<BaseEnemy *>Enemies;    //! ���̔z��ɓ����Update����for�ŉ�
	int SplitterNum; // �X�v���b�^�[�̐�
	int FordonNum;
};

