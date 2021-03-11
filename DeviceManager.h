//ishikawa reona
//デバイスポインタの受け渡し
//2021/03/01
//命名規則修正
#pragma once
#include <wrl.h>
#include<vector>
using namespace Microsoft::WRL;
class CDeviceManager
{
private:
	static HINSTANCE* ma_Hwnd;
	static ID3D12Device5*	ma_Device;
	static std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* ma_Instances;

	static ID3D12GraphicsCommandList4* ma_CommandList;
public:

	static void Init(ID3D12Device5* device) {
		ma_Device = device;
	
	}

	static void SetHinstance(HINSTANCE* g_hwnd) { ma_Hwnd = g_hwnd; }
	static void Setinstances(std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* m_instances){
		ma_Instances=m_instances;
	}
	static void SetcommandList(ID3D12GraphicsCommandList4* m_commandList) { ma_CommandList = m_commandList; }

	static HINSTANCE* GetHinstance () { return ma_Hwnd; }
	static ID3D12Device5* GetDevice() { return ma_Device; }	
	static std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* Getinstance() { return ma_Instances;}
	static ID3D12GraphicsCommandList4* GetcommandList() { return ma_CommandList; }
};

