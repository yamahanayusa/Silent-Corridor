#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Character/Player.h"
#include "GameCamera.h"
#include "Character/Enemy.h"
#include "Item/Lighter.h"
#include "UI/UIHUDElements.h"

bool Game::Start()
{
	// “–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	if (m_uiSlot && m_player) {
		m_uiSlot->SetInventoryProvider(m_player);
	}
	m_player = NewGO<Player>(0, "player");
	m_stage = NewGO<Stage>(0, "stage");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_enemy = NewGO<Enemy>(0, "enemy");
	m_lighter = NewGO<Lighter>(0, "lighter");
	m_uiSlot = NewGO<UIHUDElements>(0, "uislot");

	m_modelRender.Update();
	return true;
}

void Game::Update()
{
	if (m_uiSlot) {
		m_uiSlot->Update(g_gameTime->GetFrameDeltaTime());
	}
}

void Game::Render(RenderContext& rc)
{
	if (m_uiSlot) {
		m_uiSlot->RenderInit();
	}

	m_modelRender.Draw(rc);

	if (m_uiSlot) {
		m_uiSlot->Render(rc);
	}
}