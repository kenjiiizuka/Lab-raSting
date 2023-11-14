#pragma once
#include "eScene.h"

/* ----------------------------------------- 
// ゲームマネージャークラス               //
// ゲームクリア状況などを管理してくれます */

#define GameMgr GameManager::GetInstance()

//!どのステージのクリア状況を判断するためのenum
enum eStage {
	Stage_1_1,
	Stage_1_2,
	Stage_1_3,
	Stage_1_4,
	Stage_1_5,
	Stage_Max
};

class GameManager
{
public:
	static void Create();
	static void Destroy();
	static GameManager * GetInstance();

	bool GetStageClearState(eStage _stage);
	void SetStageClear(eStage _stage);             //! ステージクリアをセットする
	bool GetThutrial();                            //! チュートリアルをするかしないかのフラグのゲッター
	void SetThutrial(bool _state);                 //! チュートリアルのセッター
	bool GetCheackPoint();                         //! 中間ポイントを触ったかどうかのゲッター
	bool GetBossCheackPoint();                     //! ボス前中間の触ったかどうかのゲッター
	void SetBossCheackPoint(bool _state);                     //! ボス前中間の触ったかどうかのゲッター
	void SetCheackPoint(bool _state);              //! 中間ポイントをさわったかどうかのセッター
	void SetNowPlayerStage(eScene _stage);         //! 今プレイしているステージのセッター
	eScene GetNowStage();                          //! ゲッター
	bool GemeClear();                              //! このゲームをクリアしているか
	//! アニメーション関連のセッターゲッター
	bool GetAnimation();
	void SetAnimation(bool state);
	bool GetFirst();                              //! このゲームを初回プレイなのか
	void PlayedThoutrial();                       //! チュートリアルプレイしました
private:
	GameManager();
	~GameManager();

	eScene NowPlayStage;          //! 今プレイしているステージ
	bool GameFirst;               //! このゲームを初めて起動したのかを判断するフラグ
	bool Thutrial;                //! チュートリアルから開始するフラグ
	bool CheackPoint;             //! 中間ポイントを触れたかどうかを管理するフラグ
	bool BossCheackPoint;         //! ボス前中間に触れたかどうか
	bool ClearStage[Stage_Max];   //! ステージのクリア状況を管理する配列　コンストラクタでファイルからクリア状況を読み込み、デストラクタでクリア状況を書き込む
	static GameManager * mcpIns;  //! 
	bool Animatiom = true;        //! アニメーションをするかどうか

};



