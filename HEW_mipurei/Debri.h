#pragma once
#include "AnimationHitObject.h"
#include "Box.h"

//! ネクトールの攻撃で出てくるがれきです
//! 初期値はネクトールから設定する

class NecthorDebri :
	public AnimationHitObject
{
	enum eDebreState{
		State_Up,
		State_Fadeout, 
		State_None
	};

public:
	NecthorDebri();
	~NecthorDebri();

	void Update();
	void Draw();
	void UpStart(Vector2 _initpos, bool _drawstate = false);  //! がれきが出てくる
	void FadeoutStart(); //! がれきが消える
	Box * GetCol();
private:
	void Up();        //! がれきが出てくる処理
	void Fadeout();   //! がれきが消える処理


	Box * mcpBox;
	eDebreState State;
	
	float totalUp;
	float Arufa; //! 透明度
};

