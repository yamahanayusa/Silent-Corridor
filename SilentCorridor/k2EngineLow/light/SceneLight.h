#pragma once

namespace nsK2EngineLow
{
	/// <summary>
	///  ディレクションライトの構造体
	/// </summary>
	struct SDirectionLight {
		Vector3 m_direction; // ライトの方向。
		float pad0;
		Vector3 m_color; // ライトのカラー。
		float pad1;
		Vector3 eyePos = Vector3::Zero; // 視点の位置

	public:
		void SetDirection(const Vector3& direction) {
			m_direction = direction;
		};
		void SetColor(const Vector3& color) {
			m_color = color;
		};
	};

	struct SPointLight {
		Vector3 m_position;// 位置
		float pad0;
		Vector3 m_color;// カラー
		float m_range;// 影響範囲

	public:
		/// <summary>
		/// ポイントライト位置の設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos){
			m_position = pos;
		}
		void SetPosition(float x, float y, float z){
			SetPosition({ x,y,z });
		}

		/// <summary>
		/// ポイントライト色の設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color){
			m_color = color;
		}
		void SetColor(float x, float y, float z) {
			SetColor({ x,y,z });
		}

		/// <summary>
		/// ポイントライト影響範囲の設定
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