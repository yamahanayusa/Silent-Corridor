#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"

bool GameOver::Start()
{
	// 初期化
	m_baseSprite.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);

	m_restartText.Init("Assets/modelData/UI/Restart.dds", 250.0f, 80.0f);
	m_restartText.SetPosition(Vector3(780.0f, -380.0f, 0.0f));

	m_menuText.Init("Assets/modelData/UI/Menu.dds", 250.0f, 80.0f);
	m_menuText.SetPosition(Vector3(780.0f, -470.0f, 0.0f));

	// 位置更新
	m_restartText.Update();
	m_menuText.Update();
	return true;
}

void GameOver::Update()
{
	// 選択ボタンの処理
	UpdateSelection();

	// どの選択に進かの処理
	CheckConfirmation();

	// 選択中のUIの大きさや色の処理
	UpdateVisuals();
}

void GameOver::Render(RenderContext& rc)
{
	m_baseSprite.Draw(rc);
	m_restartText.Draw(rc);
	m_menuText.Draw(rc);
}

void GameOver::UpdateSelection()
{
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_selectIndex = 0;
	}
	else if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_selectIndex = 1;
	}
}

void GameOver::CheckConfirmation()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (m_selectIndex == 0) {
			NewGO<Game>(0, "game");
		}
		else {
			NewGO<Title>(0, "title");
		}
		DeleteGO(this);
	}
}

void GameOver::UpdateVisuals()
{
	if (m_selectIndex == 0) {
		m_restartText.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_restartText.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		m_menuText.SetScale(Vector3(0.8f, 0.8f, 1.0f));
		m_menuText.SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.6f));
	}
	else if (m_selectIndex == 1) {
		m_menuText.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_menuText.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		m_restartText.SetScale(Vector3(0.8f, 0.8f, 1.0f));
		m_restartText.SetColor(Vector4(1.0f, 1.0f, 1.0f, 0.6f));
	}

	// 大きさの更新
	m_restartText.Update();
	m_menuText.Update();
}