#include "EffectManager.h"
#include <stdio.h>
#include "TextureManager.h"

EffectManager* EffectManager::Instance = nullptr;

EffectManager::EffectManager()
{
	for (int i = 0; i < MaxEffect; i++) {
		mcpEffect[i] = nullptr;
		mcpFollowEffect[i] = nullptr;
	}

	//! 解放の時にエラーが出ないように初期化する
	for (int i = 0; i < eEffect::EffectMax; i++) {
		msEffectInf[i].mTexture = nullptr;
	}

	//! エフェクトの読み込み
	LoadEffect(L"assets/Debug/SampleEffect01.png",HitEffect,0.2f,0.2f,5,1);
	LoadEffect(L"assets/Gimmick/Dynamo/ChargeEffect_01.png", DynamoCharge, 0.2f, 0.2f, 10, 1);
	LoadEffect(L"assets/Player/Recovery.png", Recovery, 0.5f, 0.5f, 8, 1);
	LoadEffect(L"assets/Effect/bolttest.png", Elect, 0.8f, 0.8f, 30, 1);
	LoadEffect(L"assets/Gimmick/Goal/Effect01.png", GoalEffect01,0.5f,0.5f,10,1);
	LoadEffect(L"assets/Effect/SuperElect.png", ElectSuper02, 0.55f, 0.55f, 10, 1);
	LoadEffect(L"assets/Effect/ElectSuper2.png", ElectSuper01, 0.55f, 0.55f, 10, 1);
	LoadEffect(L"assets/Effect/Houden.png", DisCharge, 0.3f, 0.2f, 10, 1);
	LoadEffect(L"assets/Effect/effect1.png", Hibana, 0.3f, 0.2f, 5, 1);
	LoadEffect(L"assets/Effect/effect17.png", Explosion, 0.5f, 0.5f, 10, 1);
	LoadEffect(L"assets/Effect/bakuhatu.png", Explosion02, 0.5f, 0.5f, 10, 1);
	LoadEffect(L"assets/Effect/effect11.png", HitEffect01,0.5f,0.5f,6,1);
	LoadEffect(L"assets/Effect/effect4.png", HitEffect02, 0.5f, 0.5f, 10, 1);
	LoadEffect(L"assets/Effect/effect6.png", DaynamoEffect, 0.5f, 0.5f, 10, 1);
	//! 花火エフェクト
	LoadEffect(L"assets/Effect/Hanabi_Blue.png", Hanabi_B, 0.5f, 0.5f, 14, 1);
	LoadEffect(L"assets/Effect/Hanabi_Red.png", Hanabi_R, 0.5f, 0.5f, 14, 1);
	LoadEffect(L"assets/Effect/Hanabi_Yellow.png", Hanabi_Y, 0.5f, 0.5f, 14, 1);
	LoadEffect(L"assets/Effect/Hanabi_Green.png", Hanabi_G, 0.5f, 0.5f, 14, 1);
	LoadEffect(L"assets/Effect/Hanabi_Purple.png", Hanabi_P, 0.5f, 0.5f, 14, 1);
	LoadEffect(L"assets/Effect/Hanabi_Orenge.png", Hanabi_O, 0.5f, 0.5f, 14, 1);
	LoadEffect(L"assets/Effect/hpani.png", Hp_Recvery, 0.5f, 0.5f, 6, 1);
}

EffectManager::~EffectManager()
{
	for (int i = 0; i < MaxEffect; i++) {
		delete mcpEffect[i];
		delete mcpFollowEffect[i];
	}


	for (int num = 0; num < EffectMax; num++) {
		if (msEffectInf[num].mTexture == nullptr) {
			COM_SAFE_RELEASE(msEffectInf[num].mTexture);
		}
	}
}

//! エフェクトの読み込み関数
void EffectManager::LoadEffect(const wchar_t * _fileName, eEffect _effectID ,float _width ,float _height, int _splitx, int _splity, int _animspeed)
{
	LoadTexture(_fileName, &msEffectInf[_effectID].mTexture);
	msEffectInf[_effectID].mSize_x = _width;
	msEffectInf[_effectID].mSize_y = _height;
	msEffectInf[_effectID].Split_x = _splitx;
	msEffectInf[_effectID].Split_y = _splity;
	msEffectInf[_effectID].AnimSpeed = _animspeed;
	msEffectInf[_effectID].ID = _effectID;
	msEffectInf[_effectID].Angle = 0;	
}

EffectManager * EffectManager::GetInstance()
{
	if (Instance) {
		return Instance;
	}
	return nullptr;
}

void EffectManager::Create()
{
	if (!Instance) {
		Instance = new EffectManager;
	}
}

void EffectManager::Destroy()
{
	delete Instance;
}

