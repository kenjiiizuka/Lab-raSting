#pragma once
#include "Character.h"
#include "PlugTail.h"
#include "HitStop.h"

class EnemyProt :
	public Character
{
public:
	EnemyProt();   //! コンストラクタ　敵のステータスをファイルから読み込んで調整できるようにする
	EnemyProt(float _x, float _y); //! コンストラクタ　座標設定可能
	~EnemyProt();	//! デストラクタ
	void Update() override;
	void Draw() override;
	void Move();
private:
	HitStop * mcpHitStop;
	float MoveDis;
	bool LiveFlg;
	bool MoveDirFlg;
	bool GetAttack;
};