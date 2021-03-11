//ishikawa reona
//ゲームオブジェクト
//2021/03/01 コード微調整
#pragma once

#include "DXSample.h"

//using namespace DirectX;
//
//using Microsoft::WRL::ComPtr;
//#include<dxcapi.h>
//#include<vector>
//#include"nv_helpers_dx12/TopLevelASGenerator.h"
//#include "nv_helpers_dx12/ShaderBindingTableGenerator.h"

#include "glm/gtc/type_ptr.hpp"
#include "DeviceManager.h"
class Object{
protected:
	ComPtr< ID3D12Resource > m_MengerVB;
	ComPtr< ID3D12Resource > m_MengerIB;
	D3D12_VERTEX_BUFFER_VIEW m_MengerVBView;
	D3D12_INDEX_BUFFER_VIEW m_MengerIBView;

	UINT m_MengerIndexCount;
	UINT m_MengerVertexCount;

	AccelerationStructureBuffers m_Buffers;

	glm::vec3 m_Color = { 0.0f, 0.0f, 0.0f };
	bool m_Colorflag = false;
protected:
	//gamedata
	glm::vec3 m_Position;
	glm::vec3 m_prePosition;
	glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_StartPosition = {1.0f, 1.0f, 0.0f};
	glm::vec3 m_Front = glm::vec3{ .1f,0.0f,0.0f };
private:
	std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* m_Instances;
	int m_InstancesNumber;

	bool m_Destroy = true;
public:
	Object() : m_Position(m_StartPosition) {}
	Object(glm::vec3 position) : m_Position(position) , m_StartPosition(position){}
	//Get
	ID3D12Resource* GetVB() { return m_MengerVB.Get(); }
	ID3D12Resource* GetIB() {return m_MengerIB.Get();}
	D3D12_GPU_VIRTUAL_ADDRESS GetVBAdd() { return m_MengerVB->GetGPUVirtualAddress(); }
	D3D12_GPU_VIRTUAL_ADDRESS GetIBAdd() { return m_MengerIB->GetGPUVirtualAddress(); }
	UINT GetVC() { return m_MengerVertexCount; }
	UINT GetIC() {return  m_MengerIndexCount;}
	AccelerationStructureBuffers* GetBuffers() {return &m_Buffers;}
	int GetInstanceNumber() { return m_InstancesNumber; }
	//gameget
	//Get
	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 GetRotation() { return m_Rotation; }
	glm::vec3 GetScale() { return m_Scale; }
	//glm::vec3 GetFront() { return m_Front; }
	float GetDistance(glm::vec3 position) {
		glm::vec3 l_Position = position - m_Position;
		float distance = std::sqrt(l_Position.x * l_Position.x + l_Position.y * l_Position.y + l_Position.z * l_Position.z);
		return distance;
	}

	//Set
	void SetPosition(glm::vec3 position) { m_Position = position; }
	void SetStartPosition(glm::vec3 position) { m_StartPosition = position; m_Position = position; }
	void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
	void SetScale(glm::vec3 scale) { m_Scale = scale; }
	//void SetFront(glm::vec3 m_Front) { m_Front= Front; }
	void SetDestroy(bool destroy) { m_Destroy = destroy; }
	bool GetDestroy(){return m_Destroy; }
	bool Destroy() {
		if (m_Destroy) {

			m_Scale = { 0.0f, 0.0f, 0.0f };

			//Uninit();
			//delete this;
			return true;
		}
		else {
			return false;
		}
	}
	void SetColor(glm::vec3 color) {
		m_Color = color;
		m_Colorflag = true;
	}
	 

	virtual void Init();
	virtual void Init(const char* file_name, int vertnum, int facenum);
	virtual void Update();
	void Uninit();
	virtual void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* m_sbtHelper);
	void CreateBLAS();
	void DrawCommand(ID3D12GraphicsCommandList4* m_commandList);

	

	std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX> GetInstance(void) {
		return { m_Buffers.pResult,XMMatrixTranslation(m_StartPosition.x,m_StartPosition.y,m_StartPosition.z) };
	}

	void PushBackInstsnce() {
		std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances=CDeviceManager::Getinstance();
		instances->push_back(GetInstance());
		m_InstancesNumber=instances->size();
		m_Instances = instances;
	}
	void PushBackInstsnce(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances) {
		instances->push_back(GetInstance());
		m_InstancesNumber=instances->size();
		if(!m_Instances){m_Instances = instances;}
	}
	 
	XMMATRIX* GetMatrix() {
		return &m_Instances->at(m_InstancesNumber - 1).second;
			
	//return &(m_instances[m_instancesNumber - 1].data()->second);
	}
};