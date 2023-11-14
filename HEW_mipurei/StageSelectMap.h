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
	void AddX(float _x); //! X�����ɂ��炷
	bool CollisionUpdate(Character * _chra);
	Vector2 GetDoorPos(int _num); //! �w�肵���h�A�̍��W���擾


private:	
	StageDoor * mcpDoorTutorial;
	StageDoor * mcpDoor1_1; 
	StageDoor * mcpDoor1_2;
	StageDoor * mcpDoor1_3;
	StageDoor * mcpDoor1_4;
	StageDoor * mcpDoor1_5;

	bool ClearState[5]; //! ���݂̃X�e�[�W�̃N���A��

	std::vector<StageDoor *>Door;
};

