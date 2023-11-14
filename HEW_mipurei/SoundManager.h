#pragma once
#include "eSoundID.h"
#include "xAudio.h"

//===============================================================
// �T�E���h�}�l�[�W���[�N���X
// SE�ABGM���Đ��ł��܂��B
// �t���[�����Ƃ�BGM�̏�Ԃ��X�V���Ă���̂ŁABGM���ēx�Ȃ炵�����ꍇ��BGM���~�߂āA
// ���̃t���[���ōĐ��p�̊֐����g�p���Ă�������
// ����� : �ђˌ��i
//===============================================================
#define SoundMgr SoundManager::GetInstance()
#define PLAYSE(seid,vol) SoundManager::GetInstance()->PlaySE(seid,vol)

class SoundManager
{
	//! �T�E���h�̃f�[�^�̍\����
	typedef struct {
		XAUDIO2_BUFFER buffer;
		WAVEFORMATEXTENSIBLE wfx;
		BYTE * pDataBuffer;
	}Sound;

public:
	static SoundManager* GetInstance();
	static void Create();
	static void Destroy();

	void PlaySE(eSEID _SEID, float _volume = 1.0f);                          //! SE�Đ��֐�
	void PlayBGM(eBGMID _BGMID, float _volume = 1.0f, bool _fadein = false); //! BGM�Đ��֐�
	void StopBGM(bool _fadeout = false);                                     //! BGM��~�֐�
	void SetBGMVolume(float _volume);                                        //! BGM�̉��ʂ̃Z�b�^�[
	void SoundUpdate();                                                      //! �X�V����
	void Init();                                                             //! ����������

private:
	SoundManager();                                             //! �R�X�g���N�^
	~SoundManager();                                            //! �f�X�g���N�^
	void  LoadSound(const wchar_t * _fileName, Sound * _sound); //! �T�E���h�̓ǂݍ���

	static SoundManager* mInstance;                             //! ���g�̃C���X�^���X	
	IXAudio2* mpxAudio2;                                        //! xAudio2�̃C���X�^���X
	IXAudio2SourceVoice* mpSESourceVoice[SE_Max];               //! SE�\�[�X�{�C�X 
	IXAudio2SourceVoice* mpBGMSourceVoice;                      //! BGM�\�[�X�{�C�X 
	Sound msSE[SE_Max];                                         //! SE�̃f�[�^
	Sound msBGM[BGM_Max];                                       //! BGM�̃f�[�^
	bool  mBGMState;                                            //! BGM�̌��݂̏��  true---�Đ��� false---�Đ����Ă��Ȃ�
	int   mBGMPlayType;                                         //! BGM�̍Đ��d���@��~�̎d��
	float mVolume;                                              //! BGM�̉��� 
	float mVolumeFade;                                          //! �t�F�[�h����Ƃ��Ɏg��
	eBGMID mPlayingBGM;                                         //! �Đ����Ă���BGM 
	
};

