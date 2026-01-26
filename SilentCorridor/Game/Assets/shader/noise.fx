// -----------------------------------------------------------
// 既存の定数バッファ（スプライト描画用）
// -----------------------------------------------------------
cbuffer cb : register(b0)
{
    float4x4 mvp; // 座標変換行列
    float4 mulColor; // 乗算色
    float4 screenPrame; // LocalConstantBufferに合わせて追加
};

// -----------------------------------------------------------
// ノイズ用の定数バッファを追加 (b1に登録)
// -----------------------------------------------------------
cbuffer NoiseBuffer : register(b1)
{
    float time; // プログラムから送られてくる現在の時間
    float strength; // ノイズの強さ
    float2 pad;
};

struct SVSIn
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct SPSIn
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

Texture2D<float4> g_texture : register(t0); // 画面全体のテクスチャ
sampler g_sampler : register(s0);

// -----------------------------------------------------------
// 頂点シェーダー 
// -----------------------------------------------------------
SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    psIn.pos = mul(mvp, vsIn.pos);
    psIn.uv = vsIn.uv;
    return psIn;
}

// -----------------------------------------------------------
// ピクセルシェーダー (ここでノイズを計算)
// -----------------------------------------------------------
float4 PSMain(SPSIn psIn) : SV_Target0
{
    // 元の画面の色（背景＋文字）をサンプリング
    float4 color = g_texture.Sample(g_sampler, psIn.uv);
    
    // 擬似乱数生成アルゴリズム
    // uv座標とtimeを混ぜることで、毎フレーム・全ピクセルでバラバラの値が出る
    float2 noiseUV = psIn.uv + float2(time, time);
    float n = frac(sin(dot(noiseUV, float2(12.9898, 78.233))) * 43758.5453);
    
    // ノイズを色に反映
    // (n - 0.5) は -0.5 ～ 0.5 の範囲になるので、色が明るくなったり暗くなったりする
    // strengthをかけてザラザラ具合を調整
    color.rgb += (n - 0.5f) * strength;
    
    return color;
}