#include "stdafx.h"
#include "FlashBattery.h"
#include "Character/Player.h"
#include "Character/Inventory.h"

bool FlashBattery::OnCollect(Player* player) 
{
	// Inventory‚Ìƒ|ƒCƒ“ƒ^‚ğæ“¾
	Inventory* inventory = player->GetInventory();
	if (inventory == nullptr) return false;

	// Inventory‚ÉİŒÉ‚ğ’Ç‰Á
	if (inventory->AddFlash()) {
		K2_LOG("FlashBattery collected");
		return true;
	}

	// ’Ç‰Á‚É¸”s‚µ‚½ê‡
	return false;
}

ItemType FlashBattery::GetType()const
{
	return enItemType_Flash;
}