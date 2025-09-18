#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {
	SceneLight::SceneLight()
	{
		g_sceneLight = this;
	}

	SceneLight::~SceneLight()
	{

	}

	bool SceneLight::Start() 
	{
		m_directionLight.SetDirection(Vector3(-1,-1,1));
		m_directionLight.SetColor(Vector3(0.5f, 0.5f, 0.5f));
		m_directionLight.eyePos = g_camera3D->GetPosition();

		return true;
	}

	void SceneLight::Update() 
	{
		m_directionLight.eyePos = g_camera3D->GetPosition();
	}
}
