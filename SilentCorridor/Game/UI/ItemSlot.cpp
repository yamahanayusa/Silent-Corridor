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

void ItemSlot::Render(RenderContext& rc,int count)
{
    m_icon->Draw(rc);

    // Xマークの描画
    if (m_digitSprites.size() > 0 && m_digitSprites[0]) {
        m_digitSprites[0]->Draw(rc);
    }

    // 数字の描画
    int spriteIndex = count + 1; // count (0〜5) -> Index (1〜6)

    if (spriteIndex <= 6 && m_digitSprites.size() > spriteIndex && m_digitSprites[spriteIndex]) {
        m_digitSprites[spriteIndex]->Draw(rc);
    }
}

void ItemSlot::RenderInit()
{
    // アイコンの初期化
    m_icon->Init(m_iconFilePath.c_str(), 120.0f, 120.0f);

    // 初期設定を１度だけ実行
    m_icon->SetPosition(m_iconPosition);
    m_icon->SetScale({ 1.0f, 1.0f, 1.0f });

    m_icon->Update();

    // テキスト開始位置も設定
    m_textStartPosition = { m_x - 10.0f, m_y - 80.0f, 0.0f };

    // xの初期化
    SpriteRender* sprite = new SpriteRender;
    sprite->Init("Assets/modelData/UI/x.dds", 16.0f, 16.0f);
    sprite->SetPosition(m_textStartPosition);
    sprite->Update();
    m_digitSprites.push_back(sprite);

    // 各桁の画像ファイルと位置を更新
    for (int i = 0; i <= 5; ++i) {
        char digitChar = '0' + i;
        SpriteRender* sprite = new SpriteRender;

        // 文字に対応するファイルパスを決定
        std::string charFilePath;
        charFilePath = "Assets/modelData/UI/" + std::string(1, digitChar) + ".dds";

        sprite->Init(charFilePath.c_str(), 32.0f, 32.0f);

        // 位置設定
        sprite->SetPosition(m_textStartPosition + Vector3(0.0f, 0.0f, 0.0f));

        m_digitSprites.push_back(sprite);
    }
    
    SetSelected(false);
}

void ItemSlot::UpdateCountText(int count)
{
    // xのマークの位置設定と描画
    // xのマークは数字の左側に固定配置
    float xOffset_X = 0.0f;

    if (m_digitSprites.size() > 0 && m_digitSprites[0]) {
        m_digitSprites[0]->SetPosition(m_textStartPosition + Vector3(xOffset_X, 0.0f, 0.0f));
        m_digitSprites[0]->Update();
    }


    // 数字スプライトの選択と配置、描画リストへの登録
    // 表示したい数字に対応するインデックスを計算
    int spriteIndex = count + 1;

    // 数字スプライトの位置
    float xOffset_Digit = 18.0f;

    // m_digitSprites[]0～5までを処理
    if (spriteIndex <= 6 && m_digitSprites[spriteIndex]) {
        SpriteRender* sprite = m_digitSprites[spriteIndex];

        // 位置を設定
        sprite->SetPosition(m_textStartPosition + Vector3(xOffset_Digit, 0.0f, 0.0f));

        // 描画リストへの登録と行列更新
        sprite->Update();
    }
}

void ItemSlot::SetSelected(bool isSelected)
{
    m_isSelected = isSelected;

    // アイコンのカラーを設定
    if (m_icon) {
        if (isSelected) {
            m_icon->SetColor({ 1.0f,1.0f,1.0f,1.0f });
        }
        else {
            m_icon->SetColor({ 1.0f,1.0f,1.0f,0.3f });
        }
    }
}