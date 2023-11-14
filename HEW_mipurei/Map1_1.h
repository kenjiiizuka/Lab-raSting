#pragma once
#include "cMap.h"
#include "GimmickManager.h"
/* ----------- 
// 1-1マップ*/
class Map1_1 :
	public Map
{
public:
	Map1_1(std::string _mapfile, std::string _itemfile, ID3D11ShaderResourceView* _maptiptex, std::string _objfile); //! コンストラクタ
	~Map1_1(); //! デストラクタ

	void Update() override;
	void Draw() override;
	bool CollisionUpdate(Character * _char) override;
	GimmickManager * GetGimmickManager();               //! ギミックマネジャーの取得
	void AddX(float _x);                                //! X座標のセッター


private:
	GimmickManager * mcpGimmickManager;
};

