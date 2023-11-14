#include "SoundManager.h"
#include "direct3d.h"
#include "TextureManager.h"


SoundManager* SoundManager::mInstance = nullptr;



//! サウンドの読み込み関数
void SoundManager::Init()
{
	//! BGMの読み込み
	LoadSound(L"assets/Sound/BGM/BossBattle/1_3.wav", &msBGM[BGM_1_3]);
	LoadSound(L"assets/Sound/BGM/BossBattle/1_5.wav", &msBGM[BGM_1_5]);
	LoadSound(L"assets/Sound/BGM/BossBattle/tetsu_no_nioi.wav", &msBGM[BGM_BossBattle]);
	LoadSound(L"assets/Sound/BGM/Hanyou/tamawarashi.wav", &msBGM[BGM_Hanyou]);
	LoadSound(L"assets/Sound/BGM/StageSelect/hello_hello.wav", &msBGM[BGM_SelectScene]);
	LoadSound(L"assets/Sound/BGM/Title/hitech_factory.wav", &msBGM[BGM_Titel]);
	LoadSound(L"assets/Sound/BGM/Pause/entry_room.wav", &msBGM[BGM_Pause]);
	LoadSound(L"assets/Sound/BGM/Thotrial/tuto_and_rial.wav", &msBGM[BGM_Thotrial]);
	LoadSound(L"assets/Sound/BGM/Stage_Clear.wav", &msBGM[BGM_Stage_Clear]);
	LoadSound(L"assets/Sound/BGM/Game_Clear.wav", &msBGM[BGM_Game_Clear]);
	LoadSound(L"assets/Sound/BGM/ouchi_ni_inasai.wav", &msBGM[BGM_Ending]);
	
	//! SEの読み込み	
	LoadSound(L"assets/Sound/SE/Button01.wav", &msSE[SE_Button01]);
	LoadSound(L"assets/Sound/SE/Others/MoveCarsol.wav", &msSE[SE_MoveCarsol]);
	LoadSound(L"assets/Sound/SE/Others/GameOver.wav", &msSE[SE_GameOver]);
	LoadSound(L"assets/Sound/SE/Others/Select01.wav", &msSE[SE_Select01]);
	LoadSound(L"assets/Sound/SE/Others/Pause.wav", &msSE[SE_Pause]);
	LoadSound(L"assets/Sound/SE/Others/Monitor.wav", &msSE[SE_Monitor]);
	LoadSound(L"assets/Sound/SE/Others/Cancel.wav", &msSE[SE_Cancel]);
	LoadSound(L"assets/Sound/SE/Others/Error.wav", &msSE[SE_Error]);
	LoadSound(L"assets/Sound/SE/Others/Success.wav", &msSE[SE_Success]);


	//! プレイヤー
	LoadSound(L"assets/Sound/SE/Player/Jump.wav", &msSE[SE_Jump]);
	LoadSound(L"assets/Sound/SE/Player/damage2.wav", &msSE[SE_Damage]);
	LoadSound(L"assets/Sound/SE/Player/Heal.wav", &msSE[SE_Heal]);	
	LoadSound(L"assets/Sound/SE/Player/HPHeal.wav", &msSE[SE_HPHeal]);
	LoadSound(L"assets/Sound/SE/Player/GaugeHeal.wav", &msSE[SE_GaugeHeal]);
	LoadSound(L"assets/Sound/SE/Player/MissAtk.wav", &msSE[SE_Sting01]);
	LoadSound(L"assets/Sound/SE/Player/electric1_mono.wav", &msSE[SE_Taiden]);
	LoadSound(L"assets/Sound/SE/Player/electric2_mono.wav", &msSE[SE_TaidenAtk]);
	LoadSound(L"assets/Sound/SE/Player/NormalElec.wav", &msSE[SE_NormalElec]);
	LoadSound(L"assets/Sound/SE/Player/HardElec.wav", &msSE[SE_HardElec]);
	LoadSound(L"assets/Sound/SE/Player/tame.wav", &msSE[SE_Tame]);
	LoadSound(L"assets/Sound/SE/Player/kamae.wav", &msSE[SE_Kamae]);
	//! 敵
	//! チンピラー
	LoadSound(L"assets/Sound/SE/Enemy/Timpiller/Timpiller_Haziku.wav", &msSE[SE_Timpiller_Haziku]);
	LoadSound(L"assets/Sound/SE/Enemy/Timpiller/Timpiller_Sasaru.wav", &msSE[SE_Timpiller_Sasaru]);
	//! ホーダー
	LoadSound(L"assets/Sound/SE/Enemy/Hoder/Hoder_Sasaru.wav", &msSE[SE_Hoder_Sasaru]);
	LoadSound(L"assets/Sound/SE/Enemy/Hoder/Hoder_Haziku.wav", &msSE[SE_Hoder_Haziku]);
	//! スプリッター
	LoadSound(L"assets/Sound/SE/Enemy/Splitter/Splitter_Haziku.wav", &msSE[SE_Splitter_Haziku]);
	//! ネクトール
	LoadSound(L"assets/Sound/SE/Enemy/Necthor/Necthor_Haziku.wav", &msSE[SE_Necthor_Haziku]);
	LoadSound(L"assets/Sound/SE/Enemy/Necthor/Necthor_Sasaru.wav", &msSE[SE_Necthor_Sasaru]);
	LoadSound(L"assets/Sound/SE/Enemy/Necthor/Necthor_SPAtk.wav", &msSE[SE_Necthor_SPAtk]);
	LoadSound(L"assets/Sound/SE/Enemy/Necthor/Necthor_Atk.wav", &msSE[SE_Necthor_Atk]);
	LoadSound(L"assets/Sound/SE/Enemy/Necthor/Necthor_AtkSig.wav", &msSE[SE_Necthor_AtkSig]);
	LoadSound(L"assets/Sound/SE/Enemy/Necthor/Necthor_Bakuhatu.wav", &msSE[SE_Necthor_Bakuhatu]);

	//! ギミック関連
	LoadSound(L"assets/Sound/SE/Gimmick/Item.wav", &msSE[SE_Item]);
	LoadSound(L"assets/Sound/SE/Gimmick/Press.wav", &msSE[SE_Press]);
	LoadSound(L"assets/Sound/SE/Gimmick/CheackPoint.wav", &msSE[SE_CheackPoint]);
	LoadSound(L"assets/Sound/SE/Gimmick/Door_Stage.wav", &msSE[SE_Door_Stage]);
	LoadSound(L"assets/Sound/SE/Gimmick/Door_StageSelect.wav", &msSE[SE_Door_StageSelect]);
	LoadSound(L"assets/Sound/SE/Gimmick/Dynamo/OverHeat.wav", &msSE[SE_Dynamo_OverHeat]);
	LoadSound(L"assets/Sound/SE/Gimmick/Dynamo/OverHeat2.wav", &msSE[SE_Dynamo_OverHeat2]);
	LoadSound(L"assets/Sound/SE/Gimmick/Dynamo/NotSting.wav", &msSE[SE_Dynamo_NotSting]);
	LoadSound(L"assets/Sound/SE/Gimmick/Dynamo/Charge.wav", &msSE[SE_Dynamo_Charge]);
	LoadSound(L"assets/Sound/SE/garasu_break.wav", &msSE[SE_Glass_Break]);
	LoadSound(L"assets/Sound/SE/garasu_hajiku.wav", &msSE[SE_Glass_Hajiku]);
	LoadSound(L"assets/Sound/SE/bakuhatu.wav", &msSE[SE_Hanabi]);

	//! クリアサウンド
	LoadSound(L"assets/Sound/SE/GameClear.wav", &msSE[SE_Goal]);
	//! ゲームオーバーサウンド
	LoadSound(L"assets/Sound/SE/GameOver.wav", &msSE[SE_Lose]);

	//! SEの各種ソースボイスの作成
	for (int num = 0; num < SE_Max; num ++) {
		mpxAudio2->CreateSourceVoice(&mpSESourceVoice[num], (WAVEFORMATEX*)&msSE[num].wfx);
	}
}

