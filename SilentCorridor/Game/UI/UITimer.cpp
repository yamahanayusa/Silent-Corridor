#include "stdafx.h"
#include "UITimer.h"

bool UITimer::Start()
{
    m_fontRender.SetPosition(Vector3(730.0f, 500.0f, 0.0f));
    m_fontRender.SetScale(1.0f);
    m_fontRender.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    m_fontRender.SetText(L"00:00:00");
    return true;
}

void UITimer::Update()
{
    // 経過時間を秒から MM:SS:CC 形式に変換
    int totalSeconds = (int)m_elapsedTime;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int comma = (int)(m_elapsedTime * 100.0f) % 100;

    wchar_t timeStr[64];
    // MM:SS:CC 形式の文字列を作成
    swprintf_s(timeStr, 64, L"%02d:%02d:%02d", minutes, seconds, comma);

    // FontRenderにテキストをセット
    m_fontRender.SetText(timeStr);
}

void UITimer::Render(RenderContext& rc)
{
    m_fontRender.Draw(rc);
}