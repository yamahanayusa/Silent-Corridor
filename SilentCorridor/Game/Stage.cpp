#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	// ステージモデルの読み込み
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");

	// ステージの当たり判定用のモデルの読み込み
	m_stageCollision.Init("Assets/modelData/stage/stageCollision.tkm");
	physicsStaticObject.CreateFromModel(m_stageCollision.GetModel(), m_stageCollision.GetModel().GetWorldMatrix());
	
	// ナビメッシュ用のモデル
	m_navMesh.Init("Assets/modelData/stage/StageNav.tkn");
	return true;
}

void Stage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}