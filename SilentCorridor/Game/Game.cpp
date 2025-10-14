#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "GameCamera.h"

bool Game::Start()
{
	// “–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_stage = NewGO<Stage>(0, "stage");
	m_player = NewGO<Player>(0, "player");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_modelRender.Update();
	return true;
}

void Game::Update()
{

}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}