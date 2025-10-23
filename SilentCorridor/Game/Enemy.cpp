#include "stdafx.h"
#include "Enemy.h"
#include "Stage.h"

bool Enemy::Start()
{
    // モデル読み込み
    m_modelRender.Init("Assets/modelData/enemy/enemy.tkm");
    m_modelRender.SetScale(Vector3(10.0f, 10.0f, 10.0f));

    // 初期位置をナビメッシュ上に
    m_position = Vector3(0.0f, 0.0f, 0.0f);
    m_modelRender.SetPosition(m_position);

    // ステージからナビメッシュを取得
    m_stage = FindGO<Stage>("stage");
    if (m_stage) {
        m_navMesh = m_stage->GetNavMesh();
    }

    // キャラクターコントローラー初期化
    m_characterController.Init(25.0f, 75.0f, m_position);

    // テスト用の移動先を設定
    m_targetPos = m_position + Vector3(2000.0f, 0.0f, 1000.0f);

    // ナビメッシュがあればすぐ経路探索
    if (m_navMesh) {
        m_pathFinder.Execute(
            m_path, // 移動経路を格納するパスデータ
            *m_navMesh, // ナビメッシュ参照
            m_position, // 現在位置
            m_targetPos,  // 目的地
            PhysicsWorld::GetInstance(), // 物理情報
            25.0f, // 半径
            75.0f // 高さ
        );
        m_path.Build(); // 経路情報を構築
    }

    return true;
}

void Enemy::Update()
{
    // 経路の終端に到達したかのフラグ
    bool isEnd = false;

    // パスに沿って移動
    m_position = m_path.Move(m_position, m_speed, isEnd);

    // ゴールしたら折り返す
    if (isEnd) {
        Vector3 temp = m_position;
        m_position = m_targetPos;
        m_targetPos = temp;

        // 経路再探索
        if (m_navMesh) {
            m_pathFinder.Execute(
                m_path,
                *m_navMesh,
                m_position,
                m_targetPos,
                PhysicsWorld::GetInstance(),
                25.0f,
                75.0f
            );
            m_path.Build();
        }
    }

    // モデルを更新
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}