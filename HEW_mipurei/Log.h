#pragma once
#include <fstream>
#include <string>
#include <iostream>


/* ============================================================ **
** Logクラス　コンストラクタで指定したTextファイルにメンバ関数  **
** WriteLogを使用して変数の値を書き込むことができます。         **
** ============================================================ */

//! １つのテキストファイルを同時に複数の箇所から開くことはできません
//! 一つのテキストファイルにつき一つのLogクラスです

class Log
{
public:
	Log(std::string _fileName); //! コンストラクタ
	~Log();                     //! デストラクタ
	template <typename U> void WriteLog(U _date,std::string _variableName , bool _newline = true); //! Logに引数に設定した内容を書き込む関数
	
private:
	std::ofstream LogFile; //! ファイルを入れる変数
};

/* ================================================================= **
** Logに引数に設定した内容を書き込む関数                             **
** 引数 : 値を書き込みたい変数, 一緒に書き込みたい文字列(変数名など) **
** ================================================================= */
template<typename U>
inline void Log::WriteLog(U _date, std::string _variableName , bool _newline)
{
	std::string write = _variableName + "  " + std::to_string(_date); //! 変数と文字列を一つに連結する
	if (_newline) {
		LogFile << write << std::endl; //! ファイルに書き込む
	}
	else {
		LogFile << write << "  "; //! ファイルに書き込む
	}
}
