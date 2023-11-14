#include "TitleScene.h"
#include "Controller.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "DirectInput8.h"
#include "WinMain.h"
#include "Collision.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "StaticObject.h"

//! �R���X�g���N�^
TitleScene::TitleScene()
{
	Tag = Scene_Title;

	

	mcpCursol = new Cursol();
	mcpWindow = new Window(mcpCursol);
	mcpTitleBg = new StaticObject;
	if (GameMgr->GemeClear()) {
		mcpTitleBg->GetSprite()->SetTexture(TEXTURE(Tex_TitleBg02));
	}
	else {
		mcpTitleBg->GetSprite()->SetTexture(TEXTURE(Tex_TitleBg));
	}
	mcpTitleBg->SetSize(DRAW_WIDTH,DRAW_HEIGHT);
	

	mcpCommand = new Command[2];
	mcpCommand[0].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Title_Game));
	mcpCommand[1].GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Title_End));

	for (int C = 0; C < 2; C++)
	{
		mcpCommand[C].SetSize(0.4f, 0.2f);
		mcpCommand[C].GetFrame()->SetSize(0.7f, 0.25f);
		mcpCommand[C].GetFrame()->GetAnimSprite()->SetTexture(TEXTURE(Tex_CommmandOpen02));
		mcpCommand[C].GetFrame()->GetAnimSprite()->SetNoStopObj(false);
		mcpCommand[C].GetFrame()->GetAnimSprite()->SetStopAnimation(true);
	}

	first = true;

	//! �z��ɑ��
	for (int i = 0; i < 2; i++) {
		Commands.emplace_back(&mcpCommand[i]);
		Commands[i]->SetCursol(mcpCursol);
		//! ��Ԗڂ̃R�}���h�̈ʒu
		if (i == 0) {
			Commands[i]->SetVec(Vector2(-0.5f, -0.7f));
		}
		//! ��Ԗڈڍs�̃R�}���h�̍��W�����߂�
		else {
			Commands[i]->SetVec(Vector2(0.5f, -0.7f));
		}
	}
	
	SoundMgr->PlaySE(SE_Pause,0.5f);

	DrawCommand = CommandClose = Winflg = false;
}

//! �f�X�g���N�^
TitleScene::~TitleScene()
{
	delete mcpWindow;
	delete[] mcpCommand;
	delete mcpTitleBg;
	Commands.clear(); //! �R�}���h�̔z��̃N���A
	delete mcpCursol;
	EffMgr->Reset();
	SoundMgr->StopBGM();
}

//! �X�V����
void TitleScene::Update()
{
	//! �R�}���h
	//! �R���e�B�j���[	
	if (first) {
		SoundMgr->PlayBGM(BGM_Titel, 0.11f);
		mcpCommand[0].GetFrame()->GetAnimSprite()->SetStopAnimation(false);
		mcpCommand[1].GetFrame()->GetAnimSprite()->SetStopAnimation(false);
		first = false;
	}

	if (!Winflg) 
	{
		DrawCommand = true;
		for (int i = 0; i < Commands.size(); i++) {
			Commands[i]->SetClose(CommandClose);
			Commands[i]->Update();	
		}
		
		if (Commands[0]->Selected()) {
			SoundMgr->PlaySE(SE_Select01,0.7f);
			if (GameMgr->GetFirst()) {
				//! 1-1�̃`���[�g���A������J�n
				SceneMgr->ChageScene(Scene_1_1, true);
				GameMgr->SetThutrial(true);
			}
			else {
				SceneMgr->ChageScene(Scene_StageSelect, true);
			}
		}
		//! ���^�C��
		if (Commands[1]->Selected()) {

			SoundMgr->PlaySE(SE_Select01, 0.7f);
			Winflg = true;
			
		}
	}
	if (Winflg)
	{
		mcpWindow->Update();
	}

	mcpCursol->Update();

}

//! �`�揈��
void TitleScene::Draw()
{

	//mcpTitleBg->Draw();
	mcpTitleBg->Draw();
		if (!Winflg)
		{

			
			for (int i = 0; i < Commands.size(); i++) {
				Commands[i]->Draw();
			}
		}
		else
		{
			mcpWindow->Draw();
		}
	
	
	
	mcpCursol->Draw();
}

void TitleScene::CollisionUpdate()
{
}

