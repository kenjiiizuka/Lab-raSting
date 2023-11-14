#pragma once
#include <dinput.h>
#include <Windows.h>
#include "Vector2.h"
#include "FLOAT2.h"

/* ================================================== 
// �}�E�X�N���X                                    //
// ����� : �ђ� ���i                              */


/* -------------------------------------------------
// �}�E�X�̃{�^���̗񋓌^                         //
// �}�E�X�̃{�^���̎擾�Ɉ����Ƃ��Ďg�����߂̃��m //
// ---------------------------------------------- */
enum eMouseButton {
	Mouse_LButton,
	Mouse_RButton,
	Mouse_MButton
};


class DIMouse
{
public:
	DIMouse();                                        //! �R���X�g���N�^
	~DIMouse();                                       //! �f�X�g���N�^
	 
	void Init(LPDIRECTINPUT8 _mlpDI8, HINSTANCE _hinstance, HWND _hwnd);      //! ����������
	void Update();                                    //! �X�V����
	void UnInit();									  //! �I������

	void SetMouseSpeed(int _mousespeed);                   //! �}�E�X�X�s�[�h�̃Z�b�^�[
	Vector2 GetMouseVelocity();                            //! �}�E�X��1�t���[���̈ړ��ʂ�Ԃ����֐�
	Vector2 GetMouseVelocityNonFix();                      //! �}�E�X��1�t���[���̈ړ��ʂ�Ԃ����֐� Y�̒l�́{�[�␳�Ȃ�
	FLOAT2 GetMousePos();                                  //! �}�E�X�̌��݈ʒu(�`����W)�̎擾�֐�
	Vector2 GetMousePosVec();                              //! �}�E�X�̌��݈ʒu(�`����W)�̎擾�֐�
	FLOAT2 GetMouseWindowPos();                            //! �}�E�X�̃E�B���h�E��̍��W�̎擾�֐�
	bool GetMouseButtonTrigger(eMouseButton _button);      //! �}�E�X�̃{�^���̓��͂̃g���K�[�擾�֐�
	bool GetMouseButtonPress(eMouseButton _button);        //! �}�E�X�̃{�^���̓��͂̃v���X�擾�֐�     
	FLOAT2 GetMouseButtonTriggerPos(eMouseButton _button); //! �}�E�X�̃{�^�����������u�Ԃ̍��W���擾����֐�        
	FLOAT2 GetMouseButtonPressPos(eMouseButton _button);   //! �}�E�X�̃{�^���������Ă���ԍ��W���擾����֐�
	void SetMousePos(float _x, float _y);                  //! �}�E�X�ɍ��W(�`����W)���Z�b�g����֐�

private:
	LPDIRECTINPUTDEVICE8 mlpMouse;        //! �}�E�X�f�o�C�X
	DIMOUSESTATE mDICurrentMouseState;    //! �}�E�X�̏��
	DIMOUSESTATE mDIPrevMouseState;       //! �}�E�X�̑O�t���[���̏��
	int mDefoultSpeed = 0;                //! ���̃Q�[���J�n�O�̃}�E�X�̃X�s�[�h
	int mMouseSpeed;                      //! �}�E�X�̃X�s�[�h
	HWND mHwnd;                           //! ��������E�B���h�E�n���h��


};

