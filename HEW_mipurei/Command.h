#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "Cursol.h"
class Command 
	: public AnimationHitObject
{
public:
	Command();                                  //! コンストラクタ
	Command(ID3D11ShaderResourceView * _tex);   //! テクスチャーをセットできるコンストラクタ
	~Command();				                    //! デストラクタ
	void Update();                              //! 更新処理
	void Draw();
	bool Selected();                            //! 選択されかどうか
	void SetVec(Vector2 _vec) override;
	void SetCursol(Cursol * _cursol);           //! カーソルのセッター
	void SetSize(float _x, float _y) override;  //! サイズのセッター
	void SetClose(bool _close);
	bool GetClosed();                           //! コマンドが閉じ切ったかを返すゲッター
	Vector2 GetNextCommandPos();                //! 自分の下に来るコマンドの座標を返す　基本的にコマンドは縦並びで縦の幅は同じなので次のコマンドの位置が計算できた便利かなっておもった
	AnimationHitObject * GetFrame();            //! コマンドの後ろの枠のゲッター
private:						                				                
	Cursol * mcpCursol; 		                //! このコマンドに対応したカーソル
	Box * mcpBox;                               //! 当たり判定情報
	bool CurrentHit;                            //! 現在の当たり情報 当たっていたら大きくする
	bool PrevHit;                               //! 前フレームの当たり情報
	FLOAT2 DefaultSize;                         //! デフォルトのサイズ
	AnimationHitObject * Bg;                   //! コマンドの囲い
	bool Close = false;
	bool Opned = false;
	bool Closed  =false;                       //! クローズ完了フラグ
	float Arufa;
};

