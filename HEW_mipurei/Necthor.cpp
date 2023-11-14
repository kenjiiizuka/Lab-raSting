#include "Necthor.h"
#include"TextureManager.h"
#include"DirectInput8.h"

Necthor::Necthor(float _X, float _Y)
{
	mAttackCoolTime = 60 * StopTime;
	mLife = ResistDef;//
	mChargeTime = 60 * AtkCharge;//60(1�b)*��~���Ăق������[�v��(1�ȏ�̐���)
	mDamageCoolTime = 60 * 3;//����60�b���R���[�v��180�b�ς���悤�ɂ���

	this->mcVec.x = _X;
	this->mcVec.y = _Y;
	msSize = { 1.0f,1.0f };
	LoadTexture(L"assets/idol2.png", &mTmpTex);
	LoadTexture(L"assets/attack2.png", &mAtkTex);
	mcpAnimsprite->SetTexture(mTmpTex);
	mcpAnimsprite->SetAnimtionTable(5, 1);

	//�̂̓����蔻��ݒ�
	mpBodyColisionPos.x = this->mcVec.x + 0.15f;
	mpBodyColisionPos.y = this->mcVec.y - 0.25f;
	mpBodyCollision = new Box(mpBodyColisionPos, 0.4f, 0.32f);

	//���̓����蔻��ݒ�
	mpHeadCollisionPos.x = this->mcVec.x + 0.16f;
	mpHeadCollisionPos.y = this->mcVec.y + 0.1f;
	mpHeadCollision = new Box(mpHeadCollisionPos, 0.22f, 0.25f);

	//�n���}�[�����蔻��ݒ�
	mpHunmerCollisionPos.x = this->mcVec.x - 0.16f;
	mpHunmerCollisionPos.y = this->mcVec.y - 0.19f;
	mpHunmerCollision = new Box(mpHunmerCollisionPos, 0.3f, 0.25f);
	//�g�h���̃v���O����
	mpPlag = new Plag(this->mcVec.x + 0.35f, this->mcVec.y + 0.1f);
	mpPlag->SetSize(0.25f, 0.25f);
	mBossDownFlg = false;

	//�n���}�[�U�艺�낵���ɔ�΂��Ռ��g�̏����ݒ�
	mpWaves = new BoxObject();
	LoadTexture(L"assets/ShockWave.png", &mWavesTex);
	mpWaves->GetAnimSprite()->SetAnimtionTable(1, 1);
	mpWaves->GetAnimSprite()->SetTexture(mWavesTex);
	mpWaves->SetDrawActiv(false);
	//�Ռ��g�̈ʒu�A�g�k�̏����ݒ�
	mcWavesScale.x = 0.25f;
	mcWavesScale.y = 0.18f;
	mcWavesPos.x = mcVec.x - 0.2f;
	mcWavesPos.y = -0.7f;
	mpWaves->SetSize(mcWavesScale.x, mcWavesScale.y);
	//mpWaves->SetScale(0.2f,0.2f);
	WaveMoveFlg = false;



	//�n�ʂ��琶���邪�ꂫ�𐶐�
	mpdebris = new BoxObject();
	//���ꂫ�̃e�N�X�`����ݒ�
	LoadTexture(L"assets/debris.png", &mdebrisTex);
	mpdebris->GetAnimSprite()->SetAnimtionTable(1, 1);
	mpdebris->GetAnimSprite()->SetTexture(mdebrisTex);
	mpdebris->SetDrawActiv(false);
	//���ꂫ�̈ʒu�A�g�k�̏����ݒ�
	mcdebreisScale.x = 0.25f;
	mcdebreisScale.y = 0.25f;
	mcdebreisPos.x = mcVec.x - 0.55f;
	mcdebreisPos.y = -1.0f;
	mpdebris->SetSize(mcdebreisScale.x, mcdebreisScale.y);
	mpdebris->SetScale(1.0f, 1.0f);

	mSwingFlg = false;

	ShakeTime = 0;

	AliveFlg = true;

	//�{�X�̓_�ŏ����Ɋւ��鏉����
	DamageFlg = false;//Setter��true���_�ŏ����I������false�ɖ߂�
	AlphaFlg = false;
	mCtrShakeFlg = 0;
	Alpha = 0.0f;
	AlphaCnt = 8;//�_�ł�����
}

Necthor::~Necthor()
{
	delete mpdebris;
	delete mpPlag;
	delete mpBodyCollision;
	delete mpHeadCollision;
	delete mpHunmerCollision;
	
	if (mpWaves != nullptr) 
	{
		delete mpWaves;
	}
	COM_SAFE_RELEASE(mTmpTex);
	COM_SAFE_RELEASE(mAtkTex);
	COM_SAFE_RELEASE(mWavesTex);
}

