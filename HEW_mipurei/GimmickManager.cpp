#include "GimmickManager.h"
#include "GimmickID.h"
#include "WinMain.h"
#include "Collision.h"
#include <fstream>
#include <sstream>
#include "Player.h"

using namespace std;

//! �R���X�g���N�^
GimmickManager::GimmickManager(std::string _filename)
{
	AllDyanmoIndex = 0;
	//!�t�@�C�����J��
	ifstream file(_filename);
	if (!file) {
		int okasiiyo = 12345;
	}

	string tmp; //! �t�@�C������ǂ݂Ƃ�������ϐ�
	int num;    //! ���̃M�~�b�N�̐�

	//! �@
	//! ���Ԃ̐���
	getline(file, tmp, ',');
	stringstream CheackPointNum(tmp);
	CheackPointNum >> Num.CheackPoint;
	mcpCheackPoint = new CheackPoint[Num.CheackPoint];


	//! �A
	//! ���d�@�̐���ǂݎ��
	getline(file,tmp,','); 
	stringstream DynamoNum(tmp);
	DynamoNum >> Num.Dynamo;
	mcpDynamo = new Dynamo[Num.Dynamo];
	//! �z��ɃZ�b�g
	for (int i = 0; i < Num.Dynamo; i++) {
		Dynamos.emplace_back(&mcpDynamo[i]);
	}

	//! �B
	//! ���锭�d�@�̐���ǂݎ��
	getline(file, tmp, ',');
	stringstream WeakDynamoNum(tmp);
	WeakDynamoNum >> Num.WeakDyanamo;
	mcpWeakDynamo = new WeakDynamo[Num.WeakDyanamo];
	//! �z��ɃZ�b�g
	for (int i = 0; i < Num.WeakDyanamo; i++) {
		Dynamos.emplace_back(&mcpWeakDynamo[i]);
	}

	//! �C
	//! �傫�ȃh�A�̐���
	getline(file, tmp, ',');
	stringstream BigDoorNum(tmp);
	BigDoorNum >> num;
	mcpBigDoor = new BigDoor[num];
	//! �z��ɒǉ�
	for (int i = 0; i < num; i++) {
		Gimmicks.emplace_back(&mcpBigDoor[i]);
	}
	
	//! �D
	//! �K���X�𐶐�
	getline(file, tmp, ',');
	stringstream GlassNum(tmp);
	GlassNum >> Num.Glass;
	mcpGlass = new BreakObj[Num.Glass];
	
	//! �E
	//! �v���X�@�̐���
	getline(file, tmp ,',');
	stringstream PressNum(tmp);
	PressNum >> Num.Press;
	mcpPress = new PressMachine[Num.Press];
	for (int i = 0; i < Num.Press; i++) {
		Gimmicks.emplace_back(&mcpPress[i]);
	}

	//! �S�[���̐���
	mcpGoal = new Goal;

	getline(file, tmp); //! ���s
	getline(file, tmp); //! ���s
	int AllGimmick = Gimmicks.size() + Num.Dynamo + Num.CheackPoint + Num.Glass + Num.WeakDyanamo + 1; //! ���d�@���܂߂��S�ẴM�~�b�N�̐�
	Vector2 pos;
	int work;
	GimmickID ID;
	GimmickIndex Index = { 0 };
	Dynamo * SetDynamo = nullptr;
	for (int i = 0; i < AllGimmick; i++) {
		//! ���d�@���Z�b�g����p�̕ϐ�
		
		getline(file, tmp, ',');
		stringstream Data(tmp);
		Data >> work;
		//! �f�[�^�`�F�b�N
		if (work == -1) {
			i--;
			continue;
		}
		ID = (GimmickID)work;    //! ID�̃Z�b�g
		getline(file, tmp, ',');
		stringstream x(tmp);
		x >> pos.x;              //! X���W�̃Z�b�g
		getline(file, tmp, ',');
		stringstream y(tmp);
		y >> pos.y;              //! Y���W�̃Z�b�g

		//! ���W�̏C��
		pos.x -= DRAW_WIDTH * 0.5f - 0.1f;
		pos.y -= DRAW_HEIGHT * 0.5f - 0.1f;
		switch (ID)
		{
		case GimmickID::GI_Dynamo:
			mcpDynamo[Index.Dynamo].SetVec(pos);
			SetDynamo = &mcpDynamo[Index.Dynamo];
			Index.Dynamo++;
			break;

		case GimmickID::GI_BigDoor:
			mcpBigDoor[Index.BigDoor].SetVec(pos);
			mcpBigDoor[Index.BigDoor].SetDynamo(SetDynamo); //! ���d�@�̃Z�b�g
			Index.BigDoor++;
			break;

		case GimmickID::GI_CheakPoint:
			mcpCheackPoint[Index.CheackPoint].SetVec(pos);
			CheackPos[Index.CheackPoint] = pos;
			Index.CheackPoint++;
			break;

		case GimmickID::GI_Glass:
			mcpGlass[Index.Glass].SetVec(pos);
			Index.Glass++;
			break;

		case GimmickID::GI_WeakDyanamo:
			mcpWeakDynamo[Index.WeakDyanamo].SetVec(pos);
			SetDynamo = &mcpWeakDynamo[Index.WeakDyanamo];
			Index.WeakDyanamo++;
			break;

		case GimmickID::GI_Goal:
			mcpGoal->SetVec(pos);

			break;
		case GimmickID::GI_Press:
			mcpPress[Index.Press].SetVec(pos);
			mcpPress[Index.Press].SetDynamo(SetDynamo);
			Index.Press++;
			break;
		default:
			break;
		}
	}
}

