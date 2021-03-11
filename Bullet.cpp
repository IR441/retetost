//ishikawa reona
//bullet object
//2021/3/1
//comment�@�ǉ�
#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include "Bullet.h"
#include "Manager.h"
#include"CScene.h"
#include"Enemy.h"
//once_flag
#include <mutex>
//score
#include"ScoreManager.h"
//ui parameter
#include "UIManager.h"
void CBullet::Init() {

	//�p�������N���X���ƂɈ�x�����ǂ�
	static std::once_flag flag;
	std::call_once(flag, [this]() {
		m_Model->Init();
		});

}

void CBullet::Update()
{
	CScene* scene = CManager::GetScene();
	std::vector<CEnemy*>enemyList = scene->GetInstanceGameObjects<CEnemy>(Game);

	m_Model->Update();

	
	//���̌シ���ɂɏ�����
	//��ʒ[
	if (((m_Position.x* m_Position.x)+(m_Position.z * m_Position.z)) > 400.0f) {
		
		SetDestroy(false);
	
	}

	//enemy�Ƃ̏Փ˔���
	for (CEnemy* enemy : enemyList) {
		glm::vec3 enemyPosition = enemy->GetPosition();

		glm::vec3 ditection = m_Position - enemyPosition;
		float length = ditection.x * ditection.x+ ditection.y* ditection.y + ditection.z * ditection.z;
	
		if (length < 4.0f&& GetDestroy()&& enemy->GetDestroy()) {
			//���Ŏ�
			//���_�ǉ�
			CScoreManager::SetPrassScore(1);
			//���ŏ���
			enemy->SetDestroy(false);
			SetDestroy(false);
		}
	}


	XMMATRIX* matrix = GetMatrix();
	if (GetDestroy()) {
		//�\��
	//�\��
		if (!CUIManager::GetClearFlag() && !CUIManager::GetTitleFlag()) {
		//��]
		m_Rotation.y += 0.1f;
		//�ړ�
		m_Position += 3.0f*m_Front;
		}

		XMVECTOR scale = { m_Scale.x, m_Scale.y, m_Scale.z };
		XMVECTOR position = { m_Position.x, m_Position.y, m_Position.z };
		*matrix = XMMatrixMultiply(
			XMMatrixMultiply(XMMatrixScalingFromVector(scale),
				XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z)),
			XMMatrixTranslationFromVector(position));
	}
	else {
		//���\��
		*matrix = XMMatrixScaling(0, 0, 0);
	}
}
