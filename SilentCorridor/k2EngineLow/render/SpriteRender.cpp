#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	void SpriteRender::Init(const char* filePath, const float w, const float h)
	{
		SpriteInitData initData;
		//DDSファイル(画像データ)のファイルパスを指定する。
		initData.m_ddsFilePath[0] = filePath;
		//Sprite表示用のシェーダーのファイルパスを指定する。
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		//スプライトの幅と高さを指定する。
		initData.m_width = w;
		initData.m_height = h;
		// 透過
		initData.m_alphaBlendMode = AlphaBlendMode_Trans;
		//Sprite初期化オブジェクトを使用して、Spriteを初期化する。
		m_sprite.Init(initData);
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->RegiterSprite(this);
	}
}