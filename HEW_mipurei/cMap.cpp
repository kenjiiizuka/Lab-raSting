#include "cMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Camerah.h"
#include "Collision.h"
#include "WinMain.h"
#include "eMapTag.h"
#include "WinMain.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EffectManager.h"

using namespace std;


//! �R���X�g���N�^
Map::Map(string _filename, string _itemfile, ID3D11ShaderResourceView * _maptiptex)
{
	ActivItem = false;
	DrawBg = false;

	//! �ϐ��̏����l�ݒ�
	msScale = { 1.0f,1.0f };
	msTipSize = { 0.2f,0.2f };

	Vector2 SetBGPos(-DRAW_WIDTH,0);
	
	//! �ŉ��̃��C���[
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<StaticObject> bg01(new StaticObject);
		bg01.get()->SetCameraActiv(false);
		bg01.get()->GetSprite()->SetTexture(TEXTURE(Tex_StageBG01));
		bg01.get()->SetSize(DRAW_WIDTH + 0.04, DRAW_HEIGHT);
		bg01.get()->SetVec(SetBGPos);
		SetBGPos.x += DRAW_WIDTH;
		BG01.emplace_back(move(bg01));
	}

	//! ����
	SetBGPos = Vector2(-DRAW_WIDTH, 0);
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<StaticObject> bg02(new StaticObject);
		bg02.get()->SetCameraActiv(false);
		bg02.get()->GetSprite()->SetTexture(TEXTURE(Tex_StageBG02));
		bg02.get()->SetSize(DRAW_WIDTH + 0.04, DRAW_HEIGHT);
		bg02.get()->SetVec(SetBGPos);
		SetBGPos.x += DRAW_WIDTH;
		BG02.emplace_back(move(bg02));
	}

	//! ��O
	SetBGPos = Vector2(-DRAW_WIDTH, 0);
	for (int i = 0; i < 3; i++) {
		std::unique_ptr<StaticObject> bg03(new StaticObject);
		bg03.get()->SetCameraActiv(false);
		bg03.get()->GetSprite()->SetTexture(TEXTURE(Tex_StageBG03));
		bg03.get()->SetSize(DRAW_WIDTH + 0.04, DRAW_HEIGHT);
		bg03.get()->SetVec(SetBGPos);
		SetBGPos.x += DRAW_WIDTH;
		BG03.emplace_back(move(bg03));
	}

	mcpMapTip = new StaticObject;
	mcpMapTip->SetSize(0.21f, 0.2f);
	mcpMapTip->SetCameraActiv(false);
	mcpMapTip->GetSprite()->SetTexture(_maptiptex);


	//! �t�@�C���I�[�v��
	ifstream MapFile(_filename);
	if (!MapFile)	{
		MessageBox(NULL, L"�t�@�C���I�[�v�����s", L"�G���[����", MB_OK);
	}
	// �t�@�C���f�[�^��ǂݎ�� �}�b�v�̏c���̏��
	string tmp;
	getline(MapFile,tmp);
	getline(MapFile, tmp, ',');
	stringstream Sizex(tmp);
	Sizex >> mTipNumX;
	getline(MapFile, tmp, ',');
	stringstream Sizey(tmp);
	Sizey >> mTipNumY;
	getline(MapFile, tmp, ',');
	stringstream Splitx(tmp);
	Splitx >> mSplitx;
	getline(MapFile, tmp, ',');
	stringstream Splity(tmp);
	Splity >> mSplity;

	// �}�b�v�̏����i�[����2�����z��𐶐�����
	mspMaptip = new MapTip*[mTipNumY];
	for (int num = 0; num < mTipNumY; num++)	{
		mspMaptip[num] = new MapTip[mTipNumX];
	}

	//! �z��̒��g������������
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			mspMaptip[i][j].Number = 0; //! 
			mspMaptip[i][j].Tag = 0;    //!
			mspMaptip[i][j].mcPos = 0;  //! 
		}
	}

	// �z��Ƀ}�b�v�̏�������
	int dataCheack = 0; // �ǂݎ�����f�[�^���`�F�b�N���邽�߂̕ϐ�

	// �z��̃T�C�Y���ǂݍ���
	for (int i = 0; i < mTipNumY; i++)	{
		for (int j = 0; j < mTipNumX; j++)
		{
			getline(MapFile, tmp, ','); // �J���}��؂�œǂݍ���
			stringstream Iteminf(tmp);
			// �ǂݍ��񂾒l���`�F�b�N����
			Iteminf >> dataCheack;
			if (dataCheack == -1){
				j--;
				continue;
			}
			// �`�F�b�N���Ė��Ȃ���Δz��ɑ������
			mspMaptip[i][j].Number = dataCheack;
		}
	}

	//! �}�b�v�ɒu���A�C�e��
	mspItem = new MapTip*[mTipNumY];
	for (int num = 0; num < mTipNumY; num++) {
		mspItem[num] = new MapTip[mTipNumX];
	}

	//! �z��̒��g������������
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			mspItem[i][j].Number = 0; //! 
			mspItem[i][j].Tag = 0;    //!
			mspItem[i][j].mcPos = 0;  //! 
		}
	}

	//! �A�C�e���`��p�I�u�W�F�N�g�̐���
	mcpItem = new AnimationHitObject;
	mcpItem->GetAnimSprite()->SetTexture(TEXTURE(Tex_MapItem01));
	mcpItem->GetAnimSprite()->SetAnimtionTable(4, 1);
	mcpItem->SetCameraActiv(false);
	mcpItem->GetAnimSprite()->SetAnimSpeed(120);
	//! �t�@�C���I�[�v��
	ifstream ItemFile(_itemfile);
	if (!ItemFile) {
		//MessageBox(NULL, L"�t�@�C���I�[�v�����s", L"�G���[����", MB_OK);
	}

	// �z��̃T�C�Y���ǂݍ���
	getline(ItemFile, tmp);
	getline(ItemFile, tmp, ',');
	getline(ItemFile, tmp, ',');
	getline(ItemFile, tmp, ','); 
	getline(ItemFile, tmp, ',');
	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++)	{
			getline(ItemFile, tmp, ','); // �J���}��؂�œǂݍ���
			stringstream mapinf(tmp);
			// �ǂݍ��񂾒l���`�F�b�N����
			mapinf >> dataCheack;
			if (dataCheack == -1) {
				j--;
				continue;
			}
			// �`�F�b�N���Ė��Ȃ���Δz��ɑ������
			mspItem[i][j].Number = dataCheack;
		}
	}

	//! ����Map�̑傫����ݒ�
	mcMapSize.x = msTipSize.x * mTipNumX;
	mcMapSize.y = msTipSize.y * mTipNumY;
	//! �X�e�[�W�̍�������ʂ̍����ɂȂ�悤�ɂ���
	mcPos.x = (mcMapSize.x / 2.0f) - 2.02f;
	mcPos.y = (mcMapSize.y / 2.0f) - 1.0f - msTipSize.y * 0.5f;
	Effflg = false;
}

