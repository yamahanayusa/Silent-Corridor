#pragma once

class GameOver : public IGameObject
{
public:
	GameOver(){}
	~GameOver(){}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	void UpdateSelection();
	void CheckConfirmation();
	void UpdateVisuals();
private:
	int m_selectIndex = 0;	// メニューに戻るかリスタートするかの選択の際に使用

	SpriteRender m_baseSprite;	// ゲームオーバー画面
	SpriteRender m_restartText; // リスタートテキスト
	SpriteRender m_menuText;	// タイトルテキスト
};

