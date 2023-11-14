#include "SelectCursol.h"
#include "Input.h"
#include "TextureManager.h"

#define CORRECTIONPOS 0.04f

// コンストラクタ
// 引数　コマンドの数　一番上のコマンドの中心座標　コマンドどうしの間隔  コマンドの横幅
SelectCursol::SelectCursol(int num, float xPos, float yPos, float Interval, float width)
{
	mSelectComand = 1; //現在選んでいるコマンド  // 一番上の選択が１　上から順に1,2,3....
	mNumComnd = num; // コマンド数を入れる
	mInterval = Interval; // コマンドの間隔
	mpComandPos = new FLOAT2[mNumComnd]; // コマンドの数に応じて動的に確保
	mpcImage = new Image;
	for (int num = 0; num < mNumComnd; num++) {
		mpComandPos[num].x = xPos;
		mpComandPos[num].y = yPos - (Interval * num);
	}
	// コマンドの移動可能範囲の座標
	mComnadTopPos = mpComandPos[0].y;
	mComnadUnderPos = mpComandPos[mNumComnd - 1].y;
	// コマンドの初期位置
	msPos.x = xPos - (width / 2) - CORRECTIONPOS;
	msPos.y = yPos;

	msOldPos = msPos;
	mOldSelectComand = mSelectComand;

}

// デストラクタ
SelectCursol::~SelectCursol()
{
	delete mpcImage;
	delete[] mpComandPos;
}

// カーソル移動と選択したコマンドの値を返す
int  SelectCursol::Update()
{
	int Comand = 0;
	
	// こんどここなおして
	if (In->GetKeyTrigger(VK_UP)) {
		msPos.y += mInterval;
		mSelectComand--;
	}
	if (In->GetKeyTrigger(VK_DOWN)) {
		msPos.y -= mInterval;
		mSelectComand++;
	}
	
	// 移動制限
	if (msPos.y < mComnadUnderPos || msPos.y > mComnadTopPos) {
		msPos = msOldPos;
		mSelectComand = mOldSelectComand;
	}
	// コマンド決定
	if (In->GetKeyTrigger(VK_RETURN)) {
		Comand = mSelectComand;
	}
	// 前フレームの座標と選択していたコマンドとして保存
	msOldPos = msPos;
	mOldSelectComand = mSelectComand;

	return Comand;
}

void SelectCursol::Draw()
{
	ID3D11ShaderResourceView* CursolTex = TexMgr->GetTextuer(Tex_Game);
	mpcImage->DrawDivSprite(msPos.x,msPos.y,0.1f,0.1f,3,4,1,CursolTex);
}
