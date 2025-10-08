#pragma once

namespace nsK2EngineLow
{
	namespace {
		const int MAX_POINT_LIGHT = 32;
		const int MAX_SPOT_LIGHT = 32;
	}

	/// <summary>
	/// ディレクションライトの構造体
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

	/// <summary>
	/// ポイントライトの構造体
	/// </summary>
	struct SPointLight {
		Vector3 m_position;// 位置
		int m_isUse = false;// 使用状況
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

		/// <summary>
		/// ポイントライトの使用中にする
		/// </summary>
		void Use() {
			m_isUse = true;
		}
	};



	struct Light {
		SDirectionLight m_directionLight;// ディレクション
		SPointLight m_pointLight[MAX_POINT_LIGHT];// ポイントライト
		int  m_numPointLight = 0; //ポイントライトの使用数
	};

	class SceneLight :public IGameObject
	{
	public:
		SceneLight();
		~SceneLight();

		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 新しいポイントライトを作成
		/// </summary>
		/// <returns>新しく作成された SPointLight 型のポインタ。</returns>
		SPointLight* NewPontLight();

		SDirectionLight* GetSDirectionLight() {
			return &m_directionLight;
		}
		
	public:
		Light m_light;// シーンライト
	private:
		SDirectionLight m_directionLight;// ディレクションライト
	};
}