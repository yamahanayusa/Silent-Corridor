#include "stdafx.h"
#include "Lighter.h"
#include "Character/Player.h"

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
bool Lighter::Start()
{
    // 新しいポイントライトを登録
    m_pointLight = new PointLight();

    if (m_pointLight == nullptr) {
        return false;
    }
    // 初期設定
    m_colorBase = Vector3(1.0f, 0.7f, 0.3f);
    m_pointLight->Init(Vector3::Zero, m_colorBase, m_range);

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void Lighter::Update()
{
    // プレイヤーの位置を取得
    m_player = FindGO<Player>("player");
    if (m_player == nullptr || m_pointLight == nullptr) {
        return;
    }

    // ライトの位置の更新
    UpdateLightPosition();

    // 炎の揺らぎを計算
    UpdateFlicker();

    // 計算結果をライトに反映
    ApplyToLight();
}

/// <summary>
/// 炎の揺らぎを計算
/// </summary>
void Lighter::UpdateLightPosition()
{
    Vector3 playerPos = m_player->GetPosition();
    m_lightPos = playerPos + m_offset;
}

/// <summary>
/// ライトの位置の更新
/// </summary>
void Lighter::UpdateFlicker()
{
    // 前のフレームから今のフレームまでに経過した時間を取得
    float time = g_gameTime->GetFrameDeltaTime();

    // 明るさの揺らぎ
    m_flicker = 1.0f + sinf(time * m_flickerSpeed) * m_flickerStrength;

    // 炎の揺らめきによる位置のブレ
    m_flickerOffset = Vector3(sinf(time * 3.1f) * 3.0f, cosf(time * 2.7f) * 3.0f, 0.0f);

    // 赤～黄の色の変化
    float colorShift = 0.05 * sinf(time * 2.3f);
    m_flickerColor = Vector3(1.0f, 0.7f + colorShift, 0.3f) * m_flicker;
}

/// <summary>
/// 計算結果をライトに反映
/// </summary>
void Lighter::ApplyToLight()
{
    m_pointLight->SetPosition(m_lightPos + m_flickerOffset);
    m_pointLight->SetColor(m_flickerColor);
    m_pointLight->Update();
}
