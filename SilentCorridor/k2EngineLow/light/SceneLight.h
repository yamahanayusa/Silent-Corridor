#pragma once

namespace nsK2EngineLow
{
	/// <summary>
	///  �f�B���N�V�������C�g�̍\����
	/// </summary>
	struct SDirectionLight {
		Vector3 m_direction; // ���C�g�̕����B
		float pad0;
		Vector3 m_color; // ���C�g�̃J���[�B
		float pad1;
		Vector3 eyePos = Vector3::Zero; // ���_�̈ʒu

	public:
		void SetDirection(const Vector3& direction) {
			m_direction = direction;
		};
		void SetColor(const Vector3& color) {
			m_color = color;
		};
	};

	struct SPointLight {
		Vector3 m_position;// �ʒu
		float pad0;
		Vector3 m_color;// �J���[
		float m_range;// �e���͈�

	public:
		/// <summary>
		/// �|�C���g���C�g�ʒu�̐ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos){
			m_position = pos;
		}
		void SetPosition(float x, float y, float z){
			SetPosition({ x,y,z });
		}

		/// <summary>
		/// �|�C���g���C�g�F�̐ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color){
			m_color = color;
		}
		void SetColor(float x, float y, float z) {
			SetColor({ x,y,z });
		}

		/// <summary>
		/// �|�C���g���C�g�e���͈͂̐ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range) {
			m_range = range;
		}
	};

	struct Light {
		SDirectionLight directionLight;
		SPointLight pointLight;
	};

	class SceneLight :public IGameObject
	{
	public:
		SceneLight();
		~SceneLight();
		bool Start();
		void Update();

		SDirectionLight* GetSDirectionLight() {
			return &m_directionLight;
		}
		
	private:
		SDirectionLight m_directionLight;
	};
}