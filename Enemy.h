//ishikawa reona
//�G�l�~�[����
//2021/3/1
//comment �ǉ�
#pragma once
#include"GameInstanceObject.h"
//model
#include"ModelManager.h"
#define ENEMY_MAX (8)
class CEnemy :public CGameInstanceObject
{
public:
	CEnemy() {
		
		m_Model = CModelManager::GetEnemyModel();
		glm::vec3 color = { 1.0f, 0.0f, 0.0f };
		SetColor(color);
	}
	void Init()override;
	void Update()override;
};

