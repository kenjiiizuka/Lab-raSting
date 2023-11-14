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
	Cursol * mcpCursol;              //! カーソル
	Command * mcpCommand;            //! コマンド
	std::vector<Command *> Commands; //! コマンドを格納する配列
	std::unique_ptr<AnimationHitObject> upBg;
	std::unique_ptr<StaticObject>   Controller;
	bool Open;                //! ポーズのオープンフラグ
	bool Close;              //! クローズフラグ
	bool CommandClose;       //! コマンドのクローズフラグ
	bool DrawCommand;		 //! コマンドの描画フラグ
	bool DrawCursol;
};