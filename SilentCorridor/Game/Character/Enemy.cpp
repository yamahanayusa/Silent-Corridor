#include "stdafx.h"
#include "Enemy.h"
#include "Stage.h"
#include "time.h"
#include "Player.h"

namespace {
    const float DETECTION_RANGE = 2000.0f; // プレイヤー発見距離
    const float WALK_SPEED = 20.0f; // 徘徊速度
    const float CHASE_SPEED = 35.0f; // 追跡速度

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
    m_animationClips[enAnimationClip_Walk].Load("Assets/animData/Enemy_Walk.tka");
    m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/Enemy_Idle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Chase].Load("Assets/animData/Enemy_Run.tka");
    m_animationClips[enAnimationClip_Chase].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Stun].Load("Assets/animData/Enemy_Stun.tka");
    m_animationClips[enAnimationClip_Stun].SetLoopFlag(false);

    // モデル読み込み
    m_modelRender.Init("Assets/modelData/enemy/Enemy.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisZ);

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
    m_characterController.Init(80.0f, 300.0f, GetPosition());

    // 初回経路探索
    if (m_navMesh && !m_patrolPoints.empty()) {
        FindNextPatrolTarget();
    }

    // 初期設定
    m_logicState = enEnemyState_Walk;

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
    const float deltaTime = g_gameTime->GetFrameDeltaTime();

    if (m_logicState == enEnemyState_Stun) {
        m_stunTimer -= deltaTime;

        if (m_stunTimer <= 0.0f) {
            // スタン終了、徘徊状態に戻る
            m_logicState = enEnemyState_Walk;
            m_speed = WALK_SPEED;
            FindNextPatrolTarget(); // 次の目標を探す
        }

        // スタン中は他の全てのロジックをスキップ
        SetAnimationByState(); // アニメーションだけは更新する
        Rotation();
        m_modelRender.SetPosition(GetPosition());
        m_modelRender.SetRotation(GetRotation());
        m_modelRender.Update();
        return; // これ以降の処理は全てスキップ
    }

    // プレイヤーポインタの初期化
    if (m_player == nullptr) {
        m_player = FindGO<Player>("player");
    }

    // 追跡ロジックの実行と状態遷移チェック
    if (m_logicState == enEnemyState_Chase) {
        UpdateChase();
    }

    // 待機中でなければプレイヤー発見チェックを行う
    else if (m_logicState != enEnemyState_Idle) {
        if (CheckPlayerDetection()) {
            m_logicState = enEnemyState_Chase; // 追跡状態へ
            m_speed = CHASE_SPEED;
        }
    }

    // 移動ベクトル計算と再探索判定
    UpdateMove();

    // キャラコン実行前の位置を保存
    Vector3 oldPosition = GetPosition();

    // Character::Move()を実行
    if (m_logicState == enEnemyState_Walk || m_logicState == enEnemyState_Chase) {
        Move();
        // GetPosition()とoldPositionがほぼ等しいかチェック
        if (IsEquals(GetPosition(), oldPosition)) {
            // 動けていない場合：次の目標を再探索しm_isMovingをfalseにする
            if (m_isMoving) {
                FindNextPatrolTarget(); // 動けないなら別の経路を探す
            }
            m_isMoving = false;
            SetMoveSpeed(Vector3::Zero);
        }
        else {
            // 正常に動けている場合
            m_isMoving = true;
        }
    }
    else if (m_logicState == enEnemyState_Idle) {
        // 待機中は移動しない
        SetMoveSpeed(Vector3::Zero);
    }

    // 待機状態の管理と遷移
    SetAnimationByState();

    // 回転処理
    Rotation();

    // モデルを更新
    m_modelRender.SetPosition(GetPosition());
    m_modelRender.SetRotation(GetRotation());
    m_modelRender.Update();
}

