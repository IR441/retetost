//2021/3/1
//ishikawa reona
//class three
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberThree :
    public CGameInstanceObject
{
public:
	CNumberThree() {
		m_Model = CModelManager::GetThreeModel();

	}
public:
	void Init()override;
	void Update() override;
};

