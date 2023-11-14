#include "ClearScene.h"
#include"TextureManager.h"
#include"Controller.h"
#include"SoundManager.h"

ClearScene::ClearScene()
{
	BackObj = new BoxObject();
	LogoObj = new BoxObject();
	LoadTexture(L"assets/TestClearBack.png", &BackTex);
	LoadTexture(L"assets/ClearLogo.png", &LogoTex);

	//BackObj->GetAnimSprite()->SetTexture(BackTex);
	//BackObj->GetAnimSprite()->SetAnimtionTable(1, 1);
	//BackObj->GetAnimSprite()->SetTexture(BackTex);
	//BackObj->SetSize(4.0f,3.0f);
	//LogoObj->GetAnimSprite()->SetTexture(LogoTex);
	//LogoObj->GetAnimSprite()->SetAnimtionTable(1, 1);
	//LogoObj->GetAnimSprite()->SetTexture(LogoTex);
	//LogoObj->SetSize(1.0f, 1.0f);


	mcpCursol = new Cursol;
	mcpCommand = new Command[2];
	mcpCommand[0].GetAnimSprite()->SetTexture(BackTex);
	mcpCommand[1].GetAnimSprite()->SetTexture(LogoTex);
	//! 配列に代入
	for (int i = 0; i < 2; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);
		//! 一番目のコマンドの位置
		if (i == 0) {
			Commands[i]->SetVec(Vector2(0.0f, 0.0f));
		}
		//! 二番目移行のコマンドの座標を決める
		else {
			Commands[i]->SetVec(Commands[i - 1]->GetNextCommandPos());
		}
	}

	SoundMgr->PlaySE(SE_Pause);
}

ClearScene::~ClearScene()
{
	COM_SAFE_RELEASE(LogoTex);
	COM_SAFE_RELEASE(BackTex);
	delete LogoObj;
	delete BackObj;

	delete[] mcpCommand;
	Commands.clear(); //! コマンドの配列のクリア
	delete mcpCursol;
}

void ClearScene::Update()
{
	mcpCursol->Update();

	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Update();
	}
}

void ClearScene::Draw()
{
	//背景描画
	//BackObj->Draw();
	//LogoObj->Draw();

	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Draw();
	}
	mcpCursol->Draw();
}
