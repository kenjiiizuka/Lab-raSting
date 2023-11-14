#include "EnemyManager.h"
#include <fstream>
#include <sstream>
#include "EnemyID.h"
#include "WinMain.h"
#include "Collision.h"

//! コストラクタ
EnemyManager::EnemyManager(string _filename, Player & _player, Map & _map)
	: mcPlayer(_player), mcMap(_map)
{
	//! 敵の位置情報を持ったファイルを生成
	ifstream EnemyFile(_filename);
	if (!EnemyFile) {
		int hiraketenaiyo = 100;
	}

	string tmp;
	int num;
	//! 敵の数を読み込む
	//! ホーダーの読み込み
	getline(EnemyFile, tmp, ',');
	stringstream Hooder(tmp);
	Hooder >> num;
	mcpHooder = new SoftEnemy[num];
	//! エネミーの配列に追加
	for (int i = 0; i < num; i++) {
		Enemies.emplace_back(&mcpHooder[i]);
	}

	//! チンピラーZKの生成
	getline(EnemyFile, tmp, ',');
	stringstream Tinpiller(tmp);
	Tinpiller >> num;
	//! チンピラーの生成
	mcpTinpiller = new NormalEnemy[num];
	//! エネミーの配列に追加
	for (int i = 0; i < num; i++) {
		Enemies.emplace_back(&mcpTinpiller[i]);
	}

	//! スプリッターの生成
	//! 敵の数を読み込む
	getline(EnemyFile, tmp, ',');
	stringstream Splitter(tmp);
	Splitter >> SplitterNum;
	mcpSplitter = new SplitLowerEnemy[SplitterNum];

	//! ウンパーの生成
	getline(EnemyFile, tmp, ',');
	stringstream Unper(tmp);
	Unper >> num;

	//! アウンパーの生成
	getline(EnemyFile, tmp, ',');
	stringstream Aunper(tmp);
	Aunper >> num;
	mcpAunper = new BaseDrone[num];
	for (int i = 0; i < num; i++) {
		Enemies.emplace_back(&mcpAunper[i]);
	}

	//! フォードんの生成
	getline(EnemyFile, tmp, ',');
	stringstream frodon(tmp);
	frodon >> FordonNum;
	mcpFordon = new Fordon[FordonNum];
	for (int i = 0; i < FordonNum; i++) {
		Enemies.emplace_back(&mcpFordon[i]);
	}

	////! チンピラーSLの生成
	//getline(EnemyFile, tmp, ',');
	//stringstream TimpillerSL(tmp);
	//TimpillerSL >> num;

	////! 敵7の生成
	//getline(EnemyFile, tmp, ',');
	//stringstream Enemy7(tmp);
	//Enemy7 >> num;

	eEnemyID ID;               //! ID
	Vector2 pos;               //! 座標
	EnemyIndex Index = { 0 };  //! 添え字
	getline(EnemyFile, tmp);   //! ファイルの次の行に行く
	//getline(EnemyFile, tmp);
	//! スプリッターを足した数回す
	int EnemyNum = Enemies.size() + SplitterNum;
	for (int i = 0; i < EnemyNum; i++) {
		//! IDの取得
		getline(EnemyFile, tmp, ',');
		stringstream EnemyID(tmp);
		int work;
		EnemyID >> work;
		//! データチェック
		if (work == -1) {
			i--;
			continue;
		}
		ID = (eEnemyID)work;
		//! X,Y座標の読み込み
		getline(EnemyFile, tmp, ',');
		stringstream tmpX(tmp);
		tmpX >> pos.x;
		getline(EnemyFile, tmp, ',');
		stringstream tmpY(tmp);
		tmpY >> pos.y;
		pos.x -= DRAW_WIDTH * 0.5f - 0.1f;
		pos.y -= DRAW_HEIGHT * 0.5f - 0.1f;
		//! 敵の種類に応じて、座標をセットする
		stringstream HaveEnemyID;
		stringstream Menber;
		switch (ID) {
		case Enemy_Hooder:
			mcpHooder[Index.Hooder].SetVec(pos);
			mcpHooder[Index.Hooder].SetPlayer(&mcPlayer);
			Index.Hooder++;
			break;

		case Enemy_TinpillarZK:
			mcpTinpiller[Index.Tinpiller].SetVec(pos);
			mcpTinpiller[Index.Tinpiller].SetPlayer(&mcPlayer);
			Index.Tinpiller++;
			break;

		case Enemy_Splitter:
			mcpSplitter[Index.Splitter].SetInitVec(pos);
			mcpSplitter[Index.Splitter].SetPlayer(&mcPlayer);
			Index.Splitter++;
			break;

		case Enemy_Aunper:
			mcpAunper[Index.Aunper].SetVec(pos);
			mcpAunper[Index.Aunper].SetPlayer(&mcPlayer);
			//! ファイルからどの敵を持つのかを読み取る
			getline(EnemyFile, tmp, ',');
			HaveEnemyID << tmp;
			int work;
			eEnemyID HaveID;
			HaveEnemyID >> work;
			HaveID = (eEnemyID)work;

			if (HaveID == Enemy_Hooder) {
				mcpAunper[Index.Aunper].SetEnemy(&mcpHooder[Index.Hooder - 1]);
			}
			else if (HaveID == Enemy_TinpillarZK) {
				mcpAunper[Index.Aunper].SetEnemy(&mcpTinpiller[Index.Tinpiller - 1]);
			}
			else if (HaveID == Enemy_Splitter) {
				mcpAunper[Index.Aunper].SetEnemy(&mcpSplitter[Index.Splitter - 1]);
			}
			Index.Aunper++;
			break;

		case Enemy_Fordon:	
			mcpFordon[Index.Fodon].SetPlayer(&mcPlayer);
			getline(EnemyFile, tmp, ',');
			int Num;
			Menber << tmp;
			Menber >> Num;
			mcpFordon[Index.Fodon].CreateMenber(Num);
			mcpFordon[Index.Fodon].SetInitVec(pos);
			Index.Fodon++;
			break;
		}		
	}
	EnemyFile.close();
}

