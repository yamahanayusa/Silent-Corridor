#include "stdafx.h"
#include "ItemManager.h"
#include "Item/Item.h"
#include "Item/KeyItem.h"
#include "Item/FlashBattery.h"
#include "Character/Player.h"


ItemManager::~ItemManager()
{
}

bool ItemManager::Start()
{
    m_player = FindGO<Player>("player");

    SpawnInitialItems();
    return true;
}

void ItemManager::SpawnInitialItems()
{
    // インデックスの準備とシャッフル
    m_shuffledIndices.clear();
    for (int i = 0; i < (int)m_spawnPoints.size(); i++) {
        m_shuffledIndices.push_back(i);
    }

    // シャッフル処理
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = (int)m_shuffledIndices.size() - 1; i > 0; i--) {
        int j = std::rand() % (i + 1); // 0 から i の間でランダムな番号を選ぶ
        // i番目とj番目を入れ替える
        std::swap(m_shuffledIndices[i], m_shuffledIndices[j]);
    }

    m_nextSpawnIndex = 0;

    // 最初は鍵1個、電池4個を生成
    CreateSpecifiedItem(enItemType_Key);
    for (int i = 0;i < 4;i++) {
        CreateSpecifiedItem(enItemType_Flash);
    }
}

void ItemManager::CreateSpecifiedItem(int type)
{
    // 座標を使い切ったら何もしない
    if (m_nextSpawnIndex >= (int)m_shuffledIndices.size()) return;

    auto item = NewGO<Item>(0, "item");
    int spawnIndex = m_shuffledIndices[m_nextSpawnIndex];
    m_nextSpawnIndex++;

    // 最初の1個だけ鍵、残りは電池
    if (type == enItemType_Key) {
        item->Init(new KeyItem());
        m_remainingKeys++;
    }
    else {
        item->Init(new FlashBattery());
    }

    item->SetPosition(m_spawnPoints[spawnIndex]);
    m_itemList.push_back(item);
}

void ItemManager::OnItemCollected(Item* collectedItem)
{
    // リストから削除
    auto it = std::find(m_itemList.begin(), m_itemList.end(), collectedItem);
    if (it != m_itemList.end()) {
        m_itemList.erase(it);
    }

    if (collectedItem->GetType() != enItemType_Key) return;
    m_remainingKeys--;

    // まだ座標に余裕があり、累計の必要数に達していなければだす
    if (m_nextSpawnIndex < 8) {
        CreateSpecifiedItem(enItemType_Key);
        return;
    }

    if (m_remainingKeys <= 0) {
        m_isCanExit = true;
        K2_LOG("すべての鍵を回収！脱出可能です。");
    }
}

void ItemManager::Update()
{
    // ここで「救済措置」のチェックを将来的に書く
}