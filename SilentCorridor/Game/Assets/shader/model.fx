/*!
 * @brief	シンプルなモデルシェーダー。
 */

static const int MAX_POINT_NUM = 32;
static const int MAX_SPOT_NUM = 32;

////////////////////////////////////////////////
// ライト構造体
////////////////////////////////////////////////

// ディレクション用の構造体
struct DirectionLight
{
    float3 direction; // 方向
    float3 color; // カラー
    float3 eyePos; // 視点データにアクセスする
};
// ポイントライト用の構造体
struct PointLight
{
    float3 position; // 位置
    int use;
    float3 color; // カラー
    float range; // 影響範囲
    float3 posInView;
};
// スポットライト用の構造体
struct SpotLight
{
    float3 position; // 位置
    int use;
    float3 color; // カラー
    float range; // 放射範囲
    float3 direction; // 放射方向
    float angle; // 放射角度
    float3 posInView;
};
// リムライト用の構造体
struct RimLight
{
    float rimPower; // 強さ調整
    float3 rimColor; // 色
};

 ////////////////////////////////////////////////
 // 定数バッファ。
 ////////////////////////////////////////////////
 //モデル用の定数バッファ
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};
// ライト用定数バッファ
cbuffer LightCb : register(b1)
{
    DirectionLight m_directionLight;
    PointLight m_pointLight[MAX_POINT_NUM];
    SpotLight m_spotLight[MAX_SPOT_NUM];
    float pad;
    int m_pointLightNum;
    int m_spotLightNum;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
// スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};
// 頂点シェーダーへの入力。
struct SVSIn
{
    float4 pos : POSITION; // モデルの頂点座標。
    float2 uv : TEXCOORD0; // UV座標。
    SSkinVSIn skinVert; // スキン用のデータ。
    float3 normal : NORMAL; // 法線座標。
    
    // 頂点シェーダーの入力に接ベクトルと従ベクトルを追加
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
};
// ピクセルシェーダーへの入力。
struct SPSIn
{
    float4 pos : SV_POSITION; // スクリーン空間でのピクセルの座標。
    float2 uv : TEXCOORD0; // uv座標。
    float3 normal : NORMAL; // 法線座標。
    float3 worldPos : TEXCOORD1;
    float3 normalInView : TEXCOORD2; // カメラ空間の法線
    
    // ピクセルシェーダーの入力に接ベクトルと従ベクトルを追加
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0); // アルベドマップ 
Texture2D<float4> g_normalMap : register(t1); // 法線マップ
Texture2D<float4> g_specularMap : register(t2); // スペキュラマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3); // ボーン行列
sampler g_sampler : register(s0); // サンプラステート

////////////////////////////////////////////////
//関数宣言
////////////////////////////////////////////////

// ディレクションライトの計算
float3 CalcDirectionLig(SPSIn psIn);
// ポイントライトの計算
float3 CalcPointLig(SPSIn psIn, PointLight pointLig);
// スポットライト
float3 CalcSpotLig(SPSIn psIn, SpotLight spotLight);
// リムライトの計算
float3 CalcRimLig(SPSIn psIn);

// Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
// Phon鏡面反射光の計算
float3 CalcPhongSpecular(SPSIn psIn, float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
/// ディレクションライトの計算
/// </summary>
float3 CalcDirectionLig(SPSIn psIn)
{
     // Lambert拡散反射光を計算する
    float3 diffuseLig = CalcLambertDiffuse(m_directionLight.direction, m_directionLight.color, psIn.normal);

    // Phong鏡面反射光を計算する
    float3 specularLig = CalcPhongSpecular(psIn, m_directionLight.direction, m_directionLight.color, psIn.worldPos, psIn.normal);

    // 拡散反射光 + 鏡面反射光
    float3 lig = diffuseLig + specularLig;

    // 環境光を少し足す（固定値 0.3）
    lig += float3(0.3f, 0.3f, 0.3f);
    
    return lig;
}

/// <summary>
/// ポイントライトの計算
/// </summary>
float3 CalcPointLig(SPSIn psIn, PointLight pointLig)
{   
    // ライト → サーフェイス方向ベクトルを計算
    float3 ligDir = psIn.worldPos - pointLig.position;
    float distance = length(ligDir);
    ligDir = normalize(ligDir);

    // Lambert拡散反射光
    float3 diffPoint = CalcLambertDiffuse(ligDir, pointLig.color, psIn.normal);

    // Phong鏡面反射光
    float3 specPoint = CalcPhongSpecular(psIn, ligDir, pointLig.color, psIn.worldPos, psIn.normal);

    // 距離による減衰 (0 ～ 1)
    float affect = 1.0f - (1.0f / pointLig.range) * distance;
    //affect = max(0.0f, affect);
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    else if (affect > 0.4)
    {
        affect = 0.4f;
    }
    affect = pow(affect, 3.0f); // 減衰を急峻にする

    // 拡散反射光と鏡面反射光に減衰を乗算
    float3 lig = (diffPoint * affect) + (specPoint * affect);
    
    lig *= 500;

    return lig;
}

/// <summary>
/// スポットライトの計算
/// </summary>
float3 CalcSpotLig(SPSIn psIn, SpotLight spotLight)
{
    // サーフェイスに向かうライトベクトル
    float3 ligDir = psIn.worldPos - spotLight.position;
    ligDir = normalize(ligDir);
    
    // Lambert拡散反射
    float3 diff = CalcLambertDiffuse(ligDir, spotLight.color, psIn.normal);
    // Phong鏡面反射
    float3 spec = CalcPhongSpecular(psIn, ligDir, spotLight.color, psIn.worldPos, psIn.normal);

    float3 distance = length(psIn.worldPos - spotLight.position);

    // 距離減衰 (0～1)
    float affect = 1.0f - 1.0f / spotLight.range * distance;
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    affect = pow(affect, 3.0f); // 急峻に減衰
    diff *= affect;
    spec *= affect;

    // スポット角度による減衰
    float angle = dot(ligDir, spotLight.direction); // cosθ
    angle = abs(acos(angle));

    // cosθがcosLimitより小さければ外側 → 影響ゼロ
    float spotAffect = 1.0f - 1.0f / spotLight.angle * angle;
    if (spotAffect < 0.0f)
    {
        spotAffect = 0.0f;
    }
    spotAffect = pow(spotAffect, 0.1f);

    // 拡散+鏡面に減衰を掛け合わせ
    diff *= spotAffect;
    spec *= spotAffect;

    float3 lig = diff + spec;

    return lig;
}

/// <summary>
/// リムライトの計算
/// </summary>
float3 CalcRimLig(SPSIn psIn)
{
    // 視線方向ベクトル（ワールド空間）
    float3 toEye = normalize(m_directionLight.eyePos - psIn.worldPos);

    // 法線と視線方向の内積
    float rim = 1.0f - saturate(dot(psIn.normal, toEye));

    // 強さを指数で調整
    rim = pow(rim, 1);

    // リムライトの色を返す
    return rim;
}

/// <summary>
/// 法線マップの計算
/// </summary>
float3 CalcNormalMap(SPSIn psIn)
{
    // 法線マップから取得（0～1の範囲）
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;

    // -1～1 に変換
    localNormal = (localNormal * 2.0f) - 1.0f;

    // タンジェント・従ベクトル・法線を使ってワールド空間に変換
    float3 normal = psIn.tangent * localNormal.x 
                  + psIn.biNormal * localNormal.y
                  + psIn.normal * localNormal.z;

    return normal;
}

/// <summary>
/// スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
    [unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    psIn.pos = mul(m, vsIn.pos); // モデルの頂点をワールド座標系に変換
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos); // ワールド座標系からカメラ座標系に変換
    psIn.pos = mul(mProj, psIn.pos); // カメラ座標系からスクリーン座標系に変換
    
    // 頂点法線をピクセルシェーダーに渡す
    psIn.normal = mul(mWorld, vsIn.normal); // 法線を回転させる
    psIn.uv = vsIn.uv;
    
    // カメラ空間の法線を求める
    psIn.normalInView = mul(mView, psIn.normal); 
    
    // 接ベクトルと従ベクトルをワールド空間に変換する
    psIn.tangent = normalize(mul(mWorld, vsIn.tangent));
    psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));
    
    return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}

/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    psIn.normal = CalcNormalMap(psIn);
    
    // ディレクションライトを計算
    float3 lig = CalcDirectionLig(psIn);
    
    // ポイントライトの使用状況の確認
    if (m_pointLightNum > 0)
    {
        int count = 0; // 処理したポイントライトの数
        for (int i = 0; i < MAX_POINT_NUM; i++)
        {
            if (m_pointLight[i].use)
            {
                // ポイントライトの計算
                lig += CalcPointLig(psIn, m_pointLight[i]);
                count++;
            }
            if (count == m_pointLightNum) // 使用中のライトを処理し終えたらブレイク
            {
                break;
            }
        }

    }
    
        // ポイントライトの使用状況確認
    if (m_spotLightNum > 0)
    {
        int count = 0; // 処理したポイントライトの数
        for (int i = 0; i < MAX_SPOT_NUM; i++)
        {
            if (m_spotLight[i].use)
            {
                // ポイントライトの計算
                lig += CalcSpotLig(psIn, m_spotLight[i]);
                count++;
            }
            if (count == m_spotLightNum) // 使用中のライトを処理し終えたらブレイク
            {
                break;
            }
        }

    }
    
    // リムライトを加算
    lig *= CalcRimLig(psIn);
    
    // ここでアンビエントライトを加算
    lig += float3(0.5, 0.5, 0.5);
    
    float4 finalColor = g_albedo.Sample(g_sampler, psIn.uv);

    // 最終出力カラーに光を乗算する。
    finalColor.xyz *= lig;
    
    return finalColor;
}

/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(SPSIn psIn, float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // スペキュラマップからスペキュラ反射の強さをサンプリング
    float specPower = g_specularMap.Sample(g_sampler, psIn.uv);
    
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = m_directionLight.eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // 鏡面反射光を求める
    return lightColor * t * specPower;
}