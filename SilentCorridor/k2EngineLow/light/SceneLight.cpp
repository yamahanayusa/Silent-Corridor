#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {
	SceneLight::SceneLight()
	{

	}

	SceneLight::~SceneLight()
	{

	}

	SPointLight* SceneLight::NewPointLight()
	{
		//ライトの数が上限に達していたら作らない
		if (m_light.m_numPointLight >= MAX_POINT_LIGHT) {
			return nullptr;
		}

		//昇順でライトを登録
		for (int i = 0;i < MAX_POINT_LIGHT;i++) {
			if (m_light.m_pointLight[i].m_isUse == false) {
				m_light.m_pointLight[i].Use(); //ライトを使用中にする
				m_light.m_numPointLight++;
				return &m_light.m_pointLight[i];
			}
		}
	}

	SSpotLight* SceneLight::NewSpotLight()
	{
		//ライトの数が上限に達していたら作らない
		if (m_light.m_numSpotLight >= MAX_SPOT_LIGHT) {
			return nullptr;
		}

		//昇順でライトを登録
		for (int i = 0; i < MAX_SPOT_LIGHT;i++) {
			if (m_light.m_spotLight[i].m_isUse == false) {
				m_light.m_spotLight[i].Use();	//ライトを使用中にする
				m_light.m_numSpotLight++;
				return &m_light.m_spotLight[i];
			}
		}
	}

	void SPointLight::Update()
	{
		m_posInView = m_position;
		g_camera3D->GetViewMatrix().Apply(m_posInView);
	}

	void SSpotLight::Update()
	{
		m_posInView = m_position;
		g_camera3D->GetViewMatrix().Apply(m_posInView);
	}

	void SceneLight::Init()
	{
		m_light.m_directionLight.SetDirection(Vector3(-1, -1, 1));
		m_light.m_directionLight.SetColor(Vector3(0.5f, 0.5f, 0.5f));
		m_light.m_directionLight.eyePos = g_camera3D->GetPosition();
	}

	void SceneLight::Update() 
	{
		m_light.m_directionLight.eyePos = g_camera3D->GetPosition();
	}
}
