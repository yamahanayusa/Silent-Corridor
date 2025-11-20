#pragma once
#include "Item/IItem.h"

class Player;

class Item : public IGameObject
{
public:
	Item() = default;
	~Item()override;

	// アイテムの初期化
	void Init(IItem* logic_ptr);

	// プレイヤーがアイテムを取得した際の処理
	void Collect(Player* player);

private:
	IItem* m_itemLogic = nullptr;
	ModelRender m_modelRender;
};