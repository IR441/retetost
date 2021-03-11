//2021/3/1
//ishikawa reona
//class two
#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include "NumberTwo.h"

#include "Manager.h"
#include"CScene.h"
//once_flag
#include <mutex>
#define TWO_MODEL_VETRTEX (358)
#define TWO_MODEL_FACE (163)
#define TWO_MODEL_FILE ("model/two.ply")
//camera
#include "manipulator.h"
//player
#include "Player.h"
void CNumberTwo::Init() {

	//�p�������N���X���ƂɈ�x�����ǂ�
	static std::once_flag flag;
	std::call_once(flag, [this]() {
		m_Model->Init(TWO_MODEL_FILE, TWO_MODEL_VETRTEX, TWO_MODEL_FACE);
		});

}
void CNumberTwo::Update()
{
	CScene* scene = CManager::GetScene();
	//std::vector<CEnemy*>enemyList = scene->GetInstanceGameObjects<CEnemy>(Game);

	m_Model->Update();




	XMMATRIX* matrix = GetMatrix();
	if (GetDestroy()) {
		//Depends on camera position 
		//player position
		CPlayer* player = scene->GetGameObject<CPlayer>(Game);
		glm::vec3 playerPosition = player->GetPosition();

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


		//score manager

		XMVECTOR scale = { m_Scale.x * UI_OOKISA, m_Scale.y * UI_OOKISA, m_Scale.z * UI_OOKISA };
		XMVECTOR position = { playerPosition.x + m_Position.x, playerPosition.y + m_Position.y,playerPosition.z + m_Position.z };
		*matrix = XMMatrixMultiply(
			XMMatrixMultiply(XMMatrixScalingFromVector(scale),
				/*XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z)),*/
				XMMatrixMultiply(XMMatrixRotationRollPitchYaw(UI_KAITEN_X, UI_KAITEN_Y, UI_KAITEN_Z), xmat)),
			XMMatrixTranslationFromVector(position));
	}
	else {
		//���\��
		*matrix = XMMatrixScaling(0, 0, 0);
	}
}