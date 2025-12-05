#include "stdafx.h"
#include "UIHUDElements.h"
#include "UI/ItemSlot.h"
#include "Character/Player.h"

UIHUDElements::UIHUDElements()
{

}

UIHUDElements::~UIHUDElements()
{
    if (m_keySlot)delete m_keySlot;
    if (m_flashSlot)delete m_flashSlot;
}

bool UIHUDElements::Start()
{
    // 鍵スロットの初期化
    m_keySlot = new ItemSlot(
        ItemID::KEY,
        "Assets/modelData/UI/Key.dds",
        50.0f,
        50.0f
    );

    // フラッシュスロットの初期化
    m_flashSlot = new ItemSlot(
        ItemID::FLASH_CAMERA,
        "Assets/modelData/UI/FlashCamera.dds",
        50.0f,
        120.0f
    );

    return true;
}

void UIHUDElements::Update(float deltaTime)
{
    if (m_renderInitialized) {
        if (m_updateDelayFrames < 10) {
            m_updateDelayFrames++;
            return; // Updateの処理をスキップし、クラッシュを防ぐ
        }
    }

    // 各スロットの更新
    if (m_renderInitialized && m_inventoryProvider) {
        // 鍵スロットの更新
        int newKeyCount = m_inventoryProvider->GetKeyCount();
        if (m_keySlot) {
            m_keySlot->UpdateCountText(m_inventoryProvider->GetKeyCount());
        }
        // フラッシュスロットの更新
        int newFlashCount = m_inventoryProvider->GetFlashCount();
        if (m_flashSlot) {
            m_flashSlot->UpdateCountText(m_inventoryProvider->GetFlashCount());
        }
    }

}

void UIHUDElements::Render(RenderContext& rc)
{
    if (m_renderInitialized) {
        if (m_keySlot)
        {
            m_keySlot->Render(rc);
        }
        if (m_flashSlot)
        {
            m_flashSlot->Render(rc);
        }
    }
}

void UIHUDElements::RenderInit()
{
    if (m_renderInitialized) return;

    // 各 ItemSlot の Init を実行
    if (m_keySlot) {
        m_keySlot->RenderInit();
    }
    if (m_flashSlot) {
        m_flashSlot->RenderInit();
    }

    // Initが完了したので、初期値を改めて渡して数字スプライトを生成させる
    if (m_inventoryProvider) {
        if (m_keySlot) {
            m_keySlot->UpdateCountText(m_inventoryProvider->GetKeyCount());
        }
        if (m_flashSlot) {
            m_flashSlot->UpdateCountText(m_inventoryProvider->GetFlashCount());
        }
    }

    m_renderInitialized = true;
}