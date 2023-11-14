#pragma once
#include "BaseScene.h"
#include"Cursol.h"
#include"Command.h"
#include "StaticObject.h"
#include<vector>
class LoseScene :
	public BaseScene
{
public:
	LoseScene();
	~LoseScene();
	void Update();
	void Draw();
private:
	StaticObject * mcpBG;               //! �w�i
	Cursol * mcpCursol;              //! �J�[�\��
	Command * mcpCommand;            //! �R�}���h
	std::vector<Command *> Commands; //! �R�}���h���i�[����z��
};

