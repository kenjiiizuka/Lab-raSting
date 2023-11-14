#include "EnemyManager.h"
#include <fstream>
#include <sstream>
#include "EnemyID.h"
#include "WinMain.h"
#include "Collision.h"

//! �R�X�g���N�^
EnemyManager::EnemyManager(string _filename, Player & _player, Map & _map)
	: mcPlayer(_player), mcMap(_map)
{
	//! �G�̈ʒu�����������t�@�C���𐶐�
	ifstream EnemyFile(_filename);
	if (!EnemyFile) {
		int hiraketenaiyo = 100;
	}

	string tmp;
	int num;
	//! �G�̐���ǂݍ���
	//! �z�[�_�[�̓ǂݍ���
	getline(EnemyFile, tmp, ',');
	stringstream Hooder(tmp);
	Hooder >> num;
	mcpHooder = new SoftEnemy[num];
	//! �G�l�~�[�̔z��ɒǉ�
	for (int i = 0; i < num; i++) {
		Enemies.emplace_back(&mcpHooder[i]);
	}

	//! �`���s���[ZK�̐���
	getline(EnemyFile, tmp, ',');
	stringstream Tinpiller(tmp);
	Tinpiller >> num;
	//! �`���s���[�̐���
	mcpTinpiller = new NormalEnemy[num];
	//! �G�l�~�[�̔z��ɒǉ�
	for (int i = 0; i < num; i++) {
		Enemies.emplace_back(&mcpTinpiller[i]);
	}

	//! �X�v���b�^�[�̐���
	//! �G�̐���ǂݍ���
	getline(EnemyFile, tmp, ',');
	stringstream Splitter(tmp);
	Splitter >> SplitterNum;
	mcpSplitter = new SplitLowerEnemy[SplitterNum];

	//! �E���p�[�̐���
	getline(EnemyFile, tmp, ',');
	stringstream Unper(tmp);
	Unper >> num;

	//! �A�E���p�[�̐���
	getline(EnemyFile, tmp, ',');
	stringstream Aunper(tmp);
	Aunper >> num;
	mcpAunper = new BaseDrone[num];
	for (int i = 0; i < num; i++) {
		Enemies.emplace_back(&mcpAunper[i]);
	}

	//! �t�H�[�h��̐���
	getline(EnemyFile, tmp, ',');
	stringstream frodon(tmp);
	frodon >> FordonNum;
	mcpFordon = new Fordon[FordonNum];
	for (int i = 0; i < FordonNum; i++) {
		Enemies.emplace_back(&mcpFordon[i]);
	}

	////! �`���s���[SL�̐���
	//getline(EnemyFile, tmp, ',');
	//stringstream TimpillerSL(tmp);
	//TimpillerSL >> num;

	////! �G7�̐���
	//getline(EnemyFile, tmp, ',');
	//stringstream Enemy7(tmp);
	//Enemy7 >> num;

	eEnemyID ID;               //! ID
	Vector2 pos;               //! ���W
	EnemyIndex Index = { 0 };  //! �Y����
	getline(EnemyFile, tmp);   //! �t�@�C���̎��̍s�ɍs��
	//getline(EnemyFile, tmp);
	//! �X�v���b�^�[�𑫂�������
	int EnemyNum = Enemies.size() + SplitterNum;
	for (int i = 0; i < EnemyNum; i++) {
		//! ID�̎擾
		getline(EnemyFile, tmp, ',');
		stringstream EnemyID(tmp);
		int work;
		EnemyID >> work;
		//! �f�[�^�`�F�b�N
		if (work == -1) {
			i--;
			continue;
		}
		ID = (eEnemyID)work;
		//! X,Y���W�̓ǂݍ���
		getline(EnemyFile, tmp, ',');
		stringstream tmpX(tmp);
		tmpX >> pos.x;
		getline(EnemyFile, tmp, ',');
		stringstream tmpY(tmp);
		tmpY >> pos.y;
		pos.x -= DRAW_WIDTH * 0.5f - 0.1f;
		pos.y -= DRAW_HEIGHT * 0.5f - 0.1f;
		//! �G�̎�ނɉ����āA���W���Z�b�g����
		stringstream HaveEnemyID;
		stringstream Menber;
		switch (ID) {
		case Enemy_Hooder:
			mcpHooder[Index.Hooder].SetVec(pos);
			mcpHooder[Index.Hooder].SetPlayer(&mcPlayer);
			Index.Hooder++;
			break;

		case Enemy_TinpillarZK:
			mcpTinpiller[Index.Tinpiller].SetVec(pos);
			mcpTinpiller[Index.Tinpiller].SetPlayer(&mcPlayer);
			Index.Tinpiller++;
			break;

		case Enemy_Splitter:
			mcpSplitter[Index.Splitter].SetInitVec(pos);
			mcpSplitter[Index.Splitter].SetPlayer(&mcPlayer);
			Index.Splitter++;
			break;

		case Enemy_Aunper:
			mcpAunper[Index.Aunper].SetVec(pos);
			mcpAunper[Index.Aunper].SetPlayer(&mcPlayer);
			//! �t�@�C������ǂ̓G�����̂���ǂݎ��
			getline(EnemyFile, tmp, ',');
			HaveEnemyID << tmp;
			int work;
			eEnemyID HaveID;
			HaveEnemyID >> work;
			HaveID = (eEnemyID)work;

			if (HaveID == Enemy_Hooder) {
				mcpAunper[Index.Aunper].SetEnemy(&mcpHooder[Index.Hooder - 1]);
			}
			else if (HaveID == Enemy_TinpillarZK) {
				mcpAunper[Index.Aunper].SetEnemy(&mcpTinpiller[Index.Tinpiller - 1]);
			}
			else if (HaveID == Enemy_Splitter) {
				mcpAunper[Index.Aunper].SetEnemy(&mcpSplitter[Index.Splitter - 1]);
			}
			Index.Aunper++;
			break;

		case Enemy_Fordon:	
			mcpFordon[Index.Fodon].SetPlayer(&mcPlayer);
			getline(EnemyFile, tmp, ',');
			int Num;
			Menber << tmp;
			Menber >> Num;
			mcpFordon[Index.Fodon].CreateMenber(Num);
			mcpFordon[Index.Fodon].SetInitVec(pos);
			Index.Fodon++;
			break;
		}		
	}
	EnemyFile.close();
}

