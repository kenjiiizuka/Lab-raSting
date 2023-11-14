#pragma once
#include "BaseScene.h"
#include "Cursol.h"
#include "Command.h"
#include "StaticObject.h"
#include <vector>
#include <memory>

class PauseScene :
	public BaseScene
{
public:
	PauseScene();
	~PauseScene();

	void Update();
	void Draw();
	
private:  
	void CollisionUpdate();
	Cursol * mcpCursol;              //! �J�[�\��
	Command * mcpCommand;            //! �R�}���h
	std::vector<Command *> Commands; //! �R�}���h���i�[����z��
	std::unique_ptr<AnimationHitObject> upBg;
	std::unique_ptr<StaticObject>   Controller;
	bool Open;                //! �|�[�Y�̃I�[�v���t���O
	bool Close;              //! �N���[�Y�t���O
	bool CommandClose;       //! �R�}���h�̃N���[�Y�t���O
	bool DrawCommand;		 //! �R�}���h�̕`��t���O
	bool DrawCursol;
};