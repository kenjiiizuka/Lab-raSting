#pragma once
#include "cMap.h"
#include "GimmickManager.h"
class Map1_4 :
	public Map
{
public:
	Map1_4(std::string _mapfile, std::string _itemfile, ID3D11ShaderResourceView* _maptiptex); //! �R���X�g���N�^
	~Map1_4(); //! �f�X�g���N�^

	void Update() override;
	void Draw() override;
	bool CollisionUpdate(Character * _char) override;
	GimmickManager * GetGimmickManager();               //! �M�~�b�N�}�l�W���[�̎擾
	void AddX(float _x);       //! X���W�̃Z�b�^�[

private:
	GimmickManager * mcpGimmickManager;

};

