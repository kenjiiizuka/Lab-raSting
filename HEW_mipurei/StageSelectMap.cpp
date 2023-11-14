#include "StageSelectMap.h"
#include "eMapTag.h"
#include "TextureManager.h"
#include "Collision.h"
#include "SceneManager.h"
#include "Controller.h"
#include "GameManager.h"
#include "GameManager.h"


//! コンストラクタ
StageSelectMap_1::StageSelectMap_1(std::string _filename, std::string _Itemfile, ID3D11ShaderResourceView* _maptiptex)
	: Map(_filename,_Itemfile,_maptiptex)
{
	DrawBg = false;
	//! マップチップにタグをセットする
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			if (mspMaptip[i][j].Number == 25 || mspMaptip[i][j].Number == 19 || mspMaptip[i][j].Number == 30
				|| mspMaptip[i][j].Number == 31 || mspMaptip[i][j].Number == 32) {
				mspMaptip[i][j].Tag = Tag_Ground;
			}
		}
	}
	//! ステージの左下が画面の左下になるようにする
	mcPos.x = (mcMapSize.x / 2.0f) - 2.0f;
	mcPos.y = (mcMapSize.y / 2.0f) - 1.0f - msTipSize.y * 0.5f;
	//! ステージに行くドアの生成

	//! 現在のステージのクリア状況の取得
	for (int i = 0; i < 5; i++) {
		ClearState[i] = GameMgr->GetStageClearState(eStage(i));
	}

	//! チュートリアル
	mcpDoorTutorial = new StageDoor;
	mcpDoorTutorial->GetAnimSprite()->SetTexture(TexMgr->GetTextuer(Tex_StageDoor02));
	Door.emplace_back(mcpDoorTutorial);
	mcpDoorTutorial->SetVec(Vector2(-1.5f, -0.61f));
	mcpDoorTutorial->SetSize(0.6f, 0.6f);
	mcpDoorTutorial->SetColSize(0.1f, 0.1f);
	//! 1-1
	mcpDoor1_1 = new StageDoor;
	Door.emplace_back(mcpDoor1_1);
	mcpDoor1_1->SetVec(Vector2(-0.7f, -0.527f));
	if (ClearState[Stage_1_1])  {
		mcpDoor1_1->GetAnimSprite()->SetTexture(TEXTURE(Tex_StageDoor02));
	}
	//! 1-2
	mcpDoor1_2 = new StageDoor;
	Door.emplace_back(mcpDoor1_2);
	mcpDoor1_2->SetVec(Vector2(0.3f, -0.527f));
	if (!ClearState[Stage_1_1]) {
		mcpDoor1_2->GetAnimSprite()->SetColor(0.5f, 0.5f, 0.5f);
	}
	if(ClearState[Stage_1_2]){
		mcpDoor1_2->GetAnimSprite()->SetTexture(TEXTURE(Tex_StageDoor02));
	}
	//! 1-3
	mcpDoor1_3 = new StageDoor;
	mcpDoor1_3->SetVec(Vector2(1.3f, -0.527f));
	Door.emplace_back(mcpDoor1_3);
	if (!ClearState[Stage_1_2]) {
		mcpDoor1_3->GetAnimSprite()->SetColor(0.5f, 0.5f, 0.5f);
	}
	if (ClearState[Stage_1_3]) {
		mcpDoor1_3->GetAnimSprite()->SetTexture(TEXTURE(Tex_StageDoor02));
	}
	//! 1-4
	mcpDoor1_4 = new StageDoor;
	mcpDoor1_4->SetVec(Vector2(2.3f, -0.527f));
	Door.emplace_back(mcpDoor1_4);
	if (!ClearState[Stage_1_3]) {
		mcpDoor1_4->GetAnimSprite()->SetColor(0.5f, 0.5f, 0.5f);
	}
	if (ClearState[Stage_1_4]) {
		mcpDoor1_4->GetAnimSprite()->SetTexture(TEXTURE(Tex_StageDoor02));
	}
	//! 1-5
	mcpDoor1_5 = new StageDoor;
	mcpDoor1_5->GetAnimSprite()->SetTexture(TEXTURE(Tex_BossDoor));
	mcpDoor1_5->SetVec(Vector2(3.3f, -0.527f));
	if (!ClearState[Stage_1_4]) {
		mcpDoor1_5->GetAnimSprite()->SetColor(0.5f, 0.25f, 0.5f);
	}
	if (ClearState[Stage_1_5]){
		mcpDoor1_5->GetAnimSprite()->SetTexture(TEXTURE(Tex_StageDoor02));
	}
	Door.emplace_back(mcpDoor1_5);

	for (int i = 0; i < BG01.size(); i++) {
		BG01[i].get()->GetSprite()->SetColor(0.5f, 0.5f, 0.5f);
		BG03[i].get()->GetSprite()->SetColor(0.5f, 0.5f, 0.5f);
	}
}

