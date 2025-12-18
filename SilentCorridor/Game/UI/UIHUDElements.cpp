#include "stdafx.h"
#include "UIHUDElements.h"
#include "UI/ItemSlot.h"
#include "Character/Player.h"

UIHUDElements::UIHUDElements()
{
    // 鍵スロットの初期化
    m_keySlot = new ItemSlot(ItemID::KEY, 
        "Assets/modelData/UI/Key.dds",
        -850.0f, 450.0f);

    // フラッシュスロットの初期化
    m_flashSlot = new ItemSlot(ItemID::FLASH_CAMERA,
        "Assets/modelData/UI/FlashCamera.dds",
        -700.0f, 450.0f);
}

UIHUDElements::~UIHUDElements()
{
    if (m_keySlot)delete m_keySlot;
    if (m_flashSlot)delete m_flashSlot;
}

bool UIHUDElements::Start()
{
    m_collectMessageRenderer.Init("Assets/modelData/UI/Acquisition.dds", 200.0f, 200.0f);
    m_collectMessageRenderer.SetPosition(Vector3(200.0f, -50.0f, 0.0f));

    // 透明度設定 (初期状態では非表示)
    m_collectMessageRenderer.SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));

   return true;
}

void UIHUDElements::Update()
{
    if (m_inventoryProvider) {
        if (m_keySlot) {
            m_keySlot->UpdateCountText(m_inventoryProvider->GetKeyCount());
        }
        if (m_flashSlot) {
            m_flashSlot->UpdateCountText(m_inventoryProvider->GetFlashCount());
        }

        // アイテムの選択状態の更新
        int selectedIndex = m_inventoryProvider->GetSelectedIndex();

        if (m_keySlot) {
            m_keySlot->SetSelected(selectedIndex == 0);
        }
        if (m_flashSlot) {
            m_flashSlot->SetSelected(selectedIndex == 1);
        }
    }

    m_collectMessageRenderer.Update();
}

void UIHUDElements::Render(RenderContext& rc)
{
    if (!m_inventoryProvider) {
        return;
    }

    if (m_keySlot){
        m_keySlot->Render(rc, m_inventoryProvider->GetKeyCount());
    }
    if (m_flashSlot){
        m_flashSlot->Render(rc, m_inventoryProvider->GetFlashCount());
    }
    m_collectMessageRenderer.Draw(rc);
}

void UIHUDElements::RenderInit()
{
    // 各ItemSlotのInitを実行
    m_keySlot->RenderInit();
    m_flashSlot->RenderInit();
}

void UIHUDElements::SetCollectMessageVisible(bool isVisible, const char* message)
{
    if (isVisible)
    {
        m_collectMessageRenderer.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }
    else
    {
        m_collectMessageRenderer.SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
    }
}