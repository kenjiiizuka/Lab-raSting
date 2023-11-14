#pragma once
#include <string>
#include "Character.h"
#include "Dynamo.h"
#include "BigDoor.h"
#include "CheckPoint.h"
#include "BreakObj.h"
#include "WeakDynamo.h"
#include "Goal.h"
#include "PressMachine.h"
#include <vector>
/* ------------------------------- 
// ギミックを管理するクラスです */



class GimmickManager
{
public:
	GimmickManager(std::string _filename);  //! コンストラクタ
	~GimmickManager();                      //! デストラクタ

	void Update();
	void CollisionUpdate(Character * _char);
	void Draw();
	void MoveX(float _x);      //! 全てのギミックのXの位置をずらす
	//! チェックポイント１は普通の中間　２がボス前の中間の予定
	bool GetCheackPointState();               //! 普通の中間ポイント
	bool GetCheackPointBossState();           //! ボス前
	Vector2 GetCheackPointPos();              //! 中間の座標のゲッター
	Vector2 GetCheackPointBossPos();          //! 中間の座標のゲッター
	Goal * GetGoalIns();                      //! ゴール自体の取得　ボスがでる1-3で使う
	bool GetGoal();                           //! ゴールしたかをかえす

private:

	struct GimmickIndex
	{
		int Dynamo;
		int WeakDyanamo;
		int BigDoor;
		int Glass;
		int CheackPoint;
		int Press;
	};

	Vector2 CheackPos[2];            //! チェックポイントの座標　１つ目は普通の中間　二つ目はボス前中間
	GimmickIndex Num;                //! 各ギミックの数
	Dynamo * mcpDynamo;              //! 発電機
	WeakDynamo * mcpWeakDynamo;      //! 壊れる発電機
	BreakObj * mcpGlass;             //! ガラス
	BigDoor * mcpBigDoor;            //! 大きなドア
	CheackPoint * mcpCheackPoint;    //! 中間ぽいんと
	PressMachine * mcpPress;            //! プレス機
	Goal * mcpGoal;                  //! ゴール
	std::vector<Gimmick *> Gimmicks; //! ギミックの配列
	std::vector<Dynamo *> Dynamos;   //! 発電機の配列
	int AllDyanmoIndex;              //! 発電機全ての数
};

