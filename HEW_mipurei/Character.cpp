#include "Character.h"
#include "Time.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "Camerah.h"
//! コンストラクタ
Character::Character()
{
	ColSize = Vector2(msSize.x,msSize.y);
	mcpBoxCol = new Box(mcVec, ColSize.x, ColSize.y); //! 矩形の当たり判定の生成
	mcpShape = mcpBoxCol;                              
	mcMoveVector = 0;
	mTouchGraund = true; //! 最初は地面についている状態
	mcpImage = new Image;
	CurrentTime = PrevTime = GravityTime = 0;
}


//! デストラクタ
Character::~Character()
{
	delete mcpBoxCol;
	delete mcpImage;
}


//! キャラクター更新処理 
//! ※ 継承先の更新処理では一番最後に記述してください。
void Character::Update()
{
	/* ※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
	※  [ 処理の流れ・・・]                                                ※
	※ 継承先のクラスで移動など、移動するベクトル量関する処理をしたあとに  ※
	※ Character::Update()を呼ぶ、Character::Update()で移動ベクトルに重力  ※
	※ ベクトルを加え、このフレームでの最終的な移動ベクトル量を計算する、  ※
	※ 次に位置ベクトルに移動ベクトルを加算する。最後に次のフレームで計算  ※
	※ するために、移動ベクトルを０にする。							       ※
	※ ※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※*/

	if (mAlive) {
		bool Vibe = CAMERA->GetVibration();
		bool OnObj = mcpBoxCol->GetOnObj(); //! オブジェクトの上にのっているかを取得
		if (OnObj == true) {
			mTouchGraund = true;
		}
		//! 画面振動しているときは重力をかけない
		if (mTouchGraund == false && Vibe == false) {
			double ElapsedTime = CurrentTime - GravityTime;
			float Gravtiy = -ga * pow(ElapsedTime, 2) / 2.0f; //! 重力による下方向の力の計算	ミリ秒での計算なので1000で割る
			//! 重力の影響の最大値を超えないようにする
			if (Gravtiy >= 0.02f) {
				Gravtiy = 0.02f;
			}
			mcMoveVector.y += Gravtiy; //! 重力の力を加算
		}
		else {
			GravityTime = CurrentTime; //! 秒単位の今の時間を取得する
		}

		CurrentTime += (1.0f / 60.0f);  //! 経過時間を増やす
		mcpBoxCol->SetPrevVec(mcVec);       //! 前フレームの座標として保存する
		mcVec += mcMoveVector;              //! このキャラクターにかかっている力を足す
		mcpShape->SetMoveVec(mcMoveVector); //! 当たり判定に使うための情報をセット
		mcMoveVector.SetVector(0, 0);        //! このキャラクターにかかっている力を０にする
		mcpBoxCol->SetOnObj(false);         //! 上には乗っていないことにする　ここでfalseにした方がCollsionがすっきりするのでここでfalseにします
		//! 当たり情報にサイズセット
		mcpBoxCol->SetSize(ColSize.x * msScale.x, ColSize.y * msScale.y);
		AnimationHitObject::Update();
	}
}



//! 当たり判定を見たいとき用のDrawです
void Character::Draw()
{
	if (mcpBoxCol->GetActiv() == true) {
		mcpImage->DrawSprite(mcVec.x, mcVec.y, ColSize.x * msScale.x, ColSize.y * msScale.y, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
	}
}

//! タッチグラウンドのセッター
void Character::SetTouchGround(bool _state)
{
	mTouchGraund = _state;
}

//! 矩形の当たり判定情報のゲッター
Box * Character::GetBoxCol()
{
	return mcpBoxCol;
}
