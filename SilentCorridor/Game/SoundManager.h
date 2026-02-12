#pragma once

class SoundManager : public IGameObject
{
public:
	static SoundManager* GetInstance() { return m_instance; }
	SoundManager();
	~SoundManager() override;

	bool Start() override;

	void Update() override;
	void PlayBGM(int bankID); // BGMの処理
	void PlaySE2D(int bankID); // SEの処理

	// ループする場合は戻り値を保持して、移動や削除に使用する
	SoundSource* PlaySE3D(int bankID, const Vector3& position, bool isLoop = false);

private:
	static SoundManager* m_instance;
	SoundSource* m_bgmSource = nullptr;

	int m_currentBgmBankID = -1; // 0には音が入っているので初期値には-1を設定
};