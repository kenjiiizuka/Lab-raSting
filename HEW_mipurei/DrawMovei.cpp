#include "DrawMovei.h"
#include "WinMain.h"
#include "TextureManager.h"


DrawMovei::DrawMovei(std::wstring _filepass, int _maxSlide,Vector2 _maxSize)
{
	//! �X���C�h��BG�p�I�u�W�F�N�g
	SlideBG = new StaticObject();
	SlideBG->SetCameraActiv(false);
	SlideBG->SetSize(0, 0);
	SlideBG->SetDrawActiv(false);
	SlideBG->GetSprite()->SetTexture(TEXTURE(Tex_Pause_Bg01));
	SlideBG->GetSprite()->SetUVSpriteInf(10,11,1);

	//! �X���C�h�`��p�I�u�W�F�N�g
	SlideBoard = new StaticObject();
	SlideBoard->SetCameraActiv(false);
	SlideBoard->SetSize(_maxSize.x, _maxSize.y);
	SlideBoard->SetDrawActiv(false);
	//! �ϐ��̏����ݒ�
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
			Init = true; //! ���������t���O
			SlideBoard->SetDrawActiv(true);
		}
	}
	//! �X���C�h�̍Đ�
	if (Init && !UnInit) {
		//! �o�߃t���[���ɂ���ĉ摜��؂�ւ����t���O�𗧂Ă�
		if (AnimCnt > AnimSpeed) {
			LoadNext = true;
			COM_SAFE_RELEASE(CurrentTex);
			CurrentTex = nullptr;
			AnimCnt = 0;
		}

		//! ���̉摜�̓ǂݍ���
		if (LoadNext) {
			SlideCnt++;
			std::wstring tmp = FileName + L"(" + std::to_wstring(SlideCnt) + L").jpg";
			const wchar_t * Pass = tmp.c_str();
		//	LoadMovieTexture(tmp.c_str(), &CurrentTex);
			LoadTexture(tmp.c_str(), &CurrentTex);
			SlideBoard->GetSprite()->SetTexture(CurrentTex);
			LoadNext = false;
		}
		//! �Ō�̃X���C�h�܂ōs���������f
		if (SlideCnt == MaxSlide) { 
			if (Loop) {
				SlideCnt = 0;
			}
			else {
				UnInit = true;
				SlideBoard->SetDrawActiv(false);
			}
		}
		//! �A�j���[�V�����̃J�E���g
		AnimCnt++;
	}

	if (UnInit) {	
		LoadNext = false;
		//! �T�C�Y������������
		if (NowSize.x > 0.0f && NowSize.y > 0) {
			NowSize.x -= MaxSize.x / 10.0f;
			NowSize.y -= MaxSize.y / 10.0f;
		}
		//! �傫�����[���ɂȂ�����I���
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
	//! �T�C�Y�̃Z�b�g
	SlideBG->SetSize(NowSize.x, NowSize.y);
}

void DrawMovei::Draw()
{
	SlideBG->Draw();
	SlideBoard->Draw();
}

void DrawMovei::StartMovei(int _animSpeed, Vector2 _pos)
{
	//! �J�n���I�������Ă��Ȃ��Ƃ������X�^�[�g����
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
	//�Q�o�C�g�������n���Ȃ��Ƃ����Ȃ��@L�@������ƂQ�o�C�g������ɂȂ�
}
