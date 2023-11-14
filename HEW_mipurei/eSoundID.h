#pragma once

// SEのID 
enum eSEID {
	SE_Button01,
	SE_GameOver,
	SE_Select01,
	SE_MoveCarsol,
	SE_Pause,
	SE_Monitor,
	SE_Cancel,
	SE_Error,
	SE_Success,

	//! プレイヤー
	SE_Jump,
	SE_Damage,
	SE_Heal,
	SE_HPHeal,
	SE_GaugeHeal,
	SE_Tame,
	SE_Kamae,
	//SE_MissAtk,
	SE_Sting01,
	SE_Taiden,
	SE_TaidenAtk,
	SE_NormalElec,
	SE_HardElec,

	//! エネミー
	SE_Timpiller_Haziku,
	SE_Timpiller_Sasaru,

	SE_Hoder_Sasaru,
	SE_Hoder_Haziku,

	SE_Splitter_Haziku,
	//! ネクトール
	SE_Necthor_Haziku,
	SE_Necthor_Sasaru,
	SE_Necthor_SPAtk,
	SE_Necthor_Atk, 
	SE_Necthor_AtkSig,
	SE_Necthor_Bakuhatu,

	//! ギミック関連
	SE_Item,            //! アイテム
	SE_Press,           //! プレス機
	SE_CheackPoint,     //! 中間地点
	//SE_NewCheackPoint,     //! 中間地点
	SE_Door_Stage,			 //! ステージのドア
	SE_Door_StageSelect,	 //! ステージ選択のドア
	SE_Dynamo_NotSting,
	SE_Dynamo_OverHeat,
	SE_Dynamo_OverHeat2,
	SE_Dynamo_Charge,
	SE_Glass_Break,
	SE_Glass_Hajiku,

	SE_Goal,             //! ゴールしたとき
	SE_Hanabi,
	SE_Lose,             //! 負け犬
	SE_Max
};

// BGMのID
enum eBGMID {
	
	BGM_SelectScene,
	BGM_Titel,
	BGM_Thotrial,
	BGM_1_3,
	BGM_1_5,
	BGM_BossBattle,
	BGM_Hanyou,
	BGM_Pause,
	BGM_Stage_Clear,
	BGM_Game_Clear,
	BGM_Ending,

	BGM_Max
};


enum eSoundPlayType {
	PlayType_None,
	PlayType_Stop,
	PlayType_Play,
	PlayType_FadeIn,
	PlayType_FadeOut,
};