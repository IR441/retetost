//2021/3/1
//ishikawa reona
//class four
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberFour :
    public CGameInstanceObject
{
public:
	CNumberFour() {
		m_Model = CModelManager::GetFourModel();

	}
public:
	void Init()override;
	void Update() override;
};

