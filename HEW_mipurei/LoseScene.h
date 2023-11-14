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
	StaticObject * mcpBG;               //! 背景
	Cursol * mcpCursol;              //! カーソル
	Command * mcpCommand;            //! コマンド
	std::vector<Command *> Commands; //! コマンドを格納する配列
};

