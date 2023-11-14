#pragma once
#include "cMap.h"
#include "StageDoor.h"
#include <vector>

class StageSelectMap_1 :
	public Map
{
public:
	StageSelectMap_1(std::string _filename, std::string _Itemfile, ID3D11ShaderResourceView* _maptiptex);
	~StageSelectMap_1();

	void Update();
	void Draw();
	void AddX(float _x); //! X方向にずらす
	bool CollisionUpdate(Character * _chra);
	Vector2 GetDoorPos(int _num); //! 指定したドアの座標を取得


private:	
	StageDoor * mcpDoorTutorial;
	StageDoor * mcpDoor1_1; 
	StageDoor * mcpDoor1_2;
	StageDoor * mcpDoor1_3;
	StageDoor * mcpDoor1_4;
	StageDoor * mcpDoor1_5;

	bool ClearState[5]; //! 現在のステージのクリア状況

	std::vector<StageDoor *>Door;
};

