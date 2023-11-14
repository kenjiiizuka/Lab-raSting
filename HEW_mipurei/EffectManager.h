#pragma once
#include "FollowEffect.h"
#include "Vector2.h"
#define MaxEffect 100 //! �G�t�F�N�g�̍ő哯���Đ���
#define EffMgr EffectManager::GetInstance()


class EffectManager
{
public:
	static EffectManager * GetInstance();
	static void Create();
	static void Destroy();
	void PlayEffect(eEffect _id, float _x,float _y,float width, float height,float _angle = 0,int speed = 8);
	void PlayEffect(eEffect _id, Vector2 _pos, Vector2 _size, float _angle = 0, int speed  = 8);
	void PlayFollowEffect(eEffect _effect, float & _x, float & _y , float width, float height, bool _loop  = false); //!
	void LoopStop(eEffect _effect);
	void EffectUpdate(); // �X�V����
	void EffectDraw();
	EffectState GetState(eEffect _effect);
	eEffect GetEffectID();
	void Reset(); //! �S�ẴG�t�F�N�g���f���[�g�����������Ă���܂�
private:
	EffectManager();
	~EffectManager();

	void LoadEffect(const wchar_t * _fileName, eEffect _effectID, float _width, float _height, int _splitx, int _splity, int _animspeed = 8);

	static EffectManager* Instance;
	Effect * mcpEffect[MaxEffect];        //! �G�t�F�N�g�N���X�w�肳�ꂽ�G�t�F�N�g�𐶐����Ďg��
	FollowEffect * mcpFollowEffect[MaxEffect]; //! �Ǐ]����G�t�F�N�g�N���X
	EffectInf msEffectInf[EffectMax];    //! �G�t�F�N�g�̍\����
	EffectState mEffectState[EffectMax]; //! �e�G�t�F�N�g�̏��
};

