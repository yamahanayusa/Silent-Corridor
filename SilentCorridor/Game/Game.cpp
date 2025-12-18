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

bool Game::Start()
{
	// “–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_player = NewGO<Player>(0, "player");
	m_stage = NewGO<Stage>(0, "stage");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_enemy = NewGO<Enemy>(0, "enemy");
	m_markerLight = NewGO<MarkerLight>(0, "markerLight");
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
	// Œo‰ßŽžŠÔ‚ðXV
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();

	if (m_uiTimer != nullptr){
		m_uiTimer->SetElapsedTime(m_elapsedTime);

	}
	if (m_uiSlot) {
		m_uiSlot->Update();
	}
}

void Game::Render(RenderContext& rc)
{
}