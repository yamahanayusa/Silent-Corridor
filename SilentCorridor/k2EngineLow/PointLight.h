#pragma once
namespace nsK2EngineLow {
    class PointLight
    {
    public:
        PointLight();
        ~PointLight();

        /// <summary>
        /// �|�C���g���C�g�̏�����
        /// </summary>
        void Init(const Vector3& pos, const Vector3& color, const float& range);

        /// <summary>
        /// �|�C���g���C�g�̈ʒu��ݒ�
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
        /// �F�̐ݒ�
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
        /// �e���͈͂̐ݒ�
        /// </summary>
        /// <param name="range"></param>
        void SetRange(const float& range)
        {
            m_pointLig->SetRange(range);
        }

    private:

        SPointLight* m_pointLig = nullptr;    //�|�C���g���C�g
    };
}