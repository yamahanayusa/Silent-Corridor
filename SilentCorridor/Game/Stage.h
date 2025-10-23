#pragma once
#include "AI/PathFinding/NaviMesh.h"

class Stage : public IGameObject
{
public:
	Stage() {}
	~Stage() {}

	bool Start() override;
	void Render(RenderContext& rc) override;

	nsAI::NaviMesh* GetNavMesh()
	{
		return &m_navMesh;
	}

	ModelRender m_modelRender;	// ステージのモデル
	ModelRender m_stageCollision;	// ステージの当たり判定用のモデル
	PhysicsStaticObject physicsStaticObject;	// 当たり判定
	nsAI::NaviMesh m_navMesh;	// ナビメッシュデータ
};

