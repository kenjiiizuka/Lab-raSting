#pragma once

//! エネミーのID CSVファイルでおくために使います

typedef enum {
	Enemy_Hooder =      10, //! A
	Enemy_TinpillarZK = 20, //! B
	Enemy_Splitter =    30, //! C
	Enemy_Unper =       40, //! D //! 未実装
	Enemy_Aunper =      50, //! E
	Enemy_Fordon =      60, //! F //! 座標のあとに隊列の数を入れてください 3を入れると先頭 + 3で4体の列になります
	Enemy_TinpillarBomb = 70,
	/*Enemy_TinpillarSL = 60,
	Enemy_Bomb =        70,
	Enemy_Sumoon =      80,*/
}eEnemyID;
