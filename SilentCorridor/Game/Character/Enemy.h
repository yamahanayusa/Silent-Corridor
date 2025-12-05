#pragma once
#include "Character.h"
#include "AI/PathFinding/PathFinding.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/NaviMesh.h"

enum Animation
{
    enAnimationClip_Walk,
    enAnimationClip_Idle,
    enAnimationClip_Chase,
    enAnimationClip_Stun,
    enAnimationClip_Num
};

enum EnemyState
{
    enEnemyState_Walk, // 徘徊
    enEnemyState_Idle, // 待機
    enEnemyState_Chase, // 追跡
    enEnemyState_Stun, // スタン
};

class Stage;
class Player;
class Enemy : public Character
{
public:
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;
    void FindNextPatrolTarget(); // ランダム目標の決定と経路探索

    void SetStun(float duration); // FlashTriggerで使用

    // スタン中かどうか確認する
    bool IsStunned() const {
        return m_stunDuration > 0.0f;
    };

private:
    void InitPatrolPoints(); // ウェイポイントの定義専用
    void UpdateMove(); // 移動と実行とゴール判定
    void UpdateChase(); // プレイヤーを追跡
    bool CheckPlayerDetection(); // プレイヤーを発見判定
    void SetAnimationByState(); // アニメーションの設定

private:
    nsAI::NaviMesh* m_navMesh = nullptr; // ナビメッシュ
    nsAI::PathFinding m_pathFinder; // 経路探索
    nsAI::Path m_path; // 経路データ
    Stage* m_stage = nullptr;
    Player* m_player = nullptr;

    std::vector<Vector3>m_patrolPoints; // 徘徊ポイントリスト
    Vector3 m_targetPos = Vector3::Zero; // 移動目標

    bool m_isMoving = false;
    
    const float m_stunDuration = 3.0f; // 最大スタン時間
    const float m_lostDuration = 3.0f; // 見失うまでの猶予時間
    float m_speed = 20.0f; // 移動速度
    float m_waitDuration = 2.0f; // 待機時間
    float m_waitTimer = 0.0f; // 待機時間を計測するタイマー
    float m_lostTimer = m_lostDuration; // 見失う時間
    float m_stunTimer = 0.0f; // スタンの残り時間を管理するタイマー

    int m_patrolIndex = -1; // 現在の目標ポイントのインデックス
    int m_state = enAnimationClip_Walk; // 現在のアニメーション
    int m_logicState = enEnemyState_Walk; // 現在の状態

    ModelRender m_modelRender;
    AnimationClip m_animationClips[enAnimationClip_Num]; // アニメーションクリップ
};
