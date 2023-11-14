#include "GimmickManager.h"
#include "GimmickID.h"
#include "WinMain.h"
#include "Collision.h"
#include <fstream>
#include <sstream>
#include "Player.h"

using namespace std;

//! コンストラクタ
GimmickManager::GimmickManager(std::string _filename)
{
	AllDyanmoIndex = 0;
	//!ファイルを開く
	ifstream file(_filename);
	if (!file) {
		int okasiiyo = 12345;
	}

	string tmp; //! ファイルから読みとり代入する変数
	int num;    //! そのギミックの数

	//! ①
	//! 中間の生成
	getline(file, tmp, ',');
	stringstream CheackPointNum(tmp);
	CheackPointNum >> Num.CheackPoint;
	mcpCheackPoint = new CheackPoint[Num.CheackPoint];


	//! ②
	//! 発電機の数を読み取る
	getline(file,tmp,','); 
	stringstream DynamoNum(tmp);
	DynamoNum >> Num.Dynamo;
	mcpDynamo = new Dynamo[Num.Dynamo];
	//! 配列にセット
	for (int i = 0; i < Num.Dynamo; i++) {
		Dynamos.emplace_back(&mcpDynamo[i]);
	}

	//! ③
	//! 壊れる発電機の数を読み取る
	getline(file, tmp, ',');
	stringstream WeakDynamoNum(tmp);
	WeakDynamoNum >> Num.WeakDyanamo;
	mcpWeakDynamo = new WeakDynamo[Num.WeakDyanamo];
	//! 配列にセット
	for (int i = 0; i < Num.WeakDyanamo; i++) {
		Dynamos.emplace_back(&mcpWeakDynamo[i]);
	}

	//! ④
	//! 大きなドアの生成
	getline(file, tmp, ',');
	stringstream BigDoorNum(tmp);
	BigDoorNum >> num;
	mcpBigDoor = new BigDoor[num];
	//! 配列に追加
	for (int i = 0; i < num; i++) {
		Gimmicks.emplace_back(&mcpBigDoor[i]);
	}
	
	//! ⑤
	//! ガラスを生成
	getline(file, tmp, ',');
	stringstream GlassNum(tmp);
	GlassNum >> Num.Glass;
	mcpGlass = new BreakObj[Num.Glass];
	
	//! ⑥
	//! プレス機の生成
	getline(file, tmp ,',');
	stringstream PressNum(tmp);
	PressNum >> Num.Press;
	mcpPress = new PressMachine[Num.Press];
	for (int i = 0; i < Num.Press; i++) {
		Gimmicks.emplace_back(&mcpPress[i]);
	}

	//! ゴールの生成
	mcpGoal = new Goal;

	getline(file, tmp); //! 改行
	getline(file, tmp); //! 改行
	int AllGimmick = Gimmicks.size() + Num.Dynamo + Num.CheackPoint + Num.Glass + Num.WeakDyanamo + 1; //! 発電機を含めた全てのギミックの数
	Vector2 pos;
	int work;
	GimmickID ID;
	GimmickIndex Index = { 0 };
	Dynamo * SetDynamo = nullptr;
	for (int i = 0; i < AllGimmick; i++) {
		//! 発電機をセットする用の変数
		
		getline(file, tmp, ',');
		stringstream Data(tmp);
		Data >> work;
		//! データチェック
		if (work == -1) {
			i--;
			continue;
		}
		ID = (GimmickID)work;    //! IDのセット
		getline(file, tmp, ',');
		stringstream x(tmp);
		x >> pos.x;              //! X座標のセット
		getline(file, tmp, ',');
		stringstream y(tmp);
		y >> pos.y;              //! Y座標のセット

		//! 座標の修正
		pos.x -= DRAW_WIDTH * 0.5f - 0.1f;
		pos.y -= DRAW_HEIGHT * 0.5f - 0.1f;
		switch (ID)
		{
		case GimmickID::GI_Dynamo:
			mcpDynamo[Index.Dynamo].SetVec(pos);
			SetDynamo = &mcpDynamo[Index.Dynamo];
			Index.Dynamo++;
			break;

		case GimmickID::GI_BigDoor:
			mcpBigDoor[Index.BigDoor].SetVec(pos);
			mcpBigDoor[Index.BigDoor].SetDynamo(SetDynamo); //! 発電機のセット
			Index.BigDoor++;
			break;

		case GimmickID::GI_CheakPoint:
			mcpCheackPoint[Index.CheackPoint].SetVec(pos);
			CheackPos[Index.CheackPoint] = pos;
			Index.CheackPoint++;
			break;

		case GimmickID::GI_Glass:
			mcpGlass[Index.Glass].SetVec(pos);
			Index.Glass++;
			break;

		case GimmickID::GI_WeakDyanamo:
			mcpWeakDynamo[Index.WeakDyanamo].SetVec(pos);
			SetDynamo = &mcpWeakDynamo[Index.WeakDyanamo];
			Index.WeakDyanamo++;
			break;

		case GimmickID::GI_Goal:
			mcpGoal->SetVec(pos);

			break;
		case GimmickID::GI_Press:
			mcpPress[Index.Press].SetVec(pos);
			mcpPress[Index.Press].SetDynamo(SetDynamo);
			Index.Press++;
			break;
		default:
			break;
		}
	}
}

