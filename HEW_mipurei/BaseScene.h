#pragma once
#include "Image.h"
#include "eScene.h"
// �e�V�[���N���X�̊��N���X

class BaseScene
{
public:
	BaseScene(){}
	virtual ~BaseScene(){}
	virtual void Update() {}
	virtual void Draw(){}
protected:
	Image * mcpImage; // �`��N���X�ł��B�Î~��ȂǁA��`�悷��ۂɂ����ĉ������B�^�C�g���̔w�i�Ȃ�
	eScene Tag = Scene_None;

	bool BGM = true; //! BGM�Đ��\��
};

