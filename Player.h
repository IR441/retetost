//ishikawa reona
//プレイヤー処理
//2021/3/1
//命名規則をそろえた

#pragma once
#include"object.h"
class CPlayer:public Object
{ 


public:
	void Init()override;
	void Update()override;
	void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper)override;
};

