#pragma once

class Title : public IGameObject
{
public:
	Title(){}
	~Title(){}
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	SpriteRender m_spriteRender;
};