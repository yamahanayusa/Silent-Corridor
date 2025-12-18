#pragma once

class UITimer : public IGameObject
{
public:
    UITimer() = default;
    ~UITimer() = default;

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

    void SetElapsedTime(float time) { m_elapsedTime = time; }

private:
    FontRender m_fontRender;

    float m_elapsedTime = 0.0f; // Œo‰ßŽžŠÔ
};