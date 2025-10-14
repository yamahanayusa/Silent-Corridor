#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	m_modelRender.Init("Assets/modelData/stage.tkm");
	m_stageCollision.Init("Assets/modelData/stageCollision.tkm");
	physicsStaticObject.CreateFromModel(m_stageCollision.GetModel(), m_stageCollision.GetModel().GetWorldMatrix());
	return true;
}

void Stage::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}