//! �f�X�g���N�^
GimmickManager::~GimmickManager()
{
	delete[] mcpDynamo;
	delete[] mcpBigDoor;
	delete[] mcpCheackPoint;
	delete[] mcpWeakDynamo;
	delete[] mcpPress;
	delete[] mcpGlass;

	delete mcpGoal;

	Dynamos.clear();
	Gimmicks.clear();
}


//! �X�V����
void GimmickManager::Update()
{
	//! ���d�@�̍X�V����	
	for (int i = 0; i < Dynamos.size(); i++) {
		Dynamos[i]->Update();
	}

	//! �M�~�b�N�̍X�V����
	for (int i = 0; i < Gimmicks.size(); i++) {
		Gimmicks[i]->Update();
	}

	//! ���ԃ|�C���g�̍X�V
	for (int i = 0; i < Num.CheackPoint; i++) {
		mcpCheackPoint[i].Update();
	}

	//! �K���X�̍X�V
	for (int i = 0; i < Num.Glass; i++) {
		mcpGlass[i].Update();
	}

	//! �S�[���̍X�V����
	mcpGoal->Update();
}

//! �����蔻�菈��
void GimmickManager::CollisionUpdate(Character * _char)
{
	TailReaction Reaction;

	//! �ѓd���Ă邩���m�F
	bool Elect = false;
	if (_char->GetTag() == Tag_Player) {
		Elect = ((Player *)_char)->GetCharge();
	}

	//! ���d�@�̓����蔻��
	for (int i = 0; i < Dynamos.size(); i++) {
		//Collision::Box_Box_Collision(*_char->GetBoxCol(), *Dynamos[i]->GetBoxCol());
		//! �K���Ƃ̓����蔻��
		if (_char->GetTag() == Tag_Player) {
			Player * player = ((Player *)_char);
			//! �ѓd���Ă�����
			if (Elect) {
				for (int spearcol = 0; spearcol < 2; spearcol++) {	
					if (BCH(*Dynamos[i]->GetBoxCol(), player->GetSpearCol(spearcol))) {
						//! �ア���d�@
						if (Dynamos[i]->GetTag() == Tag_WeakDynamo) {
							Reaction = Dynamos[i]->ReturnReaction(player->GetStingPower() ,Elect); // �h���З͂�n��
							player->GetTail()->SetReaction(Reaction, Direction_None);
							if (Reaction == TailReaction_StingDeep || Reaction == TailReaction_Sting) {
								player->GetTail()->SetStingObj(Dynamos[i]);
							}
							if (Reaction == TailReaction_StingStop) {
								Dynamos[i]->SetChrage(true);
							}
						}
						else {	
							player->GetTail()->SetReaction(TailReaction_StingStop, Direction_None);
							Dynamos[i]->SetChrage(true);
						}
					}	
				}
			}
			else {
				if (Collision::Box_Circle_Hit(*Dynamos[i]->GetBoxCol(), *player->GetAttackCol())) {
					Reaction = Dynamos[i]->ReturnReaction(player->GetStingPower(),Elect); // �h���З͂�n��
					player->GetTail()->SetReaction(Reaction, Direction_None);
					//! �h�����Ă�I�u�W�F�N�g�̃Z�b�g
					if (Reaction == TailReaction_StingDeep || Reaction == TailReaction_Sting) {
						player->GetTail()->SetStingObj(Dynamos[i]);
					}
				}
			}
		}
	}

	//! �M�~�b�N�̓����蔻��
	for (int j = 0; j < Gimmicks.size(); j++) {
		//! �v���X�@�͓�����̔��肾�����
		if (Gimmicks[j]->GetTag() == Tag_Press) {
			if (_char->GetTag() == Tag_Player) {
				bool Hit = BBH(*Gimmicks[j]->GetBoxCol(), *_char->GetBoxCol());
				if (Hit) {
					if (Gimmicks[j]->GetVec().x >= _char->GetVec().x) {
						((Player *)_char)->SetDamege(Left);
					}
					else {
						((Player *)_char)->SetDamege(Right);
					}
				}
			}
		}
		//! �v���X�@�Ƃ͏Փ˔�����Ƃ�Ȃ�
		else {
			Collision::Box_Box_Collision(*_char->GetBoxCol(), *Gimmicks[j]->GetBoxCol());
		}

		//! �K���Ƃ̓����蔻��
		if (_char->GetTag() == Tag_Player) {
			if (Collision::Box_Circle_Hit(*Gimmicks[j]->GetBoxCol(), *((Player *)_char)->GetAttackCol())) {
				((Player *)_char)->GetTail()->SetReaction(TailReaction_Stop, Direction_None);
			}
		}
	}

	//! ���ԃ|�C���g�̓����蔻��v���C���[�Ȃ�Ƃ�
	if (_char->GetTag() == Tag_Player) {
		for (int k = 0; k < Num.CheackPoint; k++) {
			if (Collision::Box_Box_Hit(*_char->GetBoxCol(), *mcpCheackPoint[k].GetBox())) {
				mcpCheackPoint[k].HitCheckPoint();
			}
		}
	}

	//! �K���X�Ƃ̓����蔻��
	for (int l = 0; l < Num.Glass; l++) {
		Collision::Box_Box_Collision(*mcpGlass[l].GetBoxCol(), *_char->GetBoxCol());
		//! �K���Ƃ̓����蔻��
		if (_char->GetTag() == Tag_Player) {
			if (Collision::Box_Circle_Hit(*mcpGlass[l].GetBoxCol(), *((Player *)_char)->GetAttackCol())) {
				Reaction = mcpGlass[l].ReturnReaction(((Player *)_char)->GetStingPower());
				((Player *)_char)->GetTail()->SetReaction(Reaction, Direction_None);
			}
		}
	}

	//! �v���C���[�Ƃ̓����蔻��
	if (_char->GetTag() == Tag_Player) {
		BBC(*mcpGoal->GetBoxCol(), *_char->GetBoxCol());
		if (Collision::Box_Circle_Hit(*mcpGoal->GetBoxCol(), *((Player *)_char)->GetAttackCol())) {
			Reaction = mcpGoal->ReturnReaction(((Player *)_char)->GetStingPower());
			//! �͂�����郊�A�N�V����
			if (mcpGoal->GetVec().x < _char->GetVec().x) { //! �E
				((Player *)_char)->GetTail()->SetReaction(Reaction, Right);
			}
			else {                                         //! ��
				((Player *)_char)->GetTail()->SetReaction(Reaction, Left);
			}
		}
	}
}

