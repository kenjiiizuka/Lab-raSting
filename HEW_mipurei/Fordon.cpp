#include "Fordon.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Angle.h"
#include "EffectManager.h"

//! コンストラクタ
Fordon::Fordon()
{
	mTag = Tag_Fordon;
	Top = true;
	FormaionNum = 0;
	Movevec = mcVec;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));
	mcpAnimsprite->SetAnimtionTable(6,2);
	MoveRad = DegreeToRadian(MoveDeg);
}

//! デストラクタ
Fordon::~Fordon()
{
	if (Top) {
		for (int i = 0; 9 < Member.size(); i++) {
			Member[i].reset();
		}
		Member.clear();
	}
}

//! 更新処理
void Fordon::Update()
{
	float distance = 0.0f;
	//! 先頭にいる奴の処理	
	Update_Top();
	for (int i = 0; i < FormaionNum; i++) {
		if (i == 0) {
			distance = Member[i]->Movevec.PosToPos(Movevec);
			//! ちょっと離れてから移動する
			if (distance > 0.138f) {
				float Angle = PositionRelationAngle(Member[i]->Movevec, Movevec);
				if (Atk) {
					Member[i]->mcMoveVector.x += cosf(Angle) * -AtkSpeed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -AtkSpeed;
				}
				else {
					Member[i]->mcMoveVector.x += cosf(Angle) * -Speed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -Speed;
				}
			}
			Member[i]->ForceProces();
		}
		else {
			distance = Member[i]->Movevec.PosToPos(Member[i - 1]->Movevec);
			//! ちょっと離れてから移動する
			if (distance > 0.138f) {
				float Angle = PositionRelationAngle(Member[i]->Movevec, Member[i - 1]->Movevec);
				if (Atk) {
					Member[i]->mcMoveVector.x += cosf(Angle) * -AtkSpeed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -AtkSpeed;
				}
				else {
					Member[i]->mcMoveVector.x += cosf(Angle) * -Speed;
					Member[i]->mcMoveVector.y += sinf(Angle) * -Speed;
				}
			}
			Member[i]->ForceProces();
		}
		if (!Member[i]->mAlive) {
			Member[i]->Destroy();
		}
	}
	if (!mAlive) {
		Destroy();
	}

}

void Fordon::Draw()
{	
	GameObject::Draw();
	if (Top) {
		mcpAnimsprite->SetColor(1.0f,0.5f,1.0f);
		for (int i = 0; i < FormaionNum; i++) {
			Member[i]->Draw();
		}
	}
}

void Fordon::CreateMenber(int _num)
{
	FormaionNum = _num;
	for (int i = 0; i < _num; i++) {
		std::unique_ptr<Fordon> member(new Fordon(false,FormaionNum));
		member->Top = false;
		member->SetVec(Vector2(mcVec.x + (0.14f * (i + 1)), mcVec.y));
		Member.emplace_back(std::move(member));
	}
}

int Fordon::GetNumMenber()
{
	return FormaionNum;
}

//! リアクションを返す関数
TailReaction Fordon::SetStingPower(float _Power, bool _Elect)
{
	TailReaction Reaction = TailReaction_None;

	if (_Elect) {
		Reaction = TailReaction_Through;
		SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.11f);
		mAlive = false;
		Stinged = true;	
		EffMgr->PlayEffect(HitEffect02, mcVec, Vector2(0.3f,0.3f));
	}
	else {
		if (_Power >= STING_STRONG) {
			Reaction = TailReaction_Through;
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.11f);
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.3f, 0.3f));
			mAlive = false;
			Stinged = true;
		}
		else if (_Power > STING_MIDIUME) {
			Reaction = TailReaction_Through;
			SoundMgr->PLAYSE(SE_Timpiller_Sasaru, 0.11f);
			EffMgr->PlayEffect(HitEffect01, mcVec, Vector2(0.3f, 0.3f));
			mAlive = false;
			Stinged = true;
		}
	}
	return Reaction;
}


Fordon * Fordon::GetMenber(int _index)
{
	return Member[_index].get();
}

void Fordon::SetInitVec(Vector2 _vec)
{
	SetVec(_vec);
	Movevec = mcVec;
	if (Top) {
		for (int i = 0; i < Member.size(); i++) {
			Member[i]->SetVec(Vector2(mcVec.x + (0.14f * (i + 1)), mcVec.y));
		}
	}
}

void Fordon::SetVec(Vector2 _vec)
{
	Vector2 dif = mcVec - _vec;
	mcVec = _vec;
	Movevec = _vec;
}

