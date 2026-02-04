#include "stdafx.h"
#include "Item.h"
#include "Character/Player.h"
#include "Item/IItem.h"
#include "Item/ItemManager.h"

Item::~Item()
{
	// ロジックの消去
	if (m_itemLogic) {
		delete m_itemLogic;
		m_itemLogic = nullptr;
	}
}

void Item::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="logic_ptr"></param>
void Item::Init(IItem* logic_ptr)
{
	// IItemロジックを設定
	m_itemLogic = logic_ptr;
	if (!m_itemLogic) return;

	// ロジックからアイテムの種類を聞いて、モデルを切り替える
	ItemType type = logic_ptr->GetType();
	const char* modelPath = nullptr;

	if (type == enItemType_Key) {
		// 鍵のモデルパスを設定
		modelPath = "Assets/modelData/Item/Key.tkm";
	}
	else if (type == enItemType_Flash) {
		// フラッシュの時に使用する電池のモデルパスを設定
		modelPath = "Assets/modelData/Item/Battery.tkm";
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
	if (m_itemLogic == nullptr)	return;

	// ロジックの結果に基づき、Itemを破棄するか決定
	if (m_itemLogic->OnCollect(player)) {
		ItemManager* itemManager = FindGO<ItemManager>("itemManager");
		if(itemManager){
			itemManager->OnItemCollected(this);
		}
		// 自分を消す
		Dead();
	}
}
