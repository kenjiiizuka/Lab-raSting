#include "Window.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Box.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "Game.h"

Window::Window(Cursol * cursol)
{
	mcpCursol = cursol;
	mcpCommand = new Command;
	mcpNCommand = new Command;
	
	mcpWindowBg = new StaticObject;
	mcpWindowBg->GetSprite()->SetTexture(TEXTURE(Tex_Window));
	mcpWindowBg->SetSize(Vector2(1.0f, 0.6f));
	mcpWindowBg->SetPos(0.0f, -0.05f);
	mcpCommand->SetSize(0.2f, 0.1f);
	mcpNCommand->SetSize(0.3f, 0.1f);
	mcpCommand->GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_Yes));
	mcpNCommand->GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_No));

	//! �w�i�̉摜�̃Z�b�g
	upBg.reset(new AnimationHitObject);
	AnimationSprite * BgSp = upBg->GetAnimSprite();
	upBg->SetSize(1.92f, 1.0f);
	BgSp->SetNoStopObj(true);
	BgSp->SetTexture(TEXTURE(Tex_Pause_Bg01));
	BgSp->SetAnimSpeed(2);
	BgSp->SetAnimtionTable(11, 1);
	upBg->SetCameraActiv(false);

	//! ���Z�b�g�@���W�@�J�[�\���@�摜		
	mcpCommand->SetVec(Vector2(-0.3f, -0.2f));
	mcpCommand->GetFrame()->SetSize(0.5f, 0.2f);
	mcpCommand->SetCursol(mcpCursol);
	Commands.emplace_back(mcpCommand);
	
	mcpNCommand->SetVec(Vector2(0.3f, -0.2f));
	mcpNCommand->GetFrame()->SetSize(0.5f, 0.2f);
	mcpNCommand->SetCursol(mcpCursol);
	Commands.emplace_back(mcpNCommand);
	
	SoundMgr->PlaySE(SE_Pause);

	DrawCursol = DrawCommand = CommandClose = Close = false;
	Open = true;
}

Window::~Window()
{	
	delete mcpCommand;
	delete mcpNCommand;
	delete mcpWindowBg;
	Commands.clear(); //! �R�}���h�̔z��̃N���A	
}

void Window::Update()
{
	//!�@�w�i�I�u�W�F�N�g�̃A�j���[�V�����X�v���C�g���擾
	AnimationSprite * BgSp = upBg->GetAnimSprite();

	int AnimX = BgSp->GetCurrentXSplit();
	//! �J���Ƃ��̏���	
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


	//! �R�}���h���`�悳��Ă���I�ׂ�悤�ɂ���
	if (DrawCommand) {
		//! �R�}���h
		//! �R���e�B�j���[
		if (mcpCommand->Selected()) {
			SoundMgr->PlaySE(SE_Select01);
			GameIns->SetActiv(false);
		}
		//! �R�}���h
	//! �������������ꂽ�Ƃ�
		if (mcpNCommand->Selected()) {
			SoundMgr->PlaySE(SE_Select01);
			SceneMgr->ChageScene(Scene_Title, true);
		}
	}
	
	for (int i = 0; i < Commands.size(); i++) {
		Commands[i]->Update();
	}
}

void Window::Draw()
{
	upBg->Draw();
	//mcpWindowBg->Draw();
	if (DrawCommand) {
		for (int i = 0; i < Commands.size(); i++) {
			Commands[i]->Draw();
		}
	}
	if (DrawCursol) {
		mcpCursol->Draw();
	}
}

void Window::CollisionUpdate()
{
}
