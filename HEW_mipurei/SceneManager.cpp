#include "SceneManager.h"
#include "direct3d.h"
// �V�[���N���X�̃w�b�_���C���N���[�h���Ă�������
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "ResultScene.h"
#include "Stage1_1Scene.h"
#include "Stage1_2Scene.h"
#include "Stage_1_3.h"
#include "Stage1_4.h"
#include "Stage1_5.h"
#include "PauseScene.h"
#include "ClearScene.h"
#include "EffectManager.h"
#include "LoseScene.h"
#include "EndingScene.h"

//! �f�o�b�O�p�V�[��
#include "AoiScene.h"
#include "ProtDebugScene.h"
#include "DebugScene.h"
#include "CharacterDebugScene.h"
#include "ProtoTypeScene.h"

SceneManager* SceneManager::Instance = NULL;

//! ���̂̎擾�֐�
SceneManager * SceneManager::GetInstance()
{
	return Instance;
}

//! �����֐�
void SceneManager::Create()
{
	if (!Instance) { Instance = new SceneManager; }
}

//! ���̂̔j��
void SceneManager::Destroy()
{
	delete Instance;
}

//! �R���X�g���N�^
SceneManager::SceneManager()
{
	mcpFade = new Fade; //! �V�[���J�ڎ��Ɏg���t�F�[�h�N���X
	mStackClear = false;
	mFirst = true;
	mFade = false;
	OldScene = nullptr;
	NowSceneID = OldSceneID = NextSceneID = Scene_None;
}

//! �f�X�g���N�^
SceneManager::~SceneManager()
{
	//! SceneStack�̗v�f�����擾
	int numStack = SceneStack.size();
	//! �v�f����pop���A��ɂ���
	for (int num = 0; num < numStack; num++) {
		delete SceneStack.top();
		SceneStack.pop();
	}
	SceneStackClear(); //! �V�[���̃X�^�b�N���N���A���Ă���I������
	delete mcpFade;
	
}

/* --------------------------------------------------------------------- */
//! �V�[���̐؂�ւ��֐�(���̊֐����g���ăV�[����؂�ւ���܂�)         //
//! ���� : �J�ڂ������V�[�� , �V�[���X�^�b�N���N���A���邩�ǂ���         //
void SceneManager::ChageScene(eScene _scene, bool _stackClear, bool _fade , bool _oldscenedraw)
{
	mStackClear = _stackClear;
	NextSceneID = _scene;
	mFade = _fade;
	OldSceneID = NowSceneID; //!�O�̃V�[����ID
	NowSceneID = _scene; //! ���̃V�[���Ƃ��đ������
	OldSceneDraw = _oldscenedraw;
	//! �|�[�Y�V�[���Ȃ�O�̃V�[����ۑ�����
	if (_oldscenedraw) {
		OldScene = SceneStack.top();	
	}	
	//! �t�F�[�h�A�E�g
	if (!mFirst && mFade) {
		mcpFade->FadeOut();
	}

	if (mFirst) { mFirst = false; }
}


//! �V�[���̐؂�ւ��ƁA�X�^�b�N�̈�ԏ�̃V�[���̍X�V����������
void SceneManager::Update()
{
	if (NextSceneID != Scene_None) {
		//! �t�F�[�h�A�E�g���̓V�[����ς��Ȃ�
		if (mcpFade->GetFadeState() != Fade::FADEOUT) {
			//! �X�^�b�N�̒��̃V�[�������ׂĔj������
			if (mStackClear) {
				SceneStackClear(); //! �X�^�b�N�̒��g��j������
				mStackClear = false;
			}
			//! �X�^�b�N���N���A���ꂽ��Ɏ��̃V�[���𐶐�����
			if (!mStackClear) {
				BaseScene* NextScene = CreateScene(NextSceneID); //! ���̃V�[���̐���

				//! NextScene��nullptr�������Ă�����O�̃V�[���ɖ߂�
				if (NextScene == nullptr) {
					//! ���g������Ƃ��̂�
					if (SceneStack.size() > 0) {
						delete SceneStack.top(); //! ��ԏ�̃V�[�����f���[�g
						SceneStack.pop();
					}
				}
				else {
					SceneStack.push(NextScene); //! �X�^�b�N�Ɏ��̃V�[����push
				}
			}
			if (mFade) {
				mcpFade->FadeIn(); //! �t�F�[�h�C���J�n
			}
		}
	}

	//! �X�^�b�N�̒��g������̏�Ԃł͂Ȃ����A�t�F�[�h�A�E�g���Ă��Ȃ��Ƃ�
	if (SceneStack.size() != 0 && mcpFade->GetFadeState() == Fade::NONE) {
		if (!OldSceneDraw) {
			OldScene = nullptr;
		}
		SceneStack.top()->Update(); // �X�^�b�N�̈�ԏ�̍X�V����������
		
	}
	mcpFade->Update(); //! �t�F�[�h�̍X�V����
}

//! �X�^�b�N�̈�ԏ�̃V�[���̕`�������
void SceneManager::Draw()
{
	//! �V�[�����|�[�Y��ʂȂ�O�̃V�[����`�悷��t�F�[�h�A�E�g���鎞�ɂ܂��̃V�[�����|�[�Y�Ȃ�`�悷��
	if (OldSceneDraw) {
		/*if (OldScene != nullptr) {
			OldScene->Draw();
		}*/
	}

	//! ���Ԃ�o�O��
	if (OldScene != nullptr) {
		OldScene->Draw();
	}

	//! �X�^�b�N�̒��g������̏�Ԃł͂Ȃ����A�t�F�[�h�A�E�g���Ă��Ȃ��Ƃ�
	if (SceneStack.size() != 0) {
		SceneStack.top()->Draw();  //! �X�^�b�N�̈�ԏ�̕`�揈��������
	}
	EffMgr->EffectDraw(); //! �G�t�F�N�g�̕`��@�V�[���ŕ`�悵���������������@�������ł�
	mcpFade->Draw(); //! �t�F�[�h�̕`��
}

eScene SceneManager::GetBackScene()
{
	return OldSceneID;
}

//! ���̃V�[���̎擾
eScene SceneManager::GetNowScene()
{
	return NowSceneID;
}


//! �V�[���̐����֐�
BaseScene * SceneManager::CreateScene(eScene _sceneID)
{
	BaseScene* scene = nullptr;
	switch (_sceneID)
	{
	case Scene_Title:
		scene = new TitleScene;
		break;
	case Scene_Result:
		scene = new ResultScene;
		break;

	case Scene_StageSelect:
		scene = new StageSelectScene;
		break;

	case Scene_Ending:
		scene = new EndingScene;
		break;
	case Scene_1_1:
		scene = new Stage1_1;
		break;

	case Scene_1_2:
		scene = new Stage1_2;
		break;

	case Scene_1_3:
		scene = new Stage1_3;
		break;

	case Scene_1_4:
		scene = new Stage1_4;
		break;

	case Scene_1_5:
		scene = new Stage1_5;
		break;

	case Scene_Pause:
		scene = new PauseScene;
		break;

	case Scene_Clear:
		scene = new ClearScene;
		break;

	case Scene_Lose:
		scene = new LoseScene;
		break;
		//! �ȉ��f�o�b�O�V�[��
	case Scene_Debug:
		scene = new DebugScene;
		break;

	case Scene_kenjiDebug:
		scene = new CharacterDebugScene;
		break;

	case Scene_AoiDebug:
		scene = new AoiScene;
		break;

	case Scene_NakanoDebug:
		scene = new PrototypeScene;
		break;


	case Scene_DebugScene_Prot:
		scene = new ProtDebugScene;
		break;

	case Scene_Back:
		scene = nullptr;
		break;
	}
	NextSceneID = Scene_None;
	return scene;
}


void SceneManager::SceneStackClear()
{
	//! SceneStack�̗v�f�����擾
	int numStack = SceneStack.size();
	//! �v�f����pop���A��ɂ���
	for (int num = 0; num < numStack; num++) {
		delete SceneStack.top();
		SceneStack.pop();
	}

	//! �O�̃V�[����nullptr������
	OldScene = nullptr;
}

