#pragma once
#include "cMap.h"
#include "GimmickManager.h"
class Map1_3 :
	public Map
{
public:
	Map1_3(std::string _mapfile, std::string _itemfile, ID3D11ShaderResourceView* _maptiptex); //! コンストラクタ
	~Map1_3(); //! デストラクタ

	void Update() override;
	void Draw() override;
	bool CollisionUpdate(Character * _char) override;
	GimmickManager * GetGimmickManager();               //! ギミックマネジャーの取得
	void AddX(float _x);                                //! X座標のセッター
private:
	GimmickManager * mcpGimmickManager;
};

