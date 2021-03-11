//2021/3/1
//ishikawa reona
//class nine
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberNine :
    public CGameInstanceObject
{
public:
	CNumberNine() {
		m_Model = CModelManager::GetNineModel();

	}
public:
	void Init()override;
	void Update() override;
};

