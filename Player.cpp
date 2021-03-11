//ishikawa reona
//player
//2021/3/1
//命名規則をそろえた
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include"Manager.h"
#include"CScene.h"
#include "Player.h"
#include "Bullet.h"

#include"Input.h"
#include"DeviceManager.h"

#include <fstream>
#include <iostream>
#include <string>
//ui parameter
#include "UIManager.h"

#define MODEL_VERTEX_SIZE (36)
void CPlayer::Init()
{


	ID3D12Device5* m_device = CDeviceManager::GetDevice();


#if 0

	char signature[3] = {};

	//file pointer fclose v
	FILE* fp = fopen("model/Alicia/MMD/color_Alica.pmd", "rb");



	struct MMDtag {
		float version;
		char model_name[20];
		char comment[256];
	} pmdheader;

	fread(signature, sizeof(signature), 1, fp);
	fread(&pmdheader, sizeof(pmdheader), 1, fp);

	struct PMDVertex
	{
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 uv;
		unsigned short boneNo[2];
		unsigned char boneWeight;
		unsigned char edgeFig;
	};

	//vertex
	unsigned int vertNum;
	fread(&vertNum, sizeof(vertNum), 1, fp);
	std::vector<unsigned char>model_data(vertNum * pmdvertex_size);//buffer
	fread(model_data.data(), model_data.size(), 1, fp);

	//index
	// インデックスバッファの生成.
	unsigned int indicesNum;//index number
	fread(&indicesNum, sizeof(indicesNum), 1, fp);
	std::vector<unsigned short> g_indices;
	g_indices.resize(indicesNum);
	fread(g_indices.data(), g_indices.size() * sizeof(g_indices[0]), 1, fp);

#pragma pack(1)
	//material
	struct PMDMaterial {
		XMFLOAT3 difuuse;
		float alpha;
		float specularity;
		XMFLOAT3 specular;
		XMFLOAT3 ambient;
		unsigned char toonIdx;
		unsigned char edgeFig;

		unsigned int indicesNum;

		char texFilePath[20];
	};//70byte
#pragma pack()

	unsigned int materialNum;
	fread(&materialNum, sizeof(materialNum), 1, fp);

	std::vector<PMDMaterial>pmdMaterials(materialNum);

	fread(pmdMaterials.data(), pmdMaterials.size() * sizeof(PMDMaterial), 1, fp);

	fclose(fp);

	//texture
	//std::vector<byte> img;
	//std::fstream fs();

	// 頂点バッファの生成.
	std::vector< Vertex > vertices;
	{
		unsigned char* p = model_data.data();

		for (int i = 0; i < model_data.size() / 38; i++) {
			PMDVertex g_vert;
			memcpy(&g_vert.pos.x, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.pos.y, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.pos.z, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.normal.x, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.normal.y, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.normal.z, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.uv.x, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.uv.x, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.boneNo[0], p, sizeof(unsigned char) * 2); ++p; ++p;
			memcpy(&g_vert.boneNo[1], p, sizeof(unsigned char) * 2); ++p; ++p;
			memcpy(&g_vert.boneWeight, p, sizeof(unsigned char)); ++p;
			memcpy(&g_vert.edgeFig, p, sizeof(unsigned char)); ++p;


			Vertex vec = { {g_vert.pos.x,g_vert.pos.y,g_vert.pos.z,0.0f }, {g_vert.normal.x,g_vert.normal.y,g_vert.normal.z}, { 1.f, 1.f, 1.f, 1.f },{g_vert.uv.x,g_vert.uv.y} };

			vertices.push_back(vec);
		}

	}

	// indexバッファの生成.
	std::vector< UINT > indices;
	{

		for (int i = 0; i < g_indices.size(); i++) {

			UINT ind = { (UINT)g_indices[i] };
			indices.push_back(ind);
		}

	}
	std::vector<unsigned short>().swap(g_indices);

	//material format Adjustment
	struct MaterialForHLSL {
		XMFLOAT3 diffuse;
		float alpha;
		XMFLOAT3 specular;
		float specularity;
		XMFLOAT3 ambient;
	};

	struct AdditionalMaterials {
		std::string texPath;
		int toonIdx;
		bool edgeFig;
	};

	struct Material {
		/*unsigned int indicesNum;
		MaterialForHLSL material;
		AdditionalMaterials additional;*/
		XMFLOAT3 diffuse;
		XMFLOAT3 specular;
		XMFLOAT3 ambient;
	};

	std::vector<Material> materals(pmdMaterials.size());

	for (int i = 0; i < pmdMaterials.size(); ++i) {
		/*materals[i].indicesNum = pmdMaterials[i].indicesNum;
		materals[i].material.diffuse = pmdMaterials[i].difuuse;
		materals[i].material.alpha = pmdMaterials[i].alpha;
		materals[i].material.specular = pmdMaterials[i].specular;
		materals[i].material.specularity = pmdMaterials[i].specularity;
		materals[i].material.ambient = pmdMaterials[i].ambient;*/
		materals[i].diffuse = pmdMaterials[i].difuuse;
		materals[i].specular = pmdMaterials[i].specular;
		materals[i].ambient = pmdMaterials[i].ambient;


	}
	//material end
#else

	//file open close ok
	FILE* fp = fopen("model/player.ply", "rb");

	int vertices_num = 240;
	int  faces_num = 80;
	char str[256];
	int i = 0;
	while (fgets(str, 256, fp) != NULL) {
		//printf("%c", str);
		_RPTN(_CRT_WARN, "debug %25s\n", str);
		i++;
		if (i == 19)break;
	}
	struct PLYVertex
	{
		float x;
		float y;
		float z;
		float nx;
		float ny;
		float nz;
		float s;
		float t;
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;
	};

	//vertex
	std::vector<unsigned char>model_data(vertices_num * MODEL_VERTEX_SIZE);//buffer
	fread(model_data.data(), model_data.size(), 1, fp);

	// 頂点バッファの生成.
	std::vector< Vertex > vertices;
	{
		unsigned char* p = model_data.data();

		for (int i = 0; i < model_data.size() /MODEL_VERTEX_SIZE; i++) {
			PLYVertex g_vert;
			memcpy(&g_vert.x, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.y, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.z, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.nx, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.ny, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.nz, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.s, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.t, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_vert.red, p, sizeof(unsigned char)); ++p;
			memcpy(&g_vert.green, p, sizeof(unsigned char)); ++p;
			memcpy(&g_vert.blue, p, sizeof(unsigned char)); ++p;
			memcpy(&g_vert.alpha, p, sizeof(unsigned char)); ++p;


			Vertex vec = { {g_vert.x,g_vert.y,g_vert.z,0.0f }, {g_vert.nx,g_vert.ny,g_vert.nz}, {(float) g_vert.red/255.0f,(float) g_vert.green / 255.0f,(float) g_vert.blue / 255.0f,(float) g_vert.alpha / 255.0f },{0,0} };

			vertices.push_back(vec);
		}

	}

	struct PLYIndex
	{
		UCHAR index;//1
		UINT one;//4
		UINT two;
		UINT three;
	};
	//index
	std::vector<unsigned char> g_indices;
	g_indices.resize(faces_num*13);
	fread(g_indices.data(), g_indices.size() * sizeof(g_indices[0]), 1, fp);
	fclose(fp);
	std::vector< UINT > indices;
	
	unsigned char* p = g_indices.data();
		for (int i = 0; i < faces_num; i++) {
			PLYIndex g_index;
			memcpy(&g_index.index, p, sizeof(unsigned char) * 4); ++p;
			memcpy(&g_index.one, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_index.two, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			memcpy(&g_index.three, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
			UINT index = g_index.one;
			indices.push_back(index);
			 index = g_index.two;
			indices.push_back(index);
			 index = g_index.three;
			indices.push_back(index);
		}
#endif

		{
			const UINT mengerVBSize = static_cast<UINT>(vertices.size()) * sizeof(Vertex);

			// Note: using upload heaps to transfer static data like vert buffers is not
			// recommended. Every time the GPU needs it, the upload heap will be
			// marshalled over. Please read up on Default Heap usage. An upload heap is
			// used here for code simplicity and because there are very few verts to
			// actually transfer.
			CD3DX12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			CD3DX12_RESOURCE_DESC bufferResource = CD3DX12_RESOURCE_DESC::Buffer(mengerVBSize);
			ThrowIfFailed(m_device->CreateCommittedResource(
				&heapProperty, D3D12_HEAP_FLAG_NONE, &bufferResource, //
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_MengerVB)));

			// Copy the triangle data to the vertex buffer.
			UINT8* pVertexDataBegin;
			CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
			ThrowIfFailed(m_MengerVB->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
			memcpy(pVertexDataBegin, vertices.data(), mengerVBSize);
			m_MengerVB->Unmap(0, nullptr);

			// Initialize the vertex buffer view.
			m_MengerVBView.BufferLocation = m_MengerVB->GetGPUVirtualAddress();
			m_MengerVBView.StrideInBytes = sizeof(Vertex);
			m_MengerVBView.SizeInBytes = mengerVBSize;
		}
		{
			const UINT mengerIBSize = static_cast<UINT>(indices.size()) * sizeof(UINT);

			// Note: using upload heaps to transfer static data like vert buffers is not
			// recommended. Every time the GPU needs it, the upload heap will be
			// marshalled over. Please read up on Default Heap usage. An upload heap is
			// used here for code simplicity and because there are very few verts to
			// actually transfer.
			CD3DX12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
			CD3DX12_RESOURCE_DESC bufferResource = CD3DX12_RESOURCE_DESC::Buffer(mengerIBSize);
			ThrowIfFailed(m_device->CreateCommittedResource(
				&heapProperty, D3D12_HEAP_FLAG_NONE, &bufferResource, //
				D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_MengerIB)));

			// Copy the triangle data to the index buffer.
			UINT8* pIndexDataBegin;
			CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
			ThrowIfFailed(m_MengerIB->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin)));
			memcpy(pIndexDataBegin, indices.data(), mengerIBSize);
			m_MengerIB->Unmap(0, nullptr);

			// Initialize the index buffer view.
			m_MengerIBView.BufferLocation = m_MengerIB->GetGPUVirtualAddress();
			m_MengerIBView.Format = DXGI_FORMAT_R32_UINT;
			m_MengerIBView.SizeInBytes = mengerIBSize;


			m_MengerIndexCount = static_cast<UINT>(indices.size());
			m_MengerVertexCount = static_cast<UINT>(vertices.size());
		}

	
}
void CPlayer::Update()
{
	CScene* scene = CManager::GetScene();

	
	//start game
	if (CInput::GetKeyPress('S')) { CUIManager::SetTitleFlag(false); }

	//game
	if (!CUIManager::GetClearFlag() && !CUIManager::GetTitleFlag()) {
		//move
		if (CInput::GetKeyPress('J')) { m_Position.x -= 0.1f; }
		if (CInput::GetKeyPress('L')) { m_Position.x += 0.1f; }
		if (CInput::GetKeyPress('I')) { m_Position.z -= 0.1f; }
		if (CInput::GetKeyPress('K')) { m_Position.z += 0.1f; }
	}
	XMMATRIX* matrix = GetMatrix();
	XMVECTOR scale = { m_Scale.x, m_Scale.y, m_Scale.z };
	XMVECTOR position = { m_Position.x, m_Position.y, m_Position.z };
	m_Rotation.z = -atan2(m_Front.x, m_Front.z);
	m_Rotation.z += 1.5f;
	*matrix = XMMatrixMultiply(
		XMMatrixMultiply(XMMatrixScalingFromVector(scale),
			XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z)),
		XMMatrixTranslationFromVector(position));
	if (!CUIManager::GetClearFlag() && !CUIManager::GetTitleFlag()) {
	
	if(m_prePosition != m_Position){ m_Front = m_Position - m_prePosition; }
	m_prePosition = m_Position;

	
	if (CInput::GetKeyTrigger('N')) {
		//弾発射
		//弾全体の取得
		std::vector<CBullet*> objects=scene->GetInstanceGameObjects<CBullet>(Layer::Game);
		for (CBullet* o : objects) {
			//未表示の弾検索
			if (!o->GetDestroy()) {
				//弾の表示
				o->SetDestroy(true);
				//弾の座標指定
				o->SetPosition(m_Position);
				o->SetRotation(glm::vec3{ 0.0f, 0.0f, 0.0f });
				o->SetScale(glm::vec3{ .3f, .3f, .3f });
				o->SetFront(m_Front);
				return;
			}

		}
	}
	}

	//reset
	if (CInput::GetKeyTrigger('Y')) {
		scene->SetReset(true);
	}
}
void CPlayer::Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper) {
	sbtHelper->AddHitGroup(L"HitGroup", { (void*)(m_MengerVB->GetGPUVirtualAddress()),
									   (void*)(m_MengerIB->GetGPUVirtualAddress())
									/*,(void*)(m_mengerMB->GetGPUVirtualAddress()) */});
	sbtHelper->AddHitGroup(L"ShadowHitGroup", {});
}