#include "stdafx.h"
#include "Item.h"
#include "Character/Player.h"
#include "Item/IItem.h"

Item::~Item()
{
	if (m_itemLogic) {
		delete m_itemLogic;
		m_itemLogic = nullptr;
	}
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="logic_ptr"></param>
void Item::Init(IItem* logic_ptr)
{
	// IItemロジックを設定
	m_itemLogic = logic_ptr;
	
	// モデルの描画
	ItemType type = logic_ptr->GetType();
	const char* modelPath = nullptr; // モデルパスを保持するポインタ

	if (type == enItemType_Key) {
		// 鍵のモデルパスを設定
		modelPath = "Assets/modelData/Item/Key.tkm";
	}
	else if (type == enItemType_Flash) {
		// フラッシュの時に使用する電池のモデルパスを設定
		modelPath = "Assets/modelData/Item/Flash.tkm";
	}

	// モデル描画コンポーネントを初期化
	if (modelPath != nullptr) {
		m_modelRender.Init(modelPath);
	}
}

/// <summary>
/// 取得処理
/// </summary>
/// <param name="player"></param>
void Item::Collect(Player* player)
{
	// ロジックがない場合は何もしない
	if (m_itemLogic == nullptr) {
		return;
	}

	// IItemロジックのOnCollect()を呼ぶ
	bool destroySelf = m_itemLogic->OnCollect(player);

	// ロシックの結果に基づき、Itemを破棄するか決定
	if (destroySelf) {
		Dead();
	}
}
