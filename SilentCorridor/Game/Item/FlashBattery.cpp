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

	// Inventoryのポインタを取得
	Inventory* inventory = player->GetInventory();
	if (inventory == nullptr) return false;

	// Inventoryに在庫を追加
	if (inventory->AddFlash()) {
		K2_LOG("FlashBattery collected");
		return true;
	}

	// 追加に失敗した場合
	return false;
}

void FlashBattery::Render(RenderContext& rc)
{
	// モデルの位置をm_positionに更新
	m_modelRender.SetPosition(m_position);

	// 行列の更新と描画
	m_modelRender.Update();
	m_modelRender.Draw(rc);
}