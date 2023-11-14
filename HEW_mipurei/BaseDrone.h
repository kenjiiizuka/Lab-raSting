#pragma once
#include "BaseEnemy.h"

//! ドローンの基本となるクラス
class BaseDrone :
	public BaseEnemy
{
public:
	BaseDrone();	//! コンストラクタ
	BaseDrone(float _x, float _y);		//! コンストラクタ２
	~BaseDrone();						//! デストラクタ
	void Update();						//! 更新処理
	void Draw();						//! 描画処理
	void SetEnemy(BaseEnemy* _EnemyNo);	//! 敵のセッター
	void EnemyBase();		//! 持たれている敵の行動（今はドローンに追従するだけ）
	void Fly();				//! 移動と実際の行動の処理
	bool GetCarryFlg();     //! キャリーフラグのゲッター
	TailReaction Reaction;	//! 刺されたしっぽの反応
	TailReaction SetStingPower(float _Power, bool _Elect)override;	//! 刺された強さのセッター
	//! フラグ関係
	bool CarryFlg;	//! 敵を持ち運んでいるかどうかの判断
private:
	float TotalMove; //! 移動距離
	float mfSpeed;   //! スピード
	BaseEnemy * mcpEnemy;	//! 持たれている敵
};