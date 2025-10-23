#pragma once
#include "Character.h"

/// <summary>
/// Characterクラスを継承している
/// </summary>
class Player : public Character
{
public:
    Player() {}
    ~Player() {}
    bool Start() override;     // 初期化処理
    void Update() override;    // 更新処理


    Vector3	m_forward = Vector3::AxisZ; //ライト用

private:
    void HandleInput();   // 入力処理
};