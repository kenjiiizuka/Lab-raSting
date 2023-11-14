#pragma once
#include "BaseEnemy.h"
#include <vector>

class Fordon :
	public BaseEnemy
{
public:
	Fordon(); 
	~Fordon();
	void Update();
	void Draw();
	void CreateMenber(int _num);

	int GetNumMenber(); //! メンバーの数を返す
	TailReaction SetStingPower(float _Power, bool _Elect);  //! 刺されてリアクションを返す関数
	Fordon * GetMenber(int _index);                         //! メンバーの取得関数 引数は何番目のメンバー
	void SetInitVec(Vector2 _vec);
	void SetVec(Vector2 _vec);
	Vector2 GetVec() override;
private:
	Fordon(bool _state, int _formation);                    //! メンバーを生成するときに使うコンストラクタ
	void Update_Top();                      //! 先頭の更新処理
	void Update_Member(Vector2 _pos);       //! メンバーの更新処理

	void Move();                            //! 移動関数
	void ForceProces();                     //! 座標を移動させる関数
	void Move_Menber(Vector2 _destination); //! メンバーの時の移動

	Vector2 Movevec; //!　メンバーに渡す用の座標（倒された後もうごかすため）
	std::vector<std::unique_ptr<Fordon>> Member;        //! 隊列のメンバー
	bool Top;										    //! 先頭にいるかどうか
	int AtkIntervalCnt = 0;                             //! 攻撃までのインターバル
	int ReturnCnt = 0;                                  //! 攻撃のあともどる時のカウントなにかにつっかえたときよう
	bool Atk = false;                                   //! 攻撃フラグ
	bool AtkRetrun = false;                             //! 攻撃が終了して一定の高度まで戻る
 	float Speed = 0.008f;                               //! ムーブスピード
	float AtkSpeed = 0.01f;
	float TotalMove = 0;                                //! 移動合計
	float MoveDeg   = 30;                               //! 移動画度
	float Totaldeg  = 0;                                //! 角度の変位した量
	float MoveRad   = 0;                                //! 移動の角度(弧度法)
	float Add       = -0.5f;                            //! 角度の変位する量
	int FormaionNum;                                    //! 隊列の数
	bool Moved      = false;                            //! デバッグ用変数
};

