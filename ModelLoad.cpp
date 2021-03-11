#include "ModelLoad.h"
//#include <asdxMisc.h>

bool ModelLoad::Init()
{ 
    //HRESULT hr = S_OK;

    //{
    //    //file pass load
    //    std::wstring path;
    //    if (!asdx::SearchFilePathW(L"res/pronama/プロ生ちゃん.pmd", path))
    //    {
    //        ELOG("Error : SearchFilePath() Failed. ");
    //        return false;
    //    }
    //    //file data load
    //    if (!m_ModelData.Load(path.c_str()))
    //    {
    //        ELOG("Error : ResPmd::Load() Failed.");
    //        return false;
    //    }
    //}

    //std::vector<s32> textureIdList;
    //std::vector<std::wstring> textureNameList;
    //{
    //    //material pass
    //    std::string path;
    //    textureIdList.resize(m_ModelData.Materials.size());

    //    {
    //        //texture  name load
    //        std::wstring wpath;
    //        if (asdx::SearchFilePathW(L"res/dummy.dds", wpath))
    //        {
    //            textureNameList.push_back(wpath.c_str());
    //        }
    //    }

    //    for (size_t i = 0; i < m_ModelData.Materials.size(); ++i)
    //    {
    //        std::string temp = m_ModelData.Materials[i].TextureName;
    //        if (temp.empty())
    //        {
    //            continue;
    //        }

    //        // スフィアマップ名は取り除く.
    //        size_t idx = temp.find('*');
    //        if (idx != std::string::npos)
    //        {
    //            temp = temp.substr(0, idx);
    //        }

    //        std::string input = "res/pronama/" + temp;

    //        // 存在確認.
    //        if (!asdx::SearchFilePathA(input.c_str(), path))
    //        {
    //            textureIdList[i] = 0; // 見つからなかったらダミーテクスチャを使用.
    //            continue;
    //        }

    //        // ワイド文字に変換.
    //        auto filePath = asdx::ToStringW(path);

    //        // リストを検索.
    //        auto isFind = false;
    //        for (size_t j = 0; j < textureNameList.size(); ++j)
    //        {
    //            if (textureNameList[j] == filePath)
    //            {
    //                isFind = true;
    //                textureIdList[i] = u32(j);
    //                break;
    //            }
    //        }

    //        // 検索に引っかからなかったら追加.
    //        if (!isFind)
    //        {
    //            textureNameList.push_back(filePath);
    //            textureIdList[i] = u32(textureNameList.size() - 1);
    //        }
    //    }
    //}


    // 頂点バッファの生成.
    {
        /*if (!m_ModelVB.Init(
            m_pDevice.GetPtr(),
            sizeof(asdx::PMD_VERTEX) * m_ModelData.Vertices.size(),
            sizeof(asdx::PMD_VERTEX),
            &m_ModelData.Vertices[0]))
        {
            ELOG("Error : VertexBuffer::Init() Failed.");
            return false;
        }*/
    }

    // インデックスバッファの生成.
    {
       /* if (!m_ModelIB.Init(
            m_pDevice.GetPtr(),
            sizeof(u16) * m_ModelData.Indices.size(),
            DXGI_FORMAT_R16_UINT,
            &m_ModelData.Indices[0]))
        {
            ELOG("Error : IndexBuffer::Init() Faild.");
            return false;
        }*/
    }

    //// マテリアルバッファの生成.
    //{
    //    if (!m_ModelMB.Init(
    //        m_pDevice.GetPtr(),
    //        sizeof(ResMaterialBuffer) * m_ModelData.Materials.size()))
    //    {
    //        ELOG("Error : ConstantBuffer::Init() Failed.");
    //        return false;
    //    }

    //    u32 size = static_cast<u32>(sizeof(ResMaterialBuffer));

    //    // 定数バッファビューの設定.
    //    D3D12_CONSTANT_BUFFER_VIEW_DESC bufferDesc = {};
    //    bufferDesc.BufferLocation = m_ModelMB->GetGPUVirtualAddress();
    //    bufferDesc.SizeInBytes = size;

    //    u32 offset = 0;
    //    for (size_t i = 0; i < m_ModelData.Materials.size(); ++i)
    //    {
    //        m_ModelMB.Update(&m_ModelData.Materials[i], size, offset);

    //        m_pDevice->CreateConstantBufferView(&bufferDesc, m_Heap[DESC_HEAP_BUFFER].GetHandleCPU(1 + u32(i)));
    //        bufferDesc.BufferLocation += size;
    //        offset += size;
    //    }
    //}

    //// 定数バッファを生成.
    //{
    //    if (!m_ModelTB.Init(m_pDevice.GetPtr(), sizeof(ResConstantBuffer)))
    //    {
    //        ELOG("Error : ConstantBuffer::Init() Failed.");
    //        return false;
    //    }

    //    // 定数バッファビューの設定.
    //    D3D12_CONSTANT_BUFFER_VIEW_DESC bufferDesc = {};
    //    bufferDesc.BufferLocation = m_ModelTB->GetGPUVirtualAddress();
    //    bufferDesc.SizeInBytes = sizeof(ResConstantBuffer);

    //    // 定数バッファビューを生成.
    //    m_pDevice->CreateConstantBufferView(&bufferDesc, m_Heap[DESC_HEAP_BUFFER].GetHandleCPU(0));

    //    // アスペクト比算出.
    //    auto aspectRatio = static_cast<FLOAT>(m_Width) / static_cast<FLOAT>(m_Height);

    //    // 定数バッファデータの設定.
    //    m_ModelParam.World = asdx::Matrix::CreateIdentity();
    //    m_ModelParam.View = asdx::Matrix::CreateLookAt(asdx::Vector3(0.0f, 15.0f, -35.0f), asdx::Vector3(0.0f, 10.0f, 0.0f), asdx::Vector3(0.0f, 1.0f, 0.0f));
    //    m_ModelParam.Proj = asdx::Matrix::CreatePerspectiveFieldOfView(asdx::F_PIDIV4, aspectRatio, 1.0f, 1000.0f);

    //    // コピる.
    //    m_ModelTB.Update(&m_ModelParam, sizeof(m_ModelParam), 0);
    //}

    // テクスチャ・シェーダリソースビューの生成.
    //{
        //m_ModelTexture.resize(textureNameList.size());

        //auto idx = 0;
        //auto offset = 1 + static_cast<u32>(m_ModelData.Materials.size());

        //for (auto textureName : textureNameList)
        //{
        //    auto ext = asdx::GetExtW(textureName.c_str());

        //    // DDSを読み込みリソースを生成.
        //    if (ext == L"dds")
        //    {
        //        asdx::ResDDS dds;
        //        if (dds.Load(textureName.c_str()))
        //        {
        //            auto desc = asdx::Texture::Desc();
        //            desc.ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        //            desc.ResourceDesc.Width = dds.GetWidth();
        //            desc.ResourceDesc.Height = dds.GetHeight();
        //            desc.ResourceDesc.MipLevels = 1;
        //            desc.ResourceDesc.Format = static_cast<DXGI_FORMAT>(dds.GetFormat());
        //            desc.HandleCPU = m_Heap[DESC_HEAP_BUFFER].GetHandleCPU(offset + idx);

        //            if (!m_ModelTexture[idx].Init(m_pDevice.GetPtr(), desc))
        //            {
        //                continue;
        //            }

        //            // サブリソースを設定.
        //            D3D12_SUBRESOURCE_DATA res = {};
        //            res.pData = dds.GetSurfaces()->pPixels;
        //            res.RowPitch = dds.GetSurfaces()->Pitch;
        //            res.SlicePitch = dds.GetSurfaces()->SlicePitch;

        //            asdx::RefPtr<ID3D12Resource> intermediate;

        //            m_Immediate.Clear(m_pPipelineState.GetPtr());

        //            // サブリソースを更新.
        //            if (!m_ModelTexture[idx].Upload(
        //                m_Immediate.GetGfxCmdList(),
        //                &res,
        //                intermediate.GetAddress()))
        //            {
        //                continue;
        //            }

        //            // コマンドリストを閉じておく.
        //            m_Immediate->Close();

        //            // GPUにテクスチャ転送.
        //            m_Immediate.Execute(m_pCmdQueue.GetPtr());

        //            // 実行完了を待機.
        //            WaitForGpu();

        //        }
        //    }

        //    idx++;
        //}
   // }
return true;
}
