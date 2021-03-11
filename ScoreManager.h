//2021/02/28
//ishikawa reona
//score manager
#pragma once
#include"Manager.h"
#include"CScene.h"
#include"NumberOne.h"
#include"NumberTwo.h"
#include"NumberThree.h"
#include"NumberFour.h"
#include"NumberFive.h"
#include"NumberSix.h"
#include"NumberSeven.h"
#include"NumberEight.h"
#include"NumberNine.h"
#include"NumberZero.h"
//enemy max
#include"Enemy.h"
//ui parameter
#include "UIManager.h"
class CScoreManager
{
private:
	static int* ma_ScorePointer;
public:
	static void SetScorePointer(int* score) { ma_ScorePointer = score; }
	static int GetScore() { return *ma_ScorePointer; }
	static void SetPrassScore(int tokuten) {
		*ma_ScorePointer += tokuten;
		Draw();
	}
	static void ResetScore() { *ma_ScorePointer = 0; }
	static void Draw() {
		CScene* scene = CManager::GetScene();
		CNumberOne*   one   = scene->GetInstanceGameObject<CNumberOne>(UI);
		CNumberTwo*   two   = scene->GetInstanceGameObject<CNumberTwo>(UI);
		CNumberThree* three = scene->GetInstanceGameObject<CNumberThree>(UI);
		CNumberFour*  four  = scene->GetInstanceGameObject<CNumberFour>(UI);
		CNumberFive*  five  = scene->GetInstanceGameObject<CNumberFive>(UI);
		CNumberSix*   six   = scene->GetInstanceGameObject<CNumberSix>(UI);
		CNumberSeven* seven = scene->GetInstanceGameObject<CNumberSeven>(UI);
		CNumberEight* eight = scene->GetInstanceGameObject<CNumberEight>(UI);
		CNumberNine*  nine  = scene->GetInstanceGameObject<CNumberNine>(UI);
		CNumberZero*  zero  = scene->GetInstanceGameObject<CNumberZero>(UI);
		
		one  ->SetDestroy(false);
		two  ->SetDestroy(false);
		three->SetDestroy(false);
		four ->SetDestroy(false);
		five ->SetDestroy(false);
		six  ->SetDestroy(false);
		seven->SetDestroy(false);
		eight->SetDestroy(false);
		nine ->SetDestroy(false);
		zero ->SetDestroy(false);
		
	
		switch (*ma_ScorePointer) {
		case 0:
			zero->SetDestroy(true);
			break;
		case 1:
			one->SetDestroy(true);
			break;
		case 2:
			two->SetDestroy(true);
			break;
		case 3:
			three->SetDestroy(true);
			break;
		case 4:
			four->SetDestroy(true);
			break;
		case 5:
			five->SetDestroy(true);
			break;
		case 6:
			six->SetDestroy(true);
			break;
		case 7:
			seven->SetDestroy(true);
			break;
		case 8:
			eight->SetDestroy(true);
			break;
		case 9:
			nine->SetDestroy(true);
			break;
		default:
			break;
		}

		if (ENEMY_MAX == *ma_ScorePointer)
		{
			CUIManager::SetClearFlag(true);
		}
	}
};

