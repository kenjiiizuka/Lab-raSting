#include "AnimationHitObject.h"
#include "AnimationSprite.h"
#include "TextureManager.h"
#include <math.h>

//! �R���X�g���N�^
AnimationHitObject::AnimationHitObject()
{
	mcpAnimsprite = new AnimationSprite(mcVec);
	mcpSprite = mcpAnimsprite;	
	msSize = FLOAT2(0.2f,0.2f);
	mcpShape = nullptr;
	//! ���̂悤�ɉ摜��A�j���[�V�����e�[�u���͌p����̃R���X�g���N�^���Őݒ肷��
	/*mcpSprite->SetTexture(TexMgr->GetTextuer(Tex_Game));
	mcpAnimsprite->SetAnimtionTable(1, 1);*/	
}

//! �f�X�g���N�^
AnimationHitObject::~AnimationHitObject()
{	
	delete mcpAnimsprite;
}

//! �X�V����
void AnimationHitObject::Update()
{
	
}

//! �����蔻�菈����
void AnimationHitObject::LastUpdate()
{
	
}


//! Hit�t���O�̃Z�b�^�[
void AnimationHitObject::SetHit(bool _state)
{
	mHitFlg = _state;
}
//! �����蔻��̃I���I�t�؂�ւ��̃Z�b�^�[
void AnimationHitObject::SetHitActiv(bool _state)
{
	if (mcpShape != nullptr) {
		mcpShape->SetActiv(_state);
	}
}

AnimationSprite * AnimationHitObject::GetAnimSprite()
{
	return mcpAnimsprite;
}




