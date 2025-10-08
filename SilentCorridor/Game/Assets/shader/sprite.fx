/*!
 * @brief  スプライト用のシェーダー。
 */

cbuffer cb : register(b0)
{
    float4x4 mvp; // ワールドビュー射影行列（モデル→スクリーン変換）
    float4 mulColor; // 乗算カラー（色を掛ける）
};

// 頂点シェーダー入力構造体
struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

// ピクセルシェーダー入力構造体（頂点シェーダーの出力）
struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

// カラーテクスチャ
Texture2D<float4> colorTexture : register(t0);

// サンプラー
sampler Sampler : register(s0);

// --------------------------------------------
// 頂点シェーダー
// --------------------------------------------
PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

// --------------------------------------------
// ピクセルシェーダー（通常）
// --------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
    return colorTexture.Sample(Sampler, In.uv) * mulColor;
}

// --------------------------------------------
// ピクセルシェーダー（ガンマ補正あり）
// --------------------------------------------
float4 PSMainGamma(PSInput In) : SV_Target0
{
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
    color.xyz = pow(max(color.xyz, 0.0001f), 1.0f / 2.2f);
    return color;
}