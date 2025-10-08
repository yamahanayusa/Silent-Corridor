#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {
	SceneLight::SceneLight()
	{
	}

	SceneLight::~SceneLight()
	{

	}

	SPointLight* SceneLight::NewPontLight()
	{
		//ライトの数が上限に達していたら作らない
		if (m_light.m_numPointLight >= MAX_POINT_LIGHT) {
			return nullptr;
		}

		//昇順でライトを登録
		for (int i = 0;i <= MAX_POINT_LIGHT;i++) {
			if (m_light.m_pointLight[i].m_isUse == false) {
				m_light.m_pointLight[i].Use(); //ライトを使用中にする
				m_light.m_numPointLight++;
				return &m_light.m_pointLight[i];
			}
		}
	}

	void SceneLight::Init()
	{
		m_directionLight.SetDirection(Vector3(-1, -1, 1));
		m_directionLight.SetColor(Vector3(1.5f, 0.5f, 0.5f));
		m_directionLight.eyePos = g_camera3D->GetPosition();
	}

	void SceneLight::Update() 
	{
		m_directionLight.eyePos = g_camera3D->GetPosition();
	}
}