void Necthor::Update()
{
	//==�{�X���g�̏���=========================================
	if (mBossDownFlg == false)//�{�X�̗̑͂��c���Ă��ԂȂ�n���}�[�U�艺�낵�������s��
	{
		if (mChargeTime > 0)
		{
			mChargeTime -= 1;//�U�艺�낵�܂ł̎��Ԃ����炵�Ă���
		}

		if (mChargeTime <= 0)//�n���}�[��U�艺�낷
		{

			if (mSwingFlg == false)
			{
				mSwingFlg = true;
				mcpAnimsprite->SetTexture(mAtkTex);
				mcpAnimsprite->SetAnimtionTable(9, 1);
				mcpAnimsprite->ResetAnimCnt();
				mChargeTime = 0;
			}
			else
			{
				if (mAttackCoolTime > 0)
				{
					mAttackCoolTime--;//�U�艺�낵��̍d�����Ԍ���
					if (mAttackCoolTime < 492)
					{
						mCtrShakeFlg = 0;
						mpWaves->SetDrawActiv(true);
						WaveMoveFlg = true;
						mcpAnimsprite->SetStopAnimation(true);
						mpHeadCollisionPos.y = this->mcVec.y - 0.05f;

						//�n���}�[�U�艺�낵���ɉ�ʂ𐔕b�h�炷
						if (mAttackCoolTime > 484)
						{
							CAMERA->StartVibration(1);
							mCtrShakeFlg = 1;
						}

					}
			

					//���ꂫ�����N���鏈��
					if (mcdebreisPos.y < -0.7f)
					{
						mcdebreisPos.x = mcVec.x - 0.55f;
						mpdebris->SetDrawActiv(true);						
						mcdebreisPos.y += 0.008f;
					}

					mpHunmerCollisionPos.x = this->mcVec.x - 0.22f;
					mpHunmerCollisionPos.y = this->mcVec.y - 0.22f;
				}
				else if (mAttackCoolTime <= 0)
				{
					mSwingFlg = false;
					mChargeTime = 60 * AtkCharge;//�U�����ߎ��Ԃ̒l���Z�b�g
					mAttackCoolTime = 60 * StopTime;//�d�����Ԃ������Ȃ����̂ŁA�����l����
					mcpAnimsprite->ResetAnimCnt();
					mcdebreisPos.y -= 1.0f;//���ꂫ��n���ɖ߂�
					mpdebris->SetDrawActiv(false);


					//�ҋ@�A�j���[�V�����ɖ߂��A�Ռ��g��������ԂɃ��Z�b�g
					mcpAnimsprite->SetTexture(mTmpTex);
					mcpAnimsprite->SetAnimtionTable(5, 1);
					mcpAnimsprite->SetStopAnimation(false);
					WaveMoveFlg = false;
					mcWavesPos.x = mcVec.x - 0.13f;
					mpWaves->SetDrawActiv(false);

					mpHeadCollisionPos.y = this->mcVec.y + 0.1f;
				}
			}
		}
	}
	//=========================================================

	//=========================================================
	//�_���[�W���󂯂����̏���
	if (mDamageCoolTime < 180 && mDamageCoolTime > 0)
	{
		mDamageCoolTime--;
	}

	if (mDamageCoolTime <= 0)
	{
		mDamageCoolTime = 180;
	}

	//���C�t���Ȃ��Ȃ������̏���
	if (mLife <= 0)
	{
		mLife = 0;//unsigned�Ȃ̂ŁA���̐�����邱�Ƃ͂Ȃ����A�O�̂���0����
		if (mBossDownFlg == false)
		{
			this->mcpSprite->SetTexture(mTmpTex);
			mcpAnimsprite->SetAnimtionTable(5, 1);
			mcpAnimsprite->SetStopAnimation(true);
			mBossDownFlg = true;
			mSwingFlg = true;//�_�E�������̂ŁA�n���}�[�����낵���ςȂ��ɂ���
			mpHeadCollisionPos.x = this->mcVec.x + 0.09f;//���̓����蔻������Ɉړ�����
			mpHeadCollisionPos.y = this->mcVec.y - 0.035f;//���̓����蔻������Ɉړ�����

			mpHunmerCollisionPos.y = this->mcVec.y - 0.27f;
			mpdebris->SetDrawActiv(true);

			//�����蔻����k�߁A�ʒu����
			mpBodyColisionPos.y = mpBodyColisionPos.y -= 0.03f;
			mpBodyCollision->SetSize(0.4f, 0.25f);

			mpHeadCollisionPos.y = mpHeadCollisionPos.y -= 0.02f;
			mpHeadCollision->SetSize(0.5f, 0.325f);
		}
		else
		{
			mpdebris->SetDrawActiv(false);

			if (mcdebreisPos.y <= -0.7f)
				mcdebreisPos.y += 0.1f;
		}
	}

	//�_���[�W���󂯂����̓_�ŏ���
	
	if (DamageFlg == true)
	{
		if (AlphaFlg == false)
			Alpha -= 0.2f;
		if (AlphaFlg == true)
			Alpha += 0.2f;

		if (Alpha <= 0.0f)
		{
			Alpha = 0;
			AlphaFlg = true;
		}
		if (Alpha >= 1.0f)
		{
			Alpha = 1.0f;
			AlphaFlg = false;
			AlphaCnt--;
		}

		mcpAnimsprite->SetArufa(Alpha);

		if (AlphaCnt < 0)//�_�ŏ����̏I��
		{
			DamageFlg = false;
			AlphaCnt = 8;
			Alpha = 1.0f;
		}
	}

	//=========================================================

	//=========================================================
	//���ꂫ�̏���
	//���ꂫ�̑傫���𖈃��[�v����
	mpdebris->SetSize(mcdebreisScale.x, mcdebreisScale.y);
	mpdebris->Update();
	mpdebris->SetVec(mcdebreisPos);
	//=========================================================

	//=========================================================
	//�Ռ��g�̏���
	if (mpWaves != nullptr)
	{
		mpWaves->Update();
		mpWaves->SetSize(mcWavesScale.x, mcWavesScale.y);
		if (WaveMoveFlg == true) 
		{
			mcWavesPos.x -= 0.025f;
		}
		mpWaves->SetVec(mcWavesPos);
	}
	//=========================================================

	mpPlag->Update();

	//�Ƃǂ߂��h���ꂽ���̐U������
	if (!AliveFlg)
	{
		ShakeTime++;
		if (ShakeTime < 180)
		{
			CAMERA->StartVibration(2);
		}
		else if (ShakeTime > 180)
		{
			ShakeTime = 180;
		}
	}
}

