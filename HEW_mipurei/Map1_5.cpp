#include "Map1_5.h"
#include "eMapTag.h"
#include "Collision.h"
#include <fstream>
#include <string>
#include <sstream>
#include "GimmickID.h"
#include "ObjTag.h"
#include "Player.h"
#include "WinMain.h"
using namespace std;

//! コンストラクタ
//! マップチップにTagを設定する
Map1_5::Map1_5(std::string _mapfile, std::string  _itemfile, ID3D11ShaderResourceView * _maptiptex)
	: Map::Map(_mapfile, _itemfile, _maptiptex)
{
	ActivItem = true;
	mcpGimmickManager = new GimmickManager("assets/Stage1/5/GimmickData.csv");
	SetDrawBg(true);

	//! マップチップにタグをセットする
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			if (mspMaptip[i][j].Number == 24 || mspMaptip[i][j].Number == 25 || mspMaptip[i][j].Number == 26
				|| mspMaptip[i][j].Number == 19 || mspMaptip[i][j].Number == 30
				|| mspMaptip[i][j].Number == 31 || mspMaptip[i][j].Number == 32
				|| mspMaptip[i][j].Number == 36 || mspMaptip[i][j].Number == 37
				|| mspMaptip[i][j].Number == 38 || mspMaptip[i][j].Number == 39) {
				mspMaptip[i][j].Tag = Tag_Ground;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		BG01[i]->GetSprite()->SetColor(1.0, 0.42f, 0.2f);
		BG02[i]->GetSprite()->SetColor(1.0, 0.42f, 0.2f);
		BG03[i]->GetSprite()->SetColor(1.0, 0.42f, 0.2f);
	}
}

//!　デストラクタ
Map1_5::~Map1_5()
{
	delete mcpGimmickManager;
}

//! 更新処理
void Map1_5::Update()
{
	Map::Update();
	mcpGimmickManager->Update();
}

//! 描画処理
void Map1_5::Draw()
{
	Map::Draw();
	mcpGimmickManager->Draw();
}

//! 当たり判定処理
bool Map1_5::CollisionUpdate(Character * _char)
{
	//! ギミックとの当たり判定をとる	
	mcpGimmickManager->CollisionUpdate(_char);
	//! Mapとの当たり判定をとる
	return Map::Collision(_char);
}

GimmickManager * Map1_5::GetGimmickManager()
{
	return mcpGimmickManager;
}

void Map1_5::AddX(float _x)
{
	mcPos.x += _x;
	mcpGimmickManager->MoveX(_x);
}
