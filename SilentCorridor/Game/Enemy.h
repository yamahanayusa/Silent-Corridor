#pragma once
#include "Character.h"
#include "AI/PathFinding/PathFinding.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/NaviMesh.h"

class Stage;
class Enemy : public Character
{
public:
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    nsAI::NaviMesh* m_navMesh = nullptr; // ナビメッシュ
    nsAI::PathFinding m_pathFinder; // 経路探索
    nsAI::Path m_path; // 経路データ
    Stage* m_stage = nullptr;

    Vector3 m_targetPos = Vector3::Zero; // 移動目標

    float m_speed = 10.0f; // 移動速度

    ModelRender m_modelRender;
};
