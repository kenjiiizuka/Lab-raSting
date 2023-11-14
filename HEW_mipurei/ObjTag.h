#pragma once
//! 当たり判定のあるオブジェクトにつけるタグです。

enum ObjectTag {
	Tag_None,
	Tag_Player,          //! プレイヤー
	Tag_Tail,            //! しっぽ
	Tag_Enemy_Tinpillar, //! 固い敵
	Tag_Enemy_Soft,      //! 柔らかい敵
	Tag_Enemy_SplitU,    //! 分裂する敵上
	Tag_Enemy_SplitD,    //! 分裂する敵下
	Tag_Drone,
	Tag_Boss_Dekanutya,  //! ボスでかぬちゃ	
	Tag_Fordon,          //! Fordon
	Tag_Dynamo,          //! 発電機
	Tag_WeakDynamo,      //! もろい発電気
	Tag_Press
};