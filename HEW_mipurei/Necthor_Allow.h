#pragma once
#include "AnimationHitObject.h"
class Necthor_Allow :
	public AnimationHitObject
{
public:
	Necthor_Allow();
	~Necthor_Allow();

	void Update();

	void AllowOn(Vector2 _pos);
	void AllowOff();
private:
	float AddY;     //! Y座標をふわふわ動かすための移動量を持つ変数
	float TotalYAdd; //! Yのトータルの移動量
	float Arufa;    //! 透明度
	float AddArufa; //! 透明度に加算する量
	bool AllowActiv = false; //! オンオフ変数

};

