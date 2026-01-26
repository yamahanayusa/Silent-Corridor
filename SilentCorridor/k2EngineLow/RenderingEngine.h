#pragma once
#include "PostEffect.h"

namespace nsK2EngineLow {
	class RenderingEngine
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();

		/// <summary>
		/// メインレンダーターゲットの初期化
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// 2D描画用レンダーターゲットの初期化
		/// </summary>
		void Init2DRenderTarget();

		/// <summary>
		/// メインレンダーターゲットをフレームバッファに転送するスプライトの初期化
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();

		/// <summary>
		/// メインレンダーターゲットをフレームバッファにコピーする
		/// </summary>
		/// <param name="rc"></param>
		void CopyMainRenderTargetToFrameBufferSprite(RenderContext& rc);

		/// <summary>
		/// レンダリング処理の実行
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);

		/// <summary>
		/// 描画するモデルを登録
		/// </summary>
		/// <param name="model"></param>
		void RegisterModel(ModelRender* modelRender)
		{
			m_registerModels.push_back(modelRender);
		}
		
		/// <summary>
		/// 描画するスプライトを登録
		/// </summary>
		/// <param name="sprite"></param>
		void RegiterSprite(SpriteRender* spriteRender)
		{
			m_2DObjects.push_back(spriteRender);
		}

		/// <summary>
		/// 描画するテキストを登録
		/// </summary>
		/// <param name="sprite"></param>
		void RegiterFont(FontRender* fontRender)
		{
			m_FontObjects.push_back(fontRender);
		}

		/// <summary>
		/// 2Dオブジェクトの描画
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);

		void SetNoiseStrength(float strength) {
			m_noiseStrength = strength;
		}

	private:
		struct SNoiseBuffer {
			float time;
			float strength;
			float pad[2];
		}m_noiseData;

		ConstantBuffer	m_noiseCB;							// GPUに送るための箱
		float			m_noiseTime = 0.0f;					// 毎フレーム増える時間
		float			m_noiseStrength = 0.0f;				// ノイズの強さ

		Sprite			m_copyMainRtToFrameBufferSprite;	// メインRTをフレームバッファにコピーするスプライト
		SceneLight		m_sceneLight;						// シーンライト
		RenderTarget	m_mainRenderTarget;					// メインレンダーターゲット
		RenderTarget	m_2DRenderTarget;					// 2D描画用レンダーターゲット
		Sprite			m_2DSprite;							// 2D描画用スプライト
		Sprite			m_mainSprite;						// メインスプライト

		PostEffect		m_postEffect;

		std::vector<ModelRender*>	m_registerModels;		// モデル登録用配列
		std::vector<SpriteRender*>	m_2DObjects;			// 2Dスプライト登録用配列
		std::vector<FontRender*>	m_FontObjects;			// テキスト登録用配列
	};
}