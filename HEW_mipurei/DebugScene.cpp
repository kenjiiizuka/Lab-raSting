#include "DebugScene.h"
#include "TextureManager.h"
#include "DirectInput8.h"
#include "WinMain.h"
#include "Collision.h"
#include "SceneManager.h"

//! コンストラクタ
DebugScene::DebugScene()
{
	mcpImage = new Image;

	mcpCursol = new Cursol();

	for (auto & o : obj) {
		o = new BoxObject;
	}
	obj[0]->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_Iizuka));
	obj[0]->SetVec(Vector2(-0.7f,0.4f));
	obj[0]->SetSize(0.7f,0.4f);
	obj[1]->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_Nakano));
	obj[1]->SetVec(Vector2(-0.7f, 0.0f));
	obj[1]->SetSize(0.7f, 0.3f);
	obj[2]->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_Kitauti));
	obj[2]->SetVec(Vector2(-0.7f, -0.4f));
	obj[2]->SetSize(0.7f, 0.3f);
	obj[3]->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_Game02));
	obj[3]->SetVec(Vector2(0.7f, 0.4f));
	obj[3]->SetSize(0.7f, 0.4f);
	obj[4]->GetSprite()->SetTexture(TexMgr->GetTextuer(Tex_Arufa));
	obj[4]->SetVec(Vector2(0.7f, 0.0f));
	obj[4]->SetSize(0.85f, 0.35f);


}

//! デストラクタ
DebugScene::~DebugScene()
{
	for (auto & o : obj) {
		delete o;
	}
}

void DebugScene::Update()
{

	Vector2 MouseVec = DI8->mDIMouse->GetMousePosVec();
	Shape ms(MouseVec);
	for (auto & o : obj) {
		o->Update();
	}

	Vector2 Cvec = mcpCursol->GetSelectPos();
	Shape cs(Cvec);
	if (Collision::Point_Box_Hit(cs, *obj[0]->GetBoxCol())) {
		obj[0]->SetSize(0.75f, 0.45f);	
		SceneMgr->ChageScene(Scene_kenjiDebug, true);	
	}
	else {
		obj[0]->SetSize(0.7f, 0.4f);
	}
	if (Collision::Point_Box_Hit(cs, *obj[1]->GetBoxCol())) {
		obj[1]->SetSize(0.75f, 0.35f);	
		SceneMgr->ChageScene(Scene_NakanoDebug, true);	
	}
	else {
		obj[1]->SetSize(0.7f, 0.3f);
	}
	if (Collision::Point_Box_Hit(cs, *obj[2]->GetBoxCol())) {
		obj[2]->SetSize(0.75f, 0.35f);	
		SceneMgr->ChageScene(Scene_1_3, true);
	}
	else {
		obj[2]->SetSize(0.7f, 0.3f);
	}
	if (Collision::Point_Box_Hit(cs, *obj[3]->GetBoxCol())) {
		obj[3]->SetSize(0.75f, 0.45f);
		SceneMgr->ChageScene(Scene_Title, true);	
	}
	else {
		obj[3]->SetSize(0.7f, 0.4f);
	}
	if (Collision::Point_Box_Hit(cs, *obj[4]->GetBoxCol())) {
		obj[4]->SetSize(0.80f, 0.40f);
		SceneMgr->ChageScene(Scene_Title, true);
	}
	else {
		obj[4]->SetSize(0.85f, 0.35f);
	}



	if (Collision::Point_Box_Hit(ms, *obj[0]->GetBoxCol())) {
		obj[0]->SetSize(0.75f, 0.45f);
		if (DI8->mDIMouse->GetMouseButtonTrigger(Mouse_LButton)) {
			SceneMgr->ChageScene(Scene_kenjiDebug, true);
		}
	}
	else {
		obj[0]->SetSize(0.7f, 0.4f);
	}
	if (Collision::Point_Box_Hit(ms, *obj[1]->GetBoxCol())) {
		obj[1]->SetSize(0.75f, 0.35f);
		if (DI8->mDIMouse->GetMouseButtonTrigger(Mouse_LButton)) {
			SceneMgr->ChageScene(Scene_NakanoDebug, true);
		}
	}
	else {
		obj[1]->SetSize(0.7f, 0.3f);
	}
	if (Collision::Point_Box_Hit(ms, *obj[2]->GetBoxCol())) {
		obj[2]->SetSize(0.75f, 0.35f);
		if (DI8->mDIMouse->GetMouseButtonTrigger(Mouse_LButton)) {
			SceneMgr->ChageScene(Scene_Title, true);
		}
	}
	else {
		obj[2]->SetSize(0.7f, 0.3f);
	}
	if (Collision::Point_Box_Hit(ms, *obj[3]->GetBoxCol())) {
		obj[3]->SetSize(0.75f, 0.45f);
		if (DI8->mDIMouse->GetMouseButtonTrigger(Mouse_LButton)) {
			SceneMgr->ChageScene(Scene_Title, true);
		}
	}
	else {
		obj[3]->SetSize(0.7f, 0.4f);
	}
	if (Collision::Point_Box_Hit(ms, *obj[4]->GetBoxCol())) {
		obj[4]->SetSize(0.80f, 0.40f);
		if (DI8->mDIMouse->GetMouseButtonTrigger(Mouse_LButton)) {
			SceneMgr->ChageScene(Scene_StageSelect, true);
		}
	}
	else {
		obj[4]->SetSize(0.85f, 0.35f);
	}
	
	mcpCursol->Update();	
}

void DebugScene::Draw()
{
	mcpImage->DrawSprite(0,0,DRAW_WIDTH,DRAW_HEIGHT,TexMgr->GetTextuer(Tex_debugBG01)); //! 背景の描画
	for (auto & o : obj) {
		o->Draw();
	}
	mcpCursol->Draw();
}
