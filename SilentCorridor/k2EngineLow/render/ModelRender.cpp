#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		InitSkeleton(filePath);
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		InitModel(filePath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());

	}

	void ModelRender::InitAnimation(AnimationClip*animationClips,int numAnimationClips,EnModelUpAxis enModelAxis)
	{ 
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}

	void ModelRender::InitModel(const char* filePath, EnModelUpAxis enModelUpAxis)
	{
		ModelInitData initData;
		//tkm�t�@�C���̃t�@�C���p�X���w�肷��B
		initData.m_tkmFilePath = filePath;
		//�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
		initData.m_fxFilePath = "Assets/shader/model.fx";
		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		initData.m_vsEntryPointFunc = "VSMain";
		//���[�U�[�g���̒萔�o�b�t�@�[�ɃV�|�����C�g��o�^
		initData.m_expandConstantBuffer = g_sceneLight->GetSDirectionLight();
		initData.m_expandConstantBufferSize = sizeof(SDirectionLight);

		if (m_animationClips != nullptr) {
			//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			//�X�P���g�����w�肷��B
			initData.m_skeleton = &m_skeleton;
		}

		//���f���̏�������w�肷��B
		initData.m_modelUpAxis = enModelUpAxis;

		//�쐬�����������f�[�^�����ƂɃ��f��������������B
		m_model.Init(initData);
	}

	void ModelRender::Update()
	{
		//�X�P���g�����X�V�B
		m_skeleton.Update(m_model.GetWorldMatrix());

		//���f���̍X�V�B
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//�A�j���[�V������i�߂�B
		m_animation.Progress(g_gameTime->GetFrameDeltaTime());
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);
	}
}