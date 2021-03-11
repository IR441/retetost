//ishikawa reona
//game総合管理
//gameオブジェクト管理
//2021/01/15 scene

#pragma once
#include<list>
#include "D3D12HelloTriangle.h"
#include"object.h"
#include"GameInstanceObject.h"
//#include"Bullet.h"
//#include"Enemy.h"
enum Layer {
	Base,
	BackGround,
	Game,
	UI,
	NumberOfLayers
};
class CScene
{
protected:
	std::list<Object*> m_GameObject[NumberOfLayers];
	std::list<CGameInstanceObject*> m_GemeInstanceObject[NumberOfLayers];

	

	bool m_Pose;


	bool m_Reset = false;
public:
	
	virtual ~CScene() {}

	virtual void Init() = 0;
	virtual void Uninit(){
		for (int i = 0; i < NumberOfLayers; i++) {
			for (Object* object : m_GameObject[i]) {
				object->Uninit();
			}
			for (CGameInstanceObject* object : m_GemeInstanceObject[i]) {
				object->Uninit();
			}
			/*for (CEnemy* object : m_GemeEnemyObject[i]) {
				object->Uninit();
			}
			for (CBullet* object : m_GemeBulletObject[i]) {
				object->Uninit();
			}*/
			m_GameObject[i].clear();
			m_GemeInstanceObject[i].clear();
		}
	}
	virtual void Reset(){}
	virtual void Update() {
		if (m_Reset) {
			Reset();
		}
		for (int i = NumberOfLayers - 1; i >= 0; i--) {
			for (Object* object : m_GameObject[i]) {
				object->Update();
			}
			for (CGameInstanceObject* object : m_GemeInstanceObject[i]) {
				object->Update();
			}
		}
	}
	virtual void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper) {
		for (int i = 0; i < NumberOfLayers; i++) {
			for (Object* object : m_GameObject[i]) {
				object->Draw(sbtHelper);
			}
			for (CGameInstanceObject* object : m_GemeInstanceObject[i]) {
				object->Draw(sbtHelper);
				/*for (CEnemy* object : m_GemeEnemyObject[i]) {
					object->Draw(m_sbtHelper);
				}
				for (CBullet* object : m_GemeBulletObject[i]) {
					object->Draw(m_sbtHelper);
				}*/
			}
		}
	}
	virtual void PushBackInstsnce(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances) {
		for (int i = 0; i < NumberOfLayers; i++) {
			for (Object* object : m_GameObject[i]) {
				object->PushBackInstsnce(instances);
			}
			for (CGameInstanceObject* object : m_GemeInstanceObject[i]) {
				object->PushBackInstsnce(instances);
			}
			/*for (CEnemy* object : m_GemeEnemyObject[i]) {
				object->PushBackInstsnce(instances);
			}
			for (CBullet* object : m_GemeBulletObject[i]) {
				object->PushBackInstsnce(instances);
			}*/
		}
	}
	virtual void CreateBLAS() {
		for (int i = 0; i < NumberOfLayers; i++) {
			for (Object* object : m_GameObject[i]) {
				object->CreateBLAS();
			}
			for (CGameInstanceObject* object : m_GemeInstanceObject[i]) {
				object->CreateBLAS();
			}
			/*for (CEnemy* object : m_GemeEnemyObject[i]) {
				object->CreateBLAS();
			}
			for (CBullet* object : m_GemeBulletObject[i]) {
				object->CreateBLAS();
			}*/
		}
	}
	virtual void DrawCommand(ID3D12GraphicsCommandList4* commandList) {
		for (int i = 0; i < NumberOfLayers; i++) {
			for (Object* object : m_GameObject[i]) {
				object->DrawCommand(commandList);
			}
			for (CGameInstanceObject* object : m_GemeInstanceObject[i]) {
				object->DrawCommand(commandList);
			}
			/*for (CEnemy* object : m_GemeEnemyObject[i]) {
				object->DrawCommand(m_commandList);
			}
			for (CBullet* object : m_GemeBulletObject[i]) {
				object->DrawCommand(m_commandList);
			}*/
		}
	}
	bool GetReset(){ return m_Reset; }
	void SetReset(bool reset_bool) { m_Reset = reset_bool; }
	

	//Init
	template<typename T>
	T* AddGameObject(Layer layer) {
		T* gameObject = new T();
		m_GameObject[layer].push_back(gameObject);
		gameObject->Init();
		//gameObject->PushBackInstsnce();
		return gameObject;
	}

	template<typename T>
	T* GetGameObject(Layer layer) {
		for (Object* object : m_GameObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				return (T*)object;
			}
		}
		return NULL;
	}

	template<typename T>
	std::vector<T*> GetGameObjects(Layer layer) {
		std::vector<T*> objects;
		for (Object* object : m_GameObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	//Init
	template<typename T>
	T* AddInstanceGameObject(Layer layer) {
		T* gameObject = new T();
		m_GemeInstanceObject[layer].push_back(gameObject);
		gameObject->Init();
		return gameObject;
	}

	template<typename T>
	T* GetInstanceGameObject(Layer layer) {
		for (CGameInstanceObject* object : m_GemeInstanceObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				return (T*)object;
			}
		}
		return NULL;
	}

	template<typename T>
	std::vector<T*> GetInstanceGameObjects(Layer layer) {
		std::vector<T*> objects;
		for (CGameInstanceObject* object : m_GemeInstanceObject[layer]) {
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	////GemeEnemyObject
	//template<typename T>
	//T* AddEnemyGameObject(Layer layer) {
	//	T* gameObject = new T();
	//	m_GemeEnemyObject[layer].push_back(gameObject);
	//	gameObject->Init();
	//	return gameObject;
	//}
	//
	//template<typename T>
	//T* GetEnemyGameObject(Layer layer) {
	//	for (CEnemy* object : m_GemeEnemyObject[layer]) {
	//		if (typeid(*object) == typeid(T)) {
	//			return (T*)object;
	//		}
	//	}
	//	return NULL;
	//}
	//
	//template<typename T>
	//std::vector<T*> GetEnemyGameObjects(Layer layer) {
	//	std::vector<T*> objects;
	//	for (CEnemy* object : m_GemeEnemyObject[layer]) {
	//		if (typeid(*object) == typeid(T)) {
	//			objects.push_back((T*)object);
	//		}
	//	}
	//	return objects;
	//}
	//
	////GemeBulletObject
	//template<typename T>
	//T* AddBulletGameObject(Layer layer) {
	//	T* gameObject = new T();
	//	m_GemeBulletObject[layer].push_back(gameObject);
	//	gameObject->Init();
	//	//gameObject->PushBackInstsnce();
	//	return gameObject;
	//}
	//
	//template<typename T>
	//T* GetBulletGameObject(Layer layer) {
	//	for (CBullet* object : m_GemeBulletObject[layer]) {
	//		if (typeid(*object) == typeid(T)) {
	//			return (T*)object;
	//		}
	//	}
	//	return NULL;
	//}
	//
	//template<typename T>
	//std::vector<T*> GetBulletGameObjects(Layer layer) {
	//	std::vector<T*> objects;
	//	for (CBullet* object : m_GemeBulletObject[layer]) {
	//		if (typeid(*object) == typeid(T)) {
	//			objects.push_back((T*)object);
	//		}
	//	}
	//	return objects;
	//}
};

