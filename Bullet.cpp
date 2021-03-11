//ishikawa reona
//bullet object
//2021/3/1
//comment　追加
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

	//継承したクラスごとに一度だけ読む
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

	
	//この後すぐにに消える
	//画面端
	if (((m_Position.x* m_Position.x)+(m_Position.z * m_Position.z)) > 400.0f) {
		
		SetDestroy(false);
	
	}

	//enemyとの衝突判定
	for (CEnemy* enemy : enemyList) {
		glm::vec3 enemyPosition = enemy->GetPosition();

		glm::vec3 ditection = m_Position - enemyPosition;
		float length = ditection.x * ditection.x+ ditection.y* ditection.y + ditection.z * ditection.z;
	
		if (length < 4.0f&& GetDestroy()&& enemy->GetDestroy()) {
			//消滅時
			//得点追加
			CScoreManager::SetPrassScore(1);
			//消滅処理
			enemy->SetDestroy(false);
			SetDestroy(false);
		}
	}


	XMMATRIX* matrix = GetMatrix();
	if (GetDestroy()) {
		//表示
	//表示
		if (!CUIManager::GetClearFlag() && !CUIManager::GetTitleFlag()) {
		//回転
		m_Rotation.y += 0.1f;
		//移動
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
		//未表示
		*matrix = XMMatrixScaling(0, 0, 0);
	}
}