//! �f�X�g���N�^
Map::~Map()
{
	for (int num = 0; num < mTipNumY; num++) {
		delete[] mspMaptip[num];
		delete[] mspItem[num];
	}
	delete[] mspItem;
	delete[] mspMaptip;
	delete mcpMapTip;
	delete mcpItem;	
}

//! �X�V����
//! �J�����ɃX�e�[�W�O���f��Ȃ��悤�ɂ��Ă��܂�
void Map::Update()
{
	CAMERA->MoveDown(true);
	CAMERA->MoveLeft(true);
	CAMERA->MoveTop(true);
	CAMERA->MoveRight(true);

	//! �}�b�v�̈ړ������̈ʒu �����_�̌덷���Ȃ������߂ɕϐ��ɂ��Ă���
	float LeftLimit = -DRAW_WIDTH / 2 - msTipSize.x / 2 - 0.002f;
	float RightLimit = DRAW_WIDTH / 2 + msTipSize.x / 2;
	float TopLimit = DRAW_HEIGHT / 2 + msTipSize.y / 2;
	float BottomLimit = -DRAW_HEIGHT / 2 - msTipSize.y / 2;
	//! ���[��-DRAW_WIDTH���E�ɂ�������J�����Ɉړ�����߂Ă��炤
	if (mspMaptip[0][0].mcPos.x >= LeftLimit) {
		CAMERA->MoveLeft(false);
	}
	//! �E�[��DRAW_WIDTH��荶�ɂ����Ă���ړ�����߂Ă��炤
	else if (mspMaptip[0][mTipNumX - 1].mcPos.x <= RightLimit) {
		CAMERA->MoveRight(false);
	}
	//! �オDRAW_HEIGHT��艺�ɂ����Ă���ړ�����߂Ă��炤
	if (mspMaptip[0][0].mcPos.y <= TopLimit) {
		CAMERA->MoveTop(false);
	}
	//! ����-DRAW_HEIGHT����ɂ����Ă���ړ�����߂Ă��炤
	else if (mspMaptip[mTipNumY - 1][0].mcPos.y >= BottomLimit) {
		CAMERA->MoveDown(false);
	}

	//! �w�i�̈ړ�
	BgUpdate(BG01[0].get(), BG01[1].get(), BG01[2].get(), 0.4f);
	BgUpdate(BG02[0].get(), BG02[1].get(), BG02[2].get(), 0.6f);
	BgUpdate(BG03[0].get(), BG03[1].get(), BG03[2].get(), 0.8f);

}

