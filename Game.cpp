//ishikawa reona
//game画面マネージャー
//2021/3/1
//number追加
#include "stdafx.h"
#include "CScene.h"
#include "Game.h"
#include "Player.h"
#include"Enemy.h"
#include"GameInstanceObject.h"
#include"Bullet.h"
#include"ScoreManager.h"

//pai
#define _USE_MATH_DEFINES
#include<math.h>
#include"ModelManager.h"


//number object
#define NUMBER_KETA (1)
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
#include "Title.h"
#include "Clear.h"

//ui管理
#include"UIManager.h"

void CGame::Init() { 
	//geme object model
	CModelManager::SetBulletModel(&m_Bullet);
	CModelManager::SetEnemyModel(&m_Enemy);
	//number model init
	CModelManager::SetOneModel(&m_One);
	CModelManager::SetTwoModel(&m_Two);
	CModelManager::SetThreeModel(&m_Three);
	CModelManager::SetFourModel(&m_Four);
	CModelManager::SetFiveModel(&m_Five);
	CModelManager::SetSixModel(&m_Six);
	CModelManager::SetSevenModel(&m_Seven);
	CModelManager::SetEightModel(&m_Eight);
	CModelManager::SetNineModel(&m_Nine);
	CModelManager::SetZeroModel(&m_Zero);
	//game ui
	CModelManager::SetTitleModel(&m_Title);
	CModelManager::SetClearModel(&m_Clear);
	//ui パラメータ
	CUIManager::SetTitleFlagPointer(&m_TitleFlag);
	CUIManager::SetClearFlagPointer(&m_ClearFlag);

	CScoreManager::SetScorePointer(&m_Score);
	//使用可能なすべてのオブジェクトを入れる
	AddGameObject<CPlayer>(Layer::Game)->SetRotation(glm::vec3(1.5f, 0.0f ,0.0f));
	
	//enemy
	for (int i = 0; i < ENEMY_MAX; i++) {
		CEnemy* enemy = AddInstanceGameObject<CEnemy>(Layer::Game);
		enemy->SetStartPosition(glm::vec3(8.5*cosf(2*M_PI/ ENEMY_MAX *i), 0.0, 8.5*sinf(2*M_PI / ENEMY_MAX *i)));
		enemy->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
		enemy->SetDestroy(true);
		
	}
	//bullet
	for (int i = 0; i < CBullet::GetBulletMax(); i++) {
		CBullet* bullet=AddInstanceGameObject<CBullet>(Layer::Game);
	}
	
	//number
	for (int i = 0; i < NUMBER_KETA; i++) {
		//one
		CNumberOne* one=AddInstanceGameObject<CNumberOne>(Layer::UI);
		one->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f*i));
		//one->SetDestroy(true);
		//two
		AddInstanceGameObject<CNumberTwo>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//three
		AddInstanceGameObject<CNumberThree>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//four
		AddInstanceGameObject<CNumberFour>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//five
		AddInstanceGameObject<CNumberFive>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//six
		AddInstanceGameObject<CNumberSix>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//seven
		AddInstanceGameObject<CNumberSeven>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//eight
		AddInstanceGameObject<CNumberEight>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//nine
		AddInstanceGameObject<CNumberNine>(Layer::UI)->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		//zero
		CNumberZero* zero = AddInstanceGameObject<CNumberZero>(Layer::UI);
		zero ->SetPosition(glm::vec3(0.0f, 1.0f, 0.1f * i));
		zero->SetDestroy(true);
	}
	
	//game ui
	//title
	CTitle* title = AddInstanceGameObject<CTitle>(Layer::UI);
	title->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_TitleFlag = true;
	//clear
	//title
	CClear* clear = AddInstanceGameObject<CClear>(Layer::UI);
	clear->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	m_ClearFlag = false;


}



void CGame::Reset()
{
	CScoreManager::ResetScore();//scoreを０に

	//enemyを初期値へ
	std::vector<CEnemy*>enemyList = GetInstanceGameObjects<CEnemy>(Game);
	int i=0;
	for (CEnemy* enemy : enemyList) {
		enemy->SetStartPosition(glm::vec3(8.5 * cosf(2 * M_PI / ENEMY_MAX * i), 0.0, 8.5 * sinf(2 * M_PI / ENEMY_MAX * i)));
		enemy->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
		enemy->SetDestroy(true);
		i++;
	}
	//title&clear flag
	CUIManager::SetTitleFlag(true);
	CUIManager::SetClearFlag(false);
	//flagをfalseへ
	SetReset(false);
}

