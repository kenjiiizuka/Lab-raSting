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

//! �R���X�g���N�^
//! �}�b�v�`�b�v��Tag��ݒ肷��
Map1_5::Map1_5(std::string _mapfile, std::string  _itemfile, ID3D11ShaderResourceView * _maptiptex)
	: Map::Map(_mapfile, _itemfile, _maptiptex)
{
	ActivItem = true;
	mcpGimmickManager = new GimmickManager("assets/Stage1/5/GimmickData.csv");
	SetDrawBg(true);

	//! �}�b�v�`�b�v�Ƀ^�O���Z�b�g����
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

//!�@�f�X�g���N�^
Map1_5::~Map1_5()
{
	delete mcpGimmickManager;
}

//! �X�V����
void Map1_5::Update()
{
	Map::Update();
	mcpGimmickManager->Update();
}

//! �`�揈��
void Map1_5::Draw()
{
	Map::Draw();
	mcpGimmickManager->Draw();
}

//! �����蔻�菈��
bool Map1_5::CollisionUpdate(Character * _char)
{
	//! �M�~�b�N�Ƃ̓����蔻����Ƃ�	
	mcpGimmickManager->CollisionUpdate(_char);
	//! Map�Ƃ̓����蔻����Ƃ�
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
