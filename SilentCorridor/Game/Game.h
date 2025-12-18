#pragma once

class Stage;
class Player;
class GameCamera;
class Enemy;
class MarkerLight;
class UIHUDElements;
class FlashBattery;
class UITimer;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	float m_elapsedTime = 0.0f; // Œo‰ßŽžŠÔ

	Stage* m_stage = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Enemy* m_enemy = nullptr;
	MarkerLight* m_markerLight = nullptr;
	UIHUDElements* m_uiSlot = nullptr;
	FlashBattery* m_flashBattery = nullptr;
	UITimer* m_uiTimer = nullptr;

	ModelRender m_modelRender;
};