SoundManager * SoundManager::GetInstance()
{	
	return mInstance;	
}

void SoundManager::Create()
{
	if (!mInstance)	{ mInstance = new SoundManager;	}
}


void SoundManager::Destroy()
{
	delete mInstance;
}


//! コンストラクタ
SoundManager::SoundManager()
{

	

	xAudio2_Init();



	mpxAudio2 = xAudio2_Get();
	mVolumeFade = 0;
	mBGMState = 0;
	mBGMPlayType = PlayType_None;



	for (int num = 0; num < SE_Max; num++) 	{
		msSE[num].buffer = { 0 };
	}

	for (int num = 0; num < BGM_Max; num++) {
		msBGM[num].buffer = { 0 };
	}

	// ソースボイスの中身をnullptrで空にする
	for (auto &ISourceVoice : mpSESourceVoice) 	{
		ISourceVoice = nullptr;
	}
	mpBGMSourceVoice = nullptr;


}

//! デストラクタ
SoundManager::~SoundManager()
{
	for (int num = 0; num < SE_Max; num++) {			
		mpSESourceVoice[num]->DestroyVoice();
		mpSESourceVoice[num] = nullptr;
		delete msSE[num].pDataBuffer;
	}

	for (int num = 0; num < BGM_Max; num ++) {
		delete msBGM[num].pDataBuffer;
	}

	if (mpBGMSourceVoice != nullptr) {
		mpBGMSourceVoice->DestroyVoice();
		mpBGMSourceVoice = nullptr;
	}
	xAudio2_Release();
}


