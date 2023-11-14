#pragma once
#include "Vector2.h"
#include "direct3d.h"
#include "VERTEX2D.h"
#include "FLOAT2.h"
// �Î~��̕`��N���X�@

class Sprite
{	
public:
	Sprite(Vector2 & _pos);
	virtual ~Sprite();
	virtual void Update();
	void Draw();

	void SetTexture(ID3D11ShaderResourceView* _texture);                             //! �e�N�X�`���̃Z�b�^�[
	void SetSize(float _width, float _vertical);                                     //! �`��T�C�X�̃Z�b�^�[
	void SetUVSpriteInf(int _num, int xsplit, int splity, bool _state = true);       //! UV���̃Z�b�^�[
	void SetAngle(double _angle, float _centerx = 0.5f, float _centery = 0.5f);      //! ��]�p�x�A��]�̒��S�̃Z�b�^�[
	void SetColor(float _r, float _g, float _b);                                     //! �F���̃Z�b�^�[
	void SetArufa(float _a);                                                         //! �����x�̃Z�b�^�[
	void SetTexNum(int _num, int xsplit, int splity,bool _state = true);             //! �Z�b�g����Ă���e�N�X�`���̉��R�}�ڂ�`�悵�Ăق������Z�b�g����(�`�b�v��̉摜����ł�)
	                                                         //! �A�j���[�V�����J�E���g�����Z�b�g
protected:
	// �����o�ϐ�
	ID3D11ShaderResourceView* mTexture; //! �e�N�X�`��
	ID3D11Buffer* mVertexBuffer;        //! ���_�o�b�t�@
	Vector2 & msPos;			        //! ���S���W
	FLOAT2  msSize;					//! �`��T�C�Y
	float mPosU, mPosV;                 //! UV���W
	float mSizeU, mSizeV;               //! UV�̃T�C�Y�E�E�E�e�N�X�`���̕`��͈�
	double  mAngle;				        //! �`��p�x
	float mCenterX, mCenterY;           //! ��]�̒��S�ʒu
	RGBA msColor;                       //! �F

private:
	int TexNum;                         //! �`�b�v��̍��W�̉��R�}�ڂ�`�悵�Ăق����̂��̃Z�b�^�[
	int XSplit;                         //! ���̕�����
	int YSplit;                  		//! �c�̕�����
	bool SplitDraw;                     //! �R�}�����Ă����ĕ`�悷��Ƃ���
};
