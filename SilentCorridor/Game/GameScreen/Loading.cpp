#include "stdafx.h"
#include "RenderingEngine.h"
#include "Loading.h"
#include "Game.h"
#include <string>

namespace {
	static constexpr float NOISE_STRENGTH_DEFAULT = 0.0f; // ノイズの強さ
	static constexpr float WAIT_TIME = 8.0f; // ロード画面の表示時間
	static constexpr float JUMP_SPEED = 10.0f; // 跳ねる速さ
	static constexpr float JUMP_HEIGHT = 30.0f; // 跳ねる高さ
	static constexpr float FONT_INTERVAL = 60.0f; // 文字の間隔
	static constexpr float START_X = 150.0f; // 最初の文字のX座標
}

bool Loading::Start()
{
	m_LoadingScreen.Init("Assets/sprite/LoadingScreen.dds", 1920.0f, 1080.0f);
	m_LoadingScreen.SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

	for (int i = 0;i < FONT_COUNT;i++) {
		std::string path = "Assets/sprite/LoadingFont/" + std::to_string(i) + ".dds";

		// std::string を使ってファイル名を作ったときは、c_str()これいる
		m_fonts[i].Init(path.c_str(), 100.0f, 100.0f);

		// 基準の位置
		m_basePosition[i] = { START_X + (i * FONT_INTERVAL), -470.0f,0.0f };
		m_fonts[i].SetPosition(m_basePosition[i]);

		m_fonts[i].Update();
	}

	return true;
}

void Loading::Update()
{
	UpdateTimer(); // 時間を進める
	UpdateUI(); // ここで文字の座標を計算して更新

	if (IsTimeOver()) {
		TransitionToGame();
	}
}

void Loading::Render(RenderContext& rc)
{
	m_LoadingScreen.Draw(rc);
	for (auto& font : m_fonts) {
		font.Draw(rc);
	}
}

bool Loading::IsTimeOver() const
{
	return m_timer >= WAIT_TIME;
}

void Loading::UpdateTimer()
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	m_timer += deltaTime; // 2秒数える用
	m_totalTime += deltaTime; // アニメーション用
}

void Loading::TransitionToGame()
{
	NewGO<Game>(0, "game");
	g_renderingEngine->SetNoiseStrength(NOISE_STRENGTH_DEFAULT);
	DeleteGO(this);
}

void Loading::UpdateUI()
{
	for (int i = 0;i < FONT_COUNT;i++) {
		// 文字ごとにタイミングをずらすことでウェーブにする
		float offset = i * 0.3f;
		// sin波を使ってジャンプ量を計算する
		// 今回はfloatなので、fabs()を使用
		float jump = fabs(sin(m_totalTime * JUMP_SPEED - offset)) * JUMP_HEIGHT;

		// 保存しておいた基準の位置にジャンプを足す
		Vector3 newPosition = m_basePosition[i];
		newPosition.y += jump;
		
		m_fonts[i].SetPosition(newPosition);
		m_fonts[i].Update(); // スプライトの更新
	}
}
