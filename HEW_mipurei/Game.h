#pragma once
#include <Windows.h>

/* ======================================= 
**   Game�N���X(�V���O���g��)           **
** �Q�[���S�̂̍X�V�A�`�������N���X �@**
** ����� : �ђ� ���i                   **
** =====================================*/

#define GameIns Game::GetInstance()
#define ACTIV Game::GetInstance()->GetActiv()
//! ����n���̗񋓌^
enum Operation{
	Controller, //! �R���g���[���[����
	Mouse,      //! �}�E�X����
};

class Game
{
public:
	static Game* GetInstance();                        //! ���Ԃ��擾����֐�
	static void Create();		                       //! �����p�֐�
	static void Destroy();				               //! �N���X�̔j���p�̊֐�

	void GameInit(HINSTANCE _hinstsnce, HWND _hwnd);
	void GameUpdate();
	void GameDraw();
	void GameRelease();
	bool GetActiv();
	void SetActiv(bool _state);
	Operation GetOperation(); //! ���݂̑�����@���擾
	void ChangeOperation(Operation _operation); //! ������@�̐؂�ւ��֐�
private:
	Game();  //! �R���X�g���N�^
	~Game(); //! �f�X�g���N�^

	static Game* mcpInstance;

	//! ������@
	Operation mOperation; //! ���݂̑�����@

	bool Activ = true; //!�@���̃t���O���I�t�ɂȂ�����Q�[�����I������
};

