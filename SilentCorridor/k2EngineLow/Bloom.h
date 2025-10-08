#pragma once

namespace nsK2EngineLow {
	/// <summary>
	/// ブルーム。
	/// </summary>
	class Bloom : Noncopyable
	{
	public:
		Bloom(){}
		~Bloom(){}
		/// <summary>
		/// 初期化
		/// </summary>
		void Init(RenderTarget& mainRendertarget);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="mainRenderTarget"></param>
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// ブルームが発生する閾値を設定
		/// </summary>
		/// <param name="value"></param>
		void SetThreshold(float value)
		{
			m_samplingLuminanceCB1.threshold = value;
		}

		void GetThreshold() const
		{
			m_samplingLuminanceCB1.threshold;
		}

	private:
		/// <summary>
		/// 輝度抽出パスの定数バッファ１に送る内容。
		/// </summary>
		struct SSamplingLuminanceCB1 {
			float threshold = 1.0f;
		};
		RenderTarget m_luminanceRenderTarget;	//輝度抽出用のレンダリングターゲット
		Sprite m_luminanceSprite;				//輝度抽出用のスプライト
		GaussianBlur m_gaussianBlur[4];			//ガウシアンブラー
		Sprite m_finalSprite;					//最終合成用のスプライト
		SSamplingLuminanceCB1 m_samplingLuminanceCB1;
	};
}