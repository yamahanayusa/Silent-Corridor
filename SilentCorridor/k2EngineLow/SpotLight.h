#pragma once
namespace nsK2EngineLow{
	class SpotLight
	{
	public:
		SpotLight();
		~SpotLight();
		/// <summary>
		/// スポットライトの初期設定
		/// </summary>
		/// <param name="pos">位置</param>
		/// <param name="color">色</param>
		/// <param name="range">影響距離</param>
		/// <param name="direction">向き</param>
		/// <param name="angle">影響範囲</param>
		void Init(const Vector3& pos, const Vector3& color, const float& range, const Vector3& direction, const float angle);

		/// <summary>
		/// ライトの位置を設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_spotLig->SetPosition(pos);
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
			m_spotLig->SetColor(color);
		}
		void SetColor(float x, float y, float z)
		{
			SetColor({ x,y,z });
		}

		/// <summary>
		/// 影響距離の設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range)
		{
			m_spotLig->SetRange(range);
		}

		/// <summary>
		/// ライトの向きを設定
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(const Vector3& direction)
		{
			m_spotLig->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			SetDirection({ x,y,z });
		}

		/// <summary>
		/// ライトの影響範囲
		/// </summary>
		/// <param name="angle"></param>
		void SetAngle(const float& angle)
		{
			m_spotLig->SetAngle(angle);
		}
		void Use()
		{
			m_spotLig->m_isUse = true;
		}

		/// <summary>
		/// 更新
		/// </summary>
		void Update()
		{
			m_spotLig->Update();
		}

	private:
		SSpotLight* m_spotLig = nullptr;	//ポイントライト
	};
}