//! デストラクタ
EnemyManager::~EnemyManager()
{
	//! 各敵のデリート
	delete[] mcpTinpiller;
	delete[] mcpSplitter;
	delete[] mcpHooder;
	delete[] mcpAunper;
	delete[] mcpFordon;
	Enemies.clear(); //! 配列から要素を消去する
}

/* -----------
// 更新処理 */
void EnemyManager::Update()
{
	float CheackX = 0; //! ｘ座標をチャックして画面内に明らかに遠ければ処理をしない
	bool Charge = false;
	for (int i = 0; i < Enemies.size(); i++) {	
		Enemies[i]->Update();
		Charge = Enemies[i]->GetDeath();
		if (Charge) {
			mcPlayer.AddElect();
		}
	}
	//! スプリッターの更新処理
	for (int i = 0; i < SplitterNum; i++) {	
		mcpSplitter[i].Update();
		Charge = mcpSplitter[i].GetDeath();
		if (Charge) {
			mcPlayer.AddElect();
		}		
	}
}

/* -------------------------
// 当たり判定後の更新処理 */
void EnemyManager::LastUpdate()
{
	for (int i = 0; i < Enemies.size(); i++) {	
		Enemies[i]->LastUpdate();		
	}
	//! スプリッターの更新処理
	for (int i = 0; i < SplitterNum; i++) {	
		mcpSplitter[i].LastUpdate();			
	}
}

