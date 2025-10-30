#include "stdafx.h"
#include "Player.h"

namespace
{
    static constexpr float MOVE_FORCE = 2000.0f;     // 左スティック入力による移動
}

bool Player::Start()
{
    m_position = Vector3(2000.0f, 0.0f, 2000.0f);
    // キャラクターコントローラー初期化
    m_characterController.Init(25.0f, 75.0f, m_position);

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
    // 入力処理
    HandleInput();

    // 移動処理
    Move();

    // 回転処理
    Rotation();
}

/// <summary>
/// 入力処理
/// </summary>
void Player::HandleInput()
{
    // 水平方向の移動速度を初期化
    m_moveSpeed.x = 0.0f;
    m_moveSpeed.z = 0.0f;

    // 左スティック入力取得
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();

    // カメラの向きに基づいて移動方向を計算
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    // 水平方向だけに制限
    forward.y = 0.0f;
    right.y = 0.0f;

    // 入力値と係数を掛けて速度ベクトルに加算
    right *= stickL.x * MOVE_FORCE;
    forward *= stickL.y * MOVE_FORCE;
    m_moveSpeed += right + forward;
}