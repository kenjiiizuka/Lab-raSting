#include "Log.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include "direct3d.h"

using namespace std;

Log::Log(std::string _fileName)
{	
	LogFile.open(_fileName,std::ios::out); //! �������݂ł���悤�Ƀt�@�C�����J��
	
}

Log::~Log()
{
	LogFile.close(); //! �t�@�C�������
}




