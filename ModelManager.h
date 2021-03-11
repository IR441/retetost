//ishikawa reona
//数字オブジェクト　マネージャー
//2021/03/01

#pragma once
#include "D3D12HelloTriangle.h"
#include"object.h"
class CModelManager
{
private:
	//gameobject
	static Object* ma_BulletModelPointer;
	static Object* ma_EnemyModelPointer;
	//number
	static Object* ma_OneModelPointer;
	static Object* ma_TwoModelPointer;
	static Object* ma_ThreeModelPointer;
	static Object* ma_FourModelPointer;
	static Object* ma_FiveModelPointer;
	static Object* ma_SixModelPointer;
	static Object* ma_SevenModelPointer;
	static Object* ma_EightModelPointer;
	static Object* ma_NineModelPointer;
	static Object* ma_ZeroModelPointer;
	//ui
	static Object* ma_TitleModelPointer;
	static Object* ma_ClearModelPointer;
public:
	//Set
	static void SetBulletModel(Object* model) { ma_BulletModelPointer = model; }
	static void SetEnemyModel(Object* model) { ma_EnemyModelPointer = model; }

	static void SetOneModel(Object* model) { ma_OneModelPointer = model; }
	static void SetTwoModel(Object* model) { ma_TwoModelPointer = model; }
	static void SetThreeModel(Object* model) { ma_ThreeModelPointer = model; }
	static void SetFourModel(Object* model) { ma_FourModelPointer = model; }
	static void SetFiveModel(Object* model) { ma_FiveModelPointer = model; }
	static void SetSixModel(Object* model) { ma_SixModelPointer = model; }
	static void SetSevenModel(Object* model) { ma_SevenModelPointer = model; }
	static void SetEightModel(Object* model) { ma_EightModelPointer = model; }
	static void SetNineModel(Object* model) { ma_NineModelPointer = model; }
	static void SetZeroModel(Object* model) { ma_ZeroModelPointer = model; }

	static void SetTitleModel(Object* model) { ma_TitleModelPointer = model; }
	static void SetClearModel(Object* model) { ma_ClearModelPointer = model; }
	//Get
	static Object* GetBulletModel() { return ma_BulletModelPointer; }
	static Object* GetEnemyModel() { return  ma_EnemyModelPointer; }

	static Object* GetOneModel() { return  ma_OneModelPointer; }
	static Object* GetTwoModel() { return  ma_TwoModelPointer; }
	static Object* GetThreeModel() { return  ma_ThreeModelPointer; }
	static Object* GetFourModel() { return  ma_FourModelPointer; }
	static Object* GetFiveModel() { return  ma_FiveModelPointer; }
	static Object* GetSixModel() { return  ma_SixModelPointer; }
	static Object* GetSevenModel() { return  ma_SevenModelPointer; }
	static Object* GetEightModel() { return  ma_EightModelPointer; }
	static Object* GetNineModel() { return  ma_NineModelPointer; }
	static Object* GetZeroModel() { return  ma_ZeroModelPointer; }

	static Object* GetTitleModel() { return  ma_TitleModelPointer; }
	static Object* GetClearModel() { return  ma_ClearModelPointer; }

};

