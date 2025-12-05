#include "stdafx.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot(int itemID, const char* iconFilePath, float x, float y) 
    : m_itemID(itemID), m_iconPosition({ x, y, 0.0f }), m_iconFilePath(iconFilePath), m_x(x), m_y(y)
{
    m_icon = new SpriteRender();
}

ItemSlot::~ItemSlot()
{
    if (m_icon)delete m_icon;
    for (auto& sprite : m_digitSprites) {
        delete sprite;
    }
    m_digitSprites.clear();
}

void ItemSlot::Render(RenderContext& rc)
{
    m_icon->Draw(rc);

    // 表示中の桁数分だけ描画
    size_t drawCount = ("x " + std::to_string(m_currentCount)).length();
    for (size_t i = 0; i < drawCount && i < m_digitSprites.size(); ++i) {
        m_digitSprites[i]->Draw(rc);
    }
}

void ItemSlot::UpdateCountText(int newCount)
{
    m_currentCount = newCount;
    std::string countStr = "x " + std::to_string(m_currentCount);

    // スプライトの数が足りなければ生成
    while (m_digitSprites.size() < countStr.length()) {
        SpriteRender* newDigit = new SpriteRender();
        m_digitSprites.push_back(newDigit);
    }

    // 各桁の画像ファイルと位置を更新
    for (size_t i = 0; i < countStr.length(); ++i) {
        char character = countStr[i];
        SpriteRender* sprite = m_digitSprites[i];

        // 文字に対応するファイルパスを決定
        std::string charFilePath;
        if (character == 'x') {
            charFilePath = "Assets/modelData/UI/x.dds";
        }
        else if (character >= '0' && character <= '5') {
            charFilePath = "Assets/modelData/UI/" + std::string(1, character) + ".dds";
        }

        // 描画が完了しているときのみ呼ぶ
        if (m_isRenderInitialized) {
            sprite->Init(charFilePath.c_str(), 32.0f, 32.0f);
        }

        // 位置設定
        float offsetX = i * 30.0f;
        sprite->SetPosition(m_textStartPosition + Vector3(offsetX, 0.0f, 0.0f));
    }
}

void ItemSlot::RenderInit()
{
    if (m_isRenderInitialized) return;

    if (m_icon) {
        // アイコンの初期化
        m_icon->Init(m_iconFilePath.c_str(), 32.0f, 32.0f);

        // 初期設定を１度だけ実行
        m_icon->SetPosition(m_iconPosition);
        m_icon->SetScale({ 1.0f, 1.0f, 1.0f });

        m_icon->Update();
    }

    // テキスト開始位置も設定
    m_textStartPosition = { m_x + 50.0f, m_y, 0.0f };

    m_isRenderInitialized = true;
}
