#pragma once
//2021/03/01
//ishikawa reona
//class two
#include "GameInstanceObject.h"

//model
#include"ModelManager.h"
class CNumberTwo :
    public CGameInstanceObject
{
public:
	CNumberTwo() {
		m_Model = CModelManager::GetTwoModel();

	}
public:
	void Init()override;
	void Update() override;
};

