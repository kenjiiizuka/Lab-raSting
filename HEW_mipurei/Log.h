#pragma once
#include <fstream>
#include <string>
#include <iostream>


/* ============================================================ **
** Log�N���X�@�R���X�g���N�^�Ŏw�肵��Text�t�@�C���Ƀ����o�֐�  **
** WriteLog���g�p���ĕϐ��̒l���������ނ��Ƃ��ł��܂��B         **
** ============================================================ */

//! �P�̃e�L�X�g�t�@�C���𓯎��ɕ����̉ӏ�����J�����Ƃ͂ł��܂���
//! ��̃e�L�X�g�t�@�C���ɂ����Log�N���X�ł�

class Log
{
public:
	Log(std::string _fileName); //! �R���X�g���N�^
	~Log();                     //! �f�X�g���N�^
	template <typename U> void WriteLog(U _date,std::string _variableName , bool _newline = true); //! Log�Ɉ����ɐݒ肵�����e���������ފ֐�
	
private:
	std::ofstream LogFile; //! �t�@�C��������ϐ�
};

/* ================================================================= **
** Log�Ɉ����ɐݒ肵�����e���������ފ֐�                             **
** ���� : �l���������݂����ϐ�, �ꏏ�ɏ������݂���������(�ϐ����Ȃ�) **
** ================================================================= */
template<typename U>
inline void Log::WriteLog(U _date, std::string _variableName , bool _newline)
{
	std::string write = _variableName + "  " + std::to_string(_date); //! �ϐ��ƕ��������ɘA������
	if (_newline) {
		LogFile << write << std::endl; //! �t�@�C���ɏ�������
	}
	else {
		LogFile << write << "  "; //! �t�@�C���ɏ�������
	}
}
