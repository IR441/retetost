//ishikawa reona
//ゲームマネージャー　過去のゲームから移植
//2021/03/01
//使えないかも
#pragma once
#define UI_OOKISA (2.0f)
#define UI_KAITEN_X (0)
#define UI_KAITEN_Y (0)
#define UI_KAITEN_Z (0)
class CManager
{
private:
	static class CScene* m_Scene;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw(nv_helpers_dx12::ShaderBindingTableGenerator* sbtHelper);
	static void CreateBLAS();
	static void DrawCommand(ID3D12GraphicsCommandList4* commandList);

	static void PushBackInstsnce(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* instances);

	static class CScene* GetScene() { return m_Scene; }

	template<typename T>
	static void SetScene() {
		if (m_Scene != NULL) {
			m_Scene->Uninit();
			delete m_Scene;
		}

		T* scene = new T();
		scene->Init();

		m_Scene = scene;
	}
};

