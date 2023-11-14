#pragma once
#include "BaseEnemy.h"
class NormalEnemy :
	public BaseEnemy
{
public:
	NormalEnemy();						//! コンストラクタ
	NormalEnemy(float _x, float _y);	//! コンストラクタ
	~NormalEnemy();						//! デストラクタ
	void Update();						//! 更新処理
	void Draw();						//! 描画処理
	TailReaction Reaction;				//! 尻尾のリアクション変数
	TailReaction SetStingPower(float _Power,bool _Elect)override;		//! 尻尾を刺された時の挙動と強さ
private:
	
};

