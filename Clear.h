//2021/3/2
//ishikawa reona
//class clear
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CClear :
    public CGameInstanceObject
{
public:
	CClear() {
		m_Model = CModelManager::GetClearModel();

	}
public:
	void Init()override;
	void Update() override;
};

