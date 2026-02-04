#include "stdafx.h"
#include "KeyItem.h"
#include "Character/Player.h"
#include "Character/Inventory.h"

bool KeyItem::OnCollect(Player* player)
{
	if (player == nullptr) return false;

	// Inventory‚Ìƒ|ƒCƒ“ƒ^‚ðŽæ“¾
	Inventory* inventory = player->GetInventory();
    if (inventory == nullptr) return false;

    // Inventory‚ÉÝŒÉ‚ð’Ç‰Á
    if (inventory->SetKeyCollected(true)) {
        return true;
    }

    return false;
}

ItemType KeyItem::GetType()const
{
    return enItemType_Key;
}