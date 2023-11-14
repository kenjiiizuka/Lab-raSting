#include "BaseEnemy.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DirectInput8.h"

//! 基本となる敵
BaseEnemy::BaseEnemy()
{
	//! ヒットストップ
	mcpHitStop = new HitStop(this);
	//! フラグの初期化
	HitPlayer = false;
	ChaseFlg = false;
	Status.LiveFlg = true;
	Status.MoveDirFlg = false;
	Status.CarryMeFlg = false;
	Elect = false;
	Stinged = Deathed = Death = false;
	
	Reaction = TailReaction_None;
	//! 画像やアニメーション、ステータスの設定
	Count = 0;
	Speed = 0;
	Status.MoveDis = Speed;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! 当たり判定のサイズのセット
}

BaseEnemy::BaseEnemy(float _x, float _y)
{
	mcVec = Vector2(_x, _y);

	//! ヒットストップ
	mcpHitStop = new HitStop(this);
	//! フラグの初期化
	ChaseFlg = false;
	Status.LiveFlg = true;
	Status.MoveDirFlg = false;
	Status.CarryMeFlg = false;
	Stinged = Deathed = Death = false;
	Elect = false;
	Reaction = TailReaction_None;

	//! 画像やアニメーション、ステータスの設定
	Count = 0;
	Speed = 0;
	Status.MoveDis = Speed;
	SetSize(0.4f, 0.4f);
	ColSize = Vector2(0.2f, 0.2f); //! 当たり判定のサイズのセット
}

BaseEnemy::~BaseEnemy()
{
	//! デリート
	delete mcpHitStop;
}

void BaseEnemy::Update()
{
	//! 敵が生存している間動く
	if (mAlive)
	{
		//! ドローンとプレイヤーとの距離が一定になったら
		float px = mcPlayer->GetVec().x;
		if (fabs(mcVec.x - px) <= 1.8f)
		{
			//! 追跡フラグをtrueにする
			ChaseFlg = true;
		}

		//! 持たれている間は動かない
		if (!Status.CarryMeFlg)
		{

			if (ChaseFlg)
			{
				Move();
			}
		}
		else
		{
			SetTouchGround(true);
		}


	}
	//! クラスの更新処理
	Character::Update();

}

void BaseEnemy::Draw()
{
	//! クラスの描画処理
	GameObject::Draw();
	//Character::Draw();
}

float BaseEnemy::SetMove(float _Speed)
{
	Speed = _Speed;

	return Speed;
}

void BaseEnemy::SetMoveVec(Vector2 _MoveVec)
{
	mcMoveVector = _MoveVec;
}

void BaseEnemy::SetPlayer(Player * _Player)
{
	mcPlayer = _Player;
}

void BaseEnemy::SetCarryFlg(bool _Carryme)
{
	Status.CarryMeFlg = _Carryme;
}


void BaseEnemy::Move()
{
	//! 敵の移動方向が正の場合
	if (Status.MoveDirFlg)
	{
		mcMoveVector.x += Speed;	//! 正方向への移動
		Status.MoveDis += Speed;			//! 移動量の加算
		//! 移動量が一定数を超えたら 
		if (Status.MoveDis >= 0.0f)
		{
			mcMoveVector.x -= Speed;	//! 負方向への移動
			Status.MoveDis -= Speed;			//! 移動量の減算
			Status.MoveDirFlg = false;			//! 方向変換
		}
	}

	//! 敵の移動方向が負の場合
	if (!Status.MoveDirFlg)
	{
		mcMoveVector.x -= Speed;	//! 負方向への移動
		Status.MoveDis -= Speed;			//! 移動量の減算
		//! 移動量が一定数を超えたら
		if (Status.MoveDis <= -0.85f)
		{
			mcMoveVector.x += Speed;	//! 負方向への移動
			Status.MoveDis += Speed;			//! 移動量の加算
			Status.MoveDirFlg = true;			//! 方向変換
		}
	}
}

void BaseEnemy::Destroy()
{
	SetHitActiv(false);		//! 当たり判定を消す
	if (Count <= 50)
	{
		if (!Deathed) {
			Death = true;
		}
		if (Elect)
		{
			if (Count == 10)
			{
				SoundMgr->PlaySE(SE_TaidenAtk, 0.15f);
			}
		}
		//! 点滅させる
		if ((Count % 20) <= 10) {
			SetDrawActiv(false);

		}
		else {
			mcpAnimsprite->SetColor(1.0f, 0.0f, 0.0f);
			SetDrawActiv(true);
		}
		Count++;
	}
	else
	{
		SetDrawActiv(false);	//! 画像を消す
	}
}


bool BaseEnemy::GetDeath()
{
	if (Death && !Deathed && Stinged) {
		Deathed = true;
		return true;
	}
	Stinged = false;
	return false;
}

void BaseEnemy::SetHitPlayer(bool _hit)
{
	HitPlayer = _hit;
}

TailReaction BaseEnemy::SetStingPower(float _Power, bool _Elect)
{
	if (_Elect)
	{
		Elect = _Elect;
	}
	

	if (_Power >= STING_STRONG || _Elect)
	{
		//! 強い
		Reaction = TailReaction_Sting;
	}
	else if (_Power >= STING_MIDIUME)
	{
		//! 普通
		Reaction = TailReaction_Stop;
	}
	else
	{
		//! 弱い
		Reaction = TailReaction_Stop;
	}

	return Reaction;
}

