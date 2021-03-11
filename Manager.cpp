//ishikawa reona
//�Q�[���}�l�[�W���[�@�ߋ��̃Q�[������ڐA
//2021/03/01
//�g���Ȃ�����
#include "stdafx.h"
#include "D3D12HelloTriangle.h"

#include"CScene.h"
#include "Manager.h"
#include"Input.h"
#include"Game.h"

CScene* CManager::m_Scene = NULL;

void CManager::Init() {
	
	CInput::Init();

	SetScene<CGame>();
}

void CManager::Uninit() {

	m_Scene->Uninit();
	delete m_Scene;

	CInput::Uninit();

}

void CManager::Update() {

	CInput::Update();

	m_Scene->Update();
	
}

void CManager::Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper) {

	m_Scene->Draw(sbtHelper);
	
}
void CManager::PushBackInstsnce(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances) {

	m_Scene->PushBackInstsnce(instances);

}
void CManager::CreateBLAS(){
	m_Scene->CreateBLAS();
}

void CManager::DrawCommand(ID3D12GraphicsCommandList4* commandList){
	m_Scene->DrawCommand(commandList);
}