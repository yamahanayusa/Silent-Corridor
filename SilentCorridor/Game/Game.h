#pragma once

class Stage;
class Player;
class GameCamera;
class Enemy;
class MarkerLight;
class UIHUDElements;
class UITimer;
class GameOver;
class ItemManager;

class Game : public IGameObject
{
public:
	Game() {}
	~Game();
	bool Start() override;
	void Update() override;
	void OnPlayerCaught();
	void Render(RenderContext& rc) override;

private:
	float m_elapsedTime = 0.0f; // Œo‰ßŽžŠÔ

	Stage* m_stage = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Enemy* m_enemy1 = nullptr;
	Enemy* m_enemy2 = nullptr;
	MarkerLight* m_markerLight1 = nullptr;
	MarkerLight* m_markerLight2= nullptr;
	UIHUDElements* m_uiSlot = nullptr;
	UITimer* m_uiTimer = nullptr;
	GameOver* m_gameOver = nullptr;
	ItemManager* m_itemManager = nullptr;

	ModelRender m_modelRender;
};