//**************************************************************************
//! �J�����̊g��k�������ۂɒ��S�̈ʒu������Ă���̂ł����̏C�����܂����܂�
void Map::Draw()
{
	Vector2 CameraMove = CAMERA->GetCameraMove();	
	mcPos += CameraMove;
	msScale = CAMERA->GetScale();
	Vector2 StandardPos = { (-mcMapSize.x * msScale.x) / 2 , (mcMapSize.y * msScale.y) / 2 }; // �`��ʒu�̌v�Z�̊�ƂȂ���W ����Map�̍���
	
	
	for (int i = 0; i < 3; i++) {
		BG01[i].get()->Draw();
	}

	for (int i = 0; i < 3; i++) {
		BG02[i].get()->Draw();
		
	}
	for (int i = 0; i < 3; i++) {	
		BG03[i].get()->Draw();
	}

	Vector2 TipPos;
	//! ����̂݃}�b�v�̃`�b�v�̈ʒu���v�Z
	
	if (first) {
		for (int i = 0; i < mTipNumY; i++) {
			TipPos.y = (StandardPos.y - (i * (msTipSize.y * msScale.y))) + mcPos.y;
			for (int j = 0; j < mTipNumX; j++)
			{
				//! ����̎��͍��W���v�Z����
				if (j == 0 && i == 0) {
					float x = (StandardPos.x + (j * (msTipSize.x * msScale.x))) + mcPos.x;
					mspMaptip[i][j].mcPos.x = x;
				}
				//! ��ԏ�̒i�ō��[�ł͂Ȃ��Ƃ�
				else if (i == 0) {
					//! ���ƂȂ�̃}�b�v�`�b�v�̈ʒu����T�C�Y�����炷
					mspMaptip[i][j].mcPos.x = mspMaptip[i][j - 1].mcPos.x + msTipSize.x;
				}
				//! ��i�ڈڍs��1�i�ڂ̍��W����
				else {
					mspMaptip[i][j].mcPos.x = mspMaptip[0][j].mcPos.x;
				}
				mspMaptip[i][j].mcPos.y = TipPos.y;

				//! �A�C�e���̍��W�ɑ��
				mspItem[i][j].mcPos = mspMaptip[i][j].mcPos;
			}
		}
		first = false;
	}

	for (int i = 0; i < mTipNumY; i++) {
		for (int j = 0; j < mTipNumX; j++) {
			//! �`��
			mspMaptip[i][j].mcPos += CameraMove;
			mcpMapTip->SetVec(mspMaptip[i][j].mcPos);
			mcpMapTip->GetSprite()->SetUVSpriteInf(mspMaptip[i][j].Number, mSplitx, mSplity);
			mcpMapTip->Draw();
			//! �A�C�e���̕`��	
			if (ActivItem) {		
				if (mspItem[i][j].Number != 0) {
					mspItem[i][j].mcPos = mspMaptip[i][j].mcPos;
					mcpItem->SetVec(mspItem[i][j].mcPos);
					mcpItem->Draw();
					mspItem[i][j].Drawed = true;
				}
			}
		}
	}	
}

//! ���W�̃Z�b�^�[
void Map::SetPos(Vector2 _pos)
{
	mcPos.x = _pos.x;
	mcPos.y = _pos.y;
}

//! �����蔻��̍X�V����
bool Map::CollisionUpdate(Character * _char)
{	
	return Collision(_char);
}


//! ���g���C�Ȃǂ������Ƃ���Map�������ʒu�ɖ߂��֐�
void Map::ResetMap()
{
	//! �X�e�[�W�̍�������ʂ̍����ɂȂ�悤�ɂ���
	mcPos.x = (mcMapSize.x / 2.0f) - 2.02f;
	mcPos.y = (mcMapSize.y / 2.0f) - 1.0f - msTipSize.y * 0.5f;
}

