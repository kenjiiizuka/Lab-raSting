#pragma once
#include "direct3d.h"
#include "eTexture.h"

#define TexMgr TextureManager::GetInstance()
#define TEXTURE(TexName) TextureManager::GetInstance()->GetTextuer(TexName)

void LoadTexture(const wchar_t * _fileName, ID3D11ShaderResourceView** _outTexture);  // テクスチャの読み込み

// テクスチャーマネージャー
class TextureManager
{
public:
	static TextureManager * GetInstance();	
	static void Create();
	static void Destroy();
	ID3D11ShaderResourceView* GetTextuer(eTextureID _texID); // テクスチャのゲッター

private:
	TextureManager();
	~TextureManager();

	ID3D11ShaderResourceView* mpTexture[Tex_Max];

	static TextureManager * Instance;
    
};
