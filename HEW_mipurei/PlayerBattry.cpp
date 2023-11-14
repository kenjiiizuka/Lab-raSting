#include "PlayerBattry.h"
#include "TextureManager.h"

//! コンストラクタ
PlayerBattery::PlayerBattery()
{
	Battery.reset(new AnimationHitObject);
	Battery->SetVec(Vector2(-1.4f, 0.64f));
	Battery->SetSize(0.7f,0.47f);
	Battery->SetCameraActiv(false);
	AnimationSprite *  Sp = Battery->GetAnimSprite(); //! アニメーションスプライトの取得
	Sp->SetTexture(TEXTURE(Tex_Battery));
	Sp->SetAnimtionTable(8, 2);	
	Sp->SetStopAnimation(true);

	NumBattryDraw = NowCharge = 0;
	DifCharge = WaitFrameCnt = 0;
	Wait = false;
	WaitFrameLow = 30;
}

//! デストラクタ
PlayerBattery::~PlayerBattery()
{
}

//! 更新処理
void PlayerBattery::Update(int _charge)
{
	NowCharge = _charge;                   //! 現在にチャージに代入
	if (!Wait) {
		//! 差があった時に表示を１進める
		if (NowCharge > NumBattryDraw) {
			NumBattryDraw++;
			if (NumBattryDraw > 7) {
				NumBattryDraw = 7;
			}	
			Wait = true;
		}
		else if(NowCharge < NumBattryDraw){
			NumBattryDraw--;
			if (NumBattryDraw < 0) {
				NumBattryDraw = 0;
			}
			//Down = true;
			Wait = true;
		}
		
	}
	else {	
		//! 3フレーム待つ
		if (WaitFrameCnt >= 10) {
			Wait = false;
			WaitFrameCnt = 0;
		}
		WaitFrameCnt++;
	}
	AnimationSprite *  Sp = Battery->GetAnimSprite(); //! アニメーションスプライトの取得
	Sp->SetXSplit(NumBattryDraw);
}

//! 描画処理
void PlayerBattery::Draw()
{
	Battery->Draw();
}
