#include "ProtoTypeScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Input.h"
#include"NakanoColi.h"
#include"Collision.h"
#include"Controller.h"
#include"Character.h"
#include"PlayerState.h"
#include"EffectManager.h"

PrototypeScene::PrototypeScene()
{
	tmpPMap1_1 = new Map1_1("assets/Stage1/1/MapDate.csv", "assets/Stage1/1/ItemData.csv", TexMgr->GetTextuer(Tex_MapTip01), "assets/Stage1/1/MapObjectData.csv");
	mpNecthor = new Necthor(0.5f, -0.4f);
	tmpPlayer = new Player(-1.0f, 0.0f);//1キー押してマウス対応させる
	mpGoal = new ProtoGoal(1.1f,-0.4f);

}

PrototypeScene::~PrototypeScene()
{
	delete mpGoal;
	delete tmpPMap1_1;
	delete tmpPlayer;
	delete mpNecthor;

}

void PrototypeScene::Update()
{
	EffMgr->EffectUpdate();
	tmpPlayer->Update();
	tmpPMap1_1->Update();
	mpNecthor->Update();
	mpGoal->Update();

	//プレイヤーとボス、ハンマーの当たり判定
	//============================ 
	Box* PlayerBox = tmpPlayer->GetBoxCol();
	Circle TailCircle = *tmpPlayer->GetAttackCol();

	////プレイヤーとボス本体、ボスの持つハンマーの当たり判定
	////====================================================================

	//if (mpNecthor->GetAliveFlg() == true)
	//{
	//	//コントローラーを揺らすようにボスがハンマーをおろしたかどうか判別
	//	if (mpNecthor->GetCtrShakeFlg() == 1)
	//	{
	//		SetControllerVibration(5, 5);
	//	}

	//	//ボスのハンマーと当たり判定
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetBossHunmerCollision());
	//	//ボスの体と当たり判定
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetBossBodyCollision());
	//	//ボスの頭と当たり判定
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetBossHeadCollision());


	//	//====================================================================
	//	//しっぽとボスの当たり判定
	//	//====================================================================
	//	//しっぽVS頭
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetBossHeadCollision(), TailCircle))
	//	{
	//		//ダメージクールタイムが初期値ならライフを減らす
	//		if (mpNecthor->GetmDamageCoolTime() == 180)
	//		{
	//			if (mpNecthor->GetDownFlg() == false)//生きていればライフを減らす(ダウン時は判定しない)
	//			{
	//				mpNecthor->AddLife(-1);
	//				mpNecthor->SetDamageFlg(true);
	//				mpNecthor->SetmDamageCoolTime(179);
	//			}
	//		}
	//		tmpPlayer->SetReaction(TailReaction_StingStop, Direction_None);
	//	}
	//	//しっぽVSボスの胴体
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetBossBodyCollision(), TailCircle))
	//	{
	//		tmpPlayer->SetReaction(TailReaction_Stop,Direction_None);
	//	}
	//	//しっぽVSがれき
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetBoxCol(), TailCircle))
	//	{
	//		tmpPlayer->SetReaction(TailReaction_Stop, Direction_None);
	//	}
	//}
	////====================================================================
	////ハンマーから発生するがれきとプレイヤーの当たり判定
	//if (mpNecthor->GetDownFlg() == false) 
	//{
	//	Collision::Box_Box_Collision(*PlayerBox, *mpNecthor->GetmpDebriesBox()->GetBoxCol());
	//}
	////====================================================================


	////====================================================================
	////しっぽとトドメを刺すためのプラグの当たり判定
	//if (mpNecthor->GetDownFlg() == true) //ダウンしていればプラグと当たり判定を実地
	//{
	//	//プラグとの当たり判定が実地された場合、テスト処理としてBoss本体の描画をオフにして、透明にする
	//	if (Collision::Box_Circle_Hit(*mpNecthor->GetPlag()->GetPlagCollision(), TailCircle))
	//	{
	//		mpNecthor->SetAliveFlg(false);
	//	}
	//}
	////====================================================================
	//
	////====================================================================
	////プレイヤーと衝撃波の当たり判定
	//if (Collision::Box_Box_Hit(*PlayerBox, *mpNecthor->GetmpWavesBox()->GetBoxCol()))
	//{
	//	//衝撃波との仮処理として、衝撃波を透明にする
	//	mpNecthor->GetmpWavesBox()->SetDrawActiv(false);
	//	tmpPlayer->SetDamege(Left);

	//}
	////====================================================================

	
	//====================================================================
	//ゴールとの当たり判定(しっぽのみ)
	if (Collision::Box_Circle_Hit(*mpGoal->GetmpGoalBox(), TailCircle))
	{
		tmpPlayer->SetReaction(TailReaction_Sting, Direction_None);
		
		if (mpGoal->GetFirstStabFlg() == false)
		{
			mpGoal->SetFirstStabFlg(true);
		}

		if (mpGoal->GetSecondStabFlg() == false)
		{
			mpGoal->SetSecondStabFlg(true);
			if (mpGoal->GetSecondStabFlg())
			{
				//ゴールした仮処理として、ゴールのプラグを透明にする
				mpGoal->SetDrawActiv(false);
				//EffMgr->PlayEffect(DynamoChaege,mpGoal->GetVec().x, mpGoal->GetVec().y);
			}
		}
	}
	//====================================================================


	//====================================================================
	//mapとの当たり判定
	if (tmpPMap1_1->CollisionUpdate(tmpPlayer))
	{
		tmpPlayer->SetTouchGround(true);
	}
	else
	{
		tmpPlayer->SetTouchGround(false);
	}
	//====================================================================
	//プレイヤーHP回復の仮処理
	if (GetControllerButtonTrigger(Button_UP))
	{
		for (int i = 0; i < 10; i++) 
		{
			tmpPlayer->AddBoruto();
		}
	}
	if (GetControllerButtonTrigger(Button_DOWN))
	{
		tmpPlayer->SetDamege(Direction_None);
	}
	//====================================================================
	//仮のクリアシーン遷移処理
	if (GetControllerButtonTrigger(Button_X))
	{
		SceneMgr->ChageScene(Scene_Clear,true);
	}
	//仮のリザルトシーン遷移処理
	if (GetControllerButtonTrigger(Button_Y))
	{
		SceneMgr->ChageScene(Scene_Result, true);
	}
	//仮の負けシーン処理
	if (GetControllerButtonTrigger(Button_B))
	{
		SceneMgr->ChageScene(Scene_Lose, true);
	}
	//====================================================================
	
	tmpPlayer->LastUpdate();//当たり判定後の処理
}

void PrototypeScene::Draw()
{
	tmpPMap1_1->Draw();
	mpGoal->Draw();
	mpNecthor->Draw();
	tmpPlayer->Draw(); 
	EffMgr->EffectUpdate();
}