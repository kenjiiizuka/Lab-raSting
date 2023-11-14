#pragma once
#include "cMap.h"
#include "GimmickManager.h"

class Map1_2 :
	public Map
{
public:
	Map1_2(std::string _mapfile, std::string _itemfile, ID3D11ShaderResourceView* _maptiptex); //! �R���X�g���N�^
	~Map1_2(); //! �f�X�g���N�^

	void Update() override;
	void Draw() override;
	bool CollisionUpdate(Character * _char) override;
	GimmickManager * GetGimmickManager();               //! �M�~�b�N�}�l�W���[�̎擾
	void AddX(float _x);                                //! X���W�̃Z�b�^�[
private:
	GimmickManager * mcpGimmickManager;
};

