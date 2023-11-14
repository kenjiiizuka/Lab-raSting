#pragma once
#include "BaseScene.h"
#include "Cursol.h"
#include "Command.h"
#include <vector>
#include <memory>
#include "StaticObject.h"

class Window
{
public:
	Window(Cursol * cursol);
	~Window();
	void Update();
	void Draw();

private:
	void CollisionUpdate();
	Cursol * mcpCursol;              //! �J�[�\��
	Command * mcpCommand;            //! �R�}���h
	Command * mcpNCommand;
	std::vector<Command *> Commands; //! �R�}���h���i�[����z��
	std::unique_ptr<AnimationHitObject> upBg;
	StaticObject * mcpWindowBg;

	bool Open;                //! �|�[�Y�̃I�[�v���t���O
	bool Close;              //! �N���[�Y�t���O
	bool CommandClose;       //! �R�}���h�̃N���[�Y�t���O
	bool DrawCommand;		 //! �R�}���h�̕`��t���O
	bool DrawCursol;
};

