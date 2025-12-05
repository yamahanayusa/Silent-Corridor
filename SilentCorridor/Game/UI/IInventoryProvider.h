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
};