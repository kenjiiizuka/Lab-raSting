#pragma once
#include "BaseScene.h"
#include "BoxObject.h"
#include "Cursol.h"
class DebugScene :
	public BaseScene
{
public:
	DebugScene();
	~DebugScene();

	void Update();
	void Draw();
private:
	BoxObject * obj[5];
	Cursol * mcpCursol;
};

