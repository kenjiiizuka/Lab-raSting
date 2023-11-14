#pragma once
#include "BaseEnemy.h"

//! Hooder（通称やわらかい敵）
class SoftEnemy :
	public BaseEnemy
{
public:
	SoftEnemy();		//! コンストラクタ
	SoftEnemy(float _x,float _y);	//! デストラクタ
	~SoftEnemy();		//! コンストラクタ
	void Update();		//! 更新処理
	void Draw();		//!	描画処理
	TailReaction Reaction;	//! 尻尾のリアクションの変数
	TailReaction SetStingPower(float _Power, bool _Elect)override;	//! 尻尾で刺された時の挙動と強さ
private:
	int mMidHitcount = 0;

	int AnimFrm;
	bool Stop;
};

