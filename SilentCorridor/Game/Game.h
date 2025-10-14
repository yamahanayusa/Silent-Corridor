#pragma once

class Stage;
class Player;
class GameCamera;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	Stage* m_stage = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;

	ModelRender m_modelRender;
};