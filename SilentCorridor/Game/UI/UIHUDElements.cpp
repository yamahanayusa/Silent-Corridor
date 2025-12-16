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

}

void UIHUDElements::RenderInit()
{
    // 各 ItemSlot の Init を実行
    m_keySlot->RenderInit();
    m_flashSlot->RenderInit();
}