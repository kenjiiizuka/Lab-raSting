#include "SelectCursol.h"
#include "Input.h"
#include "TextureManager.h"

#define CORRECTIONPOS 0.04f

// �R���X�g���N�^
// �����@�R�}���h�̐��@��ԏ�̃R�}���h�̒��S���W�@�R�}���h�ǂ����̊Ԋu  �R�}���h�̉���
SelectCursol::SelectCursol(int num, float xPos, float yPos, float Interval, float width)
{
	mSelectComand = 1; //���ݑI��ł���R�}���h  // ��ԏ�̑I�����P�@�ォ�珇��1,2,3....
	mNumComnd = num; // �R�}���h��������
	mInterval = Interval; // �R�}���h�̊Ԋu
	mpComandPos = new FLOAT2[mNumComnd]; // �R�}���h�̐��ɉ����ē��I�Ɋm��
	mpcImage = new Image;
	for (int num = 0; num < mNumComnd; num++) {
		mpComandPos[num].x = xPos;
		mpComandPos[num].y = yPos - (Interval * num);
	}
	// �R�}���h�̈ړ��\�͈͂̍��W
	mComnadTopPos = mpComandPos[0].y;
	mComnadUnderPos = mpComandPos[mNumComnd - 1].y;
	// �R�}���h�̏����ʒu
	msPos.x = xPos - (width / 2) - CORRECTIONPOS;
	msPos.y = yPos;

	msOldPos = msPos;
	mOldSelectComand = mSelectComand;

}

// �f�X�g���N�^
SelectCursol::~SelectCursol()
{
	delete mpcImage;
	delete[] mpComandPos;
}

// �J�[�\���ړ��ƑI�������R�}���h�̒l��Ԃ�
int  SelectCursol::Update()
{
	int Comand = 0;
	
	// ����ǂ����Ȃ�����
	if (In->GetKeyTrigger(VK_UP)) {
		msPos.y += mInterval;
		mSelectComand--;
	}
	if (In->GetKeyTrigger(VK_DOWN)) {
		msPos.y -= mInterval;
		mSelectComand++;
	}
	
	// �ړ�����
	if (msPos.y < mComnadUnderPos || msPos.y > mComnadTopPos) {
		msPos = msOldPos;
		mSelectComand = mOldSelectComand;
	}
	// �R�}���h����
	if (In->GetKeyTrigger(VK_RETURN)) {
		Comand = mSelectComand;
	}
	// �O�t���[���̍��W�ƑI�����Ă����R�}���h�Ƃ��ĕۑ�
	msOldPos = msPos;
	mOldSelectComand = mSelectComand;

	return Comand;
}

void SelectCursol::Draw()
{
	ID3D11ShaderResourceView* CursolTex = TexMgr->GetTextuer(Tex_Game);
	mpcImage->DrawDivSprite(msPos.x,msPos.y,0.1f,0.1f,3,4,1,CursolTex);
}
