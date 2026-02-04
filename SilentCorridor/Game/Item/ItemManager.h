#pragma once

class Player;
class Item;

class ItemManager : public IGameObject
{
public:
    ItemManager() {}
    ~ItemManager() override;

    bool Start() override;
    void Update() override;
    void OnItemCollected(Item* collectedItem); // アイテムが拾われた時にItemクラスから呼んでもらう関数

private:
    void SpawnInitialItems(); // 最初の配置(5個)
    void CreateSpecifiedItem(int type); // アイテムを1つ生成する共通処理

    Player* m_player = nullptr; // プレイヤーの状態を見るため

    std::vector<Item*> m_itemList; // 今ステージにあるアイテムのリスト
    std::vector<int> m_shuffledIndices;  // ランダム管理用

    int m_remainingKeys = 0; // 残りの鍵の数
    int m_totalKeysCollected = 0; // プレイヤーがこれまでに拾った鹿銀尾総数
    int m_nextSpawnIndex = 0; // 次に使うm_shuffledIndicesの要素番号

    bool m_isCanExit = false; // 脱出可能フラグ（これがtrueになったらドアが開く）

    // 配置候補地のリスト
    const std::vector<Vector3> m_spawnPoints = {
        { 3750.0f, 330.0f, 10655.0f },
        { 4737.0f, 330.0f, 15090.0f },
        { 1770.0f, 330.0f, 15090.0f },
        { 858.0f, 330.0f, 6907.0f },
        { 10766.0f, 430.0f, -1907.0f },
        { 10766.0f, 430.0f, 1208.0f },
        { -291.0f, 430.0f, -10894.0f },
        { 2825.0f, 430.0f, -10894.0f },
        { 9640.0f, 20.0f, 8946.0f },
        { 14589.0f, 20.0f, -5803.0f },
        { 13125.0f, 20.0f, -11696.0f },
    };
};