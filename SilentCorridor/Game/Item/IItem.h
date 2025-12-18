#pragma once

class Player;

// アイテムの種類
enum ItemType
{
	enItemType_Key,	// 鍵
	enItemType_Flash,	// フラッシュ
	enItemType_Num	// アイテムの総数
};

/// <summary>
/// すべてのアイテムが実装するインターフェース
/// </summary>
class IItem
{
public:
	// 仮想デストラクタ：継承したクラスをIItem*で削除する
	virtual~IItem() {}

	// アイテムの種類を取得
	// 純粋仮想関数：派生クラスの実装が必須
	virtual ItemType GetType()const = 0;

	// プレイヤーがアイテムを取得したときの処理をする
	// 純粋仮想関数：派生クラスで実装が必須
	virtual bool OnCollect(Player* player) = 0;

	// アイテムがインベントリにある状態で使用したときに処理をする
	// 仮想関数：デフォルト実装(falseを返す)実装は任意
	virtual bool OnUse(Player* player) { return false; }

	// モデルの描画
	// 純粋仮想関数：派生クラスで実装が必須
	virtual void Render(RenderContext& rc) = 0;
};