//! �f�X�g���N�^
EnemyManager::~EnemyManager()
{
	//! �e�G�̃f���[�g
	delete[] mcpTinpiller;
	delete[] mcpSplitter;
	delete[] mcpHooder;
	delete[] mcpAunper;
	delete[] mcpFordon;
	Enemies.clear(); //! �z�񂩂�v�f����������
}

/* -----------
// �X�V���� */
void EnemyManager::Update()
{
	float CheackX = 0; //! �����W���`���b�N���ĉ�ʓ��ɖ��炩�ɉ�����Ώ��������Ȃ�
	bool Charge = false;
	for (int i = 0; i < Enemies.size(); i++) {	
		Enemies[i]->Update();
		Charge = Enemies[i]->GetDeath();
		if (Charge) {
			mcPlayer.AddElect();
		}
	}
	//! �X�v���b�^�[�̍X�V����
	for (int i = 0; i < SplitterNum; i++) {	
		mcpSplitter[i].Update();
		Charge = mcpSplitter[i].GetDeath();
		if (Charge) {
			mcPlayer.AddElect();
		}		
	}
}

/* -------------------------
// �����蔻���̍X�V���� */
void EnemyManager::LastUpdate()
{
	for (int i = 0; i < Enemies.size(); i++) {	
		Enemies[i]->LastUpdate();		
	}
	//! �X�v���b�^�[�̍X�V����
	for (int i = 0; i < SplitterNum; i++) {	
		mcpSplitter[i].LastUpdate();			
	}
}

