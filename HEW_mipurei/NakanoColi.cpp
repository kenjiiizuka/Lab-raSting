#include "NakanoColi.h"

/* --------------------------------------------------------------
//�~�Ƌ�`�̓����蔻��                                         //
// �����@ : _Box, _Circle                                      //
// �߂�l : �������Ă��邩�ǂ���                               */
bool NakanoColi::Box_Circle(Box* _Box, Circle* _Circle)
{
	//���̏�Ԃł́A�����葱����Ǝv���̂ŁA����������������Colision�N���X���ɂ���Active�m�F�֐���p�ӂ���

	bool TmpFlg = false;//���[�J���ϐ��B���̊֐����ł̓����蔻��Ɏg��

	//��`���̏���
	float Left = _Box->GetVec().x - _Box->GetSize().x / 2;
	float Right = Left + _Box->GetSize().x;
	float Bottom = _Box->GetVec().y - _Box->GetSize().y / 2;
	float Top = Bottom + _Box->GetSize().y;

	// �l�p�`�̎l�ӂɑ΂��ĉ~�̔��a�������������Ƃ��~���d�Ȃ��Ă�����
	if ((_Circle->GetVec().x > Left - _Circle->GetRadiuse()) &&
		(_Circle->GetVec().x < Right + _Circle->GetRadiuse()) &&
		(_Circle->GetVec().y > Top - _Circle->GetRadiuse()) &&
		(_Circle->GetVec().y < Bottom + _Circle->GetRadiuse()))
	{
		TmpFlg = true;
		float Radiuse2jou = _Circle->GetRadiuse() *  _Circle->GetRadiuse();


		// ��
		if (_Circle->GetVec().x < Left)
		{
			// ����
			if ((_Circle->GetVec().y < Top))
			{
				if ((DistanceBox_Circle(Left, Top, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
				{
					TmpFlg = false;
				}
			}
			else
			{
				// ����
				if ((_Circle->GetVec().y > Bottom))
				{
					if ((DistanceBox_Circle(Left, Bottom, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
					{
						TmpFlg = false;
					}
				}
			}
		}
		else
		{
			// �E
			if (_Circle->GetVec().x >Right)
			{
				// �E��
				if ((_Circle->GetVec().y < Top))
				{
					if ((DistanceBox_Circle(Right, Top, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
					{
						TmpFlg = false;
					}
				}
				else
				{
					// �E��
					if ((_Circle->GetVec().y > Bottom))
					{
						if ((DistanceBox_Circle(Right, Bottom, _Circle->GetVec().x, _Circle->GetVec().y) >= Radiuse2jou))
						{
							TmpFlg = false;
						}
					}
				}
			}
		}
	}

	return TmpFlg;
}

/* --------------------------------------------------------------
//�I�u�W�F�N�g���m�̒��S���W��������                           //
// �����@ : _Box, _Circle��X,Y���W                             //
// �߂�l : �v�Z���ʂ�2�悵�āA��������                        */
float NakanoColi::DistanceBox_Circle(const float _BoxX, const  float _BoxY, const float _CircleX, const float _CircleY)
{
	float dx = _CircleX - _BoxX;
	float dy = _CircleY - _BoxY;

	//2�悷��̂ŁA���K���̕K�v�Ȃ��H
	return (dx * dx) + (dy * dy);
}


