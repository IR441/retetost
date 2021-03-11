//2021/3/1
//ishikawa reona
//class five
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberFive :
    public CGameInstanceObject
{
public:
	CNumberFive() {
		m_Model = CModelManager::GetFiveModel();

	}
public:
	void Init()override;
	void Update() override;
};

