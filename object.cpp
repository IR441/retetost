//ishikawa reona
//ゲームオブジェクト

#include "stdafx.h"
#include "D3D12HelloTriangle.h"

#include "object.h"

//#include "DXRHelper.h"
#include "nv_helpers_dx12/BottomLevelASGenerator.h"

#include "nv_helpers_dx12/RaytracingPipelineGenerator.h"   
#include "nv_helpers_dx12/RootSignatureGenerator.h"
#include "nv_helpers_dx12/ShaderBindingTableGenerator.h"

//#include "glm/gtc/type_ptr.hpp"
//#include "manipulator.h"
//#include "Windowsx.h"

#include"DeviceManager.h"
#define MODEL_VERTEX_SIZE (28)
#define MODEL_VERTEX_SIZE_SV (36)
void Object::Update(){
	
}
void Object::Uninit(){}

void Object::Init() {

	ID3D12Device5* m_device = CDeviceManager::GetDevice();
	std::vector< Vertex > vertices = { 
		{{std::sqrtf(8.f / 9.f), 0.f, -1.f / 3.f,0.0f},{0.0f,1.0f,0.0f}, {1.f, 0.f, 0.f, 1.f},{0,0}},
		{{-std::sqrtf(2.f / 9.f), std::sqrtf(2.f / 3.f), -1.f / 3.f,0.0f},{0.0f,1.0f,0.0f},{0.f, 1.f, 0.f, 1.f},{0,0}},
		{{-std::sqrtf(2.f / 9.f), -std::sqrtf(2.f / 3.f), -1.f / 3.f,0.0f},{0.0f,1.0f,0.0f},{0.f, 0.f, 1.f, 1.f},{0,0}},
		{{0.f, 0.f, 1.f,0.0f},{0.0f,1.0f,0.0f},{1, 0, 1, 1},{0,0}}
	};
	if (m_Colorflag) {
		for (auto& vertex : vertices) {
			vertex.color = XMFLOAT4{ m_Color.x ,m_Color.y ,m_Color.z ,1.0f};
		}
	}
	std::vector< UINT > indices = { 0, 1, 2, 0, 3, 1, 0, 2, 3, 1, 3, 2 };
	//nv_helpers_dx12::GenerateMengerSponge(3, 0.75, vertices, indices);
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
void Object::Init(const char* file_name,int vertices_num,int faces_num)
{
	ID3D12Device5* m_device = CDeviceManager::GetDevice();

	//file open close ok
	FILE* fp = fopen(file_name, "rb");

	//int vertices_num = 240;
	//int  faces_num = 80;
	char str[256];
	int i = 0;
	int j = 0;
	while (fgets(str, 256, fp) != NULL) {
		//printf("%c", str);
		_RPTN(_CRT_WARN, "debug %25s\n", str);
		i++;
		if (str[0]== 'e')j++;
		if (3 == j)break;
	}
	// 頂点バッファの生成.
	std::vector< Vertex > vertices;
	if (17 == i) {
		{
			struct PLYVertex
			{
				float x;
				float y;
				float z;
				float nx;
				float ny;
				float nz;
				unsigned char red;
				unsigned char green;
				unsigned char blue;
				unsigned char alpha;
			};

			//vertex
			std::vector<unsigned char>model_data(vertices_num * MODEL_VERTEX_SIZE);//buffer
			fread(model_data.data(), model_data.size(), 1, fp);


			{
				unsigned char* p = model_data.data();

				for (int i = 0; i < model_data.size() / MODEL_VERTEX_SIZE; i++) {
					PLYVertex g_vert;
					memcpy(&g_vert.x, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
					memcpy(&g_vert.y, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
					memcpy(&g_vert.z, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
					memcpy(&g_vert.nx, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
					memcpy(&g_vert.ny, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
					memcpy(&g_vert.nz, p, sizeof(unsigned char) * 4); ++p; ++p; ++p; ++p;
					memcpy(&g_vert.red, p, sizeof(unsigned char)); ++p;
					memcpy(&g_vert.green, p, sizeof(unsigned char)); ++p;
					memcpy(&g_vert.blue, p, sizeof(unsigned char)); ++p;
					memcpy(&g_vert.alpha, p, sizeof(unsigned char)); ++p;


					Vertex vec = { {g_vert.x,g_vert.y,g_vert.z,0.0f }, {g_vert.nx,g_vert.ny,g_vert.nz}, {(float)g_vert.red / 255.0f,(float)g_vert.green / 255.0f,(float)g_vert.blue / 255.0f,(float)g_vert.alpha / 255.0f },{0,0} };

					vertices.push_back(vec);
				}

			}
		}
	}
	else if (19 == i)
	{
		struct PLYVertexST
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
		std::vector<unsigned char>model_data_st(vertices_num * MODEL_VERTEX_SIZE_SV);//buffer
		fread(model_data_st.data(), model_data_st.size(), 1, fp);

		// 頂点バッファの生成.
		//std::vector< Vertex > vertices;
		{
			unsigned char* p = model_data_st.data();

			for (int i = 0; i < model_data_st.size() / MODEL_VERTEX_SIZE_SV; i++) {
				PLYVertexST g_vert;
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


				Vertex vec = { {g_vert.x,g_vert.y,g_vert.z,0.0f }, {g_vert.nx,g_vert.ny,g_vert.nz}, {(float)g_vert.red / 255.0f,(float)g_vert.green / 255.0f,(float)g_vert.blue / 255.0f,(float)g_vert.alpha / 255.0f },{0,0} };

				vertices.push_back(vec);
			}

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
	g_indices.resize(faces_num * 13);
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

	/*std::vector< Vertex > vertices = {
		{{std::sqrtf(8.f / 9.f), 0.f, -1.f / 3.f,0.0f},{0.0f,1.0f,0.0f}, {1.f, 0.f, 0.f, 1.f},{0,0}},
		{{-std::sqrtf(2.f / 9.f), std::sqrtf(2.f / 3.f), -1.f / 3.f,0.0f},{0.0f,1.0f,0.0f},{0.f, 1.f, 0.f, 1.f},{0,0}},
		{{-std::sqrtf(2.f / 9.f), -std::sqrtf(2.f / 3.f), -1.f / 3.f,0.0f},{0.0f,1.0f,0.0f},{0.f, 0.f, 1.f, 1.f},{0,0}},
		{{0.f, 0.f, 1.f,0.0f},{0.0f,1.0f,0.0f},{1, 0, 1, 1},{0,0}}
	};
	if (colorflag) {
		for (auto& vertex : vertices) {
			vertex.color = XMFLOAT4{ m_Color.x ,m_Color.y ,m_Color.z ,1.0f };
		}
	}
	std::vector< UINT > indices = { 0, 1, 2, 0, 3, 1, 0, 2, 3, 1, 3, 2 };*/
	//nv_helpers_dx12::GenerateMengerSponge(3, 0.75, vertices, indices);
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
void Object::CreateBLAS() {
	ID3D12Device5* m_device= CDeviceManager::GetDevice();
	ID3D12GraphicsCommandList4* m_commandList= CDeviceManager::GetcommandList();
	nv_helpers_dx12::BottomLevelASGenerator bottomLevelAS;
	for (size_t i = 0; i <1; i++) {
		if (m_MengerIndexCount > 0) {
			bottomLevelAS.AddVertexBuffer(
				m_MengerVB.Get(), 0,m_MengerVertexCount,
				sizeof(Vertex),
				m_MengerIB.Get(), 0,m_MengerIndexCount,
				nullptr, 0, true);
		}
		else {
			bottomLevelAS.AddVertexBuffer(
				m_MengerVB.Get(), 0,
				m_MengerIndexCount, sizeof(Vertex), 0,
				0);
		}

	}
	// The AS build requires some scratch space to store temporary information.
	// The amount of scratch memory is dependent on the scene complexity.
	UINT64 scratchSizeInBytes = 0;
	// The final AS also needs to be stored in addition to the existing vertex
	// buffers. It size is also dependent on the scene complexity.
	UINT64 resultSizeInBytes = 0;

	bottomLevelAS.ComputeASBufferSizes(m_device, false, &scratchSizeInBytes,
		&resultSizeInBytes);
	
	
	const D3D12_HEAP_PROPERTIES kUploadHeapProps = {
	D3D12_HEAP_TYPE_UPLOAD, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 0, 0 };

	// Specifies the default heap. This heap type experiences the most bandwidth for
	// the GPU, but cannot provide CPU access.
	const D3D12_HEAP_PROPERTIES kDefaultHeapProps = {
		D3D12_HEAP_TYPE_DEFAULT, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 0, 0 };
	
	{
	// Once the sizes are obtained, the application is responsible for allocating
	// the necessary buffers. Since the entire generation will be done on the GPU,
	// we can directly allocate those on the default heap
	//AccelerationStructureBuffers buffers;
	D3D12_RESOURCE_DESC bufDesc = {};
	bufDesc.Alignment = 0;
	bufDesc.DepthOrArraySize = 1;
	bufDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	bufDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	bufDesc.Format = DXGI_FORMAT_UNKNOWN;
	bufDesc.Height = 1;
	bufDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	bufDesc.MipLevels = 1;
	bufDesc.SampleDesc.Count = 1;
	bufDesc.SampleDesc.Quality = 0;
	bufDesc.Width = scratchSizeInBytes;

	

	ID3D12Resource* pBuffer;

	ThrowIfFailed(m_device->CreateCommittedResource(&kDefaultHeapProps, D3D12_HEAP_FLAG_NONE, &bufDesc,
		D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&pBuffer)));

	m_Buffers.pScratch =pBuffer;
	//m_commandList->CopyResource(m_buffers.pScratch .Get(), pBuffer);
	/*nv_helpers_dx12::CreateBuffer(
		m_device, scratchSizeInBytes,
		D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COMMON,
		nv_helpers_dx12::kDefaultHeapProps);*/
	}

	{
		D3D12_RESOURCE_DESC bufDesc = {};
		bufDesc.Alignment = 0;
		bufDesc.DepthOrArraySize = 1;
		bufDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		bufDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
		bufDesc.Format = DXGI_FORMAT_UNKNOWN;
		bufDesc.Height = 1;
		bufDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		bufDesc.MipLevels = 1;
		bufDesc.SampleDesc.Count = 1;
		bufDesc.SampleDesc.Quality = 0;
		bufDesc.Width = resultSizeInBytes;

		ID3D12Resource* pBuffer;
		ThrowIfFailed(m_device->CreateCommittedResource(&kDefaultHeapProps, D3D12_HEAP_FLAG_NONE, &bufDesc,
			D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE, nullptr, IID_PPV_ARGS(&pBuffer)));
		
		
		m_Buffers.pResult = pBuffer;
		/*nv_helpers_dx12::CreateBuffer(
			m_device, resultSizeInBytes,
			D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,
			D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE,
			nv_helpers_dx12::kDefaultHeapProps);*/
	}
	

	// Build the acceleration structure. Note that this call integrates a barrier
	// on the generated AS, so that it can be used to compute a top-level AS right
	// after this method.
	bottomLevelAS.Generate(m_commandList, m_Buffers.pScratch.Get(),
		m_Buffers.pResult.Get(), false, nullptr);

	//return buffers;
}
void Object::Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper) {
	sbtHelper->AddHitGroup(L"HitGroup", { (void*)(m_MengerVB->GetGPUVirtualAddress()),
									   (void*)(m_MengerIB->GetGPUVirtualAddress()) });
	sbtHelper->AddHitGroup(L"ShadowHitGroup", {});
}

void Object::DrawCommand(ID3D12GraphicsCommandList4* commandList){
	commandList->IASetVertexBuffers(0, 1, &m_MengerVBView);
	commandList->IASetIndexBuffer(&m_MengerIBView);
	commandList->DrawIndexedInstanced(m_MengerIndexCount, 1, 0, 0, 0);
}