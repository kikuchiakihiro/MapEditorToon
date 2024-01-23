
//
////───────────────────────────────────────
//// テクスチャ＆サンプラーデータのグローバル変数定義
////───────────────────────────────────────
//Texture2D   g_texture : register(t0);   //テクスチャー
//SamplerState    g_sampler : register(s0);   //サンプラー
//
//Texture2D   g_toon_texture : register(t1);   //トゥーンテクスチャー
//
////───────────────────────────────────────
// // コンスタントバッファ
//// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
////───────────────────────────────────────
//cbuffer global:register(b0)
//{
//    float4x4    matW;           //ワールド行列
//    float4x4    matWVP;         // ワールド・ビュー・プロジェクションの合成行列
//    float4x4    matNormal;      //法線
//    float4      diffuseColor;   // ディフューズカラー（マテリアルの色）
//    float4      ambientColor;
//    float4      specularColor;
//    float       shininess;
//    bool        isTexture;      // テクスチャ貼ってあるかどうか
//    
//};
//
//cbuffer global:register(b1)
//{
//    float4      lightPosition;  //ライトの方向
//    float4      eyepos;         //視点
//}
////───────────────────────────────────────
//// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
////───────────────────────────────────────
//struct VS_OUT
//{
//    float4 pos      : SV_POSITION;  //位置
//    float2 uv       : TEXCOORD; //UV座標
//    float4 color    : COLOR;    //色（明るさ）
//    float4 eyev     : POSITION1;
//    float4 normal   : POSITION2;
//    float4 light    : POSITION3;
//};
//
////───────────────────────────────────────
//// 頂点シェーダ
////───────────────────────────────────────
//VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
//{
//    //ピクセルシェーダーへ渡す情報
//    VS_OUT outData = (VS_OUT)0;
//    //ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
//    //スクリーン座標に変換し、ピクセルシェーダーへ
//    outData.pos = mul(pos, matWVP);
//    outData.uv = uv;
//    normal.w = 0;
//    normal = mul(normal, matNormal);
//    normal = normalize(normal);
//    outData.normal = normal;
//
//
//
//    float4 light = normalize(lightPosition);
//    light = normalize(light);
//
//    outData.color = saturate(dot(normal, light));
//    float4 posw = mul(pos, matW);
//    outData.eyev = eyepos - posw;
//    //まとめて出力
//    return outData;
//}
//
////───────────────────────────────────────
//// ピクセルシェーダ
////───────────────────────────────────────
//float4 PS(VS_OUT inData) : SV_Target
//{
//    float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
//    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0); //物体がどれだけ環境光を反射または放射するかを制御する
//    float4 diffuse;
//    float4 ambient;
//    float4 NL = dot(inData.normal, normalize(lightPosition));
//    float4 reflection = reflect(normalize(-lightPosition), inData.normal);
//   // float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
//    float4 specular = pow(saturate(dot(reflection, normalize(inData.eyev))), shininess)* specularColor;
//
//
//   /* float4 n1 = float4(1 / 4.0, 1 / 4.0, 1 / 4.0, 1);
//    float4 n2 = float4(2 / 4.0, 2 / 4.0, 2 / 4.0, 1);
//    float4 n3 = float4(3 / 4.0, 3 / 4.0, 3 / 4.0, 1);
//    float4 n4 = float4(4 / 4.0, 4 / 4.0, 4 / 4.0, 1);
//
//    float4 tI = 0.1*step(n1, inData.color)+0.3*step(n2, inData.color)
//               +0.3*step(n3, inData.color)+0.4*step(n4, inData.color);*/ //stepの階調変換
//
//    //float4 Clr = 3.0f;
//    //inData.color = floor(inData.color * Clr) / Clr; //floorの階調変換
//
//    float2 uv;
//    uv.x = inData.color.x;
//    uv.y = 0;
//    if (abs(dot(inData.normal, normalize(inData.eyev))) < 0.4f) {
//        return g_toon_texture.Sample(g_sampler, inData.color);
//    }
//    else {
//        return float4(1, 1, 1, 0);
//    }
//    //float4 tI = g_toon_texture.Sample(g_sampler, uv);
//
//
//   /* if (inData.color.x < 1 / 3.0f)
//    {
//        Clr = float4(0.0, 0.0, 0.0, 1.0);
//    }
//    else if (inData.color.x < 2 / 3.0f)
//    {
//        Clr = float4(0.5, 0.5, 0.5, 1.0);
//    }
//    else 
//    {
//        Clr = float4(1.0, 1.0, 1.0, 1.0);
//    }*/
//
//    //ifの階調変換　*お勧めしない
//
//
//
//    /*if (isTexture == false)
//    {
//        diffuse = lightSource * diffuseColor * tI;
//        ambient = lightSource * diffuseColor * ambientSource;
//    }
//    else
//    {
//        diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * tI;
//        ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
//    }*/
//   
//   /* if (abs(dot(inData.normal,normalize(inData.eyev))) < 0.4f) {
//        return float4(0, 0, 0, 0);
//    }
//    else {
//        return float4(1, 1, 1, 0);
//    }*/
//
//    //return diffuse +ambient ;
//}

