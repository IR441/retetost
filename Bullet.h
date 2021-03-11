//ishikawa reona
//bullet object
//2021/3/1
//commentÅ@í«â¡
#pragma once
#include"GameInstanceObject.h"
//model
#include"ModelManager.h"
class CBullet: public CGameInstanceObject
{
public:
	CBullet() {
		m_Model = CModelManager::GetBulletModel();
		SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}
public:
	void Init()override;
	void Update() override;
};

