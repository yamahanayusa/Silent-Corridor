#pragma once
#include "Character.h"
#include "AI/PathFinding/PathFinding.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/NaviMesh.h"

enum Animation
{
    enAnimationClip_Walk,
    enAnimationClip_Idle,
    enAnimationClip_Num
};

class Stage;
class Enemy : public Character
{
public:
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    void InitPatrolPoints(); // ウェイポイントの定義専用
    void UpdateMove(); // 移動と実行とゴール判定
    void FindNextPatrolTarget(); // ランダム目標の決定と経路探索
    void UpdateAnimation(); // アニメーション

private:
    nsAI::NaviMesh* m_navMesh = nullptr; // ナビメッシュ
    nsAI::PathFinding m_pathFinder; // 経路探索
    nsAI::Path m_path; // 経路データ
    Stage* m_stage = nullptr;

    std::vector<Vector3>m_patrolPoints; // 徘徊ポイントリスト
    Vector3 m_targetPos = Vector3::Zero; // 移動目標

    bool m_isMoving = true;
    float m_speed = 10.0f; // 移動速度
    int m_patrolIndex = -1; // 現在の目標ポイントのインデックス

    ModelRender m_modelRender;
    AnimationClip m_animationClips[enAnimationClip_Num];		//アニメーションクリップ。

};
