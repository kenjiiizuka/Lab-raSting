#include "GameManager.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

GameManager * GameManager::mcpIns = nullptr;

//! 実体の生成用関数
void GameManager::Create()
{
	if (mcpIns == nullptr) {
		mcpIns = new GameManager();
	}
}

//! 破棄用の関数
void GameManager::Destroy()
{
	delete mcpIns;
}

//! 実体の取得関数
GameManager * GameManager::GetInstance()
{
	return mcpIns;
}


//! 指定したステージのクリア状況を返す関数
bool GameManager::GetStageClearState(eStage _stage)
{
	return ClearStage[_stage];
}


/* --------------------- 
// クリアをセットする */
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

	//! 全てのステージのクリア状況をみて、一つでもクリアして居なかったらfalseを返す
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

//! コンストラクタ
GameManager::GameManager()
{
	BossCheackPoint = CheackPoint = Thutrial = false;
	//! ファイルから現在のステージのクリア状況を読み取り代入する
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

//! デストラクタ
GameManager::~GameManager()
{
	//! ファイルに現在のステージのクリア状況を書き込む
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
