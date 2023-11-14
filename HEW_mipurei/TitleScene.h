#pragma once
#include "Image.h"
#include "BaseScene.h"
#include "Cursol.h"
#include "Command.h"
#include "Window.h"
#include <vector>

//! �^�C�g���V�[���N���X
//! ���̃Q�[���^�C�g���V�[���̏���������N���X

/* ===================================
** TitleScene�N���X�@�@�@�@�@�@     **�@�@
** �^�C�g���V�[���̏��������܂�     **
** ����� :  kita                   **
** ================================ */


class TitleScene :
	public BaseScene
{

	bool Winflg;
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	//! TitleScene���Ŏg���֐��A�ϐ���錾���Ă�������
	void CollisionUpdate();
	Window * mcpWindow;
	Cursol * mcpCursol;              //! �J�[�\��
	Command * mcpCommand;            //! �R�}���h
	std::vector<Command *> Commands; //! �R�}���h���i�[����z��
	StaticObject * mcpTitleBg;

	bool first;
	bool CommandClose;       //! �R�}���h�̃N���[�Y�t���O
	bool DrawCommand;		 //! �R�}���h�̕`��t���O
};


