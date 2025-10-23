#pragma once

class Player;
/// <summary>
/// ライター風ポイントライト
/// </summary>
class Lighter : public IGameObject
{
public:
    Lighter() {}
    ~Lighter() {}
    bool Start() override;
    void Update() override;

private:
    void UpdateLightPosition(); // 位置の更新
    void UpdateFlicker(); // 揺らぎの計算
    void ApplyToLight(); // ライトに反映

private:
    SPointLight* m_pointLight = nullptr; // ポイントライト本体
    SceneLight* m_sceneLight = nullptr;
    Player* m_player = nullptr;

    Vector3 m_offset = { 0.0f, 80.0f, 50.0f }; // プレイヤーの手元オフセット
    Vector3 m_colorBase = { 1.0f, 0.7f, 0.3f }; // 炎っぽいオレンジ
    Vector3 m_lightPos = Vector3::Zero; // ライトの位置
    Vector3 m_flickerColor = Vector3::Zero; // 揺らぎの色
    Vector3 m_flickerOffset = Vector3::Zero; // ゆらぎで動かす位置

    float m_range = 2000.0f; // 光の届く範囲
    float m_flicker = 1.0f; // 明るさの揺らぎ
    float m_flickerSpeed = 15.0f; // 揺らぎの速さ
    float m_flickerStrength = 0.3f; //揺らぎの強さ
};