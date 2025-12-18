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

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void RenderInit();

	void SetInventoryProvider(IInventoryProvider* provider) { 
		m_inventoryProvider = provider;
	}

	void SetCollectMessageVisible(bool isVisible, const char* message = nullptr); // メッセージ表示制御関数

private:
	IInventoryProvider* m_inventoryProvider = nullptr;
	Inventory* m_inventory = nullptr;

	// 管理するアイテム
	ItemSlot* m_keySlot = nullptr;
	ItemSlot* m_flashSlot = nullptr;

	SpriteRender m_collectMessageRenderer;
};