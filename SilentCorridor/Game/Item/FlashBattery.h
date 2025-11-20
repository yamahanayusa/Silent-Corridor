#pragma once
#include "Item/IItem.h"

class Player;
class Inventory;

class FlashBattery : public IItem
{
public:
	FlashBattery(){}
	~FlashBattery()override{}

	bool Start();

	// どんな種類のアイテムか知らせる
	ItemType GetType() const override;

	// 取得時の処理
	bool OnCollect(Player* player)override;

private:
	// 拾うと増える在庫数
	const int COLLECT_COUNT = 1;

	ModelRender m_modelRender;
};