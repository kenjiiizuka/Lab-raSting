 
// ���_�V�F�[�_�[�̃��C���֐�
//�����@�e���_�ɑ΂��čs�������ړ��@��]�@�k���Ȃǂ����s����
// �߂�l�F���̃V�F�[�_�[�̏����̌��ʂ��A���_�̃f�[�^�Ƃ��Ė߂�
// ���� inputPos�FVRAM�ɓ]�����ꂽ���_�f�[�^�i�̂����P�j���n�����

//return�p�̍\����

struct VS_OUTPUT
{
	float4 pos : SV_Position; //�V�X�e���Ō��߂��Ă閼�O
	float2 uv : TEXCOORD; //�V�X�e���Ō��߂��Ă閼�O
	float4 col : COLOR;
};

VS_OUTPUT vs_main(float4 inputPos : POSITION, float2 uv:TEX ,float4 col :COL /*uv*/)
{
	VS_OUTPUT output;

	output.pos = inputPos;  // �n���ꂽ���_�����̂܂�return����B�i���̂܂܎g���j
	output.uv = uv;
	output.col = col;

//	output.pos.x *= (800.0f/1536.0f);
//	output.pos.x *= (1020.0f / 1920.0f);
	output.pos.x *= (1020.0f / 1920.0f);
	output.pos.y *= 1.0f;

    return output;
}