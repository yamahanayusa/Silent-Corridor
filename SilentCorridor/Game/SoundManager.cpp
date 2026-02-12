#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::SoundManager()
{
    m_instance = this;
}

SoundManager::~SoundManager()
{
    if (m_bgmSource) {
        DeleteGO(m_bgmSource);
    }
    m_instance = nullptr;
}

bool SoundManager::Start()
{
    // BGM
    g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav"); // タイトルの音
    g_soundEngine->ResistWaveFileBank(1, "Assets/sound/GameOver.wav"); // ゲームオーバーの音

    // SE
    g_soundEngine->ResistWaveFileBank(2, "Assets/sound/EnemyLaughChasing.wav"); // 敵が追いかけてくる時の不気味な声
    g_soundEngine->ResistWaveFileBank(3, "Assets/sound/EnemySpottedScream.wav"); // 敵がプレイヤーを見つけた時の叫び声
    g_soundEngine->ResistWaveFileBank(4, "Assets/sound/BatteryPickup.wav"); // 電池を取得した時の音
    g_soundEngine->ResistWaveFileBank(5, "Assets/sound/CameraShutter.wav"); // カメラのシャッター音
    g_soundEngine->ResistWaveFileBank(6, "Assets/sound/KeyPickup.wav"); // 鍵を取得した時の音
    g_soundEngine->ResistWaveFileBank(7, "Assets/sound/MenuConfirm.wav"); // メニューの決定音
    g_soundEngine->ResistWaveFileBank(8, "Assets/sound/MenuNavigation.wav"); // メニューの切り替えの時の音
    g_soundEngine->ResistWaveFileBank(9, "Assets/sound/PlayerWalk.wav"); // プレイヤーの歩く時の音

    PlayBGM(0);

    return true;
}

void SoundManager::Update()
{
    // メインカメラの座標をサウンドエンジンに伝える
    g_soundEngine->SetListenerPosition(g_camera3D->GetPosition());
}

void SoundManager::PlayBGM(int bankID)
{
    // すでに指定されたBGMが流れていたら何もしない
    if (m_currentBgmBankID == bankID) {
        return;
    }
    
    // 前のBGMが流れていたら止めて消す
    if (m_bgmSource != nullptr) {
        m_bgmSource->Stop();
        DeleteGO(m_bgmSource);
        m_bgmSource = nullptr;
    }

    // 新しいBGMを再生
    m_bgmSource = NewGO<SoundSource>(0, "soundSource");
    m_bgmSource->Init(bankID);
    m_bgmSource->Play(true); // BGMはループ再生

    // 現在のBGMのIDを保存
    m_currentBgmBankID = bankID;
}

void SoundManager::PlaySE2D(int bankID)
{
    auto se = NewGO<SoundSource>(0, "soundSource");
    se->Init(bankID);
    se->Play(false); // SEは一回だけ再生
}

SoundSource* SoundManager::PlaySE3D(int bankID, const Vector3& position, bool isLoop)
{
    auto se = NewGO<SoundSource>(0, "soundSource");
    se->Init(bankID, true);
    se->SetPosition(position);
    se->Play(isLoop); // ループするかどうかの指定

    return se;
}