/* -----------------
// �����蔻�菈�� */
void EnemyManager::CollisionUpdate()
{
	TailReaction Reaction; //! �U�������Ă�ꂽ���Ƀv���C���[�ɓn�����A�N�V����
	float CheackX;


	//! �v���C���[�̑ѓd�̏�Ԃ��擾����
	bool Elect = mcPlayer.GetCharge();

	//! �v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < Enemies.size(); i++) {
		if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *Enemies[i]->GetBoxCol())) {
			//! �v���C���[�ւ̃_���[�W����
			//! �v���C���[�����ɂ��鎞
			if (mcPlayer.GetVec().x < Enemies[i]->GetVec().x) {
				mcPlayer.SetDamege(Left);
			}
			else {
				mcPlayer.SetDamege(Right);
			}
			Enemies[i]->SetHitPlayer(true);
		}
		else {
			Enemies[i]->SetHitPlayer(false);
		}

		//! Map�Ƃ̓����蔻�菈��
		if (Enemies[i]->GetTag() != ObjectTag::Tag_Drone) {
			if (mcMap.CollisionUpdate(Enemies[i])) {
				Enemies[i]->SetTouchGround(true);
			}
			else {
				Enemies[i]->SetTouchGround(false);
			}
		}
		//! �v���C���[�̍U���Ƃ̓����蔻��
		//! �ѓd��
		if (Elect) {
			for (int h = 0; h < 2; h++) {
				if (Collision::Box_Circle_Hit(*Enemies[i]->GetBoxCol(), mcPlayer.GetSpearCol(h))) {
					Reaction = Enemies[i]->SetStingPower(mcPlayer.GetStingPower(), Elect);		//! false �̂Ƃ���͑ѓd���
					if (mcPlayer.GetVec().x < Enemies[i]->GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
			}
		}
		//! �ʏ�
		else {
			if (Collision::Box_Circle_Hit(*Enemies[i]->GetBoxCol(), *mcPlayer.GetAttackCol())) {
				Reaction = Enemies[i]->SetStingPower(mcPlayer.GetStingPower(), false);		//! false �̂Ƃ���͑ѓd���
				if (mcPlayer.GetVec().x < Enemies[i]->GetVec().x) {
					mcPlayer.SetReaction(Reaction, Left);
				}
				else {
					mcPlayer.SetReaction(Reaction, Right);
				}
			}
		}
	}

	//! �G���m�̓����蔻��
	for (int j = 0; j < Enemies.size(); j++) {
		for (int k = 0; k < Enemies.size(); k++) {
			if (j != k) { //! ���g���m�œ����蔻������Ȃ��悤�ɂ��Ă���
				if (Enemies[j]->GetTag() != Tag_Drone && Enemies[k]->GetTag() != Tag_Drone) { //! �h���[���͓����蔻����Ƃ�Ȃ�
					Collision::Box_Box_Collision(*Enemies[j]->GetBoxCol(), *Enemies[k]->GetBoxCol());
				}
			}
		}
	}

	//! �X�v���b�^�[�̓����蔻��
	for (int l = 0; l < SplitterNum; l++) {
		SplitUpperEnemy & Upper = *mcpSplitter[l].GetUpperEnemy();
		//! �X�v���b�^�[�ƃv���C���[�̓����蔻��
		if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *mcpSplitter[l].GetBoxCol())) {
			if (mcPlayer.GetVec().x < mcpSplitter[l].GetVec().x) {
				mcPlayer.SetDamege(Left);
			}
			else {
				mcPlayer.SetDamege(Right);
			}
			//! ��x����������v���C���[��Ǐ]���Ȃ�
			mcpSplitter[l].SetFollow(false);
		}

		if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *Upper.GetBoxCol())) {
			if (mcPlayer.GetVec().x < Upper.GetVec().x) {
				mcPlayer.SetDamege(Left);
			}
			else {
				mcPlayer.SetDamege(Right);
			}
		}

		//! �X�v���b�^�[��Map�̓����蔻��
		//! ��
		CheackX = mcpSplitter[l].GetVec().x;	
		if (mcMap.CollisionUpdate(&mcpSplitter[l])) {
			mcpSplitter[l].SetTouchGround(true);
		}
		else {
			mcpSplitter[l].SetTouchGround(false);
		}
		//! ��
		Box * Up = Upper.GetBoxCol();
		if (mcMap.CollisionUpdate(&Upper)) {
			Upper.SetTouchGround(true);
		}
		else {
			Upper.SetTouchGround(false);
		}
		//}
		//! �v���C���[�Ƃ̍U���̓����蔻��
		if (Elect) {
			//! ��
			for (int z = 0; z < 2; z++) {
				if (Collision::Box_Circle_Hit(*mcpSplitter[l].GetBoxCol(), mcPlayer.GetSpearCol(z))) {
					Reaction = mcpSplitter[l].SetStingPower(mcPlayer.GetStingPower(), Elect);		//! false �̂Ƃ���͑ѓd���
					if (mcPlayer.GetVec().x < mcpSplitter[l].GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
				//! ��
				if (Collision::Box_Circle_Hit(*Upper.GetBoxCol(), mcPlayer.GetSpearCol(z))) {
					Reaction = Upper.SetStingPower(mcPlayer.GetStingPower(), Elect);		//! false �̂Ƃ���͑ѓd���
					if (mcPlayer.GetVec().x < Upper.GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
			}
		}
		else {
			//! ���i�����O�͑S�́j
			if (Collision::Box_Circle_Hit(*mcpSplitter[l].GetBoxCol(), *mcPlayer.GetAttackCol())) {
				Reaction = mcpSplitter[l].SetStingPower(mcPlayer.GetStingPower(), false);	//! false �̂Ƃ���͑ѓd���
				if (mcPlayer.GetVec().x < mcpSplitter[l].GetVec().x) {
					mcPlayer.SetReaction(Reaction, Left);
				}
				else {
					mcPlayer.SetReaction(Reaction, Right);
				}
			}
			//! ��
			if (Collision::Box_Circle_Hit(*Upper.GetBoxCol(), *mcPlayer.GetAttackCol())) {
				Reaction = Upper.SetStingPower(mcPlayer.GetStingPower(), false);		//! false �̂Ƃ���͑ѓd���
				if (mcPlayer.GetVec().x < Upper.GetVec().x) {
					mcPlayer.SetReaction(Reaction, Left);
				}
				else {
					mcPlayer.SetReaction(Reaction, Right);
				}
			}
		}
		//! �X�v���b�^�[�Ƒ��̓G�Ƃ̓����蔻��
		for (int m = 0; m < Enemies.size(); m++) {
			Collision::Box_Box_Collision(*mcpSplitter[l].GetBoxCol(),*Enemies[m]->GetBoxCol());
			Collision::Box_Box_Collision(*Upper.GetBoxCol(), *Enemies[m]->GetBoxCol());
		}
	}

	//! �t�H�[�h���̃����o�[�̓����蔻�蓖���蔻��
	for (int l = 0; l < FordonNum; l++) {
		int MenberNum = mcpFordon[l].GetNumMenber();
		for (int r = 0; r < MenberNum; r++) {
			//! �����o�[�̎擾
			Fordon * Member = mcpFordon[l].GetMenber(r);

			//! �}�b�v�Ƃ̓����蔻��
			//! Map�Ƃ̓����蔻�菈��
			if (mcMap.CollisionUpdate(Member)) {
				Member->SetTouchGround(true);
			}
			else {
				Member->SetTouchGround(false);
			}

			//! �v���C���[�Ƃ̓����蔻��
			if (Collision::Box_Box_Collision(*mcPlayer.GetBoxCol(), *Member->GetBoxCol())) {
				Member->SetTouchGround(true);
				//! �v���C���[�ւ̃_���[�W����
				//! �v���C���[�����ɂ��鎞
				if (mcPlayer.GetVec().x < Member->GetVec().x) {
					mcPlayer.SetDamege(Left);
				}
				else {
					mcPlayer.SetDamege(Right);
				}
				Member->SetHitPlayer(true);
			}
			else {
				Member->SetHitPlayer(false);
			}

			//! �v���C���[�̍U���Ƃ̓����蔻��
			if (Elect) {
				for (int g = 0; g < 2; g++) {
					if (Collision::Box_Circle_Hit(*Member->GetBoxCol(), mcPlayer.GetSpearCol(g))) {
						Reaction = Member->SetStingPower(mcPlayer.GetStingPower(), false);		//! false �̂Ƃ���͑ѓd���
						if (mcPlayer.GetVec().x < Member->GetVec().x) {
							mcPlayer.SetReaction(Reaction, Left);
						}
						else {
							mcPlayer.SetReaction(Reaction, Right);
						}
					}
				}
			}
			else {
				if (Collision::Box_Circle_Hit(*Member->GetBoxCol(), *mcPlayer.GetAttackCol())) {
					Reaction = Member->SetStingPower(mcPlayer.GetStingPower(), false);		//! false �̂Ƃ���͑ѓd���
					if (mcPlayer.GetVec().x < Member->GetVec().x) {
						mcPlayer.SetReaction(Reaction, Left);
					}
					else {
						mcPlayer.SetReaction(Reaction, Right);
					}
				}
			}
		}
	}
}

/* -----------
// �`�揈�� */
void EnemyManager::Draw()
{
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i]->Draw();
	}
	//! �X�v���b�^�[�̍X�V����
	for (int i = 0; i < SplitterNum; i++) {
		mcpSplitter[i].Draw();
	}
}

void EnemyManager::AddX(float _x)
{
	Vector2 pos;
	for (int i = 0; i < Enemies.size(); i++) {
		pos = Enemies[i]->GetVec();
		Enemies[i]->SetVec(Vector2(pos.x +_x, pos.y));
		if (Enemies[i]->GetTag() == Tag_Fordon) {
			((Fordon*)Enemies[i])->SetInitVec(Vector2(pos.x + _x, pos.y));
		}
	}
	//! �X�v���b�^�[�̍X�V����
	for (int i = 0; i < SplitterNum; i++) {
		pos = mcpSplitter[i].GetVec();
		mcpSplitter[i].SetVec(Vector2(pos.x + _x, pos.y));
	}
}
