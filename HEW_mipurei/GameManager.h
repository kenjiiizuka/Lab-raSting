#pragma once
#include "eScene.h"

/* ----------------------------------------- 
// �Q�[���}�l�[�W���[�N���X               //
// �Q�[���N���A�󋵂Ȃǂ��Ǘ����Ă���܂� */

#define GameMgr GameManager::GetInstance()

//!�ǂ̃X�e�[�W�̃N���A�󋵂𔻒f���邽�߂�enum
enum eStage {
	Stage_1_1,
	Stage_1_2,
	Stage_1_3,
	Stage_1_4,
	Stage_1_5,
	Stage_Max
};

class GameManager
{
public:
	static void Create();
	static void Destroy();
	static GameManager * GetInstance();

	bool GetStageClearState(eStage _stage);
	void SetStageClear(eStage _stage);             //! �X�e�[�W�N���A���Z�b�g����
	bool GetThutrial();                            //! �`���[�g���A�������邩���Ȃ����̃t���O�̃Q�b�^�[
	void SetThutrial(bool _state);                 //! �`���[�g���A���̃Z�b�^�[
	bool GetCheackPoint();                         //! ���ԃ|�C���g��G�������ǂ����̃Q�b�^�[
	bool GetBossCheackPoint();                     //! �{�X�O���Ԃ̐G�������ǂ����̃Q�b�^�[
	void SetBossCheackPoint(bool _state);                     //! �{�X�O���Ԃ̐G�������ǂ����̃Q�b�^�[
	void SetCheackPoint(bool _state);              //! ���ԃ|�C���g������������ǂ����̃Z�b�^�[
	void SetNowPlayerStage(eScene _stage);         //! ���v���C���Ă���X�e�[�W�̃Z�b�^�[
	eScene GetNowStage();                          //! �Q�b�^�[
	bool GemeClear();                              //! ���̃Q�[�����N���A���Ă��邩
	//! �A�j���[�V�����֘A�̃Z�b�^�[�Q�b�^�[
	bool GetAnimation();
	void SetAnimation(bool state);
	bool GetFirst();                              //! ���̃Q�[��������v���C�Ȃ̂�
	void PlayedThoutrial();                       //! �`���[�g���A���v���C���܂���
private:
	GameManager();
	~GameManager();

	eScene NowPlayStage;          //! ���v���C���Ă���X�e�[�W
	bool GameFirst;               //! ���̃Q�[�������߂ċN�������̂��𔻒f����t���O
	bool Thutrial;                //! �`���[�g���A������J�n����t���O
	bool CheackPoint;             //! ���ԃ|�C���g��G�ꂽ���ǂ������Ǘ�����t���O
	bool BossCheackPoint;         //! �{�X�O���ԂɐG�ꂽ���ǂ���
	bool ClearStage[Stage_Max];   //! �X�e�[�W�̃N���A�󋵂��Ǘ�����z��@�R���X�g���N�^�Ńt�@�C������N���A�󋵂�ǂݍ��݁A�f�X�g���N�^�ŃN���A�󋵂���������
	static GameManager * mcpIns;  //! 
	bool Animatiom = true;        //! �A�j���[�V���������邩�ǂ���

};



