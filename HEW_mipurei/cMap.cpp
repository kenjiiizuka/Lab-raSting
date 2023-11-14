#include "cMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Camerah.h"
#include "Collision.h"
#include "WinMain.h"
#include "eMapTag.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

using namespace std;


//! コンストラクタ
Map::Map(string _filename, string _itemfile, ID3D11ShaderResourceView * _maptiptex)
{
	ActivItem = false;
	DrawBg = false;

	//! 変数の初期値設定
	msScale = { 1.0f,1.0f };
	msTipSize = { 0.2f,0.2f };

	Vector2 SetBGPos(-DRAW_WIDTH,0);
	
	//! 最奥のレイヤー
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<StaticObject> bg01(new StaticObject);
		bg01.get()->SetCameraActiv(false);
		bg01.get()->GetSprite()->SetTexture(TEXTURE(Tex_StageBG01));
		bg01.get()->SetSize(DRAW_WIDTH + 0.04, DRAW_HEIGHT);
		bg01.get()->SetVec(SetBGPos);
		SetBGPos.x += DRAW_WIDTH;
		BG01.emplace_back(move(bg01));
	}

	//! 中間
	SetBGPos = Vector2(-DRAW_WIDTH, 0);
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<StaticObject> bg02(new StaticObject);
		bg02.get()->SetCameraActiv(false);
		bg02.get()->GetSprite()->SetTexture(TEXTURE(Tex_StageBG02));
		bg02.get()->SetSize(DRAW_WIDTH + 0.04, DRAW_HEIGHT);
		bg02.get()->SetVec(SetBGPos);
		SetBGPos.x += DRAW_WIDTH;
		BG02.emplace_back(move(bg02));
	}

	//! 手前
	SetBGPos = Vector2(-DRAW_WIDTH, 0);
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<StaticObject> bg03(new StaticObject);
		bg03.get()->SetCameraActiv(false);
		bg03.get()->GetSprite()->SetTexture(TEXTURE(Tex_StageBG03));
		bg03.get()->SetSize(DRAW_WIDTH + 0.04, DRAW_HEIGHT);
		bg03.get()->SetVec(SetBGPos);
		SetBGPos.x += DRAW_WIDTH;
		BG03.emplace_back(move(bg03));
	}

	mcpMapTip = new StaticObject;
	mcpMapTip->SetSize(0.21f, 0.2f);
	mcpMapTip->SetCameraActiv(false);
	mcpMapTip->GetSprite()->SetTexture(_maptiptex);


	//! ファイルオープン
	ifstream MapFile(_filename);
	if (!MapFile)	{
		MessageBox(NULL, L"ファイルオープン失敗", L"エラー発生", MB_OK);
	}
	// ファイルデータを読み取る マップの縦横の情報
	string tmp;
	getline(MapFile,tmp);
	getline(MapFile, tmp, ',');
	stringstream Sizex(tmp);
	Sizex >> mTipNumX;
	getline(MapFile, tmp, ',');
	stringstream Sizey(tmp);
	Sizey >> mTipNumY;
	getline(MapFile, tmp, ',');
	stringstream Splitx(tmp);
	Splitx >> mSplitx;
	getline(MapFile, tmp, ',');
	stringstream Splity(tmp);
	Splity >> mSplity;

	// マップの情報を格納する2次元配列を生成する
	mspMaptip = new MapTip*[mTipNumY];
	for (int num = 0; num < mTipNumY; num++)	{
		mspMaptip[num] = new MapTip[mTipNumX];
	}

	//! 配列の中身を初期化する
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			mspMaptip[i][j].Number = 0; //! 
			mspMaptip[i][j].Tag = 0;    //!
			mspMaptip[i][j].mcPos = 0;  //! 
		}
	}

	// 配列にマップの情報を入れる
	int dataCheack = 0; // 読み取ったデータをチェックするための変数

	// 配列のサイズ分読み込む
	for (int i = 0; i < mTipNumY; i++)	{
		for (int j = 0; j < mTipNumX; j++)
		{
			getline(MapFile, tmp, ','); // カンマ区切りで読み込む
			stringstream Iteminf(tmp);
			// 読み込んだ値をチェックする
			Iteminf >> dataCheack;
			if (dataCheack == -1){
				j--;
				continue;
			}
			// チェックして問題なければ配列に代入する
			mspMaptip[i][j].Number = dataCheack;
		}
	}

	//! マップに置くアイテム
	mspItem = new MapTip*[mTipNumY];
	for (int num = 0; num < mTipNumY; num++) {
		mspItem[num] = new MapTip[mTipNumX];
	}

	//! 配列の中身を初期化する
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			mspItem[i][j].Number = 0; //! 
			mspItem[i][j].Tag = 0;    //!
			mspItem[i][j].mcPos = 0;  //! 
		}
	}

	//! アイテム描画用オブジェクトの生成
	mcpItem = new AnimationHitObject;
	mcpItem->GetAnimSprite()->SetTexture(TEXTURE(Tex_MapItem01));
	mcpItem->GetAnimSprite()->SetAnimtionTable(4, 1);
	mcpItem->SetCameraActiv(false);
	mcpItem->GetAnimSprite()->SetAnimSpeed(120);
	//! ファイルオープン
	ifstream ItemFile(_itemfile);
	if (!ItemFile) {
		//MessageBox(NULL, L"ファイルオープン失敗", L"エラー発生", MB_OK);
	}

	// 配列のサイズ分読み込む
	getline(ItemFile, tmp);
	getline(ItemFile, tmp, ',');
	getline(ItemFile, tmp, ',');
	getline(ItemFile, tmp, ','); 
	getline(ItemFile, tmp, ',');
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++)	{
			getline(ItemFile, tmp, ','); // カンマ区切りで読み込む
			stringstream mapinf(tmp);
			// 読み込んだ値をチェックする
			mapinf >> dataCheack;
			if (dataCheack == -1) {
				j--;
				continue;
			}
			// チェックして問題なければ配列に代入する
			mspItem[i][j].Number = dataCheack;
		}
	}

	//! このMapの大きさを設定
	mcMapSize.x = msTipSize.x * mTipNumX;
	mcMapSize.y = msTipSize.y * mTipNumY;
	//! ステージの左下が画面の左下になるようにする
	mcPos.x = (mcMapSize.x / 2.0f) - 2.02f;
	mcPos.y = (mcMapSize.y / 2.0f) - 1.0f - msTipSize.y * 0.5f;
	Effflg = false;
}

