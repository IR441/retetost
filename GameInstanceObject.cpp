//ishikawa reona
//モデルを一度だけ読むゲームオブジェクト
//2021/3/1
//magic number回避
#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include "GameInstanceObject.h"
#include"Input.h"
#include <mutex>

#define BULLET_MAX (16)

int  CGameInstanceObject::m_BulletMax= BULLET_MAX;

void CGameInstanceObject::Init() {
	//継承したクラスごとに一度だけ読む
	static std::once_flag flag;
	std::call_once(flag, [this]() {
		m_Model->Init();
		});
	
}


void CGameInstanceObject::Update()
{
	m_Model->Update();
	XMMATRIX* matrix = GetMatrix();

	
	
	if (GetDestroy()) {
		m_Rotation.y += 0.1f;
		XMVECTOR scale = { m_Scale.x, m_Scale.y, m_Scale.z };
		XMVECTOR position = { m_Position.x, m_Position.y, m_Position.z };
		*matrix = XMMatrixMultiply(
		XMMatrixMultiply(XMMatrixScalingFromVector(scale),
			XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z) ),
		XMMatrixTranslationFromVector(position));
	}
	else {

		*matrix =XMMatrixScaling(0,0,0);
	}
	
}


void CGameInstanceObject::Uninit(){
	static std::once_flag flag;
	std::call_once(flag, [this]() {
		m_Model->Uninit();
		});
}


void CGameInstanceObject::Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper){
	m_Model->Draw(sbtHelper);
}


void CGameInstanceObject::CreateBLAS(){
	//bulletのマトリクスを適用する
	m_Model->CreateBLAS();
}


void CGameInstanceObject::DrawCommand(ID3D12GraphicsCommandList4* commandList){
	m_Model->DrawCommand(commandList);
}


void CGameInstanceObject::PushBackInstsnce(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances) {
	m_Model->PushBackInstsnce(instances);

	m_BulletNumber=m_Model->GetInstanceNumber();
}

XMMATRIX* CGameInstanceObject::GetMatrix()
{
	std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances = CDeviceManager::Getinstance();
	return &instances->at(m_BulletNumber - 1).second;
}