//! �`�揈��
void GimmickManager::Draw()
{	
	//! ���d�@�̍X�V����	
	for (int i = 0; i < Dynamos.size(); i++) {
		Dynamos[i]->Draw();
	}

	//! �M�~�b�N�̍X�V����
	for (int i = 0; i < Gimmicks.size(); i++) {
		Gimmicks[i]->Draw();
	}

	//! ���ԃ|�C���g�̍X�V
	for (int i = 0; i < Num.CheackPoint; i++) {
		mcpCheackPoint[i].Draw();
	}

	//! �K���X�̕`�揈��
	for (int i = 0; i < Num.Glass; i++) {
		mcpGlass[i].Draw();
	}

	mcpGoal->Draw();	
}

void GimmickManager::MoveX(float _x)
{
	Vector2 pos;
	if (mcpCheackPoint != nullptr) {
		pos = mcpCheackPoint[0].GetVec();
		mcpCheackPoint[0].SetVec(Vector2(pos.x + _x, pos.y));
	}
	if (Num.CheackPoint >= 2) {
		pos = mcpCheackPoint[1].GetVec();
		mcpCheackPoint[1].SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! ���d�@�̍��W�����炷
	for (int i = 0; i < Dynamos.size(); i++) {
		pos = Dynamos[i]->GetVec();
		Dynamos[i]->SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! �M�~�b�N�̍��W�����炷
	for (int j = 0; j < Gimmicks.size(); j++) {
		pos = Gimmicks[j]->GetVec();
		Gimmicks[j]->SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! �K���X�̈ʒu�����炷
	for (int k = 0; k < Num.Glass; k++) {
		pos = mcpGlass->GetVec();
		mcpGlass[k].SetVec(Vector2(pos.x + _x, pos.y));
	}

	//! �S�[���̈ʒu�����炷
	pos = mcpGoal->GetVec();
	mcpGoal->SetVec(Vector2(pos.x + _x, pos.y));
}

//! ���ԂɐG�ꂽ���ǂ�����Ԃ�
bool GimmickManager::GetCheackPointState()
{
	return	mcpCheackPoint[0].GetCheck();
}

//! �{�X�O�̒��ԂɐG�ꂽ���ǂ�����Ԃ�
bool GimmickManager::GetCheackPointBossState()
{
	//! �`�F�b�N�|�C���g�̐���2�ȏ�̂Ƃ��̂�
	if (Num.CheackPoint >= 2) {
		return mcpCheackPoint[1].GetCheck();
	}
	return false;
}

//! ���Ԃ̍��W�̃Q�b�^�[
Vector2 GimmickManager::GetCheackPointPos()
{
	return mcpCheackPoint[0].GetVec();
}

//! �{�X�O���Ԃ̍��W�̃Q�b�^�[
Vector2 GimmickManager::GetCheackPointBossPos()
{
	if (Num.CheackPoint >= 2) {
		return mcpCheackPoint[1].GetVec();
	}
	return Vector2(0, 0);
}

Goal * GimmickManager::GetGoalIns()
{
	return mcpGoal;
}

bool GimmickManager::GetGoal()
{
	return mcpGoal->GetGoal();
}
