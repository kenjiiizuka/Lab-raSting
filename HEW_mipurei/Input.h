#pragma once
#include "FLOAT2.h"
#include <Windows.h>

/* =========================================== **
** �L�[�{�[�h�A�}�E�X�̓��̓N���X              **
** ����� : �ђ� ���i                          **
** =========================================== */

#define In Input::GetInstance() //! �Q�b�g�C���X�^���X�֐��ȗ��̂��߂̃}�N��

class Input
{
public:

	static Input * GetInstance();
	static void Create();
	static void Destroy();
	
	void SetKeyDown(int key);
	void SetKeyUp(int key);
	bool GetKeyTrigger(int Key);     //! �������u��
	bool GetKeyDownPress(int key);   //! ������
	
private:
	Input();  //! �R���X�g���N�^
	~Input(); //! �f�X�g���N�^

	//! �S�L�[��Ԃ�ۑ�����z��
	bool mKeyState[256];
	bool mOldKeyState[256];

	static Input * mcpInstance; //! ����	
};