//ishikawa reona
//ƒvƒŒƒCƒ„[ˆ—
//2021/3/1
//–½–¼‹K‘¥‚ğ‚»‚ë‚¦‚½

#pragma once
#include"object.h"
class CPlayer:public Object
{ 


public:
	void Init()override;
	void Update()override;
	void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper)override;
};

