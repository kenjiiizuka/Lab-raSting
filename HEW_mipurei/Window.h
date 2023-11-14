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
	Cursol * mcpCursol;              //! カーソル
	Command * mcpCommand;            //! コマンド
	Command * mcpNCommand;
	std::vector<Command *> Commands; //! コマンドを格納する配列
	std::unique_ptr<AnimationHitObject> upBg;
	StaticObject * mcpWindowBg;

	bool Open;                //! ポーズのオープンフラグ
	bool Close;              //! クローズフラグ
	bool CommandClose;       //! コマンドのクローズフラグ
	bool DrawCommand;		 //! コマンドの描画フラグ
	bool DrawCursol;
};

