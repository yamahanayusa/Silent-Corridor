#pragma once

namespace nsK2EngineLow {
	/// <summary>
	/// �X�L�����f�������_�[�B
	/// </summary>
	class ModelRender
	{
	public:
		ModelRender() {}
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="">���f���̏�����B</param>
		void Init(const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update();

		/// <summary>
		/// �`�揈���B
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g�B</param>
		void Draw(RenderContext& rc);

		/// <summary>
		/// �A�j���[�V�����Đ��B
		/// </summary>
		/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ��B</param>
		/// <param name="interpolateTime">�⊮����(�P�ʁF�b�B)</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f) 
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/// <summary>
		/// �A�j���[�V�����̍Đ����H
		/// </summary>
		bool IsPlayingAnimation()const
		{
			return m_animation.IsPlaying();
		}

		/// <summary>
		/// ���f�����擾�B
		/// </summary>
		/// <returns>���f��</returns>
		Model& GetModel()
		{
			return m_model;
		}
		
		/// <summary>
		/// ���W�A��]�A�g���S�čX�V�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		/// <param name="rotation">��]�B</param>
		/// <param name="scale">�g��B</param>
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="pos">���W�B</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rotation">��]�B</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// �傫���B
		/// </summary>
		/// <param name="scale">�傫���B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
	private:
		/// <summary>
		/// ���f���̏������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		void InitModel(const char* failePath, EnModelUpAxis enModelUpAxis);
		/// <summary>
		/// �X�P���g���̏������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		void InitSkeleton(const char* filePath);
		/// <summary>
		/// �A�j���[�V�����̏������B
		/// </summary>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

	private:
		AnimationClip* m_animationClips = nullptr;//�A�j���[�V�����N���b�v�B
		Animation m_animation;//�A�j���[�V�����B
		Model m_model;//�X�L�����f���B
		Skeleton m_skeleton;//���B

		Vector3 m_position = Vector3::Zero;//���W�B
		Vector3 m_scale = Vector3::One;//�g�嗦�B
		Quaternion m_rotation = Quaternion::Identity;//��]�B
		EnModelUpAxis m_enFbxUpAxis = enModelUpAxisZ;//FBX�̏�����B

		int m_numAnimationClips = 0;//�A�j���[�V�����N���b�v�̐��B
        bool m_isUpdateAnimation = true; //�A�j���[�V�������X�V����H
	};
}

