#pragma once
#include "GameObject.h"
#include "AnimationSprite.h"
#include "Shape.h"
#include "ObjTag.h"
/* =========================================================== 
** AnimationHitObjectクラス                                 **
** アニメーションと当たり判定機能を持ったオブジェクトクラス **
** このクラスを継承してキャラクター等のクラスを作る予定　　 **
** 制作者 : 飯塚 健司                                       **
** ======================================================== */


class AnimationHitObject :
	public GameObject
{
public:
	AnimationHitObject();               //! コンストラクタ
	virtual ~AnimationHitObject();      //! デストラクタ
	virtual void Update();              //! 更新処理
    virtual void LastUpdate();          //! 当たり判定処理の後にする更新処理
	void SetHit(bool _state);           //! ヒットフラグのセッター
	void SetHitActiv(bool _state);      //! 当たり判定のオンオフ切り替えのセッター
	AnimationSprite * GetAnimSprite();	//! スプライトクラスのゲッター
	
protected:	
	AnimationSprite* mcpAnimsprite;     //! アニメーションスプライトクラス
	Shape * mcpShape;                   //! このオブジェクトの形を持つ
	
private:							    

	bool mHitFlg;                       //! HitFlg
};

