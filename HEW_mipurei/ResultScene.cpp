#include "ResultScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Input.h"
#include"SoundManager.h"

// コンストラクタ
ResultScene::ResultScene()
{
	BackObj = new BoxObject();
	LoadTexture(L"assets/TestResultBack.png", &BackTex);
	mcpCursol = new Cursol;
	mcpCommand = new Command[1];
	mcpCommand[0].GetAnimSprite()->SetTexture(BackTex);
	//! 配列に代入
	for (int i = 0; i < 1; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);
		//! 一番目のコマンドの位置
		if (i == 0) {
			Commands[i]->SetVec(Vector2(-0.0f, 0.0f));
		}
		//! 二番目移行のコマンドの座標を決める
		else {
			Commands[i]->SetVec(Commands[i - 1]->GetNextCommandPos());
		}
	}

	SoundMgr->PlaySE(SE_Pause,0.06f);
}

// デストラクタ
ResultScene::~ResultScene()
{
	//delete mcpImage;
	delete[] mcpCommand;
	Commands.clear(); //! コマンドの配列のクリア
	delete mcpCursol;
}

// 更新処理
void ResultScene::Update()
{
	if (In->GetKeyTrigger(VK_RETURN)) {
		SceneMgr->ChageScene(Scene_Title, true);
	}
	mcpCursol->Update();

	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Update();
	}
}

// 描画処理
void ResultScene::Draw()
{
	//mcpImage->DrawSprite(0, 0.7f, 0.6f, 0.3f, TexMgr->GetTextuer(Tex_Result));
	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Draw();
	}
	mcpCursol->Draw();
}
