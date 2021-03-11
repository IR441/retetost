#pragma once
//2021/03/01
//ishikawa reona
#include"GameInstanceObject.h"
//class one
//model
#include"ModelManager.h"
class CNumberOne : public CGameInstanceObject
{
public:
	CNumberOne() {
		m_Model = CModelManager::GetOneModel();
		
	}
public:
	void Init()override;
	void Update() override;
};

