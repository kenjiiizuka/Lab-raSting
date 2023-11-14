#include "GameScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Input.h"

//! コンストラクタ
GameScene::GameScene()
{
	mcpImage = new Image;
}

//! デストラクタ
GameScene::~GameScene()
{
	delete mcpImage;
}

//! 更新処理
void GameScene::Update()
{
	if (In->GetKeyTrigger(VK_RETURN)) {
		SceneMgr->ChageScene(Scene_Result, true);
	}
}

//! 描画処理
void GameScene::Draw()
{
	mcpImage->DrawSprite(0, 0.7f, 0.6f, 0.3f, TexMgr->GetTextuer(Tex_Game));
}
