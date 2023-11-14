#pragma once
#include "StaticObject.h"
#include <string>

class DrawMovei
{
public:
	DrawMovei(std::wstring _filepass, int _maxSlide, Vector2 _maxSize);
	~DrawMovei();

	void Update(); //! 1�����X�V�����œǂ݂���
	void Draw();
	void StartMovei(int _animSpeed,Vector2 _pos);
	void SetLoop(bool _loop);             //! ���[�v�Đ�
	bool GetMoveiState();                 //! �Đ������ǂ���
private:
	void LoadMovieTexture(const wchar_t * _fileName, ID3D11ShaderResourceView** _outTexture);  // �e�N�X�`���̓ǂݍ���

	StaticObject * SlideBoard;            //! �X���C�h��`�悷��I�u�W�F�N�g
	StaticObject * SlideBG;               //! �X���C�h�̔w�i
	bool MoveiState;                      //! �Đ������ǂ���
	bool Start;
	int AnimCnt;
	bool Init;                            //! �Đ��O�ɃX���C�h���K��̃T�C�Y�܂ő傫�����������f����
	bool UnInit;                          //! �Đ���ɏI������
	int AnimSpeed;
	bool LoadNext;                        //! ���̉摜�t���O
	bool End;	                          //! �I���t���O
	bool Loaded;                          //! ���`�悷��摜��ǂݍ��񂾂�
	bool Loop;                            //! ���[�v�Đ��t���O
	int MaxSlide;                         //! ���̃��[�r�[�̉摜�̐�
	int SlideCnt;                         //! ���݂̃X���C�h�i�ǂݍ��݂Ɏg���j

	Vector2 MaxSize;                      //! �ő�T�C�Y
	Vector2 NowSize;                      //! ���݂̃T�C�Y
	ID3D11ShaderResourceView* CurrentTex; //! ���ݕ`�悵�Ă���摜
	std::wstring FileName;
};


