#include "Log.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "direct3d.h"

using namespace std;

Log::Log(std::string _fileName)
{	
	LogFile.open(_fileName,std::ios::out); //! 書き込みできるようにファイルを開く
	
}

Log::~Log()
{
	LogFile.close(); //! ファイルを閉じる
}




