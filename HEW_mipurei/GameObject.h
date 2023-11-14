#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "DrawValue.h"
#include "ObjTag.h"
/* =============================================
** GameObjectクラス　　　　　　　　　　　     **　　　
** GameObjectの基底クラスです　               **
** 制作者 : 飯塚 健司                         **
** ========================================== */

class GameObject
{
public:
	virtual void Draw();

	void SetDrawActiv(bool _drawState);         //! 描画のオンオフ切り替え用のセッター	
	virtual Vector2  GetVec();                          //! 座標のゲッター
	virtual void SetVec(Vector2 _vec);          //! 座標のセッター
	void SetScale(float _x, float _y);          //! 拡大縮小率
	virtual void SetSize(float _widht, float _hieght);  //! サイスのセッター
	virtual void SetSize(Vector2 _size);        //! サイズのセッター
	Sprite * GetSprite();                       //! スプライトクラスのゲッター
	bool GetAlive();                            //! 生存フラグのゲッター
	void SetCameraActiv(bool _state);           //! カメラが反映されるかどうかのセッター
	ObjectTag GetTag();                 //! タグのゲッター

protected:
	Sprite * mcpSprite;                         //! 描画機能
	Vector2 mcVec;                              //! オブジェクトの座標
	FLOAT2 msSize = { 0.2f ,0.2f};              //! このオブジェクトのサイズ
	FLOAT2 msScale = {1.0f,1.0f};               //! 拡大縮小率
	bool mAlive = true;                         //! 生存フラグ
	ObjectTag mTag = ObjectTag::Tag_None;
private:
	bool mDrawActiv = true;                     //! 描画のオンオフ切り替え	
	bool mCameraActiv = true;                   //! カメラの処理を反映刺せるかさせないかのオンオフ     
};

