#pragma once
#include "Item/IItem.h"

class Player;

class KeyItem : public IItem
{
public:
	KeyItem() = default;
	~KeyItem() override = default;

	bool OnCollect(Player* player) override; // 取得時の処理
	ItemType GetType() const override; // どんな種類のアイテムか知らせる
};

