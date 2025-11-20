#include "stdafx.h"
#include "FlashBattery.h"
#include "Character/Player.h"
#include "Character/Inventory.h"

bool FlashBattery::Start()
{
	m_modelRender.Init("Assets/modelData/Item/Battery.tkm");
	return true;
}

ItemType FlashBattery::GetType()const
{
	return enItemType_Flash;
}

bool FlashBattery::OnCollect(Player* player) 
{
	if (player == nullptr)return false;

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