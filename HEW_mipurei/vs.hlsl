 
// 頂点シェーダーのメイン関数
//役割　各頂点に対して行いたい移動　回転　縮小などを実行する
// 戻り値：このシェーダーの処理の結果を、頂点のデータとして戻す
// 引数 inputPos：VRAMに転送された頂点データ（のうち１つ）が渡される

//return用の構造体

struct VS_OUTPUT
{
	float4 pos : SV_Position; //システムで決められてる名前
	float2 uv : TEXCOORD; //システムで決められてる名前
	float4 col : COLOR;
};

VS_OUTPUT vs_main(float4 inputPos : POSITION, float2 uv:TEX ,float4 col :COL /*uv*/)
{
	VS_OUTPUT output;

	output.pos = inputPos;  // 渡された頂点をそのままreturnする。（そのまま使う）
	output.uv = uv;
	output.col = col;

//	output.pos.x *= (800.0f/1536.0f);
//	output.pos.x *= (1020.0f / 1920.0f);
	output.pos.x *= (1020.0f / 1920.0f);
	output.pos.y *= 1.0f;

    return output;
}