/* -----------------
// 当たり判定処理 */
void EnemyManager::CollisionUpdate()
{
	TailReaction Reaction; //! 攻撃があてられた時にプレイヤーに渡すリアクション
	float CheackX;


	//! プレイヤーの帯電の状態を取得する
	bool Elect = mcPlayer.GetCharge();

	//! プレイヤーとの当たり判定
	for (int i = 0; i < Enemies.size(); i++) {
		if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *Enemies[i]->GetBoxCol())) {
			//! プレイヤーへのダメージ処理
			//! プレイヤーが左にいる時
			if (mcPlayer.GetVec().x < Enemies[i]->GetVec().x) {
				mcPlayer.SetDamege(Left);
			}
			else {
				mcPlayer.SetDamege(Right);
			}
			Enemies[i]->SetHitPlayer(true);
		}
		else {
			Enemies[i]->SetHitPlayer(false);
		}

		//! Mapとの当たり判定処理
		if (Enemies[i]->GetTag() != ObjectTag::Tag_Drone) {
			if (mcMap.CollisionUpdate(Enemies[i])) {
				Enemies[i]->SetTouchGround(true);
			}
			else {
				Enemies[i]->SetTouchGround(false);
			}
		}
		//! プレイヤーの攻撃との当たり判定
		//! 帯電中
		if (Elect) {
			for (int h = 0; h < 2; h++) {
				if (Collision::Box_Circle_Hit(*Enemies[i]->GetBoxCol(), mcPlayer.GetSpearCol(h))) {
					Reaction = Enemies[i]->SetStingPower(mcPlayer.GetStingPower(), Elect);		//! false のところは帯電情報
					if (mcPlayer.GetVec().x < Enemies[i]->GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
			}
		}
		//! 通常
		else {
			if (Collision::Box_Circle_Hit(*Enemies[i]->GetBoxCol(), *mcPlayer.GetAttackCol())) {
				Reaction = Enemies[i]->SetStingPower(mcPlayer.GetStingPower(), false);		//! false のところは帯電情報
				if (mcPlayer.GetVec().x < Enemies[i]->GetVec().x) {
					mcPlayer.SetReaction(Reaction, Left);
				}
				else {
					mcPlayer.SetReaction(Reaction, Right);
				}
			}
		}
	}

	//! 敵同士の当たり判定
	for (int j = 0; j < Enemies.size(); j++) {
		for (int k = 0; k < Enemies.size(); k++) {
			if (j != k) { //! 自身同士で当たり判定を取らないようにしてある
				if (Enemies[j]->GetTag() != Tag_Drone && Enemies[k]->GetTag() != Tag_Drone) { //! ドローンは当たり判定をとらない
					Collision::Box_Box_Collision(*Enemies[j]->GetBoxCol(), *Enemies[k]->GetBoxCol());
				}
			}
		}
	}

	//! スプリッターの当たり判定
	for (int l = 0; l < SplitterNum; l++) {
		SplitUpperEnemy & Upper = *mcpSplitter[l].GetUpperEnemy();
		//! スプリッターとプレイヤーの当たり判定
		if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *mcpSplitter[l].GetBoxCol())) {
			if (mcPlayer.GetVec().x < mcpSplitter[l].GetVec().x) {
				mcPlayer.SetDamege(Left);
			}
			else {
				mcPlayer.SetDamege(Right);
			}
			//! 一度あたったらプレイヤーを追従しない
			mcpSplitter[l].SetFollow(false);
		}

		if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *Upper.GetBoxCol())) {
			if (mcPlayer.GetVec().x < Upper.GetVec().x) {
				mcPlayer.SetDamege(Left);
			}
			else {
				mcPlayer.SetDamege(Right);
			}
		}

		//! スプリッターとMapの当たり判定
		//! 下
		CheackX = mcpSplitter[l].GetVec().x;	
		if (mcMap.CollisionUpdate(&mcpSplitter[l])) {
			mcpSplitter[l].SetTouchGround(true);
		}
		else {
			mcpSplitter[l].SetTouchGround(false);
		}
		//! 上
		Box * Up = Upper.GetBoxCol();
		if (mcMap.CollisionUpdate(&Upper)) {
			Upper.SetTouchGround(true);
		}
		else {
			Upper.SetTouchGround(false);
		}
		//}
		//! プレイヤーとの攻撃の当たり判定
		if (Elect) {
			//! 下
			for (int z = 0; z < 2; z++) {
				if (Collision::Box_Circle_Hit(*mcpSplitter[l].GetBoxCol(), mcPlayer.GetSpearCol(z))) {
					Reaction = mcpSplitter[l].SetStingPower(mcPlayer.GetStingPower(), Elect);		//! false のところは帯電情報
					if (mcPlayer.GetVec().x < mcpSplitter[l].GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
				//! 上
				if (Collision::Box_Circle_Hit(*Upper.GetBoxCol(), mcPlayer.GetSpearCol(z))) {
					Reaction = Upper.SetStingPower(mcPlayer.GetStingPower(), Elect);		//! false のところは帯電情報
					if (mcPlayer.GetVec().x < Upper.GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
			}
		}
		else {
			//! 下（分裂前は全体）
			if (Collision::Box_Circle_Hit(*mcpSplitter[l].GetBoxCol(), *mcPlayer.GetAttackCol())) {
				Reaction = mcpSplitter[l].SetStingPower(mcPlayer.GetStingPower(), false);	//! false のところは帯電情報
				if (mcPlayer.GetVec().x < mcpSplitter[l].GetVec().x) {
					mcPlayer.SetReaction(Reaction, Left);
				}
				else {
					mcPlayer.SetReaction(Reaction, Right);
				}
			}
			//! 上
			if (Collision::Box_Circle_Hit(*Upper.GetBoxCol(), *mcPlayer.GetAttackCol())) {
				Reaction = Upper.SetStingPower(mcPlayer.GetStingPower(), false);		//! false のところは帯電情報
				if (mcPlayer.GetVec().x < Upper.GetVec().x) {
					mcPlayer.SetReaction(Reaction, Left);
				}
				else {
					mcPlayer.SetReaction(Reaction, Right);
				}
			}
		}
		//! スプリッターと他の敵との当たり判定
		for (int m = 0; m < Enemies.size(); m++) {
			Collision::Box_Box_Collision(*mcpSplitter[l].GetBoxCol(),*Enemies[m]->GetBoxCol());
			Collision::Box_Box_Collision(*Upper.GetBoxCol(), *Enemies[m]->GetBoxCol());
		}
	}

	//! フォードンのメンバーの当たり判定当たり判定
	for (int l = 0; l < FordonNum; l++) {
		int MenberNum = mcpFordon[l].GetNumMenber();
		for (int r = 0; r < MenberNum; r++) {
			//! メンバーの取得
			Fordon * Member = mcpFordon[l].GetMenber(r);

			//! マップとの当たり判定
			//! Mapとの当たり判定処理
			if (mcMap.CollisionUpdate(Member)) {
				Member->SetTouchGround(true);
			}
			else {
				Member->SetTouchGround(false);
			}

			//! プレイヤーとの当たり判定
			if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *Member->GetBoxCol())) {
				Member->SetTouchGround(true);
				//! プレイヤーへのダメージ処理
				//! プレイヤーが左にいる時
				if (mcPlayer.GetVec().x < Member->GetVec().x) {
					mcPlayer.SetDamege(Left);
				}
				else {
					mcPlayer.SetDamege(Right);
				}
				Member->SetHitPlayer(true);
			}
			else {
				Member->SetHitPlayer(false);
			}

			//! プレイヤーの攻撃との当たり判定
			if (Elect) {
				for (int g = 0; g < 2; g++) {
					if (Collision::Box_Circle_Hit(*Member->GetBoxCol(), mcPlayer.GetSpearCol(g))) {
						Reaction = Member->SetStingPower(mcPlayer.GetStingPower(), false);		//! false のところは帯電情報
						if (mcPlayer.GetVec().x < Member->GetVec().x) {
							mcPlayer.SetReaction(Reaction, Left);
						}
						else {
							mcPlayer.SetReaction(Reaction, Right);
						}
					}
				}
			}
			else {
				if (Collision::Box_Circle_Hit(*Member->GetBoxCol(), *mcPlayer.GetAttackCol())) {
					Reaction = Member->SetStingPower(mcPlayer.GetStingPower(), false);		//! false のところは帯電情報
					if (mcPlayer.GetVec().x < Member->GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
			}
		}
	}
}

/* -----------
// 描画処理 */
void EnemyManager::Draw()
{
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i]->Draw();
	}
	//! スプリッターの更新処理
	for (int i = 0; i < SplitterNum; i++) {
		mcpSplitter[i].Draw();
	}
}

void EnemyManager::AddX(float _x)
{
	Vector2 pos;
	for (int i = 0; i < Enemies.size(); i++) {
		pos = Enemies[i]->GetVec();
		Enemies[i]->SetVec(Vector2(pos.x +_x, pos.y));
		if (Enemies[i]->GetTag() == Tag_Fordon) {
			((Fordon*)Enemies[i])->SetInitVec(Vector2(pos.x + _x, pos.y));
		}
	}
	//! スプリッターの更新処理
	for (int i = 0; i < SplitterNum; i++) {
		pos = mcpSplitter[i].GetVec();
		mcpSplitter[i].SetVec(Vector2(pos.x + _x, pos.y));
	}
}
