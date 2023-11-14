#pragma once

//! �G�t�F�N�g�̏��
enum EffectState {
	None,
	Play,
	End,
};


//! �G�t�F�N�g�̎��
enum eEffect {
	HitEffect,
	DynamoCharge,
	Recovery,
	GoalEffect01, //! �f�o�b�O�p�摜�ł�
	Explosion,    //! �΂��͂�
	Explosion02,  //! �����O�Q
	Elect,
	ElectSuper02,
	ElectSuper01,
	DisCharge,     //! ���d�̃G�t�F�N�g
	Stinged,       //! �K�����ˏo�����u��
	Hibana,        //! ���m���h�����Ƃ��ɂł�Ή�
	HitEffect01,   //! �q�b�g�G�t�F�N�g
	HitEffect02,   //! �d�C�̑��Ŏh�����Ƃ��ɂ̃G�t�F�N�g
	DaynamoEffect, //! ���d�@�̃G�t�F�N�g
	Hp_Recvery,
	Hanabi_R,
	Hanabi_Y,
	Hanabi_B,
	Hanabi_G,
	Hanabi_P,
	Hanabi_O,
	// �G�t�F�N�g��ǉ����鎞��Max�̏�ɒǉ�����
	EffectMax
};