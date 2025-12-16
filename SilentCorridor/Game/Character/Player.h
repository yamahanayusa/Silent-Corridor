#pragma once
#include "Character/Character.h"
#include "UI/IInventoryProvider.h"
#include "Character/Inventory.h"

class FlashTrigger;

class Player : public Character, public IInventoryProvider
{
public:
    Player() {};
    ~Player();
    bool Start() override; // 初期化処理
    void Update() override; // 更新処理
    int GetSelectedItemID() const; // 選択中のアイテムスロットIDを取得

    // プレイヤーの前方のベクトルを取得
    Vector3 GetForwardVector() const;

    // インベントリのポインタを返すゲッター
    Inventory* GetInventory()const { return m_inventory; }

    // IInventoryProviderの純粋仮想関数を実装
    int GetKeyCount() const override {
        return m_inventory ? m_inventory->GetKeyCount() : 0;
    }
    int GetFlashCount() const override {
        return m_inventory ? m_inventory->GetFlashCount() : 0;
    }

    // 選択中のインデックスを取得する
    int GetSelectedIndex() const override {
        return m_selectedIndex;
    }

    // 選択インデックスを選択する
    void SelectIndex(int index) override {
        if (index >= 0 && index <= 1) {
            m_selectedIndex = index;
        }
    }

private:
    void HandleInput();
    void HandleItemInput(); // アイテム取得入力処理
    void HandleSelectionInput(); // アイテム選択入力処理

public:
    Vector3	m_forward = Vector3::AxisZ; //ライト用

private:
    Inventory* m_inventory = nullptr;
    FlashTrigger* m_flashTrigger = nullptr;

    int m_selectedIndex = 0; // 選択中のインデックス
};