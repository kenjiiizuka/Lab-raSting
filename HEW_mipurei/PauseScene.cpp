
#include "PauseScene.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Box.h"
#include "SoundManager.h"
#include "GameManager.h"

//! デバッグ用の仮の処理です
//! コンストラクタ
PauseScene::PauseScene()
{
	Controller.reset(new StaticObject);
	Controller->GetSprite()->SetTexture(TEXTURE(Tex_Contrller));
	Controller->SetSize(2.50f,2.50f);
	Controller->SetVec(Vector2(0.5f,0.0f));
	mcpCursol = new Cursol;
	mcpCommand = new Command[3];
	mcpCommand[0].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Continue));
	mcpCommand[1].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Retire));
	mcpCommand[2].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Title_Pawse));
	//mcpCommand[3].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Setting));
	//! 配列に代入
	for (int i = 0; i < 3; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);
	}
	Commands[0]->SetVec(Vector2(-1.3f,0.6f));
	Commands[1]->SetVec(Vector2(-1.3f, 0.05f));
	Commands[2]->SetVec(Vector2(-1.3f, -0.5f));

	//! 背景の画像のセット
	upBg.reset(new AnimationHitObject);
	AnimationSprite * BgSp = upBg->GetAnimSprite();
	upBg->SetSize(DRAW_WIDTH,DRAW_HEIGHT);
	BgSp->SetNoStopObj(true);
	BgSp->SetTexture(TEXTURE(Tex_Pause_Bg01));
	BgSp->SetAnimSpeed(2);
	BgSp->SetAnimtionTable(11, 1);
	upBg->SetCameraActiv(false);

	SoundMgr->SetBGMVolume(0.025f);

	SoundMgr->PlaySE(SE_Pause);

	GameMgr->SetAnimation(false);

	DrawCursol = DrawCommand = CommandClose = Close = false;
	Open = true;
}

//! デストラクタ
PauseScene::~PauseScene()
{
	delete[] mcpCommand;
	Commands.clear(); //! コマンドの配列のクリア
	delete mcpCursol;
	SoundMgr->SetBGMVolume(0.08f);
	GameMgr->SetAnimation(true);
}

//! 更新処理
void PauseScene::Update()
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
		if (Commands[0]->Selected()) {
			if (SceneMgr->GetBackScene() == Scene_StageSelect)
			{
				//! 選択不可にする
			}
			else {
				SoundMgr->PlaySE(SE_Select01);
				SceneMgr->ChageScene(GameMgr->GetNowStage(), true);
			}
		}
		//! リタイヤ
		if (Commands[1]->Selected()) {
			if (SceneMgr->GetBackScene() == Scene_StageSelect)
			{
				//! 選択不可にする
			}
			else {
				SoundMgr->PlaySE(SE_Select01);
				SceneMgr->ChageScene(Scene_StageSelect, true);
			}
		}
		//! タイトル
		if (Commands[2]->Selected()) {
			SoundMgr->PlaySE(SE_Select01);
			SceneMgr->ChageScene(Scene_Title, true); //! 今は仮にデバッグシーンに行く
		}	

		mcpCursol->Update();
		for (int i = 0; i < Commands.size(); i++) {
			Commands[i]->Update();
			Commands[i]->SetClose(CommandClose);
			if (Commands[i]->GetClosed()) {
				Close = true;
				BgSp->SetNoStopObj(true);
				BgSp->SetStopAnimation(false);
			}
		}

		//! ゲームシーンに戻る
		if (!Open) {
			if (GetControllerButtonTrigger(Button_MENU) || GetControllerButtonTrigger(Button_B)) {
				SoundMgr->PlaySE(SE_Cancel);
				CommandClose = true;
				DrawCursol = false;
				BgSp->ResetAnimCnt();		
				BgSp->SetTexture(TEXTURE(Tex_Pause_Bg02));
			}
		}
	}
}

//! 描画処理
void PauseScene::Draw()
{
	upBg->Draw();
	if (DrawCommand) {
		for (int i = 0; i < Commands.size(); i++) {
			Commands[i]->Draw();
		}
		Controller->Draw();
	}
	if (DrawCursol) {
		mcpCursol->Draw();
	}
}


void PauseScene::CollisionUpdate()
{

}

























