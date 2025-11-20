#pragma once
#include "Character.h"

class Inventory;
class FlashTrigger;

/// <summary>
/// Characterクラスを継承している
/// </summary>
class Player : public Character
{
public:
    Player() {};
    ~Player();
    bool Start() override; // 初期化処理
    void Update() override; // 更新処理

    // プレイヤーの前方のベクトルを取得
    Vector3 GetForwardVector() const;

    // インベントリのポインタを返すゲッター
    Inventory* GetInventory()const { return m_inventory; }

private:
    void HandleInput();
    void HandleItemInput(); // アイテム取得入力処理

public:
    Vector3	m_forward = Vector3::AxisZ; //ライト用

private:
    Inventory* m_inventory = nullptr;
    FlashTrigger* m_flashTrigger = nullptr;
};