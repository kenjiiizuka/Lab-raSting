#include "GameScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Input.h"

//! �R���X�g���N�^
GameScene::GameScene()
{
	mcpImage = new Image;
}

//! �f�X�g���N�^
GameScene::~GameScene()
{
	delete mcpImage;
}

//! �X�V����
void GameScene::Update()
{
	if (In->GetKeyTrigger(VK_RETURN)) {
		SceneMgr->ChageScene(Scene_Result, true);
	}
}

//! �`�揈��
void GameScene::Draw()
{
	mcpImage->DrawSprite(0, 0.7f, 0.6f, 0.3f, TexMgr->GetTextuer(Tex_Game));
}
