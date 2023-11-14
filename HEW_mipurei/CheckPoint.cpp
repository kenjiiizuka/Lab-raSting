#include "CheckPoint.h"
#include "TextureManager.h"
#include "SoundManager.h"

CheackPoint::CheackPoint()
{
	mcpAnimsprite->SetTexture(TEXTURE(Tex_CheackPoint));
	mcpAnimsprite->SetAnimtionTable(10,1);
	mcpAnimsprite->SetStopAnimation(true);
	mcpAnimsprite->SetXSplit(9);
	
	mcpBox = new Box(mcVec, msSize.x, msSize.y);
	msSize.x = 0.4f;
	msSize.y = 0.4f;
	mcpShape = mcpBox;
	Check = false;
}

CheackPoint::~CheackPoint()
{
	delete mcpBox;
}

void CheackPoint::Update()
{
	//! チェックフラグが立ったらエフェクト等をいれたり、画像をかえる
	if (Check) {
		if (!Sound) {
			Sound = true;
			SoundMgr->PlaySE(SE_CheackPoint,0.2f);
		}
		mcpAnimsprite->SetStopAnimation(false);
		if (mcpAnimsprite->GetCurrentXSplit() == 0) {
			mcpAnimsprite->SetStopAnimation(true);
			
		}
	}
}

void CheackPoint::HitCheckPoint()
{
	Check = true;
}

bool CheackPoint::GetCheck()
{
	return Check;
}

Box * CheackPoint::GetBox()
{
	return mcpBox;
}


