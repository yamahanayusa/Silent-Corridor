#include "stdafx.h"
#include "Title.h"
#include "Game.h"

bool Title::Start()
{
	// 初期化
	m_baseSprite.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
	
	m_yellow_StartUI.Init("Assets/modelData/UI/UI_Yellow_Start.dds", 300.0f, 100.0f);	
	m_yellow_StartUI.SetPosition(Vector3(0.0f, -50.0f, 0.0f));
	m_yellow_SettingsUI.Init("Assets/modelData/UI/UI_Yellow_Settings.dds", 300.0f, 100.0f);
	m_yellow_SettingsUI.SetPosition(Vector3(0.0f, -150.0f, 0.0f));
	m_yellow_ExitUI.Init("Assets/modelData/UI/UI_Yellow_Exit.dds", 300.0f, 100.0f);
	m_yellow_ExitUI.SetPosition(Vector3(0.0f, -250.0f, 0.0f));

	m_red_StartUI.Init("Assets/modelData/UI/UI_Red_Start.dds", 300.0f, 100.0f);
	m_red_StartUI.SetPosition(Vector3(0.0f, -50.0f, 0.0f));
	m_red_SettingsUI.Init("Assets/modelData/UI/UI_Red_Settings.dds", 300.0f, 100.0f);
	m_red_SettingsUI.SetPosition(Vector3(0.0f, -150.0f, 0.0f));
	m_red_ExitUI.Init("Assets/modelData/UI/UI_Red_Exit.dds", 300.0f, 100.0f);
	m_red_ExitUI.SetPosition(Vector3(0.0f, -250.0f, 0.0f));
	
	// 位置更新
	m_yellow_StartUI.Update();
	m_yellow_SettingsUI.Update();
	m_yellow_ExitUI.Update();
	m_red_StartUI.Update();
	m_red_SettingsUI.Update();
	m_red_ExitUI.Update();

	return true;
}

void Title::Update()
{
	UpdateSelection();
	CheckConfirmation();
	UpdateVisuals();
}

void Title::Render(RenderContext& rc)
{
	// 背景を描画
	m_baseSprite.Draw(rc);

	// Startボタン：選択中(0)なら赤、そうでなければ黄色
	if (m_selectIndex == 0) {
		m_red_StartUI.Draw(rc);
	}
	else {
		m_yellow_StartUI.Draw(rc);
	}

	// Settingsボタン：選択中(1)なら赤、そうでなければ黄色
	if (m_selectIndex == 1) {
		m_red_SettingsUI.Draw(rc);
	}
	else {
		m_yellow_SettingsUI.Draw(rc);
	}

	// Exitボタン：選択中(2)なら赤、そうでなければ黄色
	if (m_selectIndex == 2) {
		m_red_ExitUI.Draw(rc);
	}
	else {
		m_yellow_ExitUI.Draw(rc);
	}
}

void Title::UpdateSelection()
{
	// 3つの項目があるので、上下で 0 <-> 1 <-> 2 を切り替え
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_selectIndex--;
		if (m_selectIndex < 0) m_selectIndex = 2;
	}
	else if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_selectIndex++;
		if (m_selectIndex > 2) m_selectIndex = 0;
	}
}

void Title::CheckConfirmation()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (m_selectIndex == 0) {
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
		else if (m_selectIndex == 1) {
			// 設定
		}
		else if (m_selectIndex == 2) {
			PostQuitMessage(0); // ゲーム終了
		}
	}
}

void Title::UpdateVisuals()
{
	m_yellow_StartUI.Update();
	m_yellow_SettingsUI.Update();
	m_yellow_ExitUI.Update();

	m_red_StartUI.Update();
	m_red_SettingsUI.Update();
	m_red_ExitUI.Update();
}