Vector2 Fordon::GetVec()
{
	if (mAlive) {
		return mcVec;
	}
	return Movevec;

}


//! 引数ありコンストラクタ
//! メンバーを生成するとき用のモノ
Fordon::Fordon(bool _state , int _formation)
{
	Top = false;
	Moved = false;
	FormaionNum = _formation;
	mcpAnimsprite->SetTexture(TexMgr->GetTextuer(Tex_Aunper));
	mcpAnimsprite->SetAnimtionTable(6, 2);
	MoveRad = DegreeToRadian(MoveDeg);
}


void Fordon::Update_Top()
{
	Move();
	ForceProces();
}

void Fordon::Update_Member(Vector2 _pos)
{
	
}


/* ----------
// 移動関数 */
void Fordon::Move()
{	
	Vector2 PlayerPos = mcPlayer->GetVec(); //!プレイヤーの座標の取得
	float Distance = fabs(PlayerPos.x - mcVec.x); //! プレイヤーとの距離を計算する
	//! 距離が一定いないなら、突撃までの時間を数える(7秒おきくらい)
	if (Distance < 1.6) {
		AtkIntervalCnt++;
		Atk = false;
		if (AtkIntervalCnt >= (4 * 60)) {
			Atk = true;
		}
	}

	//! 突撃開始(プレイヤーめがけて移動数)
	if(Atk){
		float AngleToPlayer = PositionRelationAngle(PlayerPos, mcVec); //! プレイヤーに対しての角度を求める
		mcMoveVector.x += cosf(AngleToPlayer) * AtkSpeed;
		mcMoveVector.y += sinf(AngleToPlayer) * AtkSpeed;
		TotalMove += fabs((cosf(AngleToPlayer) * AtkSpeed) + (sinf(AngleToPlayer) * AtkSpeed));
		//! なにかに当たったら突撃をやめる

		bool HitAny = false; //! 何かに当たったかはんだんするフラグ
		//! 先頭がなにかにあたったかを判断
		if (HitPlayer || mTouchGraund) {
			HitAny = true;
		}
		//! 先頭が当たっていなかったらメンバーがなにかに当たっていないかを判断する
		else {
			for (int i = 0; i < FormaionNum; i++) {
				if (Member[i]->HitPlayer || Member[i]->mTouchGraund) {
					HitAny = true;
					break;
				}
			}
		}

		//! 何かに当たっていないか判断する
		if (TotalMove >= 2.0f || HitAny) {
			TotalMove = 0;
			AtkIntervalCnt = 0;
			AtkRetrun = true;
		} 
	}

	//! 突撃あとに一定の高度になるまで戻る
	else if (AtkRetrun) {
		AtkIntervalCnt = 0; //! 戻ってる途中はカウントを進めない
		ReturnCnt++;
		if (Movevec.y <= 0.5f) {
			mcMoveVector.y += sinf(DegreeToRadian(90)) * Speed;
		}
		else {
			AtkRetrun = false;
			ReturnCnt = 0;
		}		

		if (ReturnCnt > 140) {
			AtkRetrun = false;
			ReturnCnt = 0;
		}
	}

	else {	
		//! 基本はぐるぐると円を描くように動く
		mcMoveVector.x = cosf(MoveRad) * -Speed;
		mcMoveVector.y = sinf(MoveRad) * -Speed;		
		MoveDeg += Add;
		Totaldeg += fabs(Add);
		if (Totaldeg >= 70) {
			if (MoveDeg >= 140) {
				MoveDeg = 30;
			}
			else {
				MoveDeg = 210;
			}
			Totaldeg = 0;
		}
		MoveRad = DegreeToRadian(MoveDeg);
	}
}

//! 移動量を足す処理
void Fordon::ForceProces()
{
	CurrentTime += (1.0f / 60.0f);		 //! 経過時間を増やす
	mcpBoxCol->SetPrevVec(mcVec);        //! 前フレームの座標として保存する
	
	Movevec += mcMoveVector;
	if (mAlive) {
		mcVec += mcMoveVector;               //! このキャラクターにかかっている力を足す
		Movevec = mcVec;
	}
	mcpShape->SetMoveVec(mcMoveVector);  //! 当たり判定に使うための情報をセット
	mcMoveVector.SetVector(0, 0);        //! このキャラクターにかかっている力を０にする
	mcpBoxCol->SetOnObj(false);          //! 上には乗っていないことにする　ここでfalseにした方がCollsionがすっきりするのでここでfalseにします
	//! 当たり情報にサイズセット
	mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
}


//! メンバーの移動関数
void Fordon::Move_Menber(Vector2 _destination)
{
	
}