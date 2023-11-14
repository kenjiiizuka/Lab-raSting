#pragma once
#include "Image.h"
#include "BaseScene.h"
#include "Cursol.h"
#include "Command.h"
#include "Window.h"
#include <vector>

//! タイトルシーンクラス
//! このゲームタイトルシーンの処理をするクラス

/* ===================================
** TitleSceneクラス　　　　　　     **　　
** タイトルシーンの処理をします     **
** 制作者 :  kita                   **
** ================================ */


class TitleScene :
	public BaseScene
{

	bool Winflg;
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	//! TitleScene内で使う関数、変数を宣言してください
	void CollisionUpdate();
	Window * mcpWindow;
	Cursol * mcpCursol;              //! カーソル
	Command * mcpCommand;            //! コマンド
	std::vector<Command *> Commands; //! コマンドを格納する配列
	StaticObject * mcpTitleBg;

	bool first;
	bool CommandClose;       //! コマンドのクローズフラグ
	bool DrawCommand;		 //! コマンドの描画フラグ
};


