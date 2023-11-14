#pragma once
#include "BossBase.h"
#include "AnimationHitObject.h"
#include"BoxObject.h"
#include"Plag.h"
#include "Image.h"
#include"Camerah.h"
/*
制作者：仲野睦基
ハンマーを振り下ろすボス、ネクターのクラスです。
*/


//ボスの処理に関するDefine
#define ResistDef 6 //プレイヤーからの攻撃を耐える回数
#define AtkCharge 6 //例）2秒なら2とこのDefineに設定してもらえば、その時間の後にハンマーおろします
#define StopTime  9 //振り下ろしてから止まる時間

class Necthor :
	public BossBase
{
public:
	Necthor(float _X, float _Y);
	~Necthor();
	void Update();
	void Draw();
	int GetChargeTime();

	/*ボスの当たり判定関連の関数*/
	//ボス頭の当たり判定を取得
	Box* GetBossBodyCollision();
	//ボスの体の当たり判定を取得
	Box* GetBossHeadCollision();
	//ボスが振り下ろすハンマーの当たり判定を取得
	Box* GetBossHunmerCollision();
	//プラグの取得
	Plag* GetPlag();

	//引数の値をChargeTime変数に直接代入する関数
	void SetChargeTime(int _Time);
	//引数の値をChargeTime変数に加算する関数
	void AddChargeTime(int _Time);
	//ボスのライフを加減算する関数
	void AddLife(int _Life);
	//ボスがダウンしているかどうか判別
	bool GetDownFlg();
	//ダメージのクールタイムを取得
	unsigned int GetmDamageCoolTime();
	void SetmDamageCoolTime(unsigned int _Time);
	bool GetAliveFlg();
	void SetAliveFlg(bool _Flg);
	//Necthorが生成するがれきと衝撃波を取得する処理
	BoxObject* GetmpDebriesBox();
	BoxObject* GetmpWavesBox();
	void SetDamageFlg(bool _Flg);
	//コントローラー振動用にハンマーをおろしたフラグを取得する関数
	unsigned int GetCtrShakeFlg();

private:

	Plag* mpPlag;                       //トドメをさすときに攻撃するプラグの変数
	unsigned int mAttackCoolTime;       //ハンマー振り下ろし後の硬直時間
	unsigned int mLife;	                //プレイヤーのぶっさしに耐える回数
	unsigned int mDamageCoolTime;        //ダメージのクールタイム
	ID3D11ShaderResourceView * mTmpTex;
	ID3D11ShaderResourceView * mPlagTex;//トドメにぶっさすプラグのテクスチャ
	ID3D11ShaderResourceView * mAtkTex;//ライフがなくなったときのテクスチャ
	bool mBossDownFlg;                  //テクスチャを切り替えるときのフラグ
	float NoDamageTime;                 //連続ダメージ防止用の無敵時間
	//ボスの体の当たり判定
	Box* mpBodyCollision;
	Vector2 mpBodyColisionPos;
	//ボスの頭の当たり判定　　//Tailリアクション型関数を作る、PlayerStateに入ってる
	Box* mpHeadCollision;
	Vector2 mpHeadCollisionPos;
	//ハンマーの当たり判定
	Box* mpHunmerCollision;
	Vector2 mpHunmerCollisionPos;
	//当たり判定確認用画像
	Image mcImage;

	//振り下ろしまでの時間
	int mChargeTime;

	//ハンマーを振り下ろすフラグ
	bool mSwingFlg = false;

	//コントローラーを振動させるフラグ
	unsigned int mCtrShakeFlg = false;

	//生きているかどうか判別
	bool AliveFlg = true;
	//画面振動用の時間計測変数
	unsigned int ShakeTime = 0;

	//ダメージを受けた時の点滅用変数
	bool DamageFlg = false;//Setterでtrue→点滅処理終了時にfalseに戻す
	bool AlphaFlg = false;
	float Alpha = 0.0f;//SetAlpha関数で渡す用の変数
	int AlphaCnt = 8;//点滅した回数

	//がれき Boxクラスを使用する、画面下から生えてくる
	BoxObject* mpdebris;
	AnimationSprite* tmpdbrisAnimSprite;
	ID3D11ShaderResourceView* mdebrisTex;
	Vector2 mcdebreisPos;//がれきの座標
	Vector2 mcdebreisScale;
	bool WaveMoveFlg;

	//衝撃波 BoxObjectクラスを使用
	BoxObject* mpWaves;
	AnimationSprite* mpWavesAnimSprite;
	ID3D11ShaderResourceView* mWavesTex;
	Vector2 mcWavesPos;//がれきの座標
	Vector2 mcWavesScale;
	Box* mpWavesCollision;//がれきの当たり判定

};

