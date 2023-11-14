#pragma once
#include "BaseEnemy.h"
#include "Image.h"

//! Splitter�i�ʏ̕��􂷂�G��j
class SplitUpperEnemy :
	public BaseEnemy
{
public:
	SplitUpperEnemy(Vector2 _vec, bool & _combi);
	~SplitUpperEnemy();

	void Update();
	void Draw();
	void SetMoveVec(Vector2 _move); //! �ړ��ʂ̃Z�b�^�[	
	void FixVec(Vector2 _vec); //! �����蔻���ɍ��W���C������
	Box * GetBoxCol() override; 
	TailReaction SetStingPower(float _Power, bool _Elect) override;
private:
	bool & Combi;
	void Destroy();  //! �|���Ƃ��̊֐�
	int Count;
	Box * MyCol;     //! �����蔻��

	Vector2 SplitedColPos; //! �����蔻��̒��S�����W(�����)
	Image mImage;
};

