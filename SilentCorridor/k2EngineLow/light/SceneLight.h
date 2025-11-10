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
		Vector3 m_direction; // ライトの方向
		float	pad0;
		Vector3 m_color; // ライトのカラー
		float	pad1;
		Vector3 eyePos = Vector3::Zero; // 視点の位置
		float	pad2;

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
		int		m_isUse = false;// 使用状況
		Vector3 m_color;// カラー
		float	m_range;// 影響範囲
		Vector3 m_posInView;// カメラ空間での座標
		float	pad0;

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

		/// <summary>
		/// 更新
		/// </summary>
		void Update();
	};

	/// <summary>
	/// スポットライトの構造体
	/// </summary>
	struct SSpotLight {
		Vector3 m_position;				// 位置
		int		m_isUse = false;	// ライトの使用状況
		Vector3 m_color;			// 色
		float	m_range;			// 影響範囲
		Vector3 m_direction;		// 向き
		float	m_angle;			// 射出角度
		Vector3 m_posInView;		// カメラ空間での座標
		float	pad;

		/// <summary>
		/// ライトの位置を設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		/// <summary>
		/// 色の設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		void SetColor(float x, float y, float z)
		{
			SetColor({ x,y,z });
		}

		/// <summary>
		/// 影響範囲の設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range)
		{
			m_range = range;
		}

		/// <summary>
		/// 向きの設定
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(const Vector3& direction)
		{
			m_direction = direction;
			m_direction.Normalize();
		}
		void SetDirection(float x, float y, float z)
		{
			SetDirection({ x,y,z });
		}

		/// <summary>
		/// 影響範囲の設定
		/// </summary>
		/// <param name="angle"></param>
		void SetAngle(const float angle)
		{
			m_angle = Math::DegToRad(angle);
		}

		/// <summary>
		/// ポイントライトを使用中にする
		/// </summary>
		void Use()
		{
			m_isUse = true;
		}

		/// <summary>
		/// 更新
		/// </summary>
		void Update();
	};

	struct Light {
		SDirectionLight m_directionLight;// ディレクション
		SPointLight m_pointLight[MAX_POINT_LIGHT];// ポイントライト
		SSpotLight m_spotLight[MAX_SPOT_LIGHT]; // スポットライト
		int m_numPointLight = 0; // ポイントライトの使用数
		int m_numSpotLight = 0; // スポットライトの使用数
	};

	class SceneLight
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
		SPointLight* NewPointLight();

		/// <summary>
		/// 新規スポットライトを登録
		/// </summary>
		/// <returns></returns>
		SSpotLight* NewSpotLight();

		Light* GetLight() {
			return &m_light;
		}
		
	public:
		Light m_light;// シーンライト
	private:
		std::deque< SPointLight* > m_pointLight;       // 未使用のポイントライトのキュー。
		std::deque< SSpotLight* > m_spotLight;         // 未使用のスポットライトのキュー。。
	};
}