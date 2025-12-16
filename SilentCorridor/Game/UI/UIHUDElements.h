#pragma once
#include "UI/ItemSlot.h"
#include "UI/IInventoryProvider.h"

class Inventory;
class Player;
class UIHUDElements : public IGameObject
{
public:
	UIHUDElements();
	~UIHUDElements();

	bool Start()override;
	void Update();
	void Render(RenderContext& rc)override;
	void RenderInit();

	void SetInventoryProvider(IInventoryProvider* provider) { 
		m_inventoryProvider = provider;
	}

private:
	IInventoryProvider* m_inventoryProvider = nullptr;
	Inventory* m_inventory = nullptr;

	// ä«óùÇ∑ÇÈÉAÉCÉeÉÄ
	ItemSlot* m_keySlot = nullptr;
	ItemSlot* m_flashSlot = nullptr;
};