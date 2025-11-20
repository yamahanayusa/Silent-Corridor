#pragma once
#include "Item/IItem.h"

class Player;
class Inventory;

class KeyItem : public IItem
{
public:
	KeyItem(){}
	~KeyItem()override {}

	// どんな種類のアイテムか知らせる
	ItemType GetType() const override;

	// 鍵を持っている状態フラグをInventoryに設定
	bool OnCollect(Player* player) override;
};

