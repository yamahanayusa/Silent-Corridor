#pragma once
#include "Bloom.h"

namespace nsK2EngineLow {
	class PostEffect :public Noncopyable
	{
	public:
		/// <summary>
		/// ‰Šú‰»
		/// </summary>
		/// <param name="mainRenderTarget"></param>
		void Init(RenderTarget& mainRenderTarget);

		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		void SetBloomThreshold(float value)
		{
			m_bloom.SetThreshold(value);
		}

	private:
		Bloom m_bloom;
	};
}