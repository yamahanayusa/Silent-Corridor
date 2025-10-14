#pragma once
class Stage : public IGameObject
{
public:
	Stage() {}
	~Stage() {}

	bool Start() override;
	void Render(RenderContext& rc) override;

	ModelRender m_modelRender;
	ModelRender m_stageCollision;
	PhysicsStaticObject physicsStaticObject;
};

