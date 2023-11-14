#pragma once

// SE��ID 
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

	//! �v���C���[
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

	//! �G�l�~�[
	SE_Timpiller_Haziku,
	SE_Timpiller_Sasaru,

	SE_Hoder_Sasaru,
	SE_Hoder_Haziku,

	SE_Splitter_Haziku,
	//! �l�N�g�[��
	SE_Necthor_Haziku,
	SE_Necthor_Sasaru,
	SE_Necthor_SPAtk,
	SE_Necthor_Atk, 
	SE_Necthor_AtkSig,
	SE_Necthor_Bakuhatu,

	//! �M�~�b�N�֘A
	SE_Item,            //! �A�C�e��
	SE_Press,           //! �v���X�@
	SE_CheackPoint,     //! ���Ԓn�_
	//SE_NewCheackPoint,     //! ���Ԓn�_
	SE_Door_Stage,			 //! �X�e�[�W�̃h�A
	SE_Door_StageSelect,	 //! �X�e�[�W�I���̃h�A
	SE_Dynamo_NotSting,
	SE_Dynamo_OverHeat,
	SE_Dynamo_OverHeat2,
	SE_Dynamo_Charge,
	SE_Glass_Break,
	SE_Glass_Hajiku,

	SE_Goal,             //! �S�[�������Ƃ�
	SE_Hanabi,
	SE_Lose,             //! ������
	SE_Max
};

// BGM��ID
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