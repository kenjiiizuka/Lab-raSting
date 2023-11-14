#include "Map1_3.h"
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
Map1_3::Map1_3(std::string _mapfile, std::string _itemfile, ID3D11ShaderResourceView * _maptiptex)
	: Map::Map(_mapfile, _itemfile, _maptiptex)
{
	ActivItem = true;
	mcpGimmickManager = new GimmickManager("assets/Stage1/3/GimmickData.csv");
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
}

//! �f�X�g���N�^
Map1_3::~Map1_3()
{
	delete mcpGimmickManager;
}

//! �X�V����
void Map1_3::Update()
{
	Map::Update();
	mcpGimmickManager->Update();
}

//! �`�揈��
void Map1_3::Draw()
{
	Map::Draw();
	mcpGimmickManager->Draw();
}

//! �����蔻�菈��
bool Map1_3::CollisionUpdate(Character * _char)
{
	//! �M�~�b�N�Ƃ̓����蔻����Ƃ�	
	mcpGimmickManager->CollisionUpdate(_char);
	//! Map�Ƃ̓����蔻����Ƃ�
	return Map::Collision(_char);
}


GimmickManager * Map1_3::GetGimmickManager()
{
	return mcpGimmickManager;
}

void Map1_3::AddX(float _x)
{
	mcPos.x += _x;
	mcpGimmickManager->MoveX(_x);
}
