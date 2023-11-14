#pragma once
#include "BaseScene.h"
#include"BoxObject.h"
#include"Cursol.h"
#include"Command.h"
#include<vector>
using namespace std;
class ClearScene :
	public BaseScene
{
public:
	ClearScene();
	~ClearScene();
	void Update();
	void Draw();
private:
	BoxObject* BackObj;
	BoxObject* LogoObj;
	ID3D11ShaderResourceView* BackTex;
	ID3D11ShaderResourceView* LogoTex;

	Cursol * mcpCursol;              //! �J�[�\��
	Command * mcpCommand;            //! �R�}���h
	std::vector<Command *> Commands; //! �R�}���h���i�[����z��

};