//! �w�i�̕`������邩���Ȃ���
void Map::SetDrawBg(bool _state)
{
	DrawBg = _state;
}

Vector2 Map::GetPos()
{
	return mcPos;
}

//! Map�ƃL�����N�^�[�Ƃ̓����蔻������n�ʂɓ������Ă��邩��Ԃ��֐�
//! �߂�l : �n�ʂɓ������Ă��邩
bool Map::Collision(Character * _char)
{	
	bool HitGround = false;
	Effflg = true;
	for (int num1 = 0; num1 < mTipNumY; num1++)
	{
		for (int num2 = 0; num2 < mTipNumX; num2++)
		{
			//! �^�O���݂Ă���ɉ���������������
			switch (mspMaptip[num1][num2].Tag)
			{			
			case Tag_Ground:

				//! �^�O���v���C���[�Ȃ炵���ۂ̍U���Ƃ̓����蔻������
				if (_char->GetTag() == Tag_Player) {
					if (Collision::Tail_Map(*((Player *)_char)->GetAttackCol(), msTipSize.x, msTipSize.y, mspMaptip[num1][num2].mcPos)) {
						((Player *)_char)->SetReaction(TailReaction::TailReaction_Stop, Direction_None);
						Vector2 pos = ((Player *)_char)->GetTail()->GetVec();
						if (Effflg) {
							EffMgr->PlayEffect(Hibana, pos.x, pos.y,0.2f,0.2f);
							Effflg = false;
						}
					}					
				}
				if (Collision::Box_BoxMap(*_char->GetBoxCol(), msTipSize.x, msTipSize.y, mspMaptip[num1][num2].mcPos)) {
					HitGround =  true; //! �n�ʂɓ������Ă��邩�̃t���O
				}	
				break;	
			}

			//! �^�O���݂Ă���ɉ���������������
			switch (mspItem[num1][num2].Number)
			{
			case 1:
				//! �v���C���[�Ȃ�Item�Ƃ̓����蔻����Ƃ蓖�����Ă�����`�����߂�
				if (mspItem[num1][num2].Drawed) {
					if (_char->GetTag() == Tag_Player) {
						if (Collision::Box_MapItem(*_char->GetBoxCol(), msTipSize.x, msTipSize.y, mspItem[num1][num2].mcPos)) {
							mspItem[num1][num2].Number = 0;
							((Player *)_char)->AddBoruto();
							SoundMgr->PlaySE(SE_Item,0.4f);
						}
						//! �A�C�e���ƐK���Ƃ̓����蔻��
						if (Collision::Circle_MapItem(*((Player *)_char)->GetAttackCol(), msTipSize.x, msTipSize.y, mspItem[num1][num2].mcPos)) {
							mspItem[num1][num2].Number = 0;
							((Player *)_char)->AddBoruto();
							SoundMgr->PlaySE(SE_Item,0.4f);
						}
					}
				}
				break;
			}
		}
	}
	return HitGround;
}

void Map::BgUpdate(StaticObject * Left, StaticObject * center, StaticObject * Right, float _speed)
{
	//! �w�i�̈ړ�
	Vector2 SetBGPos;
	if (center->GetVec().x <= -DRAW_WIDTH) {
		center->SetVec(Vector2(0, 0));
		SetBGPos = Vector2(center->GetVec().x + DRAW_WIDTH, center->GetVec().y);
		Right->SetVec(SetBGPos);
		SetBGPos = Vector2(center->GetVec().x - DRAW_WIDTH, center->GetVec().y);
		Left->SetVec(SetBGPos);
	}
	else if (center->GetVec().x >= DRAW_WIDTH) {
		center->SetVec(Vector2(0, 0));
		SetBGPos = Vector2(center->GetVec().x + DRAW_WIDTH, center->GetVec().y);
		Right->SetVec(SetBGPos);
		SetBGPos = Vector2(center->GetVec().x - DRAW_WIDTH, center->GetVec().y);
		Left->SetVec(SetBGPos);
	}

	Vector2 CameraMove = CAMERA->GetCameraMove();
	//! �J�����̈ړ����x�̔�����������
	Vector2 pos = center->GetVec();
	center->SetVec(Vector2(pos.x + CameraMove.x * _speed, 0));
	
	pos = Left->GetVec();
	Left->SetVec(Vector2(pos.x + CameraMove.x * _speed, 0));

	pos = Right->GetVec();
	Right->SetVec(Vector2(pos.x + CameraMove.x * _speed, 0));
}
