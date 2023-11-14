#pragma once
#include "Image.h"
#include "direct3d.h"
#include <math.h>

/* --------------------------------------------------------------------------------------------
// ���l��`�悵�Ă����N���X�ł�                                                            //
// Draw�֐��̑������ɕ`�悵�����ϐ�(���l)��ݒ肷�邱�Ƃŏ�����S�ʂ܂ŕ`�悵�Ă���܂��B  //
// �`��ʒu�A�`��T�C�Y�ARGBA���ύX�\�ł��B                                                //
// �� y�̈ʒu���̕���ύX���邱�Ƃ������Ȃ�Ǝv���̂ŁAy��������ɂ��Ă��܂��B             */
class DrawValue
{
public:
	DrawValue(); //! �R���X�g���N�^
	~DrawValue(); //! �f�X�g���N�^

	//! �����̒l��`�悵�Ă���܂��B
	//! �������ȍ~��ݒ肵�Ȃ��������ʍ���ɕ`�悳��܂� ���s���邽�߂ɂ����W��ς������ꍇ�𑽂��Ǝv���̂ő������ɂ��������Ă��Ă��܂�
	template <typename T> void Draw(T _value , float _y = 0.9f, float _x = -1.8f, float _width = 0.06f, float _height = 0.06f,float _r = 1.0f , float _g = 1.0f, float _b = 1.0f, float _a = 1.0f); //! ��������ϐ���`�悷��@�\
private:
	Image *mcpImage; //! �`��N���X
	ID3D11ShaderResourceView * ValueGraph[10]; //! �����̉摜
	ID3D11ShaderResourceView * Decimal;        //! �����_�̉摜
	ID3D11ShaderResourceView * Minus;          //! �}�C�i�X�̉摜

};

template<typename T>
inline void DrawValue::Draw(T _value ,float _y, float _x, float _width, float _height, float _r, float _g, float _b, float _a)
{
	T tmp = _value;
		
	if (tmp == false || tmp == true) {
		if (tmp) {
			mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[1], _r, _g, _b, _a);
		}
		else {
			mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[0], _r, _g, _b, _a);
		}
	}
	else {
		//! �l�����������f���� //���Ȃ�[��`�悷��
		if (_value < 0) {
			mcpImage->DrawSprite(_x, _y, _width, _height, Minus, _r, _g, _b, _a);
			_x += _width;
			tmp *= -1; //! ���̒l�ɂ���
		}
		//! �l��������������
		//! 0�������܂�10�Ŋ����Ă������ꂽ�񐔂��Ō����𔻒f����	
		int Digit;  //! ����
		for (Digit = 0; tmp > 1; Digit++) {
			tmp /= 10.0f;
		}
		tmp *= 10; //! �ꌅ�̒l�ɂ���

		for (int num = 0; num < Digit + 4; num++) {

			//! �������`�悵���珬���_��`�悷��
			if (num == Digit) {
				if (num == 0) {
					mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[0], _r, _g, _b, _a);
					_x += _width;
				}
				mcpImage->DrawSprite(_x, _y, _width, _height, Decimal, _r, _g, _b, _a);
				_x += _width;
				tmp += 0.0001f;
			}

			T prev = tmp;
			int Value = floor(tmp); //! �����_�ȉ��؂艺�� ����ňꌅ�ڂ̐������킩��
			//! �����̕`��
			mcpImage->DrawSprite(_x, _y, _width, _height, ValueGraph[Value], _r, _g, _b, _a);
			_x += _width;

			tmp -= Value;
			tmp *= 10;
		}
	}
}
