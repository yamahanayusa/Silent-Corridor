#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {

	nsK2EngineLow::PointLight::PointLight()
	{
		//m_pointLig = g_sceneLight->NewPointLight();
	}

	nsK2EngineLow::PointLight::~PointLight()
	{

	}

	void PointLight::Init(const Vector3& pos, const Vector3& color, const float& range)
	{
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(color);
		m_pointLig->SetRange(range);
	}
}