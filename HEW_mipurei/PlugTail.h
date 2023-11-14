#pragma once
#include "AnimationHitObject.h"
#include "PlayerState.h"
#include "Box.h"
#include "eDirection.h"
#include "Circle.h"
#include "Image.h"
#include "Log.h"

/* ==================================================================== 
// PlugTaileクラス プレイヤーのしっぽクラス　　　　　　　　　　　　  //
// 制作者 : 飯塚 健司　　　　　　　　　　　　　　　　　　　　　　　  */

//! しっぽのステータスもプレイヤーの状態によって変化するのでプレイヤー側から値を変更しやすいようにした方がいいかも

//! プレイヤーの位置をもらってその値からしっぽの位置を決める
//! しっぽはマウスと連動して動く

class PlugTail :
	public AnimationHitObject
{
public:
	PlugTail(Vector2 & _Tailvec, Vector2 & _movevec, ePlayerState & _state, eDirection & _direction, eElectricity & _electstate); //! コンストラクタ
	~PlugTail(); //! デストラクタ

	void Update() override;
	void LastUpdate() override;           //! プレイヤーが当たり判定処理を行った後に座標を修正する処理
	void Draw() override;
	bool SetState(TailState _state);      //! 状態のセット関数
	void Destroy();                       //! プレイヤーのHPが0になった時の処理
	bool GetChrage();                     //! 刺さって帯電されるか
	AnimationSprite * GetElestSpear();
	void SetFlash(bool _state);           //! 点滅かいしのセッター
private:
	//! メンバ関数
	void Idol_Controller();               //! Idol状態の関数 コントローラー	
	void Attack_Controller();             //! 攻撃状態の関数 コントローラー
	void State();                         //! 状態に応じた処理
	void Tail();						  //! しっぽの中間部分の処理
	void Aim_Controller();                //! エイム コントローラー
	void Reaction_Controller();           //! 攻撃後のリアクションの処理
	void AttackPosture_Controller();      //! マウスで操作している時の攻撃態勢関数
	void Bounce();                        //! しっぽを刺してはじかれるときのリアクション
	void Stop();                          //! 刺さらずに止まる時
	void StingStop_Controller();          //! しっぽを刺した後に止まるリアクション コントローラー
	void Through();                       //! しっぽを刺した後に貫く処理
	void Sting_Controller();              //! 刺さる時の処理
	void StingDeep_Controller();          //! 深く刺さるときの処理
	void ReturnTail();                    //! しっぽが刺した後に刺す前の位置に戻る処理
	void DisCharge();                     //! 放電
	void MoveLimit(int _speed  =12);      //! 移動制限関数
	void StingObj();                      //! 刺しているオブジェクトにたいする処理
	void ElectSpear();                    //! 電気の槍の処理


	//! 放電に使う変数をまとめた構造体
	struct SDisCharge{
		bool Able;          //! 放電可能かを判断するフラグ
		bool Doing;         //! 放電中のフラグ 
		bool End;           //! 放電終了のフラグ
		int Cnt ;           //! 放電中にフレームを数える		
		bool Hit;           //! 放電が刺してる対象に当たるかどうか
		int EffectNum;      //! 放電のエフェクトを出す数
		int DrawEffectNum;  //! 何個目のエフェクトなのか
		int EffectCnt;      //! 次にエフェクトをだすまでのカウント
		bool EffectDraw;    //! エフェクト描画フラグ
	};

	//! しっぽの節
	struct SSection {
		AnimationHitObject * Section;    //! しっぽの中間部分	
		TailSectionInf Inf[100];         //! しっぽの中間部分の座標
		TailSectionInf PrevInf[100];     //! しっぽの中間部分の座標(しっぽの軌跡として保存する)
		FLOAT2 Size;                     //! しっぽの中間部分のサイズ
		FLOAT2 DefaultSize;              //! しっぽの中間部分の通常サイズ
		FLOAT2 AimSize;                  //! エイム時のサイズ
		float Length;                    //! しっぽの長さ
		float PichDefault;               //! しっぽのふしの間隔 通常時
		float Pich;                      //! 間隔
		float PichAim;                   //! エイム時と攻撃時のしっぽの間隔
		int Num;                         //! しっぽの節を何個描画するのか
		int OldNum;                      //! しっぽの前フレームの節の数
	};

	struct SBounce {
		int TotalAngle;   //! 加算した角度
		float TotalMove;  //! 移動した量
		float speed;      //! はじかれるスピード
		bool ReTail;      //! 尻尾を戻すフラグ
		bool Flg;         //! はじかれているフラグ
		int Cnt;          //! フレームを数える
	};

	SBounce msBounce;                     //! はじかれるときのリアクションに使う構造体
	TailState mState;                     //! 自身のステート
	Vector2 mcDefaultSize;                //! 通常時のサイズ
	Vector2 mcAimeSize;                   //! エイムしてるときのサイズ
	TailAttackState AttackState;          //! 攻撃の状態
	TailReaction mReaction;               //! しっぽがはじかれたときなどのリアクションがどれかを判断する
	int mReactionFrameCnt;                //! フレームを数える
	ePlayerState & mPlayerState;          //! プレイヤーの状態	
	Vector2 & mcPlayerVec;                //! プレイヤーの位置
	eDirection & mDirection;              //! プレイヤーの向いてる方向
	eDirection PrevDirection;             //! プレイヤーの向いてる方向(前フレーム)
	Vector2 & mcTailRoot;                 //! しっぽの付け根	
	Vector2 mcOldPlayerVec;               //! プレイヤーの前フレームの位置	

	Vector2 mcTailDistance;               //! しっぽの付け根からの距離　向きが変わった時に対応できるように距離を持っておく
	Vector2 mRightStick_C;                //! 右スティックの倒れている量
	
	float mTailAngle;                     //! しっぽの角度
	float DrawTailAngle;                  //! 描画用の尻尾の角度
	float mTailRange;                     //! しっぽの動かせる範囲...届く範囲
	float mAtkSpeed;                      //! 攻撃の速度(しっぽの動く速さ)
	float mDownAtkSpeed;                  //! 敵を貫いたら下降補正をかける
	float mReturnSpeed;                   //! 攻撃後にしっぽが基の位置に戻る時のスピード 
	bool AtkStop;                         //! 刺して止まった時を判断するフラグ
	bool TameSE = true;

	float RStickAngle;                    //! 右スティックのアングル
	eDirection ReactionDerection;         //! リアクションの時に敵に対してどの方向にいるか

	bool mOverheat;                       //! 刺した発電機がオーバーヒートしたか判断するフラグ
	bool mAimeAngleSet;                   //! エイムに行ったときにしっぽの向きをセットするフラグ

	SDisCharge msDisCharge;               //! 放電構造体
	SSection msSection;                   //! しっぽの節
	eElectricity & ElectState;            //! 帯電の状態
	bool mCharge;                         //! チャージフラグ
	//! コントローラー操作のための変数
	bool TriggerStart_C;                   //! トリガーの計測開始フラグ
	bool Attack_C;                         //! 攻撃開始フラグ
	float AttackInitSpeed;			       //! 攻撃の初速
	int MaxTrigger_C;                      //! トリガーの最大値	                      
	float mStingPower;                     //! 刺す強さ(攻撃の強さ)

	Box * mcpCol;                          //! 自身の当たり判定情報を持つクラス	
	Circle * mcpAttackCircle;              //! 攻撃用値判定	
	Vector2 mcAttackPos;                   //! 攻撃が発生する座標, しっぽの先端部分
	float AttackRadius;                    //! 攻撃の半径
	FLOAT2 msColSize;                      //! 当たり判定のサイズ
	                         
	bool mOnElectForDynamo = false;

	//! 電気のやり
	struct S_ElectSting{                    
		bool Activ = false; 
		bool First = false;                 //! 帯電状態になった瞬間(最初にでんきのやりが出てくる時)
		AnimationHitObject * ElectSting;    
		Vector2 ColPos;						//! 当たり判定の位置
		Vector2 ColRootPos;                 //! 根元の当たり判定の位置
		Circle * Col;                       //! 電気の槍の当たり判定(先端)
		Circle * ColRoot;                   //! 根本
		Vector2 DefaultSize;                //! おおきくなった時のサイズ
		Vector2 SmallSize;                  //! 小さいときのサイズ
		Vector2 Size;                       //! 今現在のサイズ
		float Arufa;                        //! 透明度
		float TailDistance;                 //! 尻尾からの距離 (このながさで位置が決まる)
		bool Flash = false;
	};

	S_ElectSting msSpear;

	//! 刺しているオブジェクト
	GameObject * mcpStingObj;
	//! デバッグ用

	Image mImage;
	bool Red;
	bool Yellow;
	bool Blue;
	bool Nomal;
public: //! ゲッター、セッター
	bool GetOverheat();                           //! オーバーヒート下かをもらうゲッター
	void SetAttackState(TailAttackState _state);  //! 攻撃の状態のセッター
	Box * GetCol();                               //! 自身の当たり判定に使う情報のゲッター
	Circle* GetAttackCol();                       //! 攻撃の当たり判定のゲッター
	Circle GetSpearCol();                         //! 電気の槍の当たり判定
	Circle GetSpearColRoot();                     //! 電気の槍の根元の当たり判定
	float GetStingPower();                        //! 刺す強さゲッター
	Vector2 GetTailDistance();                    //! しっぽの距離のゲッター　
	void SetReaction(TailReaction _reaction ,eDirection _direction);     //! しっぽの刺した後のリアクションセッター
	void TailReturn();                            //! 尻尾を抜く関数(どんな状態からでも抜けます)
	bool GetTailRactionState();                   //! しっぽの状態を返す
	bool GetAttackState();                        //! 攻撃の状態を返す　trueなら攻撃中 
	void SetStingObj(GameObject * _stingobj);     //! 刺してるオブジェクトのセッター


};

