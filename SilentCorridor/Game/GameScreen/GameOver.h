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
	void UpdateSelection(); // パッドの入力をチェックして、選択項目(Index)を更新する
	void CheckConfirmation(); // 決定ボタンが押されたかチェックする
	void UpdateVisuals(); // 選択状態に合わせて、文字の色や大きさを更新する
private:
	int m_selectIndex = 0;	// メニューに戻るかリスタートするかの選択の際に使用

	SpriteRender m_baseSprite;	// ゲームオーバー画面
	SpriteRender m_restartText; // リスタートテキスト
	SpriteRender m_menuText;	// タイトルテキスト
};