//! デストラクタ
GimmickManager::~GimmickManager()
{
	delete[] mcpDynamo;
	delete[] mcpBigDoor;
	delete[] mcpCheackPoint;
	delete[] mcpWeakDynamo;
	delete[] mcpPress;
	delete[] mcpGlass;

	delete mcpGoal;

	Dynamos.clear();
	Gimmicks.clear();
}


//! 更新処理
void GimmickManager::Update()
{
	//! 発電機の更新処理	
	for (int i = 0; i < Dynamos.size(); i++) {
		Dynamos[i]->Update();
	}

	//! ギミックの更新処理
	for (int i = 0; i < Gimmicks.size(); i++) {
		Gimmicks[i]->Update();
	}

	//! 中間ポイントの更新
	for (int i = 0; i < Num.CheackPoint; i++) {
		mcpCheackPoint[i].Update();
	}

	//! ガラスの更新
	for (int i = 0; i < Num.Glass; i++) {
		mcpGlass[i].Update();
	}

	//! ゴールの更新処理
	mcpGoal->Update();
}

//! 当たり判定処理
void GimmickManager::CollisionUpdate(Character * _char)
{
	TailReaction Reaction;

	//! 帯電してるかを確認
	bool Elect = false;
	if (_char->GetTag() == Tag_Player) {
		Elect = ((Player *)_char)->GetCharge();
	}

	//! 発電機の当たり判定
	for (int i = 0; i < Dynamos.size(); i++) {
		//Collision::Box_Box_Collision(*_char->GetBoxCol(), *Dynamos[i]->GetBoxCol());
		//! 尻尾との当たり判定
		if (_char->GetTag() == Tag_Player) {
			Player * player = ((Player *)_char);
			//! 帯電していたら
			if (Elect) {
				for (int spearcol = 0; spearcol < 2; spearcol++) {	
					if (BCH(*Dynamos[i]->GetBoxCol(), player->GetSpearCol(spearcol))) {
						//! 弱い発電機
						if (Dynamos[i]->GetTag() == Tag_WeakDynamo) {
							Reaction = Dynamos[i]->ReturnReaction(player->GetStingPower() ,Elect); // 刺す威力を渡す
							player->GetTail()->SetReaction(Reaction, Direction_None);
							if (Reaction == TailReaction_StingDeep || Reaction == TailReaction_Sting) {
								player->GetTail()->SetStingObj(Dynamos[i]);
							}
							if (Reaction == TailReaction_StingStop) {
								Dynamos[i]->SetChrage(true);
							}
						}
						else {	
							player->GetTail()->SetReaction(TailReaction_StingStop, Direction_None);
							Dynamos[i]->SetChrage(true);
						}
					}	
				}
			}
			else {
				if (Collision::Box_Circle_Hit(*Dynamos[i]->GetBoxCol(), *player->GetAttackCol())) {
					Reaction = Dynamos[i]->ReturnReaction(player->GetStingPower(),Elect); // 刺す威力を渡す
					player->GetTail()->SetReaction(Reaction, Direction_None);
					//! 刺さってるオブジェクトのセット
					if (Reaction == TailReaction_StingDeep || Reaction == TailReaction_Sting) {
						player->GetTail()->SetStingObj(Dynamos[i]);
					}
				}
			}
		}
	}

	//! ギミックの当たり判定
	for (int j = 0; j < Gimmicks.size(); j++) {
		//! プレス機は当たりの判定だけ取る
		if (Gimmicks[j]->GetTag() == Tag_Press) {
			if (_char->GetTag() == Tag_Player) {
				bool Hit = BBH(*Gimmicks[j]->GetBoxCol(), *_char->GetBoxCol());
				if (Hit) {
					if (Gimmicks[j]->GetVec().x >= _char->GetVec().x) {
						((Player *)_char)->SetDamege(Left);
					}
					else {
						((Player *)_char)->SetDamege(Right);
					}
				}
			}
		}
		//! プレス機とは衝突判定をとらない
		else {
			Collision::Box_Box_Collision(*_char->GetBoxCol(), *Gimmicks[j]->GetBoxCol());
		}

		//! 尻尾との当たり判定
		if (_char->GetTag() == Tag_Player) {
			if (Collision::Box_Circle_Hit(*Gimmicks[j]->GetBoxCol(), *((Player *)_char)->GetAttackCol())) {
				((Player *)_char)->GetTail()->SetReaction(TailReaction_Stop, Direction_None);
			}
		}
	}

	//! 中間ポイントの当たり判定プレイヤーならとる
	if (_char->GetTag() == Tag_Player) {
		for (int k = 0; k < Num.CheackPoint; k++) {
			if (Collision::Box_Box_Hit(*_char->GetBoxCol(), *mcpCheackPoint[k].GetBox())) {
				mcpCheackPoint[k].HitCheckPoint();
			}
		}
	}

	//! ガラスとの当たり判定
	for (int l = 0; l < Num.Glass; l++) {
		Collision::Box_Box_Collision(*mcpGlass[l].GetBoxCol(), *_char->GetBoxCol());
		//! 尻尾との当たり判定
		if (_char->GetTag() == Tag_Player) {
			if (Collision::Box_Circle_Hit(*mcpGlass[l].GetBoxCol(), *((Player *)_char)->GetAttackCol())) {
				Reaction = mcpGlass[l].ReturnReaction(((Player *)_char)->GetStingPower());
				((Player *)_char)->GetTail()->SetReaction(Reaction, Direction_None);
			}
		}
	}

	//! プレイヤーとの当たり判定
	if (_char->GetTag() == Tag_Player) {
		BBC(*mcpGoal->GetBoxCol(), *_char->GetBoxCol());
		if (Collision::Box_Circle_Hit(*mcpGoal->GetBoxCol(), *((Player *)_char)->GetAttackCol())) {
			Reaction = mcpGoal->ReturnReaction(((Player *)_char)->GetStingPower());
			//! はじかれるリアクション
			if (mcpGoal->GetVec().x < _char->GetVec().x) { //! 右
				((Player *)_char)->GetTail()->SetReaction(Reaction, Right);
			}
			else {                                         //! 左
				((Player *)_char)->GetTail()->SetReaction(Reaction, Left);
			}
		}
	}
}

