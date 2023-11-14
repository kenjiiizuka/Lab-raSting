#pragma once
#include "direct3d.h"
#include "eTexture.h"

#define TexMgr TextureManager::GetInstance()
#define TEXTURE(TexName) TextureManager::GetInstance()->GetTextuer(TexName)

void LoadTexture(const wchar_t * _fileName, ID3D11ShaderResourceView** _outTexture);  // �e�N�X�`���̓ǂݍ���

// �e�N�X�`���[�}�l�[�W���[
class TextureManager
{
public:
	static TextureManager * GetInstance();	
	static void Create();
	static void Destroy();
	ID3D11ShaderResourceView* GetTextuer(eTextureID _texID); // �e�N�X�`���̃Q�b�^�[

private:
	TextureManager();
	~TextureManager();

	ID3D11ShaderResourceView* mpTexture[Tex_Max];

	static TextureManager * Instance;
    
};
