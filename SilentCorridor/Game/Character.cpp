#include "stdafx.h"
#include "Character.h"

/// <summary>
/// 指定方向へ移動する
/// ワールド空間上の移動方向
/// 移動方向ベクトルを正規化し、速度と経過時間を掛けて位置を更新します。
/// </summary>
/// <param name="moveDirection"></param>
void Character::Move(const Vector3& moveDirection)
{
    if (moveDirection.LengthSq() == 0.0f) {
        return; // 移動しない場合はスキップ
    }

    Vector3 normalizedDir = moveDirection;
    normalizedDir.Normalize();

    // フレームごとの移動量を加算
    m_position += normalizedDir * m_speed * GameTime().GetFrameDeltaTime();

    // 現在の進行方向を更新
    m_direction = normalizedDir;
}

/// <summary>
/// 移動速度を設定する
/// </summary>
/// <param name="speed"></param>
void Character::SetSpeed(float speed)
{
    m_speed = speed;
}

/// <summary>
/// 座標を設定する
/// </summary>
/// <param name="pos"></param>
void Character::SetPosition(const Vector3& pos)
{
    m_position = pos;
}

/// <summary>
/// 向きを設定する
/// </summary>
/// <param name="dir"></param>
void Character::SetDirection(const Vector3& dir)
{
    m_direction = dir;
}

/// <summary>
/// 現在位置を取得する
/// </summary>
/// <returns></returns>
const Vector3& Character::GetPosition() const
{
    return m_position;
}

/// <summary>
/// 現在の向きを取得する
/// </summary>
/// <returns></returns>
const Vector3& Character::GetDirection() const
{
    return m_direction;
}

/// <summary>
/// 現在の速度を取得する
/// </summary>
/// <returns></returns>
float Character::GetSpeed() const
{
    return m_speed;
}