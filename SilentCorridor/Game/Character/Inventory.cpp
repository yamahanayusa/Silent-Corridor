#include "stdafx.h"
#include "Inventory.h"


// ---KeyItem--- //

/// <summary>
/// 脱出用の鍵を取得したフラグを設定
/// </summary>
/// <param name="collected"></param>
/// <returns></returns>
bool Inventory::SetKeyCollected(bool collected)
{
	// すでに持っていても上書きせずtrueを返す
	m_hasKey = collected;
	return true;
}

/// <summary>
/// 鍵を持っているか確認
/// </summary>
/// <returns></returns>
bool Inventory::HasKey()const
{
	return m_hasKey;
}


/// ---FlashItem--- //
namespace
{
    int MAX_FLASH_COUNT = 5;
}

/// <summary>
/// FlashBatteryを拾った際に在庫を1増やす
/// </summary>
bool Inventory::AddFlash()
{
    // 在庫の上限チェック
    if (m_flashCount >= 5) return false;

    m_flashCount++;
    return true;
}

/// <summary>
/// FlashTriggerがフラッシュを焚く際に、在庫を1減らす
/// </summary>
/// <returns></returns>
bool Inventory::UseFlash()
{
    if (m_flashCount > 0) {
        m_flashCount--;
        return true;
    }

    // 在庫がないため使用不可
    return false;
}

/// <summary>
/// Flashの現在の在庫数を取得する。
/// </summary>
/// <returns></returns>
int Inventory::GetFlashCount() const
{
    return m_flashCount;
}

/// <summary>
/// Keyの現在の所持数を取得する
/// </summary>
/// <returns></returns>
int Inventory::GetKeyCount() const
{
    return m_keyCount;
}