/* ------------------------------------------------------------------------------------------------------------------------------
// SE再生関数　　　　　　　　　　　　　　　　　　　　　   //
// 引数 : 再生したいSEのID,ボリューム                     */
void SoundManager::PlaySE(eSEID _SEID, float _volume)
{
	IXAudio2SourceVoice*& pSV = mpSESourceVoice[_SEID];
	HRESULT hr;
	hr = mpxAudio2->CreateSourceVoice(&pSV, (WAVEFORMATEX*)&msSE[_SEID].wfx);

	msSE->buffer.LoopCount = XAUDIO2_NO_LOOP_REGION; // ループしない
	//! 音声を最初から最後まで再生されるように設定する
	msSE[_SEID].buffer.PlayBegin = 0;
	msSE[_SEID].buffer.PlayLength = 0;
	pSV->SubmitSourceBuffer(&msSE[_SEID].buffer);
	pSV->SetVolume(_volume);
	//! サウンドの再生
	pSV->Start(0);
}
//----------------------------------------------------------------------------------------------------------------------------

/* ---------------------------------------------------------------------------------------------------------------------------
// BGM再生関数
// 引数 : 再生したいBGMのID , 音量 , フェード再生かどうか         */
void SoundManager::PlayBGM(eBGMID _bgmid, float _volume, bool _fadein)
{
	//! BGMの再生状態を確認する
	if (mBGMPlayType == PlayType_None && mBGMState == false) 
	{
		//! フェード再生の場合
		if (_fadein) 
		{
			mBGMPlayType = PlayType_FadeIn;
			mVolume = 0;
		}
		//! 通常再生の場合
		else
		{
			mBGMPlayType = PlayType_Play;
			mVolume = _volume;
		}
		mVolumeFade = _volume;
		mPlayingBGM = _bgmid;
	}
}
//---------------------------------------------------------------------------------------------------------------------------

/* --------------------------------------------------------------------------------------------------------------------------
// BGMの停止関数                                                                                                           
// 引数 : フェードで停止するかどうか            */
void SoundManager::StopBGM( bool _fadeout)
{	
	if (mBGMPlayType == PlayType_None && mBGMState == true)
	{
		if (_fadeout)
		{
			mBGMPlayType = PlayType_FadeOut;
		}
		else
		{
			mBGMPlayType = PlayType_Stop;
		}
	}

	SoundUpdate();
}

void SoundManager::SetBGMVolume(float _volume)
{
	if (mpBGMSourceVoice != nullptr) {
		mpBGMSourceVoice->SetVolume(_volume);
	}
}
//-----------------------------------

