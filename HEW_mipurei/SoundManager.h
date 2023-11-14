#pragma once
#include "eSoundID.h"
#include "xAudio.h"

//===============================================================
// サウンドマネージャークラス
// SE、BGMを再生できます。
// フレームごとにBGMの状態を更新しているので、BGMを再度ならしたい場合はBGMを止めて、
// 次のフレームで再生用の関数を使用してください
// 制作者 : 飯塚健司
//===============================================================
#define SoundMgr SoundManager::GetInstance()
#define PLAYSE(seid,vol) SoundManager::GetInstance()->PlaySE(seid,vol)

class SoundManager
{
	//! サウンドのデータの構造体
	typedef struct {
		XAUDIO2_BUFFER buffer;
		WAVEFORMATEXTENSIBLE wfx;
		BYTE * pDataBuffer;
	}Sound;

public:
	static SoundManager* GetInstance();
	static void Create();
	static void Destroy();

	void PlaySE(eSEID _SEID, float _volume = 1.0f);                          //! SE再生関数
	void PlayBGM(eBGMID _BGMID, float _volume = 1.0f, bool _fadein = false); //! BGM再生関数
	void StopBGM(bool _fadeout = false);                                     //! BGM停止関数
	void SetBGMVolume(float _volume);                                        //! BGMの音量のセッター
	void SoundUpdate();                                                      //! 更新処理
	void Init();                                                             //! 初期化処理

private:
	SoundManager();                                             //! コストラクタ
	~SoundManager();                                            //! デストラクタ
	void  LoadSound(const wchar_t * _fileName, Sound * _sound); //! サウンドの読み込み

	static SoundManager* mInstance;                             //! 自身のインスタンス	
	IXAudio2* mpxAudio2;                                        //! xAudio2のインスタンス
	IXAudio2SourceVoice* mpSESourceVoice[SE_Max];               //! SEソースボイス 
	IXAudio2SourceVoice* mpBGMSourceVoice;                      //! BGMソースボイス 
	Sound msSE[SE_Max];                                         //! SEのデータ
	Sound msBGM[BGM_Max];                                       //! BGMのデータ
	bool  mBGMState;                                            //! BGMの現在の状態  true---再生中 false---再生していない
	int   mBGMPlayType;                                         //! BGMの再生仕方　停止の仕方
	float mVolume;                                              //! BGMの音量 
	float mVolumeFade;                                          //! フェードするときに使う
	eBGMID mPlayingBGM;                                         //! 再生しているBGM 
	
};

