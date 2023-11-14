#pragma once
#include "cMap.h"
#include "GimmickManager.h"
/* ----------- 
// 1-1�}�b�v*/
class Map1_1 :
	public Map
{
public:
	Map1_1(std::string _mapfile, std::string _itemfile, ID3D11ShaderResourceView* _maptiptex, std::string _objfile); //! �R���X�g���N�^
	~Map1_1(); //! �f�X�g���N�^

	void Update() override;
	void Draw() override;
	bool CollisionUpdate(Character * _char) override;
	GimmickManager * GetGimmickManager();               //! �M�~�b�N�}�l�W���[�̎擾
	void AddX(float _x);                                //! X���W�̃Z�b�^�[


private:
	GimmickManager * mcpGimmickManager;
};

