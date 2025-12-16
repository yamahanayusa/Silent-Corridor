#pragma once

namespace ItemID {
	const int KEY = 1;
	const int FLASH_CAMERA = 2;
}

class ItemSlot
{
public:
	ItemSlot(int itemID, const char* iconFilePath, float x, float y);
	~ItemSlot();

	void Render(RenderContext& rc,int count);
	void RenderInit(); // 描画が安定したときに呼ばれるInit
	void UpdateCountText(int count);
	void SetSelected(bool isSelected);

private:
	SpriteRender* m_icon = nullptr; // アイテムアイコンの画像

	std::vector<SpriteRender*>m_digitSprites; // 所持数表示用
	std::string m_iconFilePath; // アイコンのファイルパスを保持

	Vector3 m_iconPosition = Vector3::Zero; // アイコン座標
	Vector3 m_textStartPosition = Vector3::Zero; // テキストの表氏開始位置

	int m_currentCount = -1; // 現在の所持数
	int m_itemID = 0; // 識別ID

	float m_x = 0.0f; // xの初期値
	float m_y = 0.0f; // yの初期値

	bool m_isSelected = false;
};