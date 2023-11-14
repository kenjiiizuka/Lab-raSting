#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "cMap.h"
//! 敵のインクルード
#include "SplitLowerEnemy.h"
#include "NormalEnemy.h"
#include "SoftEnemy.h"
#include "BaseDrone.h"
#include "Fordon.h"

using namespace std;
class EnemyManager
{
public:
	EnemyManager(string _filename, Player & _player, Map & _map); //! コンストラクタ
	~EnemyManager();

	void Update();             //! 更新処理
	void LastUpdate();	       //! 当たり判定後にする更新処理
	void CollisionUpdate();    //! 当たり判定処理
	void Draw();

	void AddX(float _x);               //! 全ての敵のX座標加算する
private:

	//! 添え字に使う構造体
	struct EnemyIndex{
		int Tinpiller;
		int Splitter;
		int Hooder;
		int Aunper;
		int Fodon;
	};

	Map & mcMap;       //! そのシーンのマップ
	Player & mcPlayer; //! プレイヤー

	SoftEnemy * mcpHooder;         // ホーダー
	SplitLowerEnemy * mcpSplitter; //! スプリッター
	BaseDrone * mcpAunper;         //! アウンパー
	NormalEnemy * mcpTinpiller;    //! チンピラー  チンピラーは二体の敵が分裂するので配列に入れずに処理を行う
	Fordon * mcpFordon;            //! フォードン

	vector<BaseEnemy *>Enemies;    //! この配列に入れてUpdate等をforで回す
	int SplitterNum; // スプリッターの数
	int FordonNum;
};

