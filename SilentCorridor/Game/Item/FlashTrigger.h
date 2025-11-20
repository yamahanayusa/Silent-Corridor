#pragma once

class Player;
class Inventory;
class Enemy;

class FlashTrigger
{
public:
	FlashTrigger(Player* owner) : m_owner(owner){}
	~FlashTrigger();
	
	// 光の減衰処理の更新
	void Update(float deltaTime);
	
	// フラッシュを焚く処理
	bool TryUseFlash();

private:
	// フラッシュ時の初期化と効果の適用
	void StartFlashEffect();

	void ApplyStunToEnemy();

private:
	Player* m_owner = nullptr; // 所有者
	SpotLight* m_spotLight = nullptr; // スポットライト

	// フラッシュ演出のパラメータと状態
	float m_flashDuration = 2.0f; // フラッシュが消えるまでの時間
	float m_maxRange = 3000.0f; // 最大の光の強さ
	float m_flashTimer = 0.0f; // 現在のフラッシュタイマー
	bool m_isFlashing = false; // フラッシュが発動中かどうかのフラグ
};