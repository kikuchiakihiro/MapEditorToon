//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;           // ワールド行列
	float4x4	matNormal;           // ワールド行列
	float4		diffuseColor;		//マテリアルの色＝拡散反射係数
	bool		isTextured;			//テクスチャーが貼られているかどうか

};

cbuffer gmodel:register(b1)
{
	float4		lightPosition;
	float4		eyePosition;
};



struct PS_IN
{
	float4 pos  : SV_POSITION;	//位置
	float2 uv	: TEXCOORD;		//UV座標
	float4 eyev		:POSITION1;
	float4 normal	:POSITION2;
	float4 light	:POSITION3;
};


//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
PS_IN VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	PS_IN outData = (PS_IN)0;

	outData.pos = mul(pos, matWVP);
	//outData.pos = pos;
	outData.uv = uv;
	float4 normalout;
	normalout = mul(normal, matNormal);
	normalout.w = 0;
	normalout = normalize(normalout);
	outData.normal = normalout;

	float4 posw = mul(pos, matW);
	outData.light = normalize(lightPosition - posw);
	outData.eyev = normalize(eyePosition - posw);
	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(PS_IN inData) : SV_Target
{

	float len = length(inData.light); // 光の方向ベクトルを正規化(大きさを 1 にし

	float NL = saturate(dot(inData.normal, inData.light));
	float k = 1.0f / (1.0 * len * len);

	float3 reflect = normalize(2 * NL * inData.normal - inData.light);
	float4 specular = pow(saturate(dot(reflect, inData.eyev)), 8);


	float4 lightSource = { 1,1,1,1 };//光の色
	float4 ambientSource = { 1,1,1,1 };//環境光の色
	float4 ambTerm = 0.5;

	float4 diffuse;
	float4 ambient;
	if (isTextured.x == false)
	{
		diffuse = k * NL * lightSource * diffuseColor;
		ambient = ambTerm * ambientSource * diffuseColor;
	}
	else
	{
		diffuse = k * NL * lightSource * g_texture.Sample(g_sampler, inData.uv);
		ambient = ambTerm * ambientSource * g_texture.Sample(g_sampler, inData.uv);
	}

	return  diffuse + ambient + specular;
}