#include "stdafx.h"
#include "KeyItem.h"
#include "Character/Player.h"
#include "Character/Inventory.h"

/// <summary>
/// このアイテムは鍵であることを知らせる
/// </summary>
/// <returns></returns>
ItemType KeyItem::GetType()const
{
	return enItemType_Key;
}

bool KeyItem::OnCollect(Player* player)
{
	if (player == nullptr) return false;

	// Inventoryのポインタを取得
	Inventory* inventory = player->GetInventory();

    if (inventory == nullptr) {
        return false;
    }

    // 鍵を取得したことをしらせる
    // 状態を記録
    if (inventory->SetKeyCollected(true)) {
        return true;
    }

    return false;
}