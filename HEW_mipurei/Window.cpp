#include "Window.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Box.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "Game.h"

Window::Window(Cursol * cursol)
{
	mcpCursol = cursol;
	mcpCommand = new Command;
	mcpNCommand = new Command;
	
	mcpWindowBg = new StaticObject;
	mcpWindowBg->GetSprite()->SetTexture(TEXTURE(Tex_Window));
	mcpWindowBg->SetSize(Vector2(1.0f, 0.6f));
	mcpWindowBg->SetPos(0.0f, -0.05f);
	mcpCommand->SetSize(0.2f, 0.1f);
	mcpNCommand->SetSize(0.3f, 0.1f);
	mcpCommand->GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Yes));
	mcpNCommand->GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_No));

	//! 背景の画像のセット
	upBg.reset(new AnimationHitObject);
	AnimationSprite * BgSp = upBg->GetAnimSprite();
	upBg->SetSize(1.92f, 1.0f);
	BgSp->SetNoStopObj(true);
	BgSp->SetTexture(TEXTURE(Tex_Pause_Bg01));
	BgSp->SetAnimSpeed(2);
	BgSp->SetAnimtionTable(11, 1);
	upBg->SetCameraActiv(false);

	//! 情報セット　座標　カーソル　画像		
	mcpCommand->SetVec(Vector2(-0.3f, -0.2f));
	mcpCommand->GetFrame()->SetSize(0.5f, 0.2f);
	mcpCommand->SetCursol(mcpCursol);
	Commands.emplace_back(mcpCommand);
	
	mcpNCommand->SetVec(Vector2(0.3f, -0.2f));
	mcpNCommand->GetFrame()->SetSize(0.5f, 0.2f);
	mcpNCommand->SetCursol(mcpCursol);
	Commands.emplace_back(mcpNCommand);
	
	SoundMgr->PlaySE(SE_Pause);

	DrawCursol = DrawCommand = CommandClose = Close = false;
	Open = true;
}

Window::~Window()
{	
	delete mcpCommand;
	delete mcpNCommand;
	delete mcpWindowBg;
	Commands.clear(); //! コマンドの配列のクリア	
}

void Window::Update()
{
	//!　背景オブジェクトのアニメーションスプライトを取得
	AnimationSprite * BgSp = upBg->GetAnimSprite();

	int AnimX = BgSp->GetCurrentXSplit();
	//! 開くときの処理	
	if (Open) {
		if (AnimX == 10) {
			BgSp->SetNoStopObj(false);
			BgSp->SetStopAnimation(true);
			Open = false;
		}
		if (AnimX == 7) {
			DrawCommand = true;
		}
		if (AnimX == 5) {
			DrawCursol = true;
		}
	}
	else if (Close) {
		if (AnimX == 10) {
			BgSp->SetNoStopObj(false);
			BgSp->SetStopAnimation(true);
			SceneMgr->ChageScene(Scene_Back, false, false);
			Close = false;
		}
		if (AnimX == 2) {
			DrawCommand = false;
		}
	}


	//! コマンドが描画されてから選べるようにする
	if (DrawCommand) {
		//! コマンド
		//! コンティニュー
		if (mcpCommand->Selected()) {
			SoundMgr->PlaySE(SE_Select01);
			GameIns->SetActiv(false);
		}
		//! コマンド
	//! いいえが押されたとき
		if (mcpNCommand->Selected()) {
			SoundMgr->PlaySE(SE_Select01);
			SceneMgr->ChageScene(Scene_Title, true);
		}
	}
	
	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Update();
	}
}

void Window::Draw()
{
	upBg->Draw();
	//mcpWindowBg->Draw();
	if (DrawCommand) {
		for (int i = 0; i < Commands.size(); i++) {
			Commands[i]->Draw();
		}
	}
	if (DrawCursol) {
		mcpCursol->Draw();
	}
}

void Window::CollisionUpdate()
{
}
