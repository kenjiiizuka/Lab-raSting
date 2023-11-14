#include "GameObject.h"
#include "Camerah.h"


//! 描画処理
void GameObject::Draw()
{	
	//! 座標をチェックして画面内になかったら描画をしない
	bool DrawCheack = true;
	if (!(mcVec.x < 4.0f && mcVec.x > -4.0f)) {
		DrawCheack = false;
	}

	if (mCameraActiv == true) {
		CAMERA->CameraFix(this);    //! カメラの情報をオブジェクトに反映させる			
	}

	mcpSprite->SetSize(msSize.x * msScale.x, msSize.y * msScale.y); //! カメラから見たサイズを反映させる
	if (mDrawActiv && DrawCheack) {		
		mcpSprite->Update();                //! 描画のための処理は描画処理で行う(FadeIn,FadeOut時に描画できるようにするために)
		mcpSprite->Draw();                  //! 描画する
	}	
}

//! 描画機能のオンオフ切り替え
void GameObject::SetDrawActiv(bool _drawState)
{
	mDrawActiv = _drawState;
}

//! 座標のゲッター
Vector2 GameObject::GetVec()
{
	return mcVec;
}

//! 座標のセッター
void GameObject::SetVec(Vector2 _vec)
{
	mcVec = _vec;
}

//! 拡大縮小率のセッター
void GameObject::SetScale(float _x, float _y)
{
	msScale = FLOAT2(_x, _y);
}

void GameObject::SetSize(float _width, float _hieght)
{
	msSize = FLOAT2(_width, _hieght);
}

void GameObject::SetSize(Vector2 _size)
{
	msSize.x = _size.x;
	msSize.y = _size.y;
}

//! 描画クラスのゲッター
Sprite * GameObject::GetSprite()
{
	return mcpSprite;
}

bool GameObject::GetAlive()
{
	return mAlive;
}

void GameObject::SetCameraActiv(bool _state)
{
	mCameraActiv = _state;
}

ObjectTag GameObject::GetTag()
{
	return mTag;
}
