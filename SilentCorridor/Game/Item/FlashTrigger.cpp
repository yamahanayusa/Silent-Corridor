#include "stdafx.h"
#include "FlashTrigger.h"
#include "Character/Player.h"
#include "Character/Inventory.h"
#include "Character/Enemy.h"

namespace {
	// スポットライト用
	const Vector3 COLOR = { 1000.0f,1000.0f,1000.0f };
	const Vector3 DIRECTION = { 0.0f,0.0f,1.0f };
	const float RANGE = 20000.0f;
	const float ANGLE = Math::DegToRad(2500.0f);

	// フラッシュ効果のパラメータ
	const float STAN_RANGE = 800.0f; // スタンの有効範囲
	const float STAN_DURACTION = 5.0f; // スタン時間
}

FlashTrigger::~FlashTrigger()
{
	if (m_spotLight) {
		delete m_spotLight;
		m_spotLight = nullptr;
	}
}

void FlashTrigger::Update(float deltaTime)
{
	if (m_owner == nullptr || m_spotLight == nullptr)return;
	m_spotLight->SetPosition(m_owner->GetPosition() + Vector3(0.0f, 50.0f, 0.0f));
	m_spotLight->SetDirection(m_owner->GetForwardVector());

	if (m_isFlashing) {
		m_flashTimer += deltaTime;

		if (m_flashTimer >= m_flashDuration) {
			// 持続時間を超えると明かりを消す
			m_spotLight->SetRange(0.0f);

			// インスタンスの破棄
			delete m_spotLight;
			m_spotLight = nullptr;
			m_isFlashing = false;
			return;
		}
		else {
			// 光の強さを計算
			float progress = m_flashTimer / m_flashDuration;
			float currentRange = m_maxRange * (1.0f - progress);

			// 計算した光量をスポットライトに適用
			m_spotLight->SetRange(currentRange);
		}
		// スポットライトの更新
		m_spotLight->Update();
	}
}

bool FlashTrigger::TryUseFlash()
{
	// オーナーがいるかと発動中ではないチェック
	if (m_owner == nullptr || m_isFlashing) return false;

	// 在庫チェック
	Inventory* inventory = m_owner->GetInventory();
	if (inventory == nullptr || inventory->GetFlashCount() <= 0) {
		return false;
	}

	// 在庫の消費と効果の発動
	if (inventory->UseFlash()) {
		// SpotLightのインスタンスを生成する
		m_spotLight = new SpotLight();
		if (m_spotLight == nullptr) return false; // 生成失敗チェック

		// 生成したインスタンスの初期化
		m_spotLight->Init(m_owner->GetPosition(), COLOR, RANGE, DIRECTION, ANGLE);

		StartFlashEffect(); // 敵へのスタン効果を適用タイマーを開始

		return true;
	}
	return false;
}

void FlashTrigger::StartFlashEffect()
{
	m_flashTimer = 0.0f;
	m_isFlashing = true;

	// スポットライトを最大光量で点灯
	m_spotLight->SetRange(m_maxRange);

	// 敵へのスタン効果を適用
	ApplyStunToEnemy();
}

void FlashTrigger::ApplyStunToEnemy()
{
	// フラッシュの発生源を取得
	Vector3 flashOrigin = m_owner->GetPosition();

	// フラッシュの有効範囲
	const float range = STAN_RANGE;

	// 円錐状のフラッシュなので方向を取得
	Vector3 flashDirection = m_owner->GetForwardVector();

	// 全部のEnemyの検索
	std::vector<Enemy*> enemyList = GameObjectManager::GetInstance()->FindAll<Enemy>();

	// 検査して範囲内の敵にスタン効果を適応
	for (Enemy* enemy : enemyList) {
		// ポインタが有効かチェック
		if (enemy == nullptr)continue;

		// 敵が範囲内にいるのかチェック
		float distance = (enemy->GetPosition() - flashOrigin).Length();

		if (distance <= range) {
			enemy->SetStun(STAN_DURACTION);
		}
	}
}