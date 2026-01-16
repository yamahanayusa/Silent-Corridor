#pragma once

class Title : public IGameObject
{
public:
	Title(){}
	~Title(){}
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	void UpdateSelection(); // 選択処理
	void CheckConfirmation(); // 決定処理
	void UpdateVisuals(); // Renderで描画するスプライトを選別のためUpdateだけ呼ぶ

private:
	int m_selectIndex = 0;

	SpriteRender m_baseSprite;
	SpriteRender m_yellow_StartUI;
	SpriteRender m_yellow_SettingsUI;
	SpriteRender m_yellow_ExitUI;
	SpriteRender m_red_StartUI;
	SpriteRender m_red_SettingsUI;
	SpriteRender m_red_ExitUI;
};