//! デストラクタ
StageSelectMap_1::~StageSelectMap_1()
{

//	delete mcpDoor1_1;
	for (int i = 0; i < Door.size(); i++) {
		delete Door[i];
	}
	Door.clear();
}

//! 更新処理
void StageSelectMap_1::Update()
{
	for (int i = 0; i < 3; i++) {
		BG01[i].get()->Draw();
	}

	for (int i = 0; i < 3; i++) {
		BG03[i].get()->Draw();
	}
	Map::Update();
	for (int i = 0; i < Door.size(); i ++) {
		Door[i]->Update();
	}

	if (GetControllerButtonTrigger(Button_A)) {
		if (mcpDoor1_1->GetHit()) {
			SceneMgr->ChageScene(Scene_1_1,true); //! ステージ1_1に行く
			GameMgr->SetThutrial(false);
		}
		else if(mcpDoor1_2->GetHit()){
			SceneMgr->ChageScene(Scene_1_2, true);
		}

		else if (mcpDoor1_3->GetHit()) {
			SceneMgr->ChageScene(Scene_1_3, true);
		}

		else if (mcpDoorTutorial->GetHit()) {
			SceneMgr->ChageScene(Scene_1_1, true);
			GameMgr->SetThutrial(true); //! チュートリアルから開始
		}

		else if (mcpDoor1_4->GetHit()) {
			SceneMgr->ChageScene(Scene_1_4, true);	
		}

		else if (mcpDoor1_5->GetHit()) {
			SceneMgr->ChageScene(Scene_1_5, true);		
		}	
	}
}

//! 描画
void StageSelectMap_1::Draw()
{
	Map::Draw();
	for (int i = 0; i < Door.size(); i++) {
		Door[i]->Draw();
	}
}

void StageSelectMap_1::AddX(float _x)
{
	mcPos.x += _x;
	Vector2 pos(mcpDoor1_1->GetVec().x + _x, -0.527f);
	mcpDoor1_1->SetVec(pos);
	pos.x += 1.0f;
	mcpDoor1_2->SetVec(pos);
	pos.x += 1.0f;
	mcpDoor1_3->SetVec(pos);
	pos.x += 1.0f;
	mcpDoor1_4->SetVec(pos);
	pos.x += 1.0f;
	mcpDoor1_5->SetVec(pos);

	pos = Vector2(mcpDoorTutorial->GetVec().x + _x, -0.61f);
	mcpDoorTutorial->SetVec(pos);
}

//! 当たり判定
bool StageSelectMap_1::CollisionUpdate(Character * _char)
{
	int Stages[eStage::Stage_Max]; //! ステージのタグの番号のを入れる配列
	for (int i = 0; i < Stage_Max; i++) {
		Stages[i] = i;
	}

	
	//! チュートリアルの扉
	if (BBH(*_char->GetBoxCol(), *mcpDoorTutorial->GetBoxCol())) {
		mcpDoorTutorial->SetHit(true);
	}
	else {
		mcpDoorTutorial->SetHit(false);
	}

	//! 1-1の扉
	if (BBH(*_char->GetBoxCol(), *mcpDoor1_1->GetBoxCol())) {
		mcpDoor1_1->SetHit(true);
	}
	else {
		mcpDoor1_1->SetHit(false);
	}

	//! 1-2の扉
	if (GameMgr->GetStageClearState(Stage_1_1)) {
		if (BBH(*_char->GetBoxCol(),*mcpDoor1_2->GetBoxCol())) {
			mcpDoor1_2->SetHit(true);
		}
		else {
			mcpDoor1_2->SetHit(false);
		}
	}

	//! 1-3の扉
	if (GameMgr->GetStageClearState(Stage_1_2)) {
		if (BBH(*_char->GetBoxCol(), *mcpDoor1_3->GetBoxCol())) {
			mcpDoor1_3->SetHit(true);
		}
		else {
			mcpDoor1_3->SetHit(false);
		}
	}

	//! 1-4の扉
	if (GameMgr->GetStageClearState(Stage_1_3)) {
		if (BBH(*_char->GetBoxCol(), *mcpDoor1_4->GetBoxCol())) {
			mcpDoor1_4->SetHit(true);
		}
		else {
			mcpDoor1_4->SetHit(false);
		}
	}

	//! 1-5の扉
	if (GameMgr->GetStageClearState(Stage_1_4)) {
		if (BBH(*_char->GetBoxCol(), *mcpDoor1_5->GetBoxCol())) {
			mcpDoor1_5->SetHit(true);
		}
		else {
			mcpDoor1_5->SetHit(false);
		}
	}

	return Map::Collision(_char);
}

Vector2 StageSelectMap_1::GetDoorPos(int _num)
{
	if (_num == 1) {
		return mcpDoor1_1->GetVec();
	}
	else if (_num == 2) {
		return mcpDoor1_2->GetVec();
	}
	else if (_num == 3) {
		return mcpDoor1_3->GetVec();
	}
	else if (_num == 4) {
		return mcpDoor1_4->GetVec();
	}
	return mcpDoor1_5->GetVec();
}
