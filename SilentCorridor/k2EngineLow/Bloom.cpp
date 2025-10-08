#include "k2EngineLowPreCompile.h"
#include "Bloom.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	void Bloom::Init(RenderTarget& mainRenderTarget)
	{
        m_luminanceRenderTarget.Create(
            mainRenderTarget.GetWidth(),   // 解像度はメインレンダリングターゲットと同じ
            mainRenderTarget.GetHeight(),  // 解像度はメインレンダリングターゲットと同じ
            1,
            1,
            mainRenderTarget.GetColorBufferFormat(),
            DXGI_FORMAT_D32_FLOAT
        );
        {
            // 輝度抽出用のスプライトを初期化
            // 初期化情報を作成する
            SpriteInitData spriteInitData;
            // 輝度抽出用のシェーダーのファイルパスを指定する
            spriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
            // 頂点シェーダーのエントリーポイントを指定する
            spriteInitData.m_vsEntryPointFunc = "VSMain";
            // ピクセルシェーダーのエントリーポイントを指定する
            spriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
            spriteInitData.m_expandConstantBuffer = &m_samplingLuminanceCB1;
            spriteInitData.m_expandConstantBufferSize = sizeof(m_samplingLuminanceCB1);

            // スプライトの幅と高さはluminnceRenderTargetと同じ
            spriteInitData.m_width = mainRenderTarget.GetWidth();
            spriteInitData.m_height = mainRenderTarget.GetHeight();
            // テクスチャはメインレンダリングターゲットのカラーバッファー
            spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
            // 輝度テクスチャ
            //spriteInitData.m_textures[1] = &g_renderingEngine->GetLuminanceAvgTextureInScene();

            // 描き込むレンダリングターゲットのフォーマットを指定する
            spriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

            m_luminanceSprite.Init(spriteInitData);
        }

        //ガウシアンブラーを初期化
        m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());
        m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
        m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
        m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

        {
            SpriteInitData spriteInitData;
            spriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
            spriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
            spriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
            spriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();
            spriteInitData.m_width = mainRenderTarget.GetWidth();
            spriteInitData.m_height = mainRenderTarget.GetHeight();
            spriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
            spriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
            spriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
            spriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
            //spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

            m_finalSprite.Init(spriteInitData);
        }
	}

    void Bloom::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
    {
        rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
        rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
        rc.ClearRenderTargetView(m_luminanceRenderTarget);
        m_luminanceSprite.Draw(rc);
        rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);

        m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
        m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
        m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
        m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

        rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        rc.SetRenderTargetAndViewport(mainRenderTarget);
        m_finalSprite.Draw(rc);
        rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
    }
}