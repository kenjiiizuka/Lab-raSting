#include "TextureManager.h"
#include "WICTextureLoader.h"
#include <string>

TextureManager * TextureManager::Instance = nullptr;

TextureManager * TextureManager::GetInstance()
{
	if (Instance) {
		return Instance;
	}

	return nullptr;
}

void TextureManager::Create()
{
	if (!Instance) {
		Instance = new TextureManager();
	}
}

void TextureManager::Destroy()
{
	delete Instance;
}

ID3D11ShaderResourceView * TextureManager::GetTextuer(eTextureID _texID)
{
	return mpTexture[_texID];
}


//! コンストラクタ
//! 画像を格納する配列の初期化と画像のロードをする
TextureManager::TextureManager()
{
	for (int num = 0; num < Tex_Max; num++) {
		mpTexture[num] = nullptr;
	}
	//! コピペ用　　LoadTexture(L"assets/", &mpTexture[]);
	//! プレイヤー関係の画像
	//! "
//	LoadTexture(L"assets/tutorial_movie/tut//orial_movie(1).jpg", &mpTexture[Tex_Player_Idol]);
	LoadTexture(L"assets/Player/Idol.png", &mpTexture[Tex_Player_Idol]);
	LoadTexture(L"assets/Player/Jump5.png", &mpTexture[Tex_Player_Jump]);
	LoadTexture(L"assets/Player/Attack.png", &mpTexture[Tex_Player_Attack]);
	LoadTexture(L"assets/Player/Run.png", &mpTexture[Tex_Player_Run]);
	LoadTexture(L"assets/Player/Aim.png", &mpTexture[Tex_Player_Aim]);
	LoadTexture(L"assets/Player/Plug.png", &mpTexture[Tex_Player_Plug]);
	LoadTexture(L"assets/Player/PlugR.png", &mpTexture[Tex_Player_PlugR]);
	LoadTexture(L"assets/Player/PlugY.png", &mpTexture[Tex_Player_PlugY]);
	LoadTexture(L"assets/Player/tail.png", &mpTexture[Tex_Player_Tail]);
	LoadTexture(L"assets/Player/taleR_2.png", &mpTexture[Tex_Player_TailR]);
	LoadTexture(L"assets/Player/taleY_2.png", &mpTexture[Tex_Player_TailY]);
	LoadTexture(L"assets/Player/ElectSting.png", &mpTexture[Tex_Player_ElectSting]);
	LoadTexture(L"assets/Player/Down.png", &mpTexture[Tex_Player_Down]);
	LoadTexture(L"assets/Player/HPup.png", &mpTexture[Tex_Player_HPup]);

	

	LoadTexture(L"assets/Player/Hp.png", &mpTexture[Tex_Player_HP]);
	LoadTexture(L"assets/Effect/PlayerSmoke.png", &mpTexture[Tex_Player_Smoke]);


	//! エネミー関係の画像	
	LoadTexture(L"assets/Enemy/Tinpillar.png", &mpTexture[Tex_Timpiller]);
	LoadTexture(L"assets/Enemy/enemy2.png", &mpTexture[Tex_Split]);
	LoadTexture(L"assets/Enemy/Holder.png", &mpTexture[Tex_Soft]);
	LoadTexture(L"assets/Enemy/Aunper.png", &mpTexture[Tex_Aunper]);
	LoadTexture(L"assets/Enemy/Splitter_Main.png", &mpTexture[Tex_Splitter]);
	LoadTexture(L"assets/Enemy/Splitteer_body.png", &mpTexture[Tex_Splitter_Body]);
	LoadTexture(L"assets/Enemy/Splitter_leg.png", &mpTexture[Tex_Splitter_Leg]);
	Tex_PanelBl;
	//! ボスの画像
	LoadTexture(L"assets/Enemy/Boss/idol_v2.png", &mpTexture[Tex_Necthor_Idol]);
	LoadTexture(L"assets/Enemy/Boss/attacks_v2_1.png", &mpTexture[Tex_Necthor_Attack]);
	LoadTexture(L"assets/Enemy/Boss/attacks_v2_2.png", &mpTexture[Tex_Necthor_Attack2]);
	LoadTexture(L"assets/Enemy/Boss/idol_v2_2.png", &mpTexture[Tex_Necthor_Idol_Red]);
	LoadTexture(L"assets/Enemy/Boss/attacks_v2_3.png", &mpTexture[Tex_Necthor_Attack_Red]);
	LoadTexture(L"assets/Enemy/Boss/attacks_v2_4.png", &mpTexture[Tex_Necthor_Attack2_Red]);
	LoadTexture(L"assets/Enemy/Boss/breakPipe.png", &mpTexture[Tex_Necthor_Debri]);
	LoadTexture(L"assets/Enemy/Boss/ShockWave.png", &mpTexture[Tex_Necthor_ShockWave]);
	LoadTexture(L"assets/Enemy/Boss/Cursol.png", &mpTexture[Tex_Necthor_Allow]);

	//! ギミック関連の画像
	LoadTexture(L"assets/Gimmick/Dynamo/janeNomal.png", &mpTexture[Tex_Dynamo01]);
	LoadTexture(L"assets/Gimmick/Dynamo/jeneWeek.png", &mpTexture[Tex_Dynamo02]);
	LoadTexture(L"assets/Gimmick/Goal/goal.png", &mpTexture[Tex_Goal]);
	LoadTexture(L"assets/Gimmick/Glass/Glass.png", &mpTexture[Tex_Galss]);
	LoadTexture(L"assets/Gimmick/Door/Doortest.png", &mpTexture[Tex_Door]);
	LoadTexture(L"assets/Gimmick/CheackPoint/CheckPoint01.png", &mpTexture[Tex_CheackPoint]);
	LoadTexture(L"assets/Gimmick/Press/Press.png", &mpTexture[Tex_PressMachine]);

	//! 煙の画像
	LoadTexture(L"assets/Enemy/Boss/Smoke01.png", &mpTexture[Tex_Smoke01]);
	LoadTexture(L"assets/Enemy/Boss/Smoke02.png", &mpTexture[Tex_Smoke02]);
	LoadTexture(L"assets/Enemy/Boss/Smoke03.png", &mpTexture[Tex_Smoke03]);

	//! ステージ選択画面に使うドア
	LoadTexture(L"assets/StageSelectScene/ChooseDoor.png", &mpTexture[Tex_StageDoor01]);
	LoadTexture(L"assets/StageSelectScene/ChooseDoor2.png", &mpTexture[Tex_StageDoor02]);
	LoadTexture(L"assets/StageSelectScene/gate_3.png", &mpTexture[Tex_BossDoor]);

	//! UIの画像
	LoadTexture(L"assets/Player/heart.png", &mpTexture[Tex_UI_HP]);
	LoadTexture(L"assets/Other/cursol.png", &mpTexture[Tex_Cursol]);
	LoadTexture(L"assets/Other/Yes.png", &mpTexture[Tex_Yes]);
	LoadTexture(L"assets/Other/No.png", &mpTexture[Tex_No]);
	LoadTexture(L"assets/Player/battery.png", &mpTexture[Tex_Battery]);
	LoadTexture(L"assets/StageSelectScene/a.png", &mpTexture[Tex_AbuttonUI]);
	LoadTexture(L"assets/Player/UIFrame.png", &mpTexture[Tex_UIFrame]);
	LoadTexture(L"assets/PauseScene/Controller.png",&mpTexture[Tex_Contrller]);

	//! マップチップの画像
	LoadTexture(L"assets/Stage1/Maptiptest.png", &mpTexture[Tex_MapTip01]);
	LoadTexture(L"assets/Stage1/Item.png",&mpTexture[Tex_MapItem01]);
	//! ステージの背景画像
	LoadTexture(L"assets/Stage1/back1.png", &mpTexture[Tex_StageBG01]);
	LoadTexture(L"assets/Stage1/back2.png", &mpTexture[Tex_StageBG02]);
	LoadTexture(L"assets/Stage1/back3.png", &mpTexture[Tex_StageBG03]);

	//! コマンド画像
	LoadTexture(L"assets/PauseScene/Continue.png", &mpTexture[Tex_Continue]);
	LoadTexture(L"assets/PauseScene/Setting.png", &mpTexture[Tex_Setting]);
	LoadTexture(L"assets/PauseScene/Retire.png", &mpTexture[Tex_Retire]);
	LoadTexture(L"assets/TitleScene/Title_Title.png", &mpTexture[Tex_Title_Title]);
	LoadTexture(L"assets/TitleScene/Title_Game.png", &mpTexture[Tex_Title_Game]);
	LoadTexture(L"assets/TitleScene/Title_End.png", &mpTexture[Tex_Title_End]);
	LoadTexture(L"assets/PauseScene/Title.png", &mpTexture[Tex_Title_Pawse]);
	LoadTexture(L"assets/TitleScene/Window.png", &mpTexture[Tex_Window]);
	LoadTexture(L"assets/PauseScene/Open.png", &mpTexture[Tex_Pause_Bg01]);
	LoadTexture(L"assets/PauseScene/Close.png", &mpTexture[Tex_Pause_Bg02]);
	LoadTexture(L"assets/PauseScene/CommandOpen.png", &mpTexture[Tex_CommmandOpen]);
	LoadTexture(L"assets/PauseScene/CommandClose.png", &mpTexture[Tex_CommmandClose]);
	LoadTexture(L"assets/TitleScene/CommandOpen.png", &mpTexture[Tex_CommmandOpen02]);
	LoadTexture(L"assets/TitleScene/CommandClose.png", &mpTexture[Tex_CommmandClose02]);
	LoadTexture(L"assets/Player/heart.png", &mpTexture[Tex_UI_HP]);

	LoadTexture(L"assets/TitleScene/TitleBG.png", &mpTexture[Tex_TitleBg]);
	LoadTexture(L"assets/TitleScene/TitleBG02.png", &mpTexture[Tex_TitleBg02]);
	LoadTexture(L"assets/Effect/kamifubuki.png",&mpTexture[Tex_PaperStream]);
	//! デバッグ用画像です
	LoadTexture(L"assets/Player/Taiden.png", &mpTexture[Tex_Taiden]);
	LoadTexture(L"assets/Debug/Circle.png", &mpTexture[Tex_Circle]);
	LoadTexture(L"assets/Debug/Title.png", &mpTexture[Tex_Title]);
	LoadTexture(L"assets/Debug/Game.png", &mpTexture[Tex_Game]);
	LoadTexture(L"assets/Debug/Result.png", &mpTexture[Tex_Result]);
	
	LoadTexture(L"assets/Debug/BlackPanel.png", &mpTexture[Tex_PanelBl]);
	
	LoadTexture(L"assets/protoChara.png", &mpTexture[Tex_ProtoChara]);
	LoadTexture(L"assets/Debug/DebugBG01.jpg", &mpTexture[Tex_debugBG01]);
	LoadTexture(L"assets/Debug/nakano.png", &mpTexture[Tex_Nakano]);
	LoadTexture(L"assets/Debug/kitauti.png", &mpTexture[Tex_Kitauti]);
	LoadTexture(L"assets/Debug/iizuka.png", &mpTexture[Tex_Iizuka]);
	LoadTexture(L"assets/Debug/α.png", &mpTexture[Tex_Arufa]);
	LoadTexture(L"assets/Debug/Game01.png", &mpTexture[Tex_Game02]);
}

TextureManager::~TextureManager()
{
	// テクスチャの開放処理
	for (int i = 0; i < Tex_Max; i++) {
		if (mpTexture[i] != nullptr) { //! もし画像の読み込みに失敗した場合でも正常に終わるように
			COM_SAFE_RELEASE(mpTexture[i]);
		}
	}
}


void LoadTexture(const wchar_t* _fileName, ID3D11ShaderResourceView** _outTexture)
{
	HRESULT hr;
	DIRECT3D *d3d = Direct3D_Get();

	// 必殺技のエフェクト０２
	hr = DirectX::CreateWICTextureFromFile(d3d->device, _fileName, nullptr, _outTexture);
	//２バイト文字列を渡さないといけない　L　をつけると２バイト文字列になる

	//エラー処理
	if (FAILED(hr)) //失敗した場合
	{
		//MessageBox(NULL, L"テクスチャ読み込み失敗", L"エラー発生", MB_OK);
		_outTexture = nullptr;
	}
}
