//2021/3/1
//ishikawa reona
//class seven
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberSeven :
    public CGameInstanceObject
{
public:
	CNumberSeven() {
		m_Model = CModelManager::GetSevenModel();

	}
public:
	void Init()override;
	void Update() override;
};

