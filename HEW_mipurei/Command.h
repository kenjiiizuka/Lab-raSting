#pragma once
#include "AnimationHitObject.h"
#include "Box.h"
#include "Cursol.h"
class Command 
	: public AnimationHitObject
{
public:
	Command();                                  //! �R���X�g���N�^
	Command(ID3D11ShaderResourceView * _tex);   //! �e�N�X�`���[���Z�b�g�ł���R���X�g���N�^
	~Command();				                    //! �f�X�g���N�^
	void Update();                              //! �X�V����
	void Draw();
	bool Selected();                            //! �I�����ꂩ�ǂ���
	void SetVec(Vector2 _vec) override;
	void SetCursol(Cursol * _cursol);           //! �J�[�\���̃Z�b�^�[
	void SetSize(float _x, float _y) override;  //! �T�C�Y�̃Z�b�^�[
	void SetClose(bool _close);
	bool GetClosed();                           //! �R�}���h�����؂�������Ԃ��Q�b�^�[
	Vector2 GetNextCommandPos();                //! �����̉��ɗ���R�}���h�̍��W��Ԃ��@��{�I�ɃR�}���h�͏c���тŏc�̕��͓����Ȃ̂Ŏ��̃R�}���h�̈ʒu���v�Z�ł����֗����Ȃ��Ă�������
	AnimationHitObject * GetFrame();            //! �R�}���h�̌��̘g�̃Q�b�^�[
private:						                				                
	Cursol * mcpCursol; 		                //! ���̃R�}���h�ɑΉ������J�[�\��
	Box * mcpBox;                               //! �����蔻����
	bool CurrentHit;                            //! ���݂̓������� �������Ă�����傫������
	bool PrevHit;                               //! �O�t���[���̓�������
	FLOAT2 DefaultSize;                         //! �f�t�H���g�̃T�C�Y
	AnimationHitObject * Bg;                   //! �R�}���h�̈͂�
	bool Close = false;
	bool Opned = false;
	bool Closed  =false;                       //! �N���[�Y�����t���O
	float Arufa;
};