/* ----------------------------------
// サウンド更新関数               */
void SoundManager::SoundUpdate()
{
	HRESULT hr;	
	const float fade = 0.003f;         //! フェードをする場合のフェードのボリュームの変化量 引数で設定できるといいかも

	//! BGMが再生されていないときのみ
	if (mBGMState == false) 
	{		
		switch (mBGMPlayType)
		{
		case PlayType_Play:			
			hr = mpxAudio2->CreateSourceVoice(&mpBGMSourceVoice, (WAVEFORMATEX*)&msBGM[mPlayingBGM].wfx);
			if (FAILED(hr))	{
				MessageBox(NULL, L"ソースボイスの作成に失敗しました", L"エラー発生", MB_OK);
			}

			mpBGMSourceVoice->SetVolume(mVolume);					
			msBGM[mPlayingBGM].buffer.LoopCount = XAUDIO2_LOOP_INFINITE; //! ループ再生
			
			hr = mpBGMSourceVoice->SubmitSourceBuffer(&msBGM[mPlayingBGM].buffer);
			if (FAILED(hr))	{
				MessageBox(NULL, L"ソースバッファーの送信に失敗しました", L"エラー発生", MB_OK);
			}
			mpBGMSourceVoice->Start(0);					
			mBGMPlayType = PlayType_None;
			mBGMState = true;
			break;

		case PlayType_FadeIn:
			mVolume += fade;			
			// 再生されていない時だけ生成する
			if (mpBGMSourceVoice == nullptr)	{
				// ソースボイスの生成
				hr = mpxAudio2->CreateSourceVoice(&mpBGMSourceVoice, (WAVEFORMATEX*)&msBGM[mPlayingBGM].wfx);
				if (FAILED(hr))	{
					MessageBox(NULL, L"ソースボイスの作成に失敗しました", L"エラー発生", MB_OK);
				}
				msBGM[mPlayingBGM].buffer.LoopCount = XAUDIO2_LOOP_INFINITE; // ループ再生

				// バッファーの送信
				hr = mpBGMSourceVoice->SubmitSourceBuffer(&msBGM[mPlayingBGM].buffer);
				if (FAILED(hr))	{
					MessageBox(NULL, L"ソースバッファーの送信に失敗しました", L"エラー発生", MB_OK);
				}
			}
			mpBGMSourceVoice->SetVolume(mVolume); // 音量の設定								
			mpBGMSourceVoice->Start(0);	
			// 設定された音量になったらフェード完了
			if (mVolume >= mVolumeFade) 	{
				mBGMPlayType = PlayType_None;
				mBGMState = true;
			}
			break;
		}		
	}
	//! BGMが再生されている時
	else
	{
		switch (mBGMPlayType)
		{
		case PlayType_Stop:
			mpBGMSourceVoice->Stop();
			mpBGMSourceVoice->DestroyVoice();
			mpBGMSourceVoice = nullptr;
			mBGMPlayType = PlayType_None;
			mBGMState = false;
			break;

		case PlayType_FadeOut:
			mVolume -= fade;
			mpBGMSourceVoice->SetVolume(mVolume); // 音量の設定								
			mpBGMSourceVoice->Start(0);
			// 音量が0以下になったらフェード完了
			if (mVolume <= 0.0f)	{
				mpBGMSourceVoice->Stop();
				// mpBGMSourceVoice->DestroyVoice();
				mpBGMSourceVoice = nullptr;
				mBGMPlayType = PlayType_None;
				mBGMState = false;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------------------------------------
void SoundManager::LoadSound(const wchar_t * _fileName, Sound *_sound)
{
	
	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	
	DWORD filetype;

	HANDLE hFile = CreateFile(
		_fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &_sound->wfx, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	_sound->pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, _sound->pDataBuffer, dwChunkSize, dwChunkPosition);

	_sound->buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
	_sound->buffer.pAudioData = _sound->pDataBuffer;  //buffer containing audio data
	_sound->buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	
}
