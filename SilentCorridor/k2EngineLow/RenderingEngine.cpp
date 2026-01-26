#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	RenderingEngine::RenderingEngine()
	{
		g_sceneLight = &m_sceneLight;
	}

	RenderingEngine::~RenderingEngine()
	{
		g_sceneLight = nullptr;
	}

	void RenderingEngine::Init() 
	{
		InitMainRenderTarget();                    // mainRTを作る
		Init2DRenderTarget();                      // UI用RTを作る
		InitCopyMainRenderTargetToFrameBufferSprite();
		m_postEffect.Init(m_mainRenderTarget);
		m_sceneLight.Init();                       // ライト初期化
		m_noiseCB.Init(sizeof(SNoiseBuffer), nullptr); // ノイズ用の定数バッファを初期化
		m_noiseStrength = 1.0f;
	}

	void RenderingEngine::Update()
	{
		g_sceneLight->Update();
	}

	void RenderingEngine::InitMainRenderTarget()
	{
		float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };

		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void RenderingEngine::Init2DRenderTarget()
	{
		float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };

		m_2DRenderTarget.Create(
			UI_SPACE_WIDTH,
			UI_SPACE_HEIGHT,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			clearColor
		);

		SpriteInitData spriteInitData;

		spriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = m_mainRenderTarget.GetWidth();
		spriteInitData.m_height = m_mainRenderTarget.GetHeight();
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSMain";
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		spriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();
		m_2DSprite.Init(spriteInitData);

		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = m_2DRenderTarget.GetWidth();
		spriteInitData.m_height = m_2DRenderTarget.GetHeight();
		m_mainSprite.Init(spriteInitData);
	}

	void RenderingEngine::InitCopyMainRenderTargetToFrameBufferSprite()
	{
		SpriteInitData spriteInitData;

		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();

		spriteInitData.m_width = g_graphicsEngine->GetFrameBufferWidth();
		spriteInitData.m_height = g_graphicsEngine->GetFrameBufferHeight();

		m_noiseData.time = 0.0f;
		m_noiseData.strength = 0.5f; // テスト用に強め

		spriteInitData.m_expandConstantBuffer = &m_noiseData;
		spriteInitData.m_expandConstantBufferSize = sizeof(SNoiseBuffer);

		spriteInitData.m_fxFilePath = "Assets/shader/noise.fx";
		spriteInitData.m_psEntryPoinFunc = "PSMain";
		spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_copyMainRtToFrameBufferSprite.Init(spriteInitData);
	}

	void RenderingEngine::CopyMainRenderTargetToFrameBufferSprite(RenderContext& rc)
	{
		BeginGPUEvent("CopyMainRenderTargetToFrameBuffer");

		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<FLOAT>(g_graphicsEngine->GetFrameBufferWidth());
		viewport.Height = static_cast<FLOAT>(g_graphicsEngine->GetFrameBufferHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		rc.SetViewportAndScissor(viewport);

		m_copyMainRtToFrameBufferSprite.Draw(rc);

		EndGPUEvent();
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		Update();
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);
		for (auto model : m_registerModels)
		{
			model->GetPModel()->Draw(rc);
		}

		m_postEffect.Render(rc, m_mainRenderTarget);
		Render2D(rc);
		// ここまでで「背景＋文字」が m_mainRenderTarget に描き込まれている

		// ノイズのデータを更新して送る
		m_noiseData.time += 0.016f;

		// スプライト自身が管理している拡張バッファを更新する
		// これにより、Draw()を呼んだ時に自動的に register(b1) に送られます
		m_copyMainRtToFrameBufferSprite.GetExpandConstantBufferGPU().CopyToVRAM(&m_noiseData);

		// 最後にノイズシェーダーを通して画面完成
		CopyMainRenderTargetToFrameBufferSprite(rc);

		m_registerModels.clear();
		m_2DObjects.clear();
		m_FontObjects.clear();
	}

	void RenderingEngine::Render2D(RenderContext& rc)
	{
		rc.WaitUntilToPossibleSetRenderTarget(m_2DRenderTarget);
		rc.SetRenderTargetAndViewport(m_2DRenderTarget);
		rc.ClearRenderTargetView(m_2DRenderTarget);
		m_mainSprite.Draw(rc);
		for (auto& renderObj : m_2DObjects)
		{
			renderObj->OnRender2D(rc);
		}
		for (auto& renderObj : m_FontObjects)
		{
			renderObj->OnRender2D(rc);
		}
		rc.WaitUntilFinishDrawingToRenderTarget(m_2DRenderTarget);

		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		m_2DSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}
}