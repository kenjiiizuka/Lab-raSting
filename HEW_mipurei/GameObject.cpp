#include "GameObject.h"
#include "Camerah.h"


//! �`�揈��
void GameObject::Draw()
{	
	//! ���W���`�F�b�N���ĉ�ʓ��ɂȂ�������`������Ȃ�
	bool DrawCheack = true;
	if (!(mcVec.x < 4.0f && mcVec.x > -4.0f)) {
		DrawCheack = false;
	}

	if (mCameraActiv == true) {
		CAMERA->CameraFix(this);    //! �J�����̏����I�u�W�F�N�g�ɔ��f������			
	}

	mcpSprite->SetSize(msSize.x * msScale.x, msSize.y * msScale.y); //! �J�������猩���T�C�Y�𔽉f������
	if (mDrawActiv && DrawCheack) {		
		mcpSprite->Update();                //! �`��̂��߂̏����͕`�揈���ōs��(FadeIn,FadeOut���ɕ`��ł���悤�ɂ��邽�߂�)
		mcpSprite->Draw();                  //! �`�悷��
	}	
}

//! �`��@�\�̃I���I�t�؂�ւ�
void GameObject::SetDrawActiv(bool _drawState)
{
	mDrawActiv = _drawState;
}

//! ���W�̃Q�b�^�[
Vector2 GameObject::GetVec()
{
	return mcVec;
}

//! ���W�̃Z�b�^�[
void GameObject::SetVec(Vector2 _vec)
{
	mcVec = _vec;
}

//! �g��k�����̃Z�b�^�[
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

//! �`��N���X�̃Q�b�^�[
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
