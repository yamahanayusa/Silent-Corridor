#pragma once
#include "Item/IItem.h"

class Player;
class Inventory;

class FlashBattery : public IItem, public IGameObject
{
public:
	FlashBattery() {}
	~FlashBattery() override {}

	bool Start();
	bool OnCollect(Player* player) override;	// 取得時の処理

	void Render(RenderContext& rc);
	void SetPosition(const Vector3& position) { m_position = position; }

	ItemType GetType() const override;	// どんな種類のアイテムか知らせる

	Vector3 GetPosition() const { return m_position; } // 位置の取得

private:
	const int COLLECT_COUNT = 1; // 拾うと増える在庫数

	Vector3 m_position = Vector3::Zero; // アイテムの位置

	ModelRender m_modelRender;
};