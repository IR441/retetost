//ishikawa reona
//�f�o�C�X�|�C���^�̎󂯓n��
//2021/03/01
//�����K���C��
#include "stdafx.h"
#include "D3D12HelloTriangle.h"
#include "DeviceManager.h"
HINSTANCE* CDeviceManager::ma_Hwnd;
ID3D12Device5* CDeviceManager::ma_Device=NULL;
std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>* CDeviceManager::ma_Instances=NULL;
ID3D12GraphicsCommandList4* CDeviceManager::ma_CommandList;