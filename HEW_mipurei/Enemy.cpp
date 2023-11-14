
#include "Enemy.h"
#include "TextureManager.h"
#include "DirectInput8.h"

//! コンストラクタ
EnemyProt::EnemyProt()
{
	//! ヒットストップ
	mcpHitStop = new HitStop(this);
	//! フラグの初期化
	LiveFlg = true;
	MoveDirFlg = true;
	GetAttack = false;

	//! 画像やアニメーション、ステータスの設定
	MoveDis = 0.001f;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! 当たり判定のサイズのセット
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! エネミー画像のセット
}

EnemyProt::EnemyProt(float _x, float _y)
{
	mcVec = Vector2(_x, _y);

	//! ヒットストップ
	mcpHitStop = new HitStop(this);
	//! フラグの初期化
	LiveFlg = true;
	MoveDirFlg = true;
	GetAttack = false;

	//! 画像やアニメーション、ステータスの設定
	MoveDis = 0.001f;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! 当たり判定のサイズのセット
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Timpiller));	//! エネミー画像のセット
}

//! デストラクタ
EnemyProt::~EnemyProt()
{
	//! デリート
	delete mcpHitStop;
}

//! 更新処理
void EnemyProt::Update()
{

	//! 敵が生存している間動く
	if (LiveFlg == true)
	{
		//! 一旦のエンターキーでヒットストップ　※条件はまた変える
		if (DI8->mKeyBoard->GetKeyTrigger(DIK_RETURN))
		{

			mcpHitStop->HitStopStart(50);		//! ヒットストップフラグをオンにする

		}

		//! ヒットストップフラグがオンの場合

		mcpHitStop->HitStoptime();	//! 引数で秒数調整


		//! ヒットストップが起こっていない間動く
		if (mcpHitStop->HitStopFlg == false)
		{
			Move();
		}

	}

	//! クラスの更新処理
	Character::Update();
}

//! 描画処理
void EnemyProt::Draw()
{
	//! クラスの描画処理
	GameObject::Draw();
	Character::Draw();
}

void EnemyProt::Move()
{
	
	//! 敵の移動方向が正の場合
	if (MoveDirFlg == true)
	{
		mcMoveVector.x += 0.005f;	//! 正方向への移動
		MoveDis += 0.005f;			//! 移動量の加算
		//! 移動量が一定数を超えたら 
		if (MoveDis >= 0.8f)
		{
			mcMoveVector.x -= 0.003f;	//! 負方向への移動
			MoveDis -= 0.003f;			//! 移動量の減算
			MoveDirFlg = false;			//! 方向変換
		}
	}

	//! 敵の移動方向が負の場合
	if (MoveDirFlg == false)
	{
		mcMoveVector.x -= 0.005f;	//! 負方向への移動
		MoveDis -= 0.005f;			//! 移動量の減算
		//! 移動量が一定数を超えたら
		if (MoveDis <= 0.0f)
		{
			mcMoveVector.x += 0.005f;	//! 負方向への移動
			MoveDis += 0.005f;			//! 移動量の加算
			MoveDirFlg = true;			//! 方向変換
		}
	}

}
