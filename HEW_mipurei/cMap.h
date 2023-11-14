#pragma once
#include "Image.h"
#include "FLOAT2.h"
#include <string>
#include "Vector2.h"
#include "Character.h"
#include "StaticObject.h"
#include "CheckPoint.h"
#include "Log.h"
#include <vector>
#include <memory>

//　※　制作中 　　！カメラの処理を反映させていません!

/*************************************************************
* Mapクラス                                                  *
* 機能   : Mapを描画し、Mapとの当たり判定を取ってくれます    *
* 制作者 : 飯塚 健司                                         *
*************************************************************/

class Map
{
	//! チップごとの情報の構造体
	typedef struct {
		Vector2 mcPos; //! このチップの座標
		int Number;    //! このチップの番号　テクスチャ上での番号
		int Tag;       //! このチップのTag　地面なのか、非接触のものなのかを判断するためのもの
		bool Drawed;   //! 描画されたかを判断する　描画されていないときは当たり判定を取らないようにする
	}MapTip;

public:
	Map(std::string _filename, std::string _itemfile, ID3D11ShaderResourceView * _maptiptex); //! コンストラクタ	
	~Map();
	virtual void Update();
	virtual void Draw();
	void SetPos(Vector2 _pos);      //! 座標のセッター
	virtual bool CollisionUpdate(Character * _chra);
	void ResetMap();                //! Mapの位置を初期の位置に戻す
	void SetDrawBg(bool _state);    //! 背景を描画
	Vector2 GetPos();               //! Mapの座標のゲッター  
protected:
	bool Collision(Character * _char); //! 矩形のキャラとの当たり判定
	bool ActivItem;                         //! Itemを描画するかしないか
	Vector2 mcPos;                          //! このマップの中心座標
	Vector2 mcMapSize;                      //! このマップのサイズ
	MapTip ** mspMaptip;                    //! マップチップの情報を格納する
	MapTip ** mspItem;                      //! このMapにあるアイテムの情報
	FLOAT2 msTipSize = { 0.1f,0.1f };       //! マップチップ1つのサイズ
	int mTipNumX;                           //! マップの横のサイズ
	int mTipNumY;		                    //! マップの縦のサイズ	
	int mMaxGimmick;                        //! このMapにあるギミックの数
	bool DrawBg;                            //! 背景を描画するかしないかのフラグ
	StaticObject * mcpBG[3];                //! 背景描画
	void BgUpdate(StaticObject * Left, StaticObject * center, StaticObject * Right, float speed);
	std::vector<std::unique_ptr<StaticObject>> BG01; //! 背景描画用オブジェクトの描画
	std::vector<std::unique_ptr<StaticObject>> BG02; //! 背景描画用オブジェクトの描画
	std::vector<std::unique_ptr<StaticObject>> BG03; //! 背景描画用オブジェクトの描画
	
	bool Effflg;  //! 複数のマップチップに同時に当たってエフェクトが複数回再生されるのを防ぐ

private:		
	int mSplitx, mSplity;                   //! マップチップの分割数
	FLOAT2 msScale;                         //! 拡大縮小率	
	StaticObject * mcpMapTip;               //! マップチップ描画用オブジェクト
	AnimationHitObject * mcpItem;           //! マップチップ描画用オブジェクト
	
	bool first = true;
};