void EffectManager::PlayEffect(eEffect _id, float _x, float _y,float width, float height, float _angle, int speed)
{
	// 空いてるところにエフェクトを生成する
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpEffect[i] == NULL) {
			msEffectInf[_id].pos_x = _x;
			msEffectInf[_id].pos_y = _y;
			msEffectInf[_id].Angle = _angle;
			msEffectInf[_id].mSize_x = width;
			msEffectInf[_id].mSize_y = height;
			msEffectInf[_id].AnimSpeed = speed;
			mcpEffect[i] = new Effect(msEffectInf[_id], _id);
			mEffectState[_id] = Play; //! エフェクトの状態を再生中にする
			break;
		}
	}
}

void EffectManager::PlayEffect(eEffect _id, Vector2 _pos, Vector2 _size,float _angle,int speed)
{
	// 空いてるところにエフェクトを生成する
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpEffect[i] == NULL) {
			msEffectInf[_id].pos_x = _pos.x;
			msEffectInf[_id].pos_y = _pos.y;
			msEffectInf[_id].Angle = _angle;
			msEffectInf[_id].mSize_x = _size.x;
			msEffectInf[_id].mSize_y = _size.y;
			msEffectInf[_id].AnimSpeed = speed;
			mcpEffect[i] = new Effect(msEffectInf[_id], _id);
			mEffectState[_id] = Play; //! エフェクトの状態を再生中にする
			break;
		}
	}
}

//! 追従するエフェクト同じ奴一つしか出せないようにしてます
void EffectManager::PlayFollowEffect(eEffect _effect, float & _x, float & _y, float width, float height, bool _loop)
{
	// 空いてるところにエフェクトを生成する
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpFollowEffect[i] == NULL && mEffectState[_effect] != Play) {
			msEffectInf[_effect].pos_x = _x;
			msEffectInf[_effect].pos_y = _y;
			msEffectInf[_effect].mSize_x = width;
			msEffectInf[_effect].mSize_y = height;
			mcpFollowEffect[i] = new FollowEffect(msEffectInf[_effect], _effect, _x, _y);
			mcpFollowEffect[i]->SetLoop(_loop);
			mEffectState[_effect] = Play; //! エフェクトの状態を再生中にする
			break;
		}
	}
}

//! ループ
void EffectManager::LoopStop(eEffect _effect)
{
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpFollowEffect[i] != nullptr) {
			if (_effect == mcpFollowEffect[i]->GetEffectID()) {
				mcpFollowEffect[i]->SetLoop(false);
				delete mcpFollowEffect[i];
				mcpFollowEffect[i] = nullptr;
				mEffectState[_effect] = EffectState::None;
				break;
			}
		}
	}
}

void EffectManager::EffectUpdate()
{
	for (int i = 0; i < EffectMax; i++) {
		if (mEffectState[i] == End) { //! 前フレームにエフェクトが終了したものの状態をNoenにする
			mEffectState[i] = None; 
		}
	}
	eEffect EffectID;
	//! 通常のエフェクト
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpEffect[i] != NULL) {
			mcpEffect[i]->Update();
			if (mcpEffect[i]->GetEndFlg()){
				EffectID = mcpEffect[i]->GetEffectID(); //! どのエフェクトかを取得
				mEffectState[EffectID] = End;           //! エフェクトが終了したフレームの時だけEndを入れる
				delete mcpEffect[i];
				mcpEffect[i] = nullptr;	
			}
		}
		//! 追従するエフェクト
		if (mcpFollowEffect[i] != NULL) {
			mcpFollowEffect[i]->Update();
			if (mcpFollowEffect[i]->GetEndFlg()) {
				EffectID = mcpFollowEffect[i]->GetEffectID();
				delete mcpFollowEffect[i];
				mcpFollowEffect[i] = nullptr;
				mEffectState[EffectID] = End;           //! エフェクトが終了したフレームの時だけEndを入れる
			}
		}
	}
}

void EffectManager::EffectDraw()
{
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpEffect[i] != NULL) {
			mcpEffect[i]->Draw();
		}
	}

	for (int i = 0; i < MaxEffect; i++) {
		if (mcpFollowEffect[i] != NULL) {
			mcpFollowEffect[i]->Draw();
		}
	}
}

/* ----------------------------- 
// エフェクトの状態を返す関数 */
EffectState EffectManager::GetState(eEffect _effect)
{
	return mEffectState[_effect];
}

eEffect EffectManager::GetEffectID()
{
	return msEffectInf->ID;
}

void EffectManager::Reset()
{
	for (int i = 0; i < MaxEffect; i++) {
		if (mcpEffect[i] != NULL) {
			delete mcpEffect[i];
			mcpEffect[i] = nullptr;
		}
	}

	for (int i = 0; i < MaxEffect; i++) {
		if (mcpFollowEffect[i] != NULL) {
			delete mcpFollowEffect[i];
			mcpFollowEffect[i] = nullptr;
		}
	}

	for (int i = 0; i < EffectMax; i++) {
		mEffectState[i] = EffectState::None;
	}
}
