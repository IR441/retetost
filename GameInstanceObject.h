//ishikawa reona
//モデルを一度だけ読むゲームオブジェクト

#pragma once
#include"object.h"
#define BULLET_COUNT (16)

class CGameInstanceObject
{
protected:
	//gamedata
	glm::vec3 m_Position;
	glm::vec3 m_prePosition;
	glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_StartPosition = {1.0f, 1.0f, 0};
	glm::vec3 m_Front;

	bool m_Destroy = false;
	class Object* m_Model;
private:
	static int m_BulletMax;
	int m_BulletNumber;
public:
	CGameInstanceObject() : m_Position(m_StartPosition) {}
	CGameInstanceObject(glm::vec3 position) : m_Position(position) , m_StartPosition(position){}
	
	void BulletNumber(int i) { m_BulletNumber = i; }
	int GetBulletNumber() { return m_BulletNumber; }
	static int GetBulletMax() { return m_BulletMax;}
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
	void SetStartPosition(glm::vec3 start_position) { m_StartPosition = start_position; m_Position = start_position; }
	void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
	void SetScale(glm::vec3 scale) { m_Scale = scale; }
	void SetFront(glm::vec3 front) { m_Front= front; }


	void SetDestroy(bool destroy) { m_Destroy = destroy; }
	bool GetDestroy(){return m_Destroy; }
	bool Destroy() {
		if (m_Destroy) {

			m_Scale = { 0.0f, 0.0f, 0.0f };

			return true;
		}
		else {
			return false;
		}
	}
	void SetColor(glm::vec3 color) {
		m_Model->SetColor(color);
	}
	

	virtual void Init();
	virtual void Update();
	void Uninit();
	void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* m_sbtHelper);
	void CreateBLAS();
	void DrawCommand(ID3D12GraphicsCommandList4* m_commandList);
	void PushBackInstsnce(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances);
	XMMATRIX* GetMatrix();
};


