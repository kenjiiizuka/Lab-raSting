#include "GameManager.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

GameManager * GameManager::mcpIns = nullptr;

//! ���̂̐����p�֐�
void GameManager::Create()
{
	if (mcpIns == nullptr) {
		mcpIns = new GameManager();
	}
}

//! �j���p�̊֐�
void GameManager::Destroy()
{
	delete mcpIns;
}

//! ���̂̎擾�֐�
GameManager * GameManager::GetInstance()
{
	return mcpIns;
}


//! �w�肵���X�e�[�W�̃N���A�󋵂�Ԃ��֐�
bool GameManager::GetStageClearState(eStage _stage)
{
	return ClearStage[_stage];
}


/* --------------------- 
// �N���A���Z�b�g���� */
void GameManager::SetStageClear(eStage _stage)
{
	ClearStage[_stage] = true;
}


bool GameManager::GetThutrial()
{
	return Thutrial;
}

void GameManager::SetThutrial(bool _state)
{
	Thutrial = _state;
}

bool GameManager::GetCheackPoint()
{
	return CheackPoint;
}

bool GameManager::GetBossCheackPoint()
{
	return BossCheackPoint;
}

void GameManager::SetBossCheackPoint(bool _state)
{
	BossCheackPoint = _state;
}

void GameManager::SetCheackPoint(bool _state)
{
	CheackPoint = _state;
}

void GameManager::SetNowPlayerStage(eScene _stage)
{
	NowPlayStage = _stage;
}

eScene GameManager::GetNowStage()
{
	return NowPlayStage;
}

bool GameManager::GemeClear()
{

	//! �S�ẴX�e�[�W�̃N���A�󋵂��݂āA��ł��N���A���ċ��Ȃ�������false��Ԃ�
	for (int i = 0; i < 5; i++) {
		if (!ClearStage[i]) {
			return false;
		}
	}
	return true;
}

bool GameManager::GetAnimation()
{
	return Animatiom;
}

void GameManager::SetAnimation(bool state)
{
	Animatiom = state;
}

bool GameManager::GetFirst()
{
	return GameFirst;
}

void GameManager::PlayedThoutrial()
{
	ofstream First("assets/Save/First.dat");
	First << 0 << ',';
}

//! �R���X�g���N�^
GameManager::GameManager()
{
	BossCheackPoint = CheackPoint = Thutrial = false;
	//! �t�@�C�����猻�݂̃X�e�[�W�̃N���A�󋵂�ǂݎ��������
	ifstream Save("assets/Save/Save.csv");
	string tmp;
	stringstream State;
	bool wark;
	for (int i = 0; i < 5; i++) {
		getline(Save,tmp,',');
		if (tmp == "Clear") {
			ClearStage[i] = true;
		}
		else if (tmp == "No") {
			ClearStage[i] = false;
		}
	}

	ifstream First("assets/Save/First.dat");
	getline(First,tmp,',');
	stringstream first(tmp);
	first >> GameFirst;
}

//! �f�X�g���N�^
GameManager::~GameManager()
{
	//! �t�@�C���Ɍ��݂̃X�e�[�W�̃N���A�󋵂���������
	ofstream Save("assets/Save/Save.csv");
	for (int i = 0; i < 5; i++) {
		if (ClearStage[i]) {
			Save << "Clear" << ',';
		}
		else {
			Save << "No" << ',';
		}
	}

	Save << -1 << ',';
}
