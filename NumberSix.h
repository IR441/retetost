//2021/3/1
//ishikawa reona
//class six
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberSix :
    public CGameInstanceObject
{
public:
	CNumberSix() {
		m_Model = CModelManager::GetSixModel();

	}
public:
	void Init()override;
	void Update() override;
};

