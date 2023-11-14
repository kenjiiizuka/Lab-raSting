#pragma once
#include <stack>
#include "BaseScene.h"
#include "eScene.h"
#include "Fade.h"

/* ===============================
** SceneManager�N���X           **
** Scene�̊Ǘ�������N���X�ł�  **
** ����� : �ђ� ���i           **
** ============================ */

#define SceneMgr SceneManager::GetInstance()

class SceneManager
{
public:
	static SceneManager* GetInstance();    //! ���Ԃ��擾����֐�
	static void Create();				   //! �����p�֐�
	static void Destroy();				   //! �N���X�̔j���p�̊֐�

	void ChageScene(eScene _scene, bool _stackClear, bool _fade = true , bool _olscenedraw = false); //! �V�[����i�߂�@clear��ture������ƃX�^�b�N������ɂ���

	void Update();
	void Draw();

	eScene GetBackScene(); //! ��O�̃V�[���̎擾
	eScene GetNowScene();  //! ���̃V�[���̎擾
private:
	SceneManager();  //! �R���X�g���N�^
	~SceneManager(); //! �f�X�g���N�^

	BaseScene* CreateScene(eScene _scnenID);  //! �V�[���̐����֐�
	BaseScene * OldScene;                  //! �|�[�Y��ʂɂȂ�����O�̃V�[����`�悷��
	void SceneStackClear();                //! Stack�ɓ����Ă���V�[����S�Ĕj������֐�
	eScene NextSceneID;                    //! ���̃V�[����ID
	eScene NowSceneID;                     //! ���̃V�[��
	eScene OldSceneID;                     //! �ЂƂO�̃V�[��
	bool mStackClear;                      //! �X�^�b�N���N���A���邩���f����t���O
	bool mFade;                            //! �t�F�[�h�����邩���Ȃ���
	bool mFirst;                           //! �Q�[���̎n�܂�Ƀt�F�[�h�C�����邽�߂̕ϐ�
	std::stack<BaseScene*> SceneStack;     //! �V�[��������X�^�b�N
	Fade * mcpFade;                        //! �t�F�[�h�N���X
	static SceneManager* Instance;         //! ���Ԃ������߂̕ϐ�
	bool OldSceneDraw;                     //! �O�̃V�[����`�悷�邩�ǂ���
};



