#pragma once
#include "FollowEffect.h"
#include "Vector2.h"
#define MaxEffect 100 //! エフェクトの最大同時再生数
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
	void EffectUpdate(); // 更新処理
	void EffectDraw();
	EffectState GetState(eEffect _effect);
	eEffect GetEffectID();
	void Reset(); //! 全てのエフェクトをデリートし初期化してくれます
private:
	EffectManager();
	~EffectManager();

	void LoadEffect(const wchar_t * _fileName, eEffect _effectID, float _width, float _height, int _splitx, int _splity, int _animspeed = 8);

	static EffectManager* Instance;
	Effect * mcpEffect[MaxEffect];        //! エフェクトクラス指定されたエフェクトを生成して使う
	FollowEffect * mcpFollowEffect[MaxEffect]; //! 追従するエフェクトクラス
	EffectInf msEffectInf[EffectMax];    //! エフェクトの構造体
	EffectState mEffectState[EffectMax]; //! 各エフェクトの状態
};

