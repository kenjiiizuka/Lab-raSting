#pragma once
#include "StaticObject.h"

/* ==================================================================== ** 
** Fadeクラス                                                           **
** メンバ関数FadeIn(),FadeOut(),を使うとフェードイン、アウトができます。**
** ==================================================================== */

class Fade
{
public:
	// フェードの状態を意味する列挙型
	enum {
		NONE,
		FADEIN,
		FADEOUT
	};
	Fade();               //! コンストラクタ
	~Fade();              //! デストラクタ
	void Update();		  //! 更新処理
	void Draw();		  //! 描画処理
	void FadeIn();		  //! フェードインの開始関数
	void FadeOut();		  //! フェードアウトの開始関数
	int  GetFadeState();  //! 現在のフェードの状態を返す関数
private:
	StaticObject * mcpFadePanel;  //! フェードに使うオブジェクト 
	float mAlpha;				  //! 透明度
	int mState;					  //! fフェードの状態を判断する変数

};
