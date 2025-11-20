#include "stdafx.h"
#include "Player.h"
#include "Character/Inventory.h"
#include "Item/FlashTrigger.h"

namespace
{
    static constexpr float MOVE_FORCE = 2000.0f;     // 左スティック入力による移動
    static constexpr float INITIAL_LIGHT_HEIGHT = 50.0f;    // ライトの初期位置の高さ
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

    // アイテム入力
    HandleItemInput();

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
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        // FlashTriggerコンポーネントにフラッシュ処理の実行を依頼する
        if (m_flashTrigger) {
            bool success = m_flashTrigger->TryUseFlash();

            // 処理結果に応じて、SEやUIフィードバックを行う
            if (success) {
 
            }
            else {
             
            }
        }
    }
}