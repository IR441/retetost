//ishikawa reona
//エネミー処理
//2021/3/1
//comment 追加
#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include "Enemy.h"
//once_flag
#include <mutex>
//ui parameter
#include "UIManager.h"
void CEnemy::Init() {
	//継承したクラスごとに一度だけ読む
	static std::once_flag flag;
	std::call_once(flag, [this]() {
		m_Model->Init();
		});

}
void CEnemy::Update()
{
	
	
	//画面端
	if (((m_Position.x * m_Position.x) + (m_Position.z * m_Position.z)) > 900.0f) {

		SetDestroy(false);

	}

	XMMATRIX* matrix = GetMatrix();
	if (GetDestroy()) {
		//表示
		if (!CUIManager::GetClearFlag()&& !CUIManager::GetTitleFlag()) {
			//回転
			m_Rotation.y += 0.01f;

			//positon
			m_Position.x = m_Position.x * cosf(0.01f) - m_Position.z * sinf(0.01f);
			m_Position.z = m_Position.x * sinf(0.01f) + m_Position.z * cosf(0.01f);
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
