#pragma once
#include "BaseEnemy.h"
#include "SplitUpperEnemy.h"

//! Splitter（通称分裂する敵下）こっちがほぼ本体
class SplitLowerEnemy :
	public BaseEnemy
{
public:
	SplitLowerEnemy();					  //! コンストラクタ
	SplitLowerEnemy(float _x, float _y);  //! コンストラクタ
	~SplitLowerEnemy();					  //! デストラクタ

	void Update();						  //! 更新処理
	void Draw();						  //! 描画処理
	void LastUpdate() override;			  //! 最終更新処理
										  
	void SetInitVec(Vector2 _vec);		  //! 初期位置のセッター
	SplitUpperEnemy * GetUpperEnemy();	  //! 上にいるエネミーのゲッター
	Box * GetBoxCol() override;			  //! 当たり判定の情報
	bool GetDeath();                      //! やられたときに一度だけやられたことを返す関数
	TailReaction SetStingPower(float _Power, bool _Elect) override;		//! 尻尾が刺された時の挙動と強さ
	void SetFollow(bool _state);
private:
	void ForceProces();			//! 重力の処理
	void Walk();				//! 移動の処理
	SplitUpperEnemy * mcpSpltterUP; //! 上にいるやつ
	Box * mcpCombiCol;     //! 分割する前の当たり判定
	Box * mcpSplitedCol;   //! 分割後の当たり判定
	Vector2 mcCombiPos;    //! くっついてる状態での当たりの中心座標
	Vector2 mcSplitedColPos; //! 　分裂後の当たり判定の中心座標
	Vector2 mcCombColSize; //! くっついてる状態での当たりのサイズ
	void Destroy();  //! 倒れるときの関数
	bool Combi;      //! くっついてるか判断するフラグ
	float TotalMove; //! 移動距離
	float mfSpeed;   //! スピード
	bool Follow = true; //! プレイヤーに一度当たるまで追従する
	int Count;
	int MutekiCount;  //!分裂前にさされたらしばらく無敵(連続ヒットを避けるために)
	float FollowMove;
 
};

