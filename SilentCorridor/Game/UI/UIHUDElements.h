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
	void Update(float deltaTime);
	void Render(RenderContext& rc)override;
	void RenderInit();

	void SetInventoryProvider(IInventoryProvider* provider) { 
		m_inventoryProvider = provider;
	}

private:
	IInventoryProvider* m_inventoryProvider = nullptr;
	Inventory* m_inventory = nullptr;

	// 管理するアイテム
	ItemSlot* m_keySlot = nullptr;
	ItemSlot* m_flashSlot = nullptr;

	bool m_isInitializedDrawing = false; // 描画の初期化が完了したかのフラグ
	bool m_renderInitialized = false; // Renderでの初期化完了フラグ

	int m_updateDelayFrames = 0;
};