//! デストラクタ
Map::~Map()
{
	for (int num = 0; num < mTipNumY; num++) {
		delete[] mspMaptip[num];
		delete[] mspItem[num];
	}
	delete[] mspItem;
	delete[] mspMaptip;
	delete mcpMapTip;
	delete mcpItem;	
}

//! 更新処理
//! カメラにステージ外が映らないようにしています
void Map::Update()
{
	CAMERA->MoveDown(true);
	CAMERA->MoveLeft(true);
	CAMERA->MoveTop(true);
	CAMERA->MoveRight(true);

	//! マップの移動制限の位置 小数点の誤差をなくすために変数にしている
	float LeftLimit = -DRAW_WIDTH / 2 - msTipSize.x / 2 - 0.002f;
	float RightLimit = DRAW_WIDTH / 2 + msTipSize.x / 2;
	float TopLimit = DRAW_HEIGHT / 2 + msTipSize.y / 2;
	float BottomLimit = -DRAW_HEIGHT / 2 - msTipSize.y / 2;
	//! 左端が-DRAW_WIDTHより右にいったらカメラに移動をやめてもらう
	if (mspMaptip[0][0].mcPos.x >= LeftLimit) {
		CAMERA->MoveLeft(false);
	}
	//! 右端がDRAW_WIDTHより左にいってたら移動をやめてもらう
	else if (mspMaptip[0][mTipNumX - 1].mcPos.x <= RightLimit) {
		CAMERA->MoveRight(false);
	}
	//! 上がDRAW_HEIGHTより下にいってたら移動をやめてもらう
	if (mspMaptip[0][0].mcPos.y <= TopLimit) {
		CAMERA->MoveTop(false);
	}
	//! 下が-DRAW_HEIGHTより上にいってたら移動をやめてもらう
	else if (mspMaptip[mTipNumY - 1][0].mcPos.y >= BottomLimit) {
		CAMERA->MoveDown(false);
	}

	//! 背景の移動
	BgUpdate(BG01[0].get(), BG01[1].get(), BG01[2].get(), 0.4f);
	BgUpdate(BG02[0].get(), BG02[1].get(), BG02[2].get(), 0.6f);
	BgUpdate(BG03[0].get(), BG03[1].get(), BG03[2].get(), 0.8f);

}

