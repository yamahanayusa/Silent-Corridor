#include "k2EngineLowPreCompile.h"
#include "FontRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	void FontRender::Draw(RenderContext& rc) {
		g_renderingEngine->RegiterFont(this);

	}
}