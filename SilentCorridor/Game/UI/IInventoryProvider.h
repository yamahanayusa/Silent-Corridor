#pragma once

/// <summary>
/// UIが必要とするデータ取得機能のみ
/// </summary>
class IInventoryProvider
{
public:
	virtual ~IInventoryProvider() = default;
	virtual int GetKeyCount() const = 0;
	virtual int GetFlashCount() const = 0;
	virtual int GetSelectedIndex() const = 0; // 選択中のインデックスを取得
	virtual void SelectIndex(int index) = 0; // インデックスを設定する
};