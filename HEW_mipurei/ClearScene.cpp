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
	//! �z��ɑ��
	for (int i = 0; i < 2; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);
		//! ��Ԗڂ̃R�}���h�̈ʒu
		if (i == 0) {
			Commands[i]->SetVec(Vector2(0.0f, 0.0f));
		}
		//! ��Ԗڈڍs�̃R�}���h�̍��W�����߂�
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
	Commands.clear(); //! �R�}���h�̔z��̃N���A
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
	//�w�i�`��
	//BackObj->Draw();
	//LogoObj->Draw();

	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Draw();
	}
	mcpCursol->Draw();
}
