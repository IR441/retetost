//ishikawa reona
//�v���C���[����
//2021/3/1
//�����K�������낦��

#pragma once
#include"object.h"
class CPlayer:public Object
{ 


public:
	void Init()override;
	void Update()override;
	void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper)override;
};