void Necthor::Draw()
{
	//�g�h���̃v���O�Ɏh���܂ł́ANecthor�֘A�̕`����s��
	if (AliveFlg == true)
	{
		GameObject::Draw();
		mpPlag->Draw();
		//�̂̓����蔻��`��
		mcImage.DrawSprite(mpBodyColisionPos.x, mpBodyColisionPos.y, 0.4f, 0.32f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
		//���̓����蔻��`��
		mcImage.DrawSprite(mpHeadCollisionPos.x, mpHeadCollisionPos.y, 0.22f, 0.25f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
		//�n���}�[�̓����蔻��`��
		mcImage.DrawSprite(mpHunmerCollisionPos.x, mpHunmerCollisionPos.y, 0.3f, 0.25f, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
		//�Ռ��g�̓����蔻��
		mcImage.DrawSprite(mcWavesPos.x, mcWavesPos.y, mcWavesScale.x, mcWavesScale.y, TexMgr->GetTextuer(Tex_PanelBl), 1.0f, 1.0f, 1.0f, 0.5f);
	}
	//���ꂫ�̕`��
	mpdebris->Draw();

	if (mpWaves != nullptr)
	{
		mpWaves->Draw();
	}

}

int Necthor::GetChargeTime()
{
	return mChargeTime;
}

Box * Necthor::GetBossBodyCollision()
{
	return mpBodyCollision;
}

Box * Necthor::GetBossHeadCollision()
{
	return mpHeadCollision;
}

Box * Necthor::GetBossHunmerCollision()
{
	return mpHunmerCollision;
}

Plag * Necthor::GetPlag()
{
	return mpPlag;
}

void Necthor::SetChargeTime(int _Time)
{
	mChargeTime = _Time;
}

void Necthor::AddChargeTime(int _Time)
{
	mChargeTime += _Time;
}

void Necthor::AddLife(int _Life)
{
	mLife += _Life;
}

bool Necthor::GetDownFlg()
{
	return mBossDownFlg;
}

unsigned int Necthor::GetmDamageCoolTime()
{
	return mDamageCoolTime;
}

void Necthor::SetmDamageCoolTime(unsigned int _Time)
{
	mDamageCoolTime = _Time;
}

bool Necthor::GetAliveFlg()
{
	return AliveFlg;
}

void Necthor::SetAliveFlg(bool _Flg)
{
	AliveFlg = _Flg;
}

BoxObject * Necthor::GetmpDebriesBox()
{
	return mpdebris;
}

BoxObject * Necthor::GetmpWavesBox()
{
	return mpWaves;
}

void Necthor::SetDamageFlg(bool _Flg)
{
	DamageFlg = _Flg;
}

unsigned int Necthor::GetCtrShakeFlg()
{
	return mCtrShakeFlg;
}
