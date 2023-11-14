#pragma once
#include "StaticObject.h"
#include <string>

class DrawMovei
{
public:
	DrawMovei(std::wstring _filepass, int _maxSlide, Vector2 _maxSize);
	~DrawMovei();

	void Update(); //! 1毎ずつ更新処理で読みこみ
	void Draw();
	void StartMovei(int _animSpeed,Vector2 _pos);
	void SetLoop(bool _loop);             //! ループ再生
	bool GetMoveiState();                 //! 再生中かどうか
private:
	void LoadMovieTexture(const wchar_t * _fileName, ID3D11ShaderResourceView** _outTexture);  // テクスチャの読み込み

	StaticObject * SlideBoard;            //! スライドを描画するオブジェクト
	StaticObject * SlideBG;               //! スライドの背景
	bool MoveiState;                      //! 再生中かどうか
	bool Start;
	int AnimCnt;
	bool Init;                            //! 再生前にスライドを規定のサイズまで大きくしたか判断する
	bool UnInit;                          //! 再生後に終了処理
	int AnimSpeed;
	bool LoadNext;                        //! 次の画像フラグ
	bool End;	                          //! 終了フラグ
	bool Loaded;                          //! 今描画する画像を読み込んだか
	bool Loop;                            //! ループ再生フラグ
	int MaxSlide;                         //! このムービーの画像の数
	int SlideCnt;                         //! 現在のスライド（読み込みに使う）

	Vector2 MaxSize;                      //! 最大サイズ
	Vector2 NowSize;                      //! 現在のサイズ
	ID3D11ShaderResourceView* CurrentTex; //! 現在描画している画像
	std::wstring FileName;
};


