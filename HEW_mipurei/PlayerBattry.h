#pragma once
#include "AnimationHitObject.h"
#include <memory>
//! プレイヤー専用のばってりーUI

class PlayerBattery
{
public:
	PlayerBattery();
	~PlayerBattery();

	void Update(int _charge);
	void Draw();
private:
	int DifCharge; //! 現在のチュージすうと表示上での差(電池が順番にたまる感じにしたいの増えてからフレームをあけて次を増やすようにしたい)
	int NowCharge;
	//! バッテリーの現在の表示状態
	int NumBattryDraw;  //! 現在のチャージの数と同じになるように、描画する
	int WaitFrameCnt;   //! 数フレーム待ってから描画を切り替えるための変数
	int WaitFrameLow;   //! 一気に減るのが気持ち悪いのですこしまってから減るための変数
	bool Up;            //! 増えた
	bool Down;          //! 減った
	bool Wait;
	std::unique_ptr<AnimationHitObject> Battery;
};

