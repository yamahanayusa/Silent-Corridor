#include "stdafx.h"
#include "Game.h"

bool Game::Start()
{
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