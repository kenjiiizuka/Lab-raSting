#include "LoseScene.h"
#include"TextureManager.h"
#include"Controller.h"
#include"SoundManager.h"
#include "WinMain.h"
#include "SceneManager.h"
#include "GameManager.h"

LoseScene::LoseScene()
{
	//! 背景の生成
	mcpBG = new StaticObject;
	Sprite * BgSp = mcpBG->GetSprite();
	BgSp->SetTexture(TEXTURE(Tex_Pause_Bg01));
	BgSp->SetUVSpriteInf(10, 11, 1);
	mcpBG->SetSize(DRAW_WIDTH,DRAW_HEIGHT);

	mcpCursol = new Cursol;
	mcpCommand = new Command[2];
	mcpCommand[0].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Continue));
	mcpCommand[1].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Retire));

	//! 配列に代入
	for (int i = 0; i < 2; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);		
	}

	Commands[0]->SetVec(Vector2(0.0f, -0.1f));	
	Commands[1]->SetVec(Vector2(0.0f, -0.5f));
	SoundMgr->PlaySE(SE_Lose);
}

LoseScene::~LoseScene()
{
	delete[] mcpCommand;
	Commands.clear(); //! コマンドの配列のクリア
	delete mcpCursol;
	delete mcpBG;
}

void LoseScene::Update()
{
	mcpCursol->Update();
	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Update();
	}

	//! コマンド
	//! コンティニュー
	if (Commands[0]->Selected()) {
		SoundMgr->PlaySE(SE_Select01);
		SceneMgr->ChageScene(GameMgr->GetNowStage(), true);		
	}
	//! リタイヤ
	if (Commands[1]->Selected()) {	
		SoundMgr->PlaySE(SE_Select01);
		SceneMgr->ChageScene(Scene_StageSelect, true);
	}

}

void LoseScene::Draw()
{
	mcpBG->Draw();
	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Draw();
	}
	mcpCursol->Draw();
}
