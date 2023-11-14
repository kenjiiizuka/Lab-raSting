#pragma once
#include "direct3d.h"
#include "VERTEX2D.h"
#include "eEffecth.h"

//! エフェクトの情報の構造体
typedef struct {	
	ID3D11ShaderResourceView* mTexture; // テクスチャ	
	eEffect ID;
	int Split_x;
	int Split_y;
	float mSize_x, mSize_y; // 描画サイズ
	float pos_x;
	float pos_y;
	float Angle;
	int AnimSpeed;
}EffectInf;


/* =========================== ** 
** Effectクラス                **
** エフェクトを描画します      **
** =========================== */

//! 基本的にEffectManagerクラスでしか触らないようにして下さい。

class Effect
{
public:
	Effect(EffectInf _effect, eEffect _effectid);      //! コンストラクタ
	~Effect();					        //! デストラクタ
	virtual void Update();				//! 更新処理
	void Draw();				        //! 描画処理
	void SetPos(float _x, float _y);    //! 座標のセッター
	bool GetEndFlg();			        //! エフェクトの終了フラグのゲッター
	eEffect GetEffectID();              //! エフェクトのID
protected:						        
	ID3D11Buffer* mVertexBuffer;        //! 頂点バッファ
	EffectInf msEffectInf;              //! エフェクトの構造体
	RGBA mColor;                        //! カラー情報
	int mAnimFrameCnt; 	                //! アニメーション用のフレームカウント
	int mSplit_x, mSplit_y;             //! アニメーションのコマ番号
	int * mpAnimTable;                  //! アニメーションテーブル
	float mSize_u;                      //! 1コマの横の長さ
	float mSize_v;                      //! 1コマの縦の長さ
	float mScale_x;                     //! カメラから見たときの拡大縮小
	float mScale_y;                     //! カメラから見たときの拡大縮小
	float mLength;                      //! スプライトの長さ 
	double mdAngle;                     //! 角度
	eEffect mEffectID;                  //! エフェクトの種類
	bool mEndflg;                       //! エフェクトの終了フラグ
};




