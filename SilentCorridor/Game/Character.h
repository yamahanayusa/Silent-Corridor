#pragma once
#include "k2EngineLowPreCompile.h"

/// <summary>
/// プレイヤーや敵など、すべてのキャラクターの共通基底クラス
/// </summary>
class Character : public IGameObject
{
public:
    virtual bool Start() override { return true; }
    virtual void Update() override {}
    void Draw() {}

    // 基本的な動作
    void Move(const Vector3& moveDirection);   // 移動処理
    void SetSpeed(float speed);                // 移動速度を設定
    void SetPosition(const Vector3& pos);      // 座標を設定
    void SetDirection(const Vector3& dir);     // 向きを設定
    const Vector3& GetPosition() const;        // 現在座標を取得
    const Vector3& GetDirection() const;       // 現在の向きを取得
    float GetSpeed() const;                    // 現在の移動速度を取得

protected:
    Vector3 m_position = Vector3::Zero;     // 現在位置
    Vector3 m_direction = Vector3::AxisZ;   // 向いている方向
    float m_speed = 0.0f;                   // 現在の移動速度
};