/// <summary>
/// ウェイポイントの定義専用
/// </summary>
void Enemy::InitPatrolPoints()
{
    m_patrolPoints.push_back(Vector3(3007.0f, 0.0f, -1875.0f));
    m_patrolPoints.push_back(Vector3(-140.0f, 0.0f, -3034.0f));
    m_patrolPoints.push_back(Vector3(-2188.0f, 0.0f, 2227.0f));
    m_patrolPoints.push_back(Vector3(-2223.0f, 0.0f, 9979.0f));
    m_patrolPoints.push_back(Vector3(7640.0f, 0.0f, -1933.0f));
    m_patrolPoints.push_back(Vector3(8701.0f, 0.0f, 8817.0f));
    m_patrolPoints.push_back(Vector3(7686.0f, 0.0f, 12827.0f));
    m_patrolPoints.push_back(Vector3(760.0f, 0.0f, 12904.0f));
    m_patrolPoints.push_back(Vector3(-2132.0f, 0.0f, 9946.0f));
    m_patrolPoints.push_back(Vector3(-208.0f, 0.0f, -7781.0f));
    m_patrolPoints.push_back(Vector3(5919.0f, 0.0f, -7806.0f));
    m_patrolPoints.push_back(Vector3(12712.0f, 0.0f, -5883.0f));
    m_patrolPoints.push_back(Vector3(7739.0f, 0.0f, -10599.0f));
    m_patrolPoints.push_back(Vector3(12676.0f, 0.0f, -8754.0f));
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

    // NavMeshがない、または経路ポイントがない、待機アニメーションの場合は移動しない
    if (!m_navMesh || m_patrolPoints.empty() || m_state == enAnimationClip_Idle) {
        m_isMoving = false;
        SetMoveSpeed(Vector3::Zero);
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
     // 敵のスピード
     navMeshMoveVector *= m_speed;

     // キャラコンで使用するm_moveSpeedを設定
     SetMoveSpeed(navMeshMoveVector);

    // ゴールしたら次のランダムな目標へ
    if (isEnd) {
        SetMoveSpeed(Vector3::Zero);
        m_isMoving = false;

        if (m_logicState == enEnemyState_Chase) {

        }
        else if (m_logicState == enEnemyState_Walk){
            // 目標に到達すると待機状態に
            m_waitTimer = 0.0f;
            m_state = enAnimationClip_Idle;
        }
    }

    SetPosition(oldPosition);
}

void Enemy::UpdateChase()
{
    const float deltaTime = g_gameTime->GetFrameDeltaTime();

    // 追跡中はスピードを上げる
    m_speed = CHASE_SPEED;


    if (m_player == nullptr) {
        // プレイヤーがいなければ即座に徘徊に戻る
        m_logicState = enEnemyState_Walk;
        m_speed = WALK_SPEED;
        FindNextPatrolTarget();
        return;
    }

    // 毎フレーム、プレイヤーを目標として経路を再探索
    m_targetPos = m_player->GetPosition();

    m_pathFinder.Execute(
        m_path, 
        *m_navMesh, 
        GetPosition(), 
        m_targetPos,
        PhysicsWorld::GetInstance(), 
        80.0f, 
        300.0f
    );
    m_path.Build();


    // 追跡タイマーの管理
    // 追跡中も CheckPlayerDetection() を使用して、プレイヤーが「発見範囲内」にいるか確認
    if (CheckPlayerDetection()) {
        m_lostTimer = m_lostDuration; // 発見状態を維持できればタイマーをリセット
    }
    else {
        m_lostTimer -= deltaTime; // 発見範囲外に出たらタイマーを減らす
    }

    // m_lostDuration 秒経過したら徘徊に戻る
    if (m_lostTimer <= 0.0f) {
        m_logicState = enEnemyState_Walk; // 徘徊状態へ遷移
        m_speed = WALK_SPEED;
        FindNextPatrolTarget(); // 次のウェイポイントを探す
    }
}

bool Enemy::CheckPlayerDetection()
{
    if (m_player == nullptr) {
        return false;
    }

    Vector3 enemyToPlayer = m_player->GetPosition() - GetPosition();
    float distSq = enemyToPlayer.LengthSq();

    // 距離判定: 設定された発見距離の2乗と比較
    if (distSq < DETECTION_RANGE * DETECTION_RANGE) {
        return true;
    }

    return false;
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
        80.0f,
        300.0f
    );
    m_path.Build();
}

/// <summary>
/// 敵のスタン効果の付与
/// </summary>
/// <param name="duration"></param>
void Enemy::SetStun(float duration)
{
    // スタン時間の設定、ステートをスタンに遷移
    m_stunTimer = duration;
    m_logicState = enEnemyState_Stun;

    // スタン状態は移動速度を０にする
    SetMoveSpeed(Vector3::Zero);
    m_isMoving = false;

    // アニメーションの切り替え
    m_modelRender.PlayAnimation(enAnimationClip_Stun);

    // 追跡中の場合はロストタイマーリセット
    m_lostTimer = 0.0f;
}

/// <summary>
/// アニメーションの設定
/// </summary>
void Enemy::SetAnimationByState()
{
    // スタン状態
    if (m_logicState == enEnemyState_Stun) {
        m_modelRender.PlayAnimation(enAnimationClip_Stun);
        return;
    }

    // 状態が追跡中の場合
    if (m_logicState == enEnemyState_Chase) {
        // m_isMoving に基づいてアニメーションを切り替え
        if (m_isMoving) {
            m_modelRender.PlayAnimation(enAnimationClip_Chase);
        }
        else {
            // 壁にぶつかっているなどで動けていないが、まだ目標に向かおうとしている状態
            m_modelRender.PlayAnimation(enAnimationClip_Idle);
        }
    }

    // 状態が徘徊しているとき
    if (m_logicState == enEnemyState_Walk) {
        if (m_isMoving) {
            m_modelRender.PlayAnimation(enAnimationClip_Walk);
        }
        else {
            // 動けていないとき待機アニメーションを再生する
            m_modelRender.PlayAnimation(enAnimationClip_Idle);
        }
    }

    // 状態が待機の場合
    if (m_logicState == enEnemyState_Idle) {
        // アニメーション設定 (待機アニメーションを再生)
        m_modelRender.PlayAnimation(enAnimationClip_Idle);

        // 待機時間の更新と遷移判定
        const float deltaTime = g_gameTime->GetFrameDeltaTime();
        m_waitTimer += deltaTime;

        if (m_waitTimer >= m_waitDuration) {
            // 待機時間が終了したら次の目標を探索し移動状態へ
            FindNextPatrolTarget();
            m_logicState = enAnimationClip_Walk; // 移動状態へ遷移
        }
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