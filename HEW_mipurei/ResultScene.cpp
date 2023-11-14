#include "ResultScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Input.h"
#include"SoundManager.h"

// �R���X�g���N�^
ResultScene::ResultScene()
{
	BackObj = new BoxObject();
	LoadTexture(L"assets/TestResultBack.png", &BackTex);
	mcpCursol = new Cursol;
	mcpCommand = new Command[1];
	mcpCommand[0].GetAnimSprite()->SetTexture(BackTex);
	//! �z��ɑ��
	for (int i = 0; i < 1; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);
		//! ��Ԗڂ̃R�}���h�̈ʒu
		if (i == 0) {
			Commands[i]->SetVec(Vector2(-0.0f, 0.0f));
		}
		//! ��Ԗڈڍs�̃R�}���h�̍��W�����߂�
		else {
			Commands[i]->SetVec(Commands[i - 1]->GetNextCommandPos());
		}
	}

	SoundMgr->PlaySE(SE_Pause,0.06f);
}

// �f�X�g���N�^
ResultScene::~ResultScene()
{
	//delete mcpImage;
	delete[] mcpCommand;
	Commands.clear(); //! �R�}���h�̔z��̃N���A
	delete mcpCursol;
}

// �X�V����
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

// �`�揈��
void ResultScene::Draw()
{
	//mcpImage->DrawSprite(0, 0.7f, 0.6f, 0.3f, TexMgr->GetTextuer(Tex_Result));
	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Draw();
	}
	mcpCursol->Draw();
}
