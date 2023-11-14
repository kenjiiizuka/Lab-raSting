#pragma once
#include <stack>
#include "BaseScene.h"
#include "eScene.h"
#include "Fade.h"

/* ===============================
** SceneManagerクラス           **
** Sceneの管理をするクラスです  **
** 制作者 : 飯塚 健司           **
** ============================ */

#define SceneMgr SceneManager::GetInstance()

class SceneManager
{
public:
	static SceneManager* GetInstance();    //! 実態を取得する関数
	static void Create();				   //! 生成用関数
	static void Destroy();				   //! クラスの破棄用の関数

	void ChageScene(eScene _scene, bool _stackClear, bool _fade = true , bool _olscenedraw = false); //! シーンを進める　clearにtureを入れるとスタックをからにする

	void Update();
	void Draw();

	eScene GetBackScene(); //! 一つ前のシーンの取得
	eScene GetNowScene();  //! 今のシーンの取得
private:
	SceneManager();  //! コンストラクタ
	~SceneManager(); //! デストラクタ

	BaseScene* CreateScene(eScene _scnenID);  //! シーンの生成関数
	BaseScene * OldScene;                  //! ポーズ画面になったら前のシーンを描画する
	void SceneStackClear();                //! Stackに入っているシーンを全て破棄する関数
	eScene NextSceneID;                    //! 次のシーンのID
	eScene NowSceneID;                     //! 今のシーン
	eScene OldSceneID;                     //! ひとつ前のシーン
	bool mStackClear;                      //! スタックをクリアするか判断するフラグ
	bool mFade;                            //! フェードをするかしないか
	bool mFirst;                           //! ゲームの始まりにフェードインするための変数
	std::stack<BaseScene*> SceneStack;     //! シーンを入れるスタック
	Fade * mcpFade;                        //! フェードクラス
	static SceneManager* Instance;         //! 実態を持つための変数
	bool OldSceneDraw;                     //! 前のシーンを描画するかどうか
};



