#pragma once
#include "camera/SpringCamera.h"

class Player;

/// <summary>
/// ゲーム中のカメラを制御する
/// </summary>
class GameCamera : public IGameObject
{
public:
	GameCamera() {}
	~GameCamera() {}
	bool Start() override;
	void Update() override;

	Vector3 m_toCameraPos = Vector3::One;	// 注視点から視点に向かうベクトル。
	SpringCamera m_springCamera;	// ばねカメラ。

	Player* m_player = nullptr;		// プレイヤー。
};