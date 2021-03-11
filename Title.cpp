//2021/3/2
//ishikawa reona
//class title
#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include "Title.h"

#include "Manager.h"
#include"CScene.h"
//once_flag
#include <mutex>
#define TITLE_MODEL_VETRTEX (3966)
#define TITLE_MODEL_FACE (2608)
#define TITLE_MODEL_FILE ("model/title.ply")
//camera
#include "manipulator.h"
#include "UIManager.h"
//player
//#include "Player.h"

void CTitle::Init() {

	//継承したクラスごとに一度だけ読む
	static std::once_flag flag;
	std::call_once(flag, [this]() {
		m_Model->Init(TITLE_MODEL_FILE, TITLE_MODEL_VETRTEX, TITLE_MODEL_FACE);
		});

}
void CTitle::Update()
{
	CScene* scene = CManager::GetScene();
	//std::vector<CEnemy*>enemyList = scene->GetInstanceGameObjects<CEnemy>(Game);

	m_Model->Update();

	XMMATRIX* matrix = GetMatrix();
	SetDestroy(CUIManager::GetTitleFlag());
	if (GetDestroy()) {
		//Depends on camera position 
		

		//camera
		glm::vec3 eye;
		glm::vec3 center;
		glm::vec3 up;
		nv_helpers_dx12::CameraManip.getLookat(eye, center, up);
		glm::mat4 mat = nv_helpers_dx12::CameraManip.getMatrix();
		XMMATRIX xmat = { {mat[0][0],mat[0][1],mat[0][2],mat[0][3]},
			{mat[1][0],mat[1][1],mat[1][2],mat[1][3]},
			{mat[2][0],mat[2][1],mat[2][2],mat[2][3]},
			{mat[3][0],mat[3][1],mat[3][2],mat[3][3]} };
		xmat = XMMatrixInverse(nullptr, xmat);
		xmat.r[3].m128_f32[0] = 0.0f;
		xmat.r[3].m128_f32[1] = 0.0f;
		xmat.r[3].m128_f32[2] = 0.0f;

		glm::vec3 vec=eye- center;
		//score manager

		XMVECTOR scale = { m_Scale.x * UI_OOKISA, m_Scale.y * UI_OOKISA, m_Scale.z * UI_OOKISA };
		XMVECTOR position = { vec.x*0.5f, vec.y*0.5f , vec.z * 0.5f };
		*matrix = XMMatrixMultiply(
			XMMatrixMultiply(XMMatrixScalingFromVector(scale),
				/*XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z)),*/
				XMMatrixMultiply(XMMatrixRotationRollPitchYaw(UI_KAITEN_X, UI_KAITEN_Y, UI_KAITEN_Z), xmat)),
			XMMatrixTranslationFromVector(position));
	}
	else {
		//未表示
		*matrix = XMMatrixScaling(0, 0, 0);
	}
}