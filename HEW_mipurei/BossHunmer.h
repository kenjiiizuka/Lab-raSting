#pragma once
#include"Box.h"
#include"BoxObject.h"
#include"Sprite.h"
#include"AnimationHitObject.h"
#include "Image.h"
/*
α版ボスが使うハンマーのクラスです。
α版ボスとの位置関係は、親子関係にする予定です。(飯塚君の作った猫とプラグの感じ)
なので、このクラスはAlphaBoss内で生成して、このクラスの関数などを呼びます
振り下ろされた後のハンマーは足場として利用できます
*/
class BossHunmer :
	public AnimationHitObject
{
public:
	BossHunmer(float _x, float _y);//常にボスの手にくっつくように位置を設定する
	~BossHunmer();
	void Update(float _x, float _y,int _AtkTime,bool _AtkFlg);
	void Draw();
	Box* GetmpHunmerBox();
	Box* GetmpRodBox();
	BoxObject* GetmpDebriesBox();
private:
	ID3D11ShaderResourceView * mHunmerTex;//振り下ろす前、振り下ろした後のハンマーのテクスチャ用に2個用意する

	/*
	当たり判定2個用意(先端と持ちての部分)
	・攻撃中ハンマー両サイドに攻撃用判定の丸を用意する
	*/
	Image mcImage;
	//ハンマーの本体の当たり判定関連の変数
	Box* mpHunmer;//ハンマーに乗る時の当たり判定(四角形)
	Vector2 mpHunmerColiPos;//当たり判定の位置
	Vector2 HunmerColiScale;//当たり判定の大きさ

	//ハンマーの持ち手の当たり判定関連の変数
	Box* mpRod;//持ち手の当たり判定(四角形)
	Vector2 mcRodPos; //! 持ち手用の座標
	Vector2 mcRodColiScale;//持ち手の当たり判定の大きさ

	//がれき Boxクラスを使用する、画面下から生えてくる
	BoxObject* mpdebris;
	AnimationSprite* tmpdbrisAnimSprite;
	ID3D11ShaderResourceView* mdebrisTex;
	Vector2 mcdebreisPos;//がれきの座標
	Vector2 mcdebreisScale;
};