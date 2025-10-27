#include "stdafx.h"
#include "Enemy.h"
#include "Stage.h"
#include "time.h"

namespace {
    const float GROUND_Y = 0.0f;

    // ほぼ等しいかを判定するための関数
    bool IsEquals(const Vector3& a, const Vector3& b, const float value = 0.001f)
    {
        if (fabs(a.x - b.x) > value) return false;
        if (fabs(a.y - b.y) > value) return false;
        if (fabs(a.z - b.z) > value) return false;
        return true;
    }
}

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
bool Enemy::Start()
{
    // ランダムな値を使用するため
    srand(time(nullptr));

    // アニメーションの読み込み
    m_animationClips[enAnimationClip_Walk].Load("Assets/modelData/enemy/Enemy_Walk.tka");
    m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Idle].Load("Assets/modelData/enemy/Enemy_Walk.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);

    // モデル読み込み
    m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisZ);
    m_modelRender.SetScale(Vector3(10.0f, 10.0f, 10.0f));

    // ステージからナビメッシュを取得
    m_stage = FindGO<Stage>("stage");
    if (m_stage) {
        m_navMesh = m_stage->GetNavMesh();
    }

    InitPatrolPoints();

    // 最初のポイントに配置する
    if (!m_patrolPoints.empty()) {
        SetPosition(m_patrolPoints.at(0));
    }

    m_modelRender.SetPosition(GetPosition());
    m_characterController.Init(25.0f, 75.0f, GetPosition());

    // 初回経路探索
    if (m_navMesh && !m_patrolPoints.empty()) {
        FindNextPatrolTarget();
    }

    // 初期化
    m_isMoving = false;
    SetMoveSpeed(Vector3::Zero);

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
    // 移動ベクトル計算と再探索判定
    UpdateMove();

    // キャラコン実行前の位置を保存
    Vector3 oldPosition = GetPosition();

    // Character::Move()を実行
    Move();

    // 回転処理
    //Rotation();

    // モデルを更新
    m_modelRender.SetPosition(GetPosition());
    m_modelRender.Update();
}

/// <summary>
/// ウェイポイントの定義専用
/// </summary>
void Enemy::InitPatrolPoints()
{
    m_patrolPoints.push_back(Vector3(-75.0f, 0.0f, 2438.0f));
    m_patrolPoints.push_back(Vector3(-15.0f, 0.0f, 7358.0f));
    m_patrolPoints.push_back(Vector3(5829.0f, 0.0f, 7358.0f));
    m_patrolPoints.push_back(Vector3(5829.0f, 0.0f, 10255.0f));
    m_patrolPoints.push_back(Vector3(7823.0f, 0.0f, 10255.0f));
    m_patrolPoints.push_back(Vector3(12804.0f, 0.0f, 10255.0f));
    m_patrolPoints.push_back(Vector3(7878.0f, 0.0f, 8390.0f));
    m_patrolPoints.push_back(Vector3(12719.0f, 0.0f, 8390.0f));
    m_patrolPoints.push_back(Vector3(5857.0f, 0.0f, 6366.0f));
    m_patrolPoints.push_back(Vector3(12722.0f, 0.0f, 6366.0f));
    m_patrolPoints.push_back(Vector3(14688.0f, 0.0f, 5375.0f));
    m_patrolPoints.push_back(Vector3(2780.0f, 0.0f, 1437.0f));
    m_patrolPoints.push_back(Vector3(7859.0f, 0.0f, -1555.0f));
    m_patrolPoints.push_back(Vector3(8050.0f, 0.0f, -4843.0f));
    m_patrolPoints.push_back(Vector3(7830.0f, 0.0f, -7473.0f));
    m_patrolPoints.push_back(Vector3(8732.0f, 0.0f, -7473.0f));
    m_patrolPoints.push_back(Vector3(8816.0f, 0.0f, -9389.0f));
    m_patrolPoints.push_back(Vector3(7748.0f, 0.0f, -13292.0f));
    m_patrolPoints.push_back(Vector3(917.0f, 0.0f, -13317.0f));
    m_patrolPoints.push_back(Vector3(917.0f, 0.0f, -10400.0f));
    m_patrolPoints.push_back(Vector3(-2031.0f, 0.0f, -7350.0f));
    m_patrolPoints.push_back(Vector3(-2031.0f, 0.0f, -2510.0f));
}

/// <summary>
/// 移動と実行とゴール判定
/// </summary>
void Enemy::UpdateMove()
{
    // NavMeshがまだ取得できていない場合の遅延初期化
    if (!m_navMesh && m_stage) {
        m_navMesh = m_stage->GetNavMesh();
        if (m_navMesh && !m_patrolPoints.empty()) {
            // NavMesh取得後に初回経路探索を試みる
            FindNextPatrolTarget();
            return;
        }
    }

    // NavMeshがない、または経路ポイントがない場合は移動しない
    if (!m_navMesh || m_patrolPoints.empty()) {
        m_isMoving = false;
        return;
    }

    bool isEnd = false;

    // パスに沿って移動
    Vector3 oldPosition = GetPosition();
    Vector3 navMeshMoveVector = Vector3::Zero;
    Vector3 nextIdealPosition = m_path.Move(GetPosition(), m_speed, isEnd);
    SetPosition(nextIdealPosition);

    // 経路探索失敗しているはずなので、再度経路を探す
    if (IsEquals(oldPosition, GetPosition())) {
        m_isMoving = false;
        FindNextPatrolTarget();
    }
    else {
        m_isMoving = true;
    }

     // NavMeshが算出した移動ベクトルを計算
     navMeshMoveVector = GetPosition() - oldPosition;
     navMeshMoveVector *= 100;
     // キャラコンで使用するm_moveSpeedを設定
     SetMoveSpeed(navMeshMoveVector);

    // ゴールしたら次のランダムな目標へ
    if (isEnd) {
        SetMoveSpeed(Vector3::Zero);
        m_isMoving = false;
        FindNextPatrolTarget(); // 次の目標探索関数を呼び出す
    }

    SetPosition(oldPosition);
}

/// <summary>
/// ランダム目標の決定と経路探索
/// </summary>
void Enemy::FindNextPatrolTarget()
{
    // NavMeshが有効でない場合、処理しない
    if (m_patrolPoints.empty() || !m_navMesh) {
        return;
    }

    // ランダムインデックスを選ぶ
    int newIndex = -1;
    do {
        // 0 から m_patrolPoints.size() - 1 の範囲で乱数を生成
        int rand = std::rand();
        K2_LOG("Rondom:%d \n", rand);
        newIndex = rand % m_patrolPoints.size();
    } while (newIndex == m_patrolIndex && m_patrolPoints.size() > 1);

    m_patrolIndex = newIndex; // インデックスを更新

    // 目標の設定とスナップ
    m_targetPos = m_patrolPoints.at(m_patrolIndex);

    // 経路の再探索
    m_pathFinder.Execute(
        m_path,
        *m_navMesh,
        GetPosition(), // 新しい始点
        m_targetPos, // 新しい目的地
        PhysicsWorld::GetInstance(),
        25.0f,
        75.0f
    );
    m_path.Build();
}

/// <summary>
/// アニメーション
/// </summary>
void Enemy::UpdateAnimation()
{
    if (m_isMoving) {
        m_modelRender.PlayAnimation(enAnimationClip_Walk);
    }
    else {
        m_modelRender.PlayAnimation(enAnimationClip_Idle);
    }
}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="rc"></param>
void Enemy::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}