//**************************************************************************
//! カメラの拡大縮小した際に中心の位置がずれているのでそこの修正をまたします
void Map::Draw()
{
	Vector2 CameraMove = CAMERA->GetCameraMove();	
	mcPos += CameraMove;
	msScale = CAMERA->GetScale();
	Vector2 StandardPos = { (-mcMapSize.x * msScale.x) / 2 , (mcMapSize.y * msScale.y) / 2 }; // 描画位置の計算の基準となる座標 このMapの左上
	
	
	for (int i = 0; i < 3; i++) {
		BG01[i].get()->Draw();
	}

	for (int i = 0; i < 3; i++) {
		BG02[i].get()->Draw();
		
	}
	for (int i = 0; i < 3; i++) {	
		BG03[i].get()->Draw();
	}

	Vector2 TipPos;
	//! 初回のみマップのチップの位置を計算
	
	if (first) {
		for (int i = 0; i < mTipNumY; i++) {
			TipPos.y = (StandardPos.y - (i * (msTipSize.y * msScale.y))) + mcPos.y;
			for (int j = 0; j < mTipNumX; j++)
			{
				//! 左上の時は座標を計算する
				if (j == 0 && i == 0) {
					float x = (StandardPos.x + (j * (msTipSize.x * msScale.x))) + mcPos.x;
					mspMaptip[i][j].mcPos.x = x;
				}
				//! 一番上の段で左端ではないとき
				else if (i == 0) {
					//! 左となりのマップチップの位置からサイズ分ずらす
					mspMaptip[i][j].mcPos.x = mspMaptip[i][j - 1].mcPos.x + msTipSize.x;
				}
				//! 二段目移行は1段目の座標を代入
				else {
					mspMaptip[i][j].mcPos.x = mspMaptip[0][j].mcPos.x;
				}
				mspMaptip[i][j].mcPos.y = TipPos.y;

				//! アイテムの座標に代入
				mspItem[i][j].mcPos = mspMaptip[i][j].mcPos;
			}
		}
		first = false;
	}

	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			//! 描画
			mspMaptip[i][j].mcPos += CameraMove;
			mcpMapTip->SetVec(mspMaptip[i][j].mcPos);
			mcpMapTip->GetSprite()->SetUVSpriteInf(mspMaptip[i][j].Number, mSplitx, mSplity);
			mcpMapTip->Draw();
			//! アイテムの描画	
			if (ActivItem) {		
				if (mspItem[i][j].Number != 0) {
					mspItem[i][j].mcPos = mspMaptip[i][j].mcPos;
					mcpItem->SetVec(mspItem[i][j].mcPos);
					mcpItem->Draw();
					mspItem[i][j].Drawed = true;
				}
			}
		}
	}	
}

//! 座標のセッター
void Map::SetPos(Vector2 _pos)
{
	mcPos.x = _pos.x;
	mcPos.y = _pos.y;
}

//! 当たり判定の更新処理
bool Map::CollisionUpdate(Character * _char)
{	
	return Collision(_char);
}


//! リトライなどをしたときにMapを初期位置に戻す関数
void Map::ResetMap()
{
	//! ステージの左下が画面の左下になるようにする
	mcPos.x = (mcMapSize.x / 2.0f) - 2.02f;
	mcPos.y = (mcMapSize.y / 2.0f) - 1.0f - msTipSize.y * 0.5f;
}

//! 背景の描画をするかしないか
void Map::SetDrawBg(bool _state)
{
	DrawBg = _state;
}

Vector2 Map::GetPos()
{
	return mcPos;
}

//! Mapとキャラクターとの当たり判定を取り地面に当たっているかを返す関数
//! 戻り値 : 地面に当たっているか
bool Map::Collision(Character * _char)
{	
	bool HitGround = false;
	Effflg = true;
	for (int num1 = 0; num1 < mTipNumY; num1++)
	{
		for (int num2 = 0; num2 < mTipNumX; num2++)
		{
			//! タグをみてそれに応じた処理をする
			switch (mspMaptip[num1][num2].Tag)
			{			
			case Tag_Ground:

				//! タグがプレイヤーならしっぽの攻撃との当たり判定も取る
				if (_char->GetTag() == Tag_Player) {
					if (Collision::Tail_Map(*((Player *)_char)->GetAttackCol(), msTipSize.x, msTipSize.y, mspMaptip[num1][num2].mcPos)) {
						((Player *)_char)->SetReaction(TailReaction::TailReaction_Stop, Direction_None);
						Vector2 pos = ((Player *)_char)->GetTail()->GetVec();
						if (Effflg) {
							EffMgr->PlayEffect(Hibana, pos.x, pos.y,0.2f,0.2f);
							Effflg = false;
						}
					}					
				}
				if (Collision::Box_BoxMap(*_char->GetBoxCol(), msTipSize.x, msTipSize.y, mspMaptip[num1][num2].mcPos)) {
					HitGround =  true; //! 地面に当たっているかのフラグ
				}	
				break;	
			}

			//! タグをみてそれに応じた処理をする
			switch (mspItem[num1][num2].Number)
			{
			case 1:
				//! プレイヤーならItemとの当たり判定をとり当たっていたら描画をやめる
				if (mspItem[num1][num2].Drawed) {
					if (_char->GetTag() == Tag_Player) {
						if (Collision::Box_MapItem(*_char->GetBoxCol(), msTipSize.x, msTipSize.y, mspItem[num1][num2].mcPos)) {
							mspItem[num1][num2].Number = 0;
							((Player *)_char)->AddBoruto();
							SoundMgr->PlaySE(SE_Item,0.4f);
						}
						//! アイテムと尻尾との当たり判定
						if (Collision::Circle_MapItem(*((Player *)_char)->GetAttackCol(), msTipSize.x, msTipSize.y, mspItem[num1][num2].mcPos)) {
							mspItem[num1][num2].Number = 0;
							((Player *)_char)->AddBoruto();
							SoundMgr->PlaySE(SE_Item,0.4f);
						}
					}
				}
				break;
			}
		}
	}
	return HitGround;
}

void Map::BgUpdate(StaticObject * Left, StaticObject * center, StaticObject * Right, float _speed)
{
	//! 背景の移動
	Vector2 SetBGPos;
	if (center->GetVec().x <= -DRAW_WIDTH) {
		center->SetVec(Vector2(0, 0));
		SetBGPos = Vector2(center->GetVec().x + DRAW_WIDTH, center->GetVec().y);
		Right->SetVec(SetBGPos);
		SetBGPos = Vector2(center->GetVec().x - DRAW_WIDTH, center->GetVec().y);
		Left->SetVec(SetBGPos);
	}
	else if (center->GetVec().x >= DRAW_WIDTH) {
		center->SetVec(Vector2(0, 0));
		SetBGPos = Vector2(center->GetVec().x + DRAW_WIDTH, center->GetVec().y);
		Right->SetVec(SetBGPos);
		SetBGPos = Vector2(center->GetVec().x - DRAW_WIDTH, center->GetVec().y);
		Left->SetVec(SetBGPos);
	}

	Vector2 CameraMove = CAMERA->GetCameraMove();
	//! カメラの移動速度の半分ずつ動かす
	Vector2 pos = center->GetVec();
	center->SetVec(Vector2(pos.x + CameraMove.x * _speed, 0));
	
	pos = Left->GetVec();
	Left->SetVec(Vector2(pos.x + CameraMove.x * _speed, 0));

	pos = Right->GetVec();
	Right->SetVec(Vector2(pos.x + CameraMove.x * _speed, 0));
}
