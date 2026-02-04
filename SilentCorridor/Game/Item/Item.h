#pragma once
#include "Item/IItem.h"

class Player;

class Item : public IGameObject
{
public:
	Item() = default;
	~Item()override;

	void Update() override;
	void Render(RenderContext& rc) override;
	void Init(IItem* logic_ptr); // アイテムの初期化
	void Collect(Player* player); // プレイヤーがアイテムを取得した際の処理

	ItemType GetType() const {
		return m_itemLogic ? m_itemLogic->GetType() : enItemType_Num;
	}

	// 自身の座標を返す関数
	const Vector3& GetPosition() const {
		return m_position;
	}

	void SetPosition(const Vector3& pos) {
		m_position = pos;
		// モデルの座標も更新する
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
	}

private:
	IItem* m_itemLogic = nullptr;

	ModelRender m_modelRender;
	Vector3 m_position;
};