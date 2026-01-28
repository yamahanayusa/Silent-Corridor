#pragma once

class Loading : public IGameObject
{
public:
	Loading(){}
	~Loading(){}
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	bool IsTimeOver() const; // 時間が来たかチェックする

	void UpdateTimer(); // タイマーを進める
	void TransitionToGame(); // ゲームに切り替える処理
	void UpdateUI(); // UIを動かす処理

private:
	float m_timer = 0.0f;
	float m_totalTime = 0.0f;
	static constexpr int FONT_COUNT = 13;

	Vector3 m_basePosition[FONT_COUNT]; // 各文字の元の位置
	SpriteRender m_fonts[FONT_COUNT];
	SpriteRender m_LoadingScreen;
};