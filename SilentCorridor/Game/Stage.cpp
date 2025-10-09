#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	m_modelRender.Init("Assets/modelData/stage.tkm");
	m_modelRender.Update();
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

}

Stage::~Stage()
{

}

void Stage::Render(RenderContext& renderContext) 
{
	m_modelRender.Draw(renderContext);
}
