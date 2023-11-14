#pragma once
#include "AnimationHitObject.h"
#include "Player.h"
#include <vector>
#include <memory>

//! ネクトール調整板

class NecthorHammer;
class NecthorDebri;
class ShockWave;
class Smoke;
class Necthor_Allow;

class ReNecthor :
	public AnimationHitObject
{
protected:
	//! 自身の状態
	enum eNecthorState {
		State_Idol,
		State_PressHammer,
		State_ShockWave,
		State_RushWave,
		State_LeapDebri,  //! １－５のネクトール用の攻撃　がれきが飛び上がるやつ（ボルボロスの頭たたきつけの時出る泥攻撃みたいな）
		State_Down,   //!倒れてる状態
		State_Destroy
	};

	enum Texture_State {
		Tex_Idol,
		Tex_Attack,
		Tex_Attack2
	};

	//! 当たり判定に使う変数をまとめた構造体
	//! ボスは当たり判定を分けていて複数あるので構造体にまとめました
	struct sCol {
		Box * Col;
		Box * AtkCol;                                           //! 攻撃判定
		Vector2 Pos;	                                        
		Vector2 Size;	                                        
		bool TailHited;                                         //! 攻撃をあてられたかを判断する
		int Cnt;                                                //! あてられてから数フレームは攻撃との当たり判定を取らない、そのフレームを数える
	};

	//! 各攻撃をした回数
	struct AttackCnt {
		int Press;
		int Wave;
		int Ruch;
	};

public:
	ReNecthor();                                               //! コンストラクタ
	ReNecthor(float _x, float _y);                             //! 引数ありコンストラクタ
	~ReNecthor();                                              //! デストラクタ
											                   
	void Update();							                   
	void Draw();							                   
	void CollisionUpdate();                                    //! 当たり判定の処理
	void LastUpdate();                                         //! 最終更新処理
	void SetPlayer(Player * _player);                          //! プレイヤーをセットする
	void BattleStart();                                        //! ボスを動かす
	bool GetDestroyed();                                       //! 自身が倒されたことをつたえる関数 
protected:
	virtual void Idol();                                       //! Idolの処理
	virtual void Atk_PressHammer();                            //! ハンマーを叩きつける攻撃(がれきが出ます)
	virtual void Atk_ShockWave();                              //! 衝撃波攻撃
	virtual void AttackStateMachine();                         //! どの攻撃をするかを決める
	virtual void Atk_RushWave();                               //! 連続衝撃波攻撃
	void FallDwoned();                                         //! 倒された時の処理
	void Destroy();                                            //! とどめを刺されたときのしょり　
	void ColFix();                                             //! 自身の当たり判定の位置の調整関数
	void Damage();                                             //! ダメージの処理
	virtual void SmokeUpdate();                                        //! スモークの更新処理
	void TexChange();                                          //! テクスチャの状態に合わせて変更してくれる

	//! ↓　メンバ変数　↓
	eNecthorState State;                                       //! 状態
	int IdolCnt;                                               //! アイドル状態のフレームカウント(攻撃開始の判断に使う)
	int AttackCoolTime;                                        //! 攻撃時のアニメーションのフレームを数える
	Player * mcPlayer;                                         //! 外側で当たり判定を取るのがめんどくさいのでプレイヤーのアドレスをもらってここでします
	sCol MyCol;												   //! 本体の当たり判定
	sCol WeekCol;											   //! 弱点の当たり判定
	float HP;												   //! 体力10     (もしゲージがいることになったときのためにフロート型にしておく)
	float TakenDamage;										   //! 被ダメージ (もしゲージがいることになったときのためにフロート型にしておく)
	int DamageFrameCnt;										   //! ダメージに処理に使う変数
	bool DamageFlg;											   //! ダメージ処理をするか判断するフラグ
	bool BattleActiv = false;                                  //! 戦闘フラグ
	bool ShockWaved = false;                                   //! 衝撃波攻撃をしたかどうか
	AttackCnt AtkCnt;                                          //! 各攻撃をした回数
	int RushCnt;                                               //! ラッシュ攻撃中に何回攻撃したかを数える
	int RushMax;                                               //! 連打の最大回数
	int RushFrameCnt;                                          //! ラッシュ攻撃の溜め時間
	bool RushPreparation = false;                              //! ラッシュ攻撃の予備動作
	int PreparationCnt;                                        //! 予備動作のフレームを数える
	float Shiver;                                                //! 予備動作で震える値
	int ShockWaveCoolTime;                                     //! 衝撃波攻撃のクールタイム 
	int ShockWaveCoolTimeMax;                                  //! 衝撃波攻撃のクールタイムに必要な時間
	NecthorHammer * Hammer;                                    //! ハンマー
	std::vector < std::unique_ptr<NecthorDebri>> Debri;        //! がれき
	std::vector<std::unique_ptr<ShockWave>> Wave;              //! 衝撃波    
	std::vector<std::unique_ptr<Smoke>> Smokes;                //! 煙
	std::unique_ptr<Necthor_Allow> Allow;         //! ハンマーに乗るところのやじるし
	bool LeftSmoke, RightSmoke, NomalSmoke;                    //! 煙を出すフラグ
	int AnimX;                                                 //! アニメーションのX方向の現在の番号
	Texture_State TexState;                                    //! 今のどのテクスチゃなのか
	Texture_State TexState_Prev;                               //! 過去フレームのどのテクスチゃなのか
	bool mDestroy = false;                                     //! 倒れるときの演出も全て終わり完全に動かなくなったこフラグ
	int DestroyCnt = 0;                                        //! 最後の演出の時にエフェクトを出すタイミングを調整するための変数
	float Arufa = 1.0f;
	bool HightHP = true;

	bool AtkSEflg;
	//! デバッグ用
	Image image;
	
};

