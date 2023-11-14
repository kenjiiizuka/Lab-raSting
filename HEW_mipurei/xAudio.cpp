#include "xAudio.h"



#pragma comment (lib, "xaudio2.lib")

static IXAudio2* pxAudio2 = nullptr;
static IXAudio2MasteringVoice* pMasterVioce = nullptr;


// XAudio2�̏�����
bool xAudio2_Init()
{
	HRESULT hr;	

	//ZeroMemory(pxAudio2, sizeof(IXAudio2));

	// COM�̏�����	
	/*hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		MessageBox(NULL,L"COM�̏������Ɏ��s���܂���",L"�G���[����",MB_OK);
	}	*/

	// XAudio2�G���W���̃C���X�^���X�쐬	
	hr = XAudio2Create(&pxAudio2,0);
	if (FAILED(hr)) 
	{
		MessageBox(NULL,L"XAudio2�̃C���X�^���X�쐬�Ɏ��s���܂���",L"�G���[����",MB_OK);
	}

	// �}�X�^�����O�����̍쐬�i�}�X�^���H�C�X�j
	
	hr = pxAudio2->CreateMasteringVoice(&pMasterVioce);
	if (FAILED(hr)) 
	{
		MessageBox(NULL,L"�}�X�^�{�C�X�̍쐬�Ɏ��s���܂���",L"�G���[����",MB_OK);
	}

	return true;
}

// XAudio2�̏I������
void xAudio2_Release()
{
	// �}�X�^�[�{�C�X�̔j��
	if (pMasterVioce) {
		pMasterVioce->DestroyVoice();
		pMasterVioce = nullptr;
	}

	// xAudio2�̉��
	if (pxAudio2) {
		pxAudio2->Release();
		pxAudio2 = nullptr;
	}

	CoUninitialize();
}

IXAudio2 * xAudio2_Get()
{
	return pxAudio2;
}


HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}

	return S_OK;

}


HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
