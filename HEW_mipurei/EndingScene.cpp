#include "EndingScene.h"
#include "SceneManager.h"
#include "WinMain.h"
#include "Controller.h"
#include "SoundManager.h"
//! コンストラクタ
EndingScene::EndingScene()
{
	EndingMovie = new DrawMovei(L"assets/ending/ending ",1006,Vector2(DRAW_WIDTH,DRAW_HEIGHT));
	PlayBGM = false;
	FrameCnt = 0;
}

//! デストラクタ
EndingScene::~EndingScene()
{
	delete EndingMovie;
}

//! 更新処理
void EndingScene::Update()
{
	EndingMovie->StartMovei(4,Vector2(0,0));
	EndingMovie->Update();
	FrameCnt++;
	if (FrameCnt == 30) {
		PlayBGM = true;
	}

	if (PlayBGM) {
		SoundMgr->PlayBGM(BGM_Ending ,0.5f);
	}

	if (!EndingMovie->GetMoveiState()) {
		SceneMgr->ChageScene(Scene_Title,true);
		SoundMgr->StopBGM();
		PlayBGM = false;
	}

	//! メニューボタンでスキップ
	if (GetControllerButtonTrigger(Button_MENU)) {
		SceneMgr->ChageScene(Scene_Title, true);
		SoundMgr->StopBGM();
		PlayBGM = false;
	}
}

//! 描画処理
void EndingScene::Draw()
{
	EndingMovie->Draw();
}
