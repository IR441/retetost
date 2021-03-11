//2021/3/1
//ishikawa reona
//class eight
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberEight :
    public CGameInstanceObject
{
public:
	CNumberEight() {
		m_Model = CModelManager::GetEightModel();

	}
public:
	void Init()override;
	void Update() override;
};

