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
	// resultシーン内で使う関数、変数を宣言してください
	BoxObject* BackObj;
	ID3D11ShaderResourceView* BackTex;

	Cursol * mcpCursol;              //! カーソル
	Command * mcpCommand;            //! コマンド
	std::vector<Command *> Commands; //! コマンドを格納する配列
};

