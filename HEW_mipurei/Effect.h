#pragma once
#include "direct3d.h"
#include "VERTEX2D.h"
#include "eEffecth.h"

//! �G�t�F�N�g�̏��̍\����
typedef struct {	
	ID3D11ShaderResourceView* mTexture; // �e�N�X�`��	
	eEffect ID;
	int Split_x;
	int Split_y;
	float mSize_x, mSize_y; // �`��T�C�Y
	float pos_x;
	float pos_y;
	float Angle;
	int AnimSpeed;
}EffectInf;


/* =========================== ** 
** Effect�N���X                **
** �G�t�F�N�g��`�悵�܂�      **
** =========================== */

//! ��{�I��EffectManager�N���X�ł����G��Ȃ��悤�ɂ��ĉ������B

class Effect
{
public:
	Effect(EffectInf _effect, eEffect _effectid);      //! �R���X�g���N�^
	~Effect();					        //! �f�X�g���N�^
	virtual void Update();				//! �X�V����
	void Draw();				        //! �`�揈��
	void SetPos(float _x, float _y);    //! ���W�̃Z�b�^�[
	bool GetEndFlg();			        //! �G�t�F�N�g�̏I���t���O�̃Q�b�^�[
	eEffect GetEffectID();              //! �G�t�F�N�g��ID
protected:						        
	ID3D11Buffer* mVertexBuffer;        //! ���_�o�b�t�@
	EffectInf msEffectInf;              //! �G�t�F�N�g�̍\����
	RGBA mColor;                        //! �J���[���
	int mAnimFrameCnt; 	                //! �A�j���[�V�����p�̃t���[���J�E���g
	int mSplit_x, mSplit_y;             //! �A�j���[�V�����̃R�}�ԍ�
	int * mpAnimTable;                  //! �A�j���[�V�����e�[�u��
	float mSize_u;                      //! 1�R�}�̉��̒���
	float mSize_v;                      //! 1�R�}�̏c�̒���
	float mScale_x;                     //! �J�������猩���Ƃ��̊g��k��
	float mScale_y;                     //! �J�������猩���Ƃ��̊g��k��
	float mLength;                      //! �X�v���C�g�̒��� 
	double mdAngle;                     //! �p�x
	eEffect mEffectID;                  //! �G�t�F�N�g�̎��
	bool mEndflg;                       //! �G�t�F�N�g�̏I���t���O
};




