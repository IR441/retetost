//2021/3/1
//ishikawa reona
//class zero
#pragma once
#include "GameInstanceObject.h"
//model
#include"ModelManager.h"
class CNumberZero :
    public CGameInstanceObject
{
public:
	CNumberZero() {
		m_Model = CModelManager::GetZeroModel();

	}
public:
	void Init()override;
	void Update() override;
};

