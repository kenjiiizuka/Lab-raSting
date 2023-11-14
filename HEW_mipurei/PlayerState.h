#pragma once
#include "Vector2.h"
#include "eDirection.h"
#define STING_STRONG 0.12f
#define STING_MIDIUME 0.06f
//! 刺す強さの弱は中以下にで判断できるので定義はしません


//! プレイヤー本体に使うenumと構造体---------------------------------------------------------
/* -------------------------------
// プレイヤーの状態の列挙型です //
// 制作者 : 飯塚 健司           */
enum ePlayerState {
	Player_Idol_Walk,  //! 通常
	Player_Walk,       //! 歩き
	Player_Attack,     //! 攻撃中
	Player_Down        //! HPが無くなった時
	//Player_Reaction, //! 攻撃したときのリアクションをする状態、
};

enum eElectricity {
	Elect_None,     //! 帯電していない
	Elect_Small,    //! 小帯電
	Elect_Midiume,  //! 中帯電
	Elect_Large,    //! 大帯電
	Elect_Super,    //! 超帯電
};

//! プレイヤーのステータス構造体です
struct PlayerStatus {
	float MoveSpeed;     //! 移動速度
	float InitJumpPower; //! ジャンプ力 これを代入して使う
	float TmpJumpPower;  //! 実際に処理に使う用変数
	int HP;              //! 体力
	bool MoveAble;       //! 移動可能フラグ
	PlayerStatus();
};

//! ジャンプに使う変数をまとめた構造体
struct SJump {
	int FrameCnt; //! ジャンプ中のフレームカウント
	int AnimCnt;  //! ジャンプ中のアニメーションカウント
	bool Doing;   //! ジャンプ(空中にいるか)中のフラグ
	bool Up;      //! ジャンプ前の助走、ため時間
	bool End;     //! ジャンプして着地したフラグ
	bool Jump;    //! ジャンプ中かどうか
	SJump();
};

//! ダメージ演出に使う構造体
struct SDamage {
	int Cnt;                //! フレームカウント
	bool Flg;               //! ダメージを受けたフラグ
	bool Effect;            //! ダメージエフェクトフラグ(取り合えず30フレーム点滅)
	bool NockBack;          //! ノックバックフラグ
	bool Overheat;          //! オーバーヒートによるダメージ
	eDirection NockBackWay; //! ノックバックの方向
	SDamage();
};

//! 帯電に関する変数をまとめた構造体
struct SElectricity {
	int ChargeCnt;  //! 帯電のカウント　この数値によって帯電の状態が変わる
	int SuperCnt;   //! 超帯電の時のフレームを数える
	float UpRate;   //! ステータスの上昇倍率
	bool EndSuper;  //! 超帯電終了フラグ
	bool Super;     //! 超帯電中のフラグ
	SElectricity();
};

//! しっぽに使う構造体と列挙型----------------------------------------------------------------
//! しっぽの位置と角度を入れる構造体
struct TailSectionInf {
	Vector2 Pos;
	float Width; //! 横幅
	float Angle;
	Vector2 Velocity;     //! 移動量
	float Gravity;        //! 重力
	Vector2 Acceleration; //! 加速度
	Vector2 Tension_Up;   //! 上から引っ張られる力
	Vector2 Tension_Down; //! 下から引っ張られる力
	Vector2 Resultant;    //! 合力
	bool Fin;             
};

//! しっぽの状態
enum TailState {
	Tail_Idol,
	Tail_Attack,
};

//! しっぽを刺したときのリアクションの列挙型です
//! どんなリアクションをするのかを返す時に使います
enum TailReaction {
	TailReaction_None,      //! なにしていない状態
	TailReaction_Bounce,    //! はじかれる
	TailReaction_Stop,      //! 止まる 刺さらない(絶対にささらないものMapなどに刺したとき用)
	TailReaction_StingStop, //! 刺さって止まる
	TailReaction_Through,   //! 貫く
	TailReaction_Sting,     //! 刺さる
	TailReaction_StingDeep, //! 深く刺さる
	TailReaction_End        //! リアクションの終了
};

// 攻撃時の状態
enum TailAttackState {
	AttackState_None,
	AttackState_Aim,      //! 狙っている時
	AttackState_Sting,    //! 刺している（RTを押してから何かに当たるか攻撃がおわるまで）
	AttackState_Reaction, //! 攻撃後のリアクション
	AttackState_End       //! 攻撃終了
};

