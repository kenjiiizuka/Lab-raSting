#pragma once
#include "Character.h"
#include "PlugTail.h"
#include "Log.h"
#include "PlayerState.h"

//! あとで場所移動させます

class PlayerSmoke;
class HPICon;
class PlayerBattery;

class Player :
	public Character
{
public:
	Player();                    //! コンストラクタ　プレイヤーのステータスをファイルから読み込んで調整できるようにする
	Player(float _x, float _y);  //! 座標設定可
	~Player();	                 //!  デストラクタ
	void Update() override;
	void LastUpdate() override;              //! 当たり判定処理の後に行う処理
	void Draw() override;
	void SetDamege(eDirection _nockback);    //! ダメージは１固定です
	int GetHP();                             //! HPのゲッター(UIに情報を渡すために必要)
	bool GetCharge();                        //! 帯電の状態を返す
	void AddBoruto();
	void AddElect();                         //! 帯電する関数
	void MoveStop(bool _state);              //! アイドルになって停止する関数
	void SetUIActiv(bool _activ);            //! UI描画の切り替え関数
	//! たぶん回復もある
private:
	//! メンバ関数
	void Electricity();           //! 帯電の度合に応じた処理をする
	void State_Controller();      //! コントローラー操作の時の状態に応じた処理
	void ForceProces();           //! プレイヤーだけジャンプなどの、他のキャラクターとは違う部分が多くなると予想されるので、この関数内で重力の処理や、かかった力の加算などを行います
	void Move_Mouse();            //! 移動関数 マウス
	void Move_Controller();       //! 移動関数 コントローラー
	void MoveReady();
	void Jump();                  //! ジャンプ関数
	void Damage();                //! ダメージを受けたときの処理
	void Recovary();              //! 回復する時の処理
	void Destroy();               //! Hpが0になった時の処理
	
	//! メンバ変数

	bool UIActiv = true;         //! UIの表示非表示の切り替
	bool KamaeSE = true;
	PlayerStatus msStatus;	      //! ステータス
	eDirection mDirection;        //! 向き
	ePlayerState mState;          //! 状態
	eElectricity mElectState;     //! 帯電の状態
	SJump msJump;                 //! ジャンプ構造体
	SDamage msDamage;             //! ダメージ構造体
	SElectricity msElect;         //! 帯電構造体
	AnimationHitObject * UIFrame; //! UIの枠
	int mNumBoruto;               //! ボルトを拾った数
	int mToalBoruto;              //! ボルトを拾った合計
	bool mRecovery;               //! 回復フラグ(ボルトを一定数拾ったら回復する)
	bool Stop = false;
	//! プレイヤーのしっぽに関する変数
	PlugTail * mcpPlugTail;       //! しっぽ
	Vector2 mcTailRoot;           //! しっぽの付け根の位置
	Vector2 BeforColPos;          //! 当たり判定処理を行う前の座標　当たり判定処理を行った後にしっぽの位置も修正するために必要
	
	//! フラグ関連
	bool AttackFlg;               //! 攻撃フラグ
	bool OnObj;                   //! オブジェクトの上に乗っているか
	bool Destroyed = false;         //! HPが０になりダウン演出も終わったに立てるフラグ
	bool ChangeDestroy = false;
	int DestroyCnt = 0;

	bool TailDraw = true;
	float Shive;                  //! Hpがゼロになった時に震える時の値
	bool Death = false;           //! Hpがゼロになったら立てる
	PlayerSmoke * Smoke;          //! Hpが無くなった時のスモーク
	float TailArufa = 0.0f;
	HPICon * mcpHPIcon;           //! HP描画用UI
	PlayerBattery * Battery;      //! 帯電のUI
	Vector2 CameraMoveMent;  //! カメラにこのフレームにどれだけ移動したかを渡すための変数
public: //! セッター、ゲッター
	void SetVec(Vector2 _vec) override;               //! プレイヤーの座標をセットするとしっぽの根元の位置がセットしてから次のフレームの更新処理までずれが生まれるので、専用につくる
	Box    *   GetTailCol();                          //! しっぽの　当たり判定のゲッター
	Circle*    GetAttackCol();                        //! 攻撃の当たり判定のゲッター
	Circle     GetSpearCol(int _index);               //! 電気の槍の当たり判定のゲッター(引数で根本か先端化選べる)
	bool       GetAttackFlg();                        //! 攻撃が発生しているかのゲッター
	float      GetStingPower();                       //! 刺す強さのゲッター
	Vector2    GetTailRoot();                         //! しっぽの根本の座標のゲッター
	Vector2    GetCameraMovement();
	bool       GetDeath();                            //! プレイヤーのHPが０になったフラグ
	void       SetReaction(TailReaction _reaction, eDirection _direction);   //! 刺したときのリアクションのセッター
	PlugTail * GetTail();                             //! しっぽのゲッター カメラに渡すよう
};

