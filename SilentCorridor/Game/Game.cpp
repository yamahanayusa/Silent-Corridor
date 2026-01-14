#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Character/Player.h"
#include "GameCamera.h"
#include "Character/Enemy.h"
#include "Character/MarkerLight.h"
#include "UI/UIHUDElements.h"
#include "Item/FlashBattery.h"
#include "UI/UITimer.h"
#include "GameScreen/GameOver.h"

Game::~Game()
{
	if (m_player) DeleteGO(m_player);
	if (m_stage) DeleteGO(m_stage);
	if (m_gameCamera) DeleteGO(m_gameCamera);
	if (m_enemy1) DeleteGO(m_enemy1);
	if (m_enemy2) DeleteGO(m_enemy2);
	if (m_uiSlot) DeleteGO(m_uiSlot);
	if (m_uiTimer) DeleteGO(m_uiTimer);
	if (m_flashBattery) DeleteGO(m_flashBattery);
	if (m_markerLight1) DeleteGO(m_markerLight1);
	if (m_markerLight2) DeleteGO(m_markerLight2);
}

bool Game::Start()
{
	// 当たり判定の可視化
	// PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_player = NewGO<Player>(0, "player");
	m_stage = NewGO<Stage>(0, "stage");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	m_enemy1 = NewGO<Enemy>(0, "enemy1");
	m_markerLight1 = NewGO<MarkerLight>(0, "markerLight1");
	m_markerLight1->SetTargetName("enemy1");

	m_enemy2 = NewGO<Enemy>(0, "enemy2");
	m_markerLight2 = NewGO<MarkerLight>(0, "markerLight2");
	m_markerLight2->SetTargetName("enemy2");

	m_uiSlot = NewGO<UIHUDElements>(0, "uislot");
	m_uiSlot->RenderInit();
	m_uiSlot->SetInventoryProvider(m_player);
	m_flashBattery = NewGO< FlashBattery>(0, "flashBattery");
	m_uiTimer = NewGO<UITimer>(0, "uiTimer");


	if (m_player) {
		m_player->SetUIHUDElements(m_uiSlot);
	}

	return true;
}

void Game::Update()
{
	// 経過時間を更新
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();

	if (m_uiTimer != nullptr){
		m_uiTimer->SetElapsedTime(m_elapsedTime);

	}
	if (m_uiSlot) {
		m_uiSlot->Update();
	}
}

void Game::OnPlayerCaught()
{
	// ゲームオーバーの表示
	m_gameOver = NewGO<GameOver>(0, "gameover");

	// ゲームオーバーの処理が呼ばれたらGameの削除
	DeleteGO(this);
}

void Game::Render(RenderContext& rc)
{
}