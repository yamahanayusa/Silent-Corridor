#pragma once
namespace nsK2EngineLow {
    class PointLight
    {
    public:
        PointLight();
        ~PointLight();

        /// <summary>
        /// ポイントライトの初期化
        /// </summary>
        void Init(const Vector3& pos, const Vector3& color, const float& range);

        /// <summary>
        /// ポイントライトの位置を設定
        /// </summary>
        /// <param name="pos"></param>
        void SetPosition(const Vector3& pos)
        {
            m_pointLig->SetPosition(pos);
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
            m_pointLig->SetColor(color);
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
            m_pointLig->SetRange(range);
        }

    private:

        SPointLight* m_pointLig = nullptr;    //ポイントライト
    };
}