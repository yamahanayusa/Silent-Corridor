#pragma once

class IItem;

/// <summary>
/// プレイヤーが持っているアイテムや状態を管理するクラス
/// </summary>
class Inventory
{
public:
	Inventory() = default;
	~Inventory() = default;

	// ---鍵が利用するメソッド--- //
	
	// 鍵を取得したかどうかのフラグを設定
	bool SetKeyCollected(bool collected);

	// 鍵を持っているかの確認（ドアで使用）
	bool HasKey()const;

	// ---フラッシュを焚く際にに使用するバッテリーが利用するメソッド--- //

	// バッテリーの在庫を増やす
	bool AddFlash();

	// バッテリーの在庫を減らす
	bool UseFlash();

	// 現在のバッテリーの個数を取得する
	int GetFlashCount()const;
private:
	bool m_hasKey = false;	// 鍵の管理

	int m_flashCount = 4;	// バッテリーの在庫の管理
};

