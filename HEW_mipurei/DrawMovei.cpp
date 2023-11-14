#include "DrawMovei.h"
#include "WinMain.h"
#include "TextureManager.h"


DrawMovei::DrawMovei(std::wstring _filepass, int _maxSlide,Vector2 _maxSize)
{
	//! スライドのBG用オブジェクト
	SlideBG = new StaticObject();
	SlideBG->SetCameraActiv(false);
	SlideBG->SetSize(0, 0);
	SlideBG->SetDrawActiv(false);
	SlideBG->GetSprite()->SetTexture(TEXTURE(Tex_Pause_Bg01));
	SlideBG->GetSprite()->SetUVSpriteInf(10,11,1);

	//! スライド描画用オブジェクト
	SlideBoard = new StaticObject();
	SlideBoard->SetCameraActiv(false);
	SlideBoard->SetSize(_maxSize.x, _maxSize.y);
	SlideBoard->SetDrawActiv(false);
	//! 変数の初期設定
	AnimCnt = 0;
	FileName = _filepass;
	UnInit = Init = End = Loaded = Start = false;
	LoadNext = true;
	SlideCnt = AnimCnt = 0;
	AnimSpeed = 8;
	MaxSlide = _maxSlide;
	MaxSize = _maxSize;
	Loop = false;
	

}

DrawMovei::~DrawMovei()
{
	delete SlideBoard;
	delete SlideBG;
	if (CurrentTex != nullptr) { COM_SAFE_RELEASE(CurrentTex); }
}

void DrawMovei::Update()
{
	if (Start) {
		MoveiState = true;
		SlideBG->SetDrawActiv(true);
		if (NowSize.x < MaxSize.x + (MaxSize.x / 20.0f) 
			&& NowSize.y < MaxSize.y + (MaxSize.y / 20.0f)) {
			NowSize.x += MaxSize.x /20.0f;
			NowSize.y += MaxSize.y /20.0f;
		}
		else {
			Init = true; //! 準備完了フラグ
			SlideBoard->SetDrawActiv(true);
		}
	}
	//! スライドの再生
	if (Init && !UnInit) {
		//! 経過フレームによって画像を切り替えうフラグを立てる
		if (AnimCnt > AnimSpeed) {
			LoadNext = true;
			COM_SAFE_RELEASE(CurrentTex);
			CurrentTex = nullptr;
			AnimCnt = 0;
		}

		//! 次の画像の読み込み
		if (LoadNext) {
			SlideCnt++;
			std::wstring tmp = FileName + L"(" + std::to_wstring(SlideCnt) + L").jpg";
			const wchar_t * Pass = tmp.c_str();
		//	LoadMovieTexture(tmp.c_str(), &CurrentTex);
			LoadTexture(tmp.c_str(), &CurrentTex);
			SlideBoard->GetSprite()->SetTexture(CurrentTex);
			LoadNext = false;
		}
		//! 最後のスライドまで行ったか判断
		if (SlideCnt == MaxSlide) { 
			if (Loop) {
				SlideCnt = 0;
			}
			else {
				UnInit = true;
				SlideBoard->SetDrawActiv(false);
			}
		}
		//! アニメーションのカウント
		AnimCnt++;
	}

	if (UnInit) {	
		LoadNext = false;
		//! サイズを小さくする
		if (NowSize.x > 0.0f && NowSize.y > 0) {
			NowSize.x -= MaxSize.x / 10.0f;
			NowSize.y -= MaxSize.y / 10.0f;
		}
		//! 大きさがゼロになったら終わり
		else { 
			End = true;
			MoveiState = false;
			Start = false;
			Init = false;
			UnInit = false;
			SlideCnt = 0;	
			SlideBG->SetDrawActiv(false);
		}
	}
	//! サイズのセット
	SlideBG->SetSize(NowSize.x, NowSize.y);
}

void DrawMovei::Draw()
{
	SlideBG->Draw();
	SlideBoard->Draw();
}

void DrawMovei::StartMovei(int _animSpeed, Vector2 _pos)
{
	//! 開始も終了もしていないときだけスタートする
	if (!Start && !End) {
		AnimSpeed = _animSpeed;
		SlideBoard->SetVec(_pos);
		SlideBG->SetVec(_pos);
		SlideBG->SetCameraActiv(true);
		SlideBoard->SetCameraActiv(true);
		Start = true;
	}
}

void DrawMovei::SetLoop(bool _loop)
{
	Loop = _loop;
}

bool DrawMovei::GetMoveiState()
{
	return MoveiState;
}

void DrawMovei::LoadMovieTexture(const wchar_t* _fileName, ID3D11ShaderResourceView** _outTexture)
{
	//HRESULT hr;
	DIRECT3D *d3d = Direct3D_Get();	
	LoadTexture(_fileName, _outTexture);
	//２バイト文字列を渡さないといけない　L　をつけると２バイト文字列になる
}
