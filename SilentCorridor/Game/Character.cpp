#include "stdafx.h"
#include "Character.h"

/// <summary>
/// characterの移動処理
/// </summary>
/// <param name="moveDirection"></param>
void Character::Move()
{
    const float deltaTime = g_gameTime->GetFrameDeltaTime();

    // キャラコンを必ず使う
    m_position = m_characterController.Execute(m_moveSpeed, deltaTime);
}

/// <summary>
/// characterの回転処理
/// </summary>
void Character::Rotation()
{
    if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f){
        m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
    }
}