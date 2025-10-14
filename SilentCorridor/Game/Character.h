#pragma once

/// <summary>
/// プレイヤーや敵など、すべてのキャラクターの共通基底クラス
/// </summary>
class Character : public IGameObject
{
public:
    Character() {}
    ~Character() {}
    virtual bool Start() override { return true; }
    virtual void Update() override {}

    void Move();    // 移動処理
    void Rotation();    // 回転処理

    // 基本的な動作
    void SetPosition(const Vector3& pos) 
    {
        m_position = pos; 
    }
    const Vector3& GetPosition() const 
    {
        return m_position; 
    }

    void SetRotation(const Quaternion& rot) 
    {
        m_rotation = rot; 
    }
    const Quaternion& GetRotation() const {
        return m_rotation; 
    }

    void SetMoveSpeed(const Vector3& move) 
    {
        m_moveSpeed = move; 
    }
    const Vector3& GetMoveSpeed() const 
    {
        return m_moveSpeed; 
    }

protected:
    Vector3 m_position = Vector3::Zero;    // 現在位置
    Vector3 m_moveSpeed = Vector3::AxisZ;   // 移動速度
    Quaternion m_rotation = Quaternion::Identity;   // 現在の回転
    CharacterController m_characterController;  // キャラコン
};