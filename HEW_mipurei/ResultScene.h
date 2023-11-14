#pragma once
#include "BaseScene.h"
#include"BoxObject.h"
#include"Cursol.h"
#include"Command.h"
#include<vector>
class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	void Update();
	void Draw();
private:
	// result�V�[�����Ŏg���֐��A�ϐ���錾���Ă�������
	BoxObject* BackObj;
	ID3D11ShaderResourceView* BackTex;

	Cursol * mcpCursol;              //! �J�[�\��
	Command * mcpCommand;            //! �R�}���h
	std::vector<Command *> Commands; //! �R�}���h���i�[����z��
};

