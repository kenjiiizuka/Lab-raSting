#pragma once
//! �����蔻��̂���I�u�W�F�N�g�ɂ���^�O�ł��B

enum ObjectTag {
	Tag_None,
	Tag_Player,          //! �v���C���[
	Tag_Tail,            //! ������
	Tag_Enemy_Tinpillar, //! �ł��G
	Tag_Enemy_Soft,      //! �_�炩���G
	Tag_Enemy_SplitU,    //! ���􂷂�G��
	Tag_Enemy_SplitD,    //! ���􂷂�G��
	Tag_Drone,
	Tag_Boss_Dekanutya,  //! �{�X�ł��ʂ���	
	Tag_Fordon,          //! Fordon
	Tag_Dynamo,          //! ���d�@
	Tag_WeakDynamo,      //! ���낢���d�C
	Tag_Press
};