#include "SceneManager.h"
#include "direct3d.h"
// シーンクラスのヘッダをインクルードしてください
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

//! デバッグ用シーン
#include "AoiScene.h"
#include "ProtDebugScene.h"
#include "DebugScene.h"
#include "CharacterDebugScene.h"
#include "ProtoTypeScene.h"

SceneManager* SceneManager::Instance = NULL;

//! 実体の取得関数
SceneManager * SceneManager::GetInstance()
{
	return Instance;
}

//! 生成関数
void SceneManager::Create()
{
	if (!Instance) { Instance = new SceneManager; }
}

//! 実体の破棄
void SceneManager::Destroy()
{
	delete Instance;
}

//! コンストラクタ
SceneManager::SceneManager()
{
	mcpFade = new Fade; //! シーン遷移時に使うフェードクラス
	mStackClear = false;
	mFirst = true;
	mFade = false;
	OldScene = nullptr;
	NowSceneID = OldSceneID = NextSceneID = Scene_None;
}

//! デストラクタ
SceneManager::~SceneManager()
{
	//! SceneStackの要素数を取得
	int numStack = SceneStack.size();
	//! 要素数分popし、空にする
	for (int num = 0; num < numStack; num++) {
		delete SceneStack.top();
		SceneStack.pop();
	}
	SceneStackClear(); //! シーンのスタックをクリアしてから終了する
	delete mcpFade;
	
}

/* --------------------------------------------------------------------- */
//! シーンの切り替え関数(この関数を使ってシーンを切り替えれます)         //
//! 引数 : 遷移したいシーン , シーンスタックをクリアするかどうか         //
void SceneManager::ChageScene(eScene _scene, bool _stackClear, bool _fade , bool _oldscenedraw)
{
	mStackClear = _stackClear;
	NextSceneID = _scene;
	mFade = _fade;
	OldSceneID = NowSceneID; //!前のシーンのID
	NowSceneID = _scene; //! 今のシーンとして代入する
	OldSceneDraw = _oldscenedraw;
	//! ポーズシーンなら前のシーンを保存する
	if (_oldscenedraw) {
		OldScene = SceneStack.top();	
	}	
	//! フェードアウト
	if (!mFirst && mFade) {
		mcpFade->FadeOut();
	}

	if (mFirst) { mFirst = false; }
}


//! シーンの切り替えと、スタックの一番上のシーンの更新処理をする
void SceneManager::Update()
{
	if (NextSceneID != Scene_None) {
		//! フェードアウト中はシーンを変えない
		if (mcpFade->GetFadeState() != Fade::FADEOUT) {
			//! スタックの中のシーンをすべて破棄する
			if (mStackClear) {
				SceneStackClear(); //! スタックの中身を破棄する
				mStackClear = false;
			}
			//! スタックがクリアされた後に次のシーンを生成する
			if (!mStackClear) {
				BaseScene* NextScene = CreateScene(NextSceneID); //! 次のシーンの生成

				//! NextSceneにnullptrが入っていたら前のシーンに戻る
				if (NextScene == nullptr) {
					//! 中身があるときのみ
					if (SceneStack.size() > 0) {
						delete SceneStack.top(); //! 一番上のシーンをデリート
						SceneStack.pop();
					}
				}
				else {
					SceneStack.push(NextScene); //! スタックに次のシーンをpush
				}
			}
			if (mFade) {
				mcpFade->FadeIn(); //! フェードイン開始
			}
		}
	}

	//! スタックの中身がからの状態ではないかつ、フェードアウトしていないとき
	if (SceneStack.size() != 0 && mcpFade->GetFadeState() == Fade::NONE) {
		if (!OldSceneDraw) {
			OldScene = nullptr;
		}
		SceneStack.top()->Update(); // スタックの一番上の更新処理をする
		
	}
	mcpFade->Update(); //! フェードの更新処理
}

//! スタックの一番上のシーンの描画をする
void SceneManager::Draw()
{
	//! シーンがポーズ画面なら前のシーンを描画するフェードアウトする時にまえのシーンがポーズなら描画する
	if (OldSceneDraw) {
		/*if (OldScene != nullptr) {
			OldScene->Draw();
		}*/
	}

	//! たぶんバグる
	if (OldScene != nullptr) {
		OldScene->Draw();
	}

	//! スタックの中身がからの状態ではないかつ、フェードアウトしていないとき
	if (SceneStack.size() != 0) {
		SceneStack.top()->Draw();  //! スタックの一番上の描画処理をする
	}
	EffMgr->EffectDraw(); //! エフェクトの描画　シーンで描画した方がいいかも　検討中です
	mcpFade->Draw(); //! フェードの描画
}

eScene SceneManager::GetBackScene()
{
	return OldSceneID;
}

//! 今のシーンの取得
eScene SceneManager::GetNowScene()
{
	return NowSceneID;
}


//! シーンの生成関数
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
		//! 以下デバッグシーン
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
	//! SceneStackの要素数を取得
	int numStack = SceneStack.size();
	//! 要素数分popし、空にする
	for (int num = 0; num < numStack; num++) {
		delete SceneStack.top();
		SceneStack.pop();
	}

	//! 前のシーンもnullptrを入れる
	OldScene = nullptr;
}