//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D   g_texture : register(t0);   //テクスチャー
SamplerState    g_sampler : register(s0);   //サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global:register(b0)
{
    float4x4    matW;           //ワールド行列
    float4x4    matWVP;         // ワールド・ビュー・プロジェクションの合成行列
    float4x4    matNormal;      //法線
    float4      diffuseColor;   // ディフューズカラー（マテリアルの色）
    float4      ambientColor;
    float4      specularColor;
    float       shininess;
    bool        isTexture;      // テクスチャ貼ってあるかどうか

};

cbuffer global:register(b1)
{
    float4      lightPosition;  //ライトの方向
    float4      eyepos;         //視点
}
//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
    float4 pos      : SV_POSITION;  //位置
    float2 uv       : TEXCOORD; //UV座標
    float4 color    : COLOR;    //色（明るさ）
    float4 eyev     : POSITION1;
    float4 normal   : POSITION2;
    float4 light    : POSITION3;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
    //ピクセルシェーダーへ渡す情報
    VS_OUT outData = (VS_OUT)0;
    //ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
    //スクリーン座標に変換し、ピクセルシェーダーへ
    outData.pos = mul(pos, matWVP);
    outData.uv = uv;
    normal.w = 0;
    normal = mul(normal, matNormal);
    normal = normalize(normal);
    outData.normal = normal;



    float4 light = normalize(lightPosition);
    light = normalize(light);

    outData.color = saturate(dot(normal, light));
    float4 posw = mul(pos, matW);
    outData.eyev = eyepos - posw;
    //まとめて出力
    return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
    float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0); //物体がどれだけ環境光を反射または放射するかを制御する
    float4 diffuse;
    float4 ambient;
    float4 NL = dot(inData.normal, normalize(lightPosition));
    float4 reflection = reflect(normalize(-lightPosition), inData.normal);
    // float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));
     float4 specular = pow(saturate(dot(reflection, normalize(inData.eyev))), shininess) * specularColor;

     float4 Clr = 3.0f;
     inData.color = floor(inData.color * Clr) / Clr;

     /*if (inData.color.x < 1 / 3.0f)
     {
         Clr = float4(0.0, 0.0, 0.0, 1.0);
     }
     else if (inData.color.x < 2 / 3.0f)
     {
         Clr = float4(0.5, 0.5, 0.5, 1.0);
     }
     else
     {
         Clr = float4(1.0, 1.0, 1.0, 1.0);
     }*/



     if (isTexture == false)
     {
         diffuse = lightSource * diffuseColor * inData.color;
         ambient = lightSource * diffuseColor * ambientSource;
     }
     else
     {
         diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
         ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
     }

     return diffuse + ambient;
}