#pragma once

class Enemy;
/// <summary>
/// ライター風ポイントライト
/// </summary>
class MarkerLight : public IGameObject
{
public:
    MarkerLight() {}
    ~MarkerLight() {}
    bool Start() override;
    void Update() override;

private:
    void UpdateLightPosition(); // 位置の更新
    void UpdateFlicker(); // 揺らぎの計算
    void ApplyToLight(); // ライトに反映

private:
    PointLight* m_pointLight = nullptr; // ポイントライト本体
    Enemy* m_enemy = nullptr;

    Vector3 m_offset = { 0.0f, 50.0f, 50.0f }; // プレイヤーの手元オフセット
    Vector3 m_colorBase = { 0.5f, 0.35f, 0.15f }; // 炎っぽいオレンジ
    Vector3 m_lightPos = Vector3::Zero; // ライトの位置
    Vector3 m_flickerColor = Vector3::Zero; // 揺らぎの色
    Vector3 m_flickerOffset = Vector3::Zero; // ゆらぎで動かす位置

    float m_range = 500.0f; // 光の届く範囲
    float m_flicker = 1.5f; // 明るさの揺らぎ
    float m_flickerSpeed = 20.0f; // 揺らぎの速さ
    float m_flickerStrength = 0.5f; //揺らぎの強さ
};