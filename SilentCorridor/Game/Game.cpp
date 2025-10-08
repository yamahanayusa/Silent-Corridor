#include "stdafx.h"
#include "Game.h"
#include "Stage.h"

bool Game::Start()
{
	m_stage = NewGO<Stage>(0, "stage");
 	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	m_modelRender.Update();
	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}