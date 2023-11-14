#include "HPICon.h"
#include"TextureManager.h"
HPICon::HPICon(int _MaxHP)
{
	//引数なしコンストラクタ
	mcpAnimsprite->SetAnimtionTable(1, 1);
	mcpAnimsprite->SetTexture(TEXTURE(Tex_Player_HP));
	mcpSprite = mcpAnimsprite;
	mcVec.x = 0.0f;
	mcVec.y = 0.0f;
	SetSize(0.14f, 0.14f);
	//引数を指定してない場合、大量のライフを表示するようにする
	MaxHP = OldHP = NowHP = _MaxHP;
	HPDecreseFlg = false;
	HPRecoverFlg = false;

	DecresePlayFlg = false;
	RecoverPlayFlg = false;
	HPIndex = 0;
	FrameWait = 0;
	DecreFrameWait = 0;
	DrawObj = new AnimationHitObject[MaxHP];
	for (int i = 0; i < MaxHP; i++) {
		DrawObj[i].SetCameraActiv(false);
	}

	mpIconState = new IconState[MaxHP];
	for (int i = 0; i < MaxHP; i++) {
		mpIconState[i] = State_None;
	}
	
}

HPICon::HPICon(int _MaxHP, float _x, float _y)
{
	//引数ありコンストラクタ。位置指定、ライフ量指定。
	//HPIconのテクスチャ読み込み
	//OldHP = NowHP = _MaxHP;
	NowHP = _MaxHP;
	MaxHP = _MaxHP;
	OldHP = _MaxHP;
	SetSize(0.12f, 0.12f);
	HPDecreseFlg = false;
	HPRecoverFlg = false;
	DecresePlayFlg = false;
	RecoverPlayFlg = false;
	HPIndex = 0;
	FrameWait = 0;
	DecreFrameWait = 0;
	DrawObj = new AnimationHitObject[MaxHP];
	for (int i = 0; i < MaxHP; i++) {
		DrawObj[i].GetAnimSprite()->SetAnimtionTable(10, 2);
		DrawObj[i].GetAnimSprite()->SetTexture(TEXTURE(Tex_Player_HP));
		DrawObj[i].GetAnimSprite()->SetStopAnimation(true);
		DrawObj[i].SetVec(Vector2(_x + (0.2f*i), _y));
		mcpSprite = DrawObj[i].GetAnimSprite();
	}
	for (int i = 0; i < MaxHP; i++) {
		DrawObj[i].SetCameraActiv(false);
	}

	mpIconState = new IconState[MaxHP];
	for (int i = 0; i < MaxHP; i++) {
		mpIconState[i] = State_None;
	}
}

HPICon::~HPICon()
{	
	delete[] DrawObj;
	delete[] mpIconState;
}

void HPICon::Update(int _HP)
{
	if (_HP <= MaxHP)
	{
		NowHP = _HP;//現在の体力を取得
	}

	if (OldHP != NowHP)//この書き方だと、OldとNowが一致した場合、通らなくなる?
	{
		if (NowHP > OldHP)//Now=3 >Old =3だと通らないので、ここを変える必要がある
		{
			mpIconState[NowHP-1] = State_Recvery;


		}
		else if (NowHP < OldHP)
		{
			mpIconState[OldHP-1] = State_Decrese;
		
		}
	}

	//今ループHPが前ループHPの数値と比較して、違う場合Lifeのアニメーションを行う
	//if (HPDecreseFlg == false || HPRecoverFlg == false)
	//{	
	//	if (OldHP != NowHP)//この書き方だと、OldとNowが一致した場合、通らなくなる?
	//	{
	//		if (NowHP > OldHP)//Now=3 >Old =3だと通らないので、ここを変える必要がある
	//		{
	//			HPIndex = NowHP;
	//			HPRecoverFlg = true;
	//		}
	//		else if (NowHP < OldHP)
	//		{
	//			HPIndex = OldHP;
	//			HPDecreseFlg = true;
	//		}
	//	}
	//
	//}	

	for (int i = 0; i < MaxHP; i++) {
		if (mpIconState[i] == State_Recvery) {
			if (Recovery(&DrawObj[i])) {
				mpIconState[i] = State_None;
			}

		}
		else if (mpIconState[i] == State_Decrese) {
			if (Decrease(&DrawObj[i])) {
				mpIconState[i] = State_None;
			}
		}	
	}



	//if (HPDecreseFlg == true)
	//{
	//	Decrease(&DrawObj[HPIndex-1]);
	//}

	//if (HPRecoverFlg == true) 
	//{
	//	Recovery(&DrawObj[HPIndex-1]);
	//}
	if (OldHP <= 0)
	{
		OldHP = 0;
	}
	if (NowHP <= 0)
	{
		NowHP = 0;
	}

	for (int i = 0; i < MaxHP; i++) {
		DrawObj[i].Update();
		DrawObj[i].LastUpdate();
	}

	if (NowHP != OldHP)
	{
		OldHP = NowHP;//前ループの体力を保持しておく
	}
}

void HPICon::Draw()
{
	for (int i = 0; i < MaxHP; i++) {
		DrawObj[i].Draw();
	}	
}

bool HPICon::Recovery(AnimationHitObject * _obj)
{
	AnimationSprite * Sp = _obj->GetAnimSprite();

	if (RecoverPlayFlg == false)
	{
		FrameWait = 0;
		Sp->ResetAnimCnt();
		Sp->SetStopAnimation(false);	
		Sp->SetColor(0.85f, 0.85f, 0.85f);
		Sp->SetYSplit(1);
		Sp->SetXSplit(0);
		RecoverPlayFlg = true;
		DecresePlayFlg = false;
	}
	

	
	if (FrameWait >= 1)
	{
		//! 9コマ目まで進めて、9コマに到達すればアニメーションを止める
		if (Sp->GetCurrentXSplit() == 9)
		{
			Sp->SetStopAnimation(true);
			Sp->SetColor(1.0f, 1.0f, 1.0f);
			RecoverPlayFlg = false;
			return true;
		}
	}
	FrameWait++;

	return false;
	
}

bool HPICon::Decrease(AnimationHitObject * _obj)
{
	AnimationSprite * Sp = _obj->GetAnimSprite();

	if (!DecresePlayFlg)
	{
		DecreFrameWait = 0;
		Sp->ResetAnimCnt();
		Sp->SetStopAnimation(false);	
		Sp->SetColor(0.5f, 0.5f, 0.5f);
		Sp->SetYSplit(0);
		DecresePlayFlg = true;
		RecoverPlayFlg = false;
	}
	
	
	if (DecreFrameWait >= 1)
	{
		//! 9コマ目まで進めて、9コマに到達すればアニメーションを止める
		if (Sp->GetCurrentXSplit() == 9)
		{
			Sp->SetStopAnimation(true);
			Sp->SetColor(0.5f, 0.5f, 0.5f);
			DecresePlayFlg = false;
			return true;
		}
	}
	
	DecreFrameWait++;
	return false;
	
}