//! 描画処理
void GimmickManager::Draw()
{	
	//! 発電機の更新処理	
	for (int i = 0; i < Dynamos.size(); i++) {
		Dynamos[i]->Draw();
	}

	//! ギミックの更新処理
	for (int i = 0; i < Gimmicks.size(); i++) {
		Gimmicks[i]->Draw();
	}

	//! 中間ポイントの更新
	for (int i = 0; i < Num.CheackPoint; i++) {
		mcpCheackPoint[i].Draw();
	}

	//! ガラスの描画処理
	for (int i = 0; i < Num.Glass; i++) {
		mcpGlass[i].Draw();
	}

	mcpGoal->Draw();	
}

void GimmickManager::MoveX(float _x)
{
	Vector2 pos;
	if (mcpCheackPoint != nullptr) {
		pos = mcpCheackPoint[0].GetVec();
		mcpCheackPoint[0].SetVec(Vector2(pos.x + _x, pos.y));
	}
	if (Num.CheackPoint >= 2) {
		pos = mcpCheackPoint[1].GetVec();
		mcpCheackPoint[1].SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! 発電機の座標をずらす
	for (int i = 0; i < Dynamos.size(); i++) {
		pos = Dynamos[i]->GetVec();
		Dynamos[i]->SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! ギミックの座標をずらす
	for (int j = 0; j < Gimmicks.size(); j++) {
		pos = Gimmicks[j]->GetVec();
		Gimmicks[j]->SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! ガラスの位置をずらす
	for (int k = 0; k < Num.Glass; k++) {
		pos = mcpGlass->GetVec();
		mcpGlass[k].SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! ゴールの位置をずらす
	pos = mcpGoal->GetVec();
	mcpGoal->SetVec(Vector2(pos.x + _x, pos.y));
}

//! 中間に触れたかどうかを返す
bool GimmickManager::GetCheackPointState()
{
	return	mcpCheackPoint[0].GetCheck();
}

//! ボス前の中間に触れたかどうかを返す
bool GimmickManager::GetCheackPointBossState()
{
	//! チェックポイントの数が2以上のときのみ
	if (Num.CheackPoint >= 2) {
		return mcpCheackPoint[1].GetCheck();
	}
	return false;
}

//! 中間の座標のゲッター
Vector2 GimmickManager::GetCheackPointPos()
{
	return mcpCheackPoint[0].GetVec();
}

//! ボス前中間の座標のゲッター
Vector2 GimmickManager::GetCheackPointBossPos()
{
	if (Num.CheackPoint >= 2) {
		return mcpCheackPoint[1].GetVec();
	}
	return Vector2(0, 0);
}

Goal * GimmickManager::GetGoalIns()
{
	return mcpGoal;
}

bool GimmickManager::GetGoal()
{
	return mcpGoal->GetGoal();
}
