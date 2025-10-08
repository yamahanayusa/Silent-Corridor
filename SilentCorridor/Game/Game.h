#pragma once

class Stage;
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Stage* m_stage = nullptr;

	ModelRender m_modelRender;
};