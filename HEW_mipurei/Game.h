#pragma once
#include <Windows.h>

/* ======================================= 
**   Gameクラス(シングルトン)           **
** ゲーム全体の更新、描画をするクラス 　**
** 制作者 : 飯塚 健司                   **
** =====================================*/

#define GameIns Game::GetInstance()
#define ACTIV Game::GetInstance()->GetActiv()
//! 操作系統の列挙型
enum Operation{
	Controller, //! コントローラー操作
	Mouse,      //! マウス操作
};

class Game
{
public:
	static Game* GetInstance();                        //! 実態を取得する関数
	static void Create();		                       //! 生成用関数
	static void Destroy();				               //! クラスの破棄用の関数

	void GameInit(HINSTANCE _hinstsnce, HWND _hwnd);
	void GameUpdate();
	void GameDraw();
	void GameRelease();
	bool GetActiv();
	void SetActiv(bool _state);
	Operation GetOperation(); //! 現在の操作方法お取得
	void ChangeOperation(Operation _operation); //! 操作方法の切り替え関数
private:
	Game();  //! コンストラクタ
	~Game(); //! デストラクタ

	static Game* mcpInstance;

	//! 操作方法
	Operation mOperation; //! 現在の操作方法

	bool Activ = true; //!　このフラグがオフになったらゲームを終了する
};

