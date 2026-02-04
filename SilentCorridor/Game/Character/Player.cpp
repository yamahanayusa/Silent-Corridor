#include "stdafx.h"
#include "Player.h"
#include "Character/Inventory.h"
#include "Item/FlashTrigger.h"
#include "UI/ItemSlot.h"
#include "UI/UIHUDElements.h"
#include "Item/Item.h"

namespace
{
    static constexpr float MOVE_FORCE = 2000.0f; // 左スティック入力による移動
    static constexpr float INITIAL_LIGHT_HEIGHT = 50.0f; // ライトの初期位置の高さ
    static constexpr float COLLECT_RANGE = 800.0f; // 取得可能な最大距離
    static constexpr float COLLECT_FOV_DEGREE = 60.0f; // 取得に必要な視野角
}

Player::~Player()
{
    if (m_inventory)delete m_inventory;
    if (m_flashTrigger)delete m_flashTrigger;
}

bool Player::Start()
{
    m_position = Vector3(2000.0f, 0.0f, 2000.0f);
    // キャラクターコントローラー初期化
    m_characterController.Init(70.0f, 250.0f, m_position);

    // アイテムシステムの初期化
    m_inventory = new Inventory();
    m_flashTrigger = new FlashTrigger(this);

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
    // 移動
    HandleInput();

    // アイテムの選択の入力処理
    HandleSelectionInput();

    // アイテム入力
    HandleItemInput();

    // 視覚的なフィードバックを処理
    HandleCollectionMessage();

    // アイテム取得処理
    HandleItemCollection();

    // FlashTriggerの更新処理
    if (m_flashTrigger) {
        m_flashTrigger->Update(g_gameTime->GetFrameDeltaTime());
    }

    // 移動処理
    Move();

    // 回転処理
    Rotation();
}

Vector3 Player::GetForwardVector() const
{
    // カメラから前方ヴェクトルの取得
    Vector3 forward = g_camera3D->GetForward();
    forward.y = 0.0f;
    forward.Normalize();

    return forward;
}

int Player::GetSelectedItemID() const
{
    if (m_selectedIndex == 0) {
        return ItemID::KEY;
    }
    else if (m_selectedIndex == 1) {
        return ItemID::FLASH_CAMERA;
    }
    return 0;
}

void Player::HandleInput()
{
    Vector3 moveSpeed;
    // 水平方向の移動速度を初期化
    moveSpeed.x = 0.0f;
    moveSpeed.z = 0.0f;

    // 左スティック入力取得
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();

    // カメラの向きに基づいて移動方向を計算
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    // 水平方向だけに制限
    forward.y = 0.0f;
    right.y = 0.0f;

    // 入力値と係数を掛けて速度ベクトルに加算
    right *= stickL.x * MOVE_FORCE;
    forward *= stickL.y * MOVE_FORCE;
    moveSpeed += right + forward;

    // ここで移動速度の登録
    SetMoveSpeed(moveSpeed);
}

void Player::HandleItemInput()
{
    // ボタンが押されていなければ終了
    if (!g_pad[0]->IsTrigger(enButtonA)) return;

    // 選択中アイテムがフラッシュでなければ終了
    if (GetSelectedItemID() != ItemID::FLASH_CAMERA) return;

    // 電池がなければ終了
    if (m_inventory->GetFlashCount() <= 0) {
        K2_LOG("電池がありません！");
        return;
    }

    // メインの処理
    if (m_flashTrigger) {
        m_flashTrigger->TryUseFlash();
    }
}

void Player::HandleSelectionInput()
{
    static constexpr int ITEM_COUNT = 2;

    // 左矢印キーが押されたら前のアイテムへ
    if (g_pad[0]->IsTrigger(enButtonLeft)) {
        int newIndex = m_selectedIndex - 1;

        // 現在がインデックス0で左を押したら最後のインデックスに戻る
        if (newIndex < 0) {
            newIndex = ITEM_COUNT - 1;
        }

        SelectIndex(newIndex);
    }

    // 右矢印キーが押されたら次のアイテムへ
    else if (g_pad[0]->IsTrigger(enButtonRight)) {
        int newIndex = m_selectedIndex + 1;

        // 現在が最後のインデックスで→を押したらインデックス0に戻る
        if (newIndex >= ITEM_COUNT) {
            newIndex = 0;
        }

        SelectIndex(newIndex);
    }
}

void Player::HandleCollectionMessage()
{
    if (m_uiHUDElements == nullptr) return;

    // 取得可能範囲内の最も近いItemを検索
    Item* item = FindNearestCollectableItem(COLLECT_RANGE);

    if (item != nullptr)
    {
        // 取得可能なアイテムが見つかった場合、メッセージを表示
        m_uiHUDElements->SetCollectMessageVisible(true);
    }
    else
    {
        // アイテムが見つからない場合、メッセージを非表示
        m_uiHUDElements->SetCollectMessageVisible(false);
    }
}

void Player::HandleItemCollection()
{
    // 取得キーが押されたかチェック
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        Item* item = FindNearestCollectableItem(COLLECT_RANGE);
        if (item != nullptr) {
            item->Collect(this);
        }
    }
}

Item* Player::FindNearestCollectableItem(float range)
{
    Vector3 playerPos = GetPosition();
    playerPos.y = 0.0f;
    float nearestDistSq = range * range;
    Item* nearestItem = nullptr;

    Vector3 playerForward = GetForwardVector();
    playerForward.y = 0.0f; // 水平方向に限定
    //playerForward.Normalize();

    constexpr float HALF_FOV_RAD = Math::DegToRad(COLLECT_FOV_DEGREE / 2.0f);
    const float COS_FOV_THRESHOLD = Math::Cos(HALF_FOV_RAD);

    // FindAll は vector を返すので auto または std::vector<Item*> で受ける
    auto items = GameObjectManager::GetInstance()->FindAll<Item>();

    for (Item* item : items) {
        if (item == nullptr) continue;

        // アイテムとの距離と角度を判定するロジックを追加
        Vector3 itemPos = item->GetPosition();
        itemPos.y = 0.0f;
        Vector3 playerToItem = itemPos - playerPos;
        float distSq = playerToItem.LengthSq();

        // 距離チェック
        if (distSq > nearestDistSq) continue;

        // 視野角チェック
        playerToItem.Normalize();
        float dotProduct = playerForward.Dot(playerToItem);

        if (dotProduct >= COS_FOV_THRESHOLD) {
            // 最も近いものを更新
            nearestDistSq = distSq;
            nearestItem = item;
        }
    }
    return nearestItem;
}