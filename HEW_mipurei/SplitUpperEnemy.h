#pragma once
#include "BaseEnemy.h"
#include "Image.h"

//! Splitter（通称分裂する敵上）
class SplitUpperEnemy :
	public BaseEnemy
{
public:
	SplitUpperEnemy(Vector2 _vec, bool & _combi);
	~SplitUpperEnemy();

	void Update();
	void Draw();
	void SetMoveVec(Vector2 _move); //! 移動量のセッター	
	void FixVec(Vector2 _vec); //! 当たり判定後に座標を修正する
	Box * GetBoxCol() override; 
	TailReaction SetStingPower(float _Power, bool _Elect) override;
private:
	bool & Combi;
	void Destroy();  //! 倒れるときの関数
	int Count;
	Box * MyCol;     //! 当たり判定

	Vector2 SplitedColPos; //! 当たり判定の中心座座標(分裂後)
	Image mImage;
};

