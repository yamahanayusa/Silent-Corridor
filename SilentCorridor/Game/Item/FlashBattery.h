#pragma once
#include "Item/IItem.h"

class Player;

class FlashBattery : public IItem
{
public:
	FlashBattery() = default;
	~FlashBattery() override = default;

	bool OnCollect(Player* player) override;	// 取得時の処理
	ItemType GetType() const override;	// どんな種類のアイテムか知らせる
};