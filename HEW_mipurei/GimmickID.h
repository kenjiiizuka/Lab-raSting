#pragma once

//! ギミックのID　マップ側でnewしたり、ギミックを管理するために使う
typedef enum {
	GI_CheakPoint        = 99,     //! A 中間ポイントでぇす
	GI_Dynamo            = 100,    //! B 発電機デス！！！！！
	GI_WeakDyanamo       = 103,    //! C 壊れる発電機Daeth
	GI_BigDoor           = 110,    //! D 大きなドアです
	GI_Glass             = 120,    //! E ガラスです
	GI_Goal              = 130,    //! ゴールです(必ず一つなので数を指定する必要はありません)
                                   //! ですが必ずゴールの座標を指定しないと動きません
	GI_Press             = 140     //! F プレス機です
}GimmickID;