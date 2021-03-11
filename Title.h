//2021/3/2
//ishikawa reona
//class title
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CTitle :
    public CGameInstanceObject
{
public:
	CTitle() {
		m_Model = CModelManager::GetTitleModel();

	}
public:
	void Init()override;
	void Update() override;
};

