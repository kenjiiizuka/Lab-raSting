#pragma once

//! エフェクトの状態
enum EffectState {
	None,
	Play,
	End,
};


//! エフェクトの種類
enum eEffect {
	HitEffect,
	DynamoCharge,
	Recovery,
	GoalEffect01, //! デバッグ用画像です
	Explosion,    //! ばくはつ
	Explosion02,  //! 爆発０２
	Elect,
	ElectSuper02,
	ElectSuper01,
	DisCharge,     //! 放電のエフェクト
	Stinged,       //! 尻尾を射出した瞬間
	Hibana,        //! モノを刺したときにでる火花
	HitEffect01,   //! ヒットエフェクト
	HitEffect02,   //! 電気の槍で刺したときにのエフェクト
	DaynamoEffect, //! 発電機のエフェクト
	Hp_Recvery,
	Hanabi_R,
	Hanabi_Y,
	Hanabi_B,
	Hanabi_G,
	Hanabi_P,
	Hanabi_O,
	// エフェクトを追加する時はMaxの上に追加する
	EffectMax
};