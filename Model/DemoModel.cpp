// DemoModel.cpp : Implements the CDemoModel class.
//
//
//

#include "DemoModel.h"
#include "ObjParser.h"


//////////////////////////////////////////////////////////////////////
// Constructors

CDemoModel::CDemoModel(float specular)
{
    m_pVS = NULL;
    m_pPS = NULL;
    m_pInputLayout = NULL;
    m_pVertexBuffer = NULL;
    m_pColorMap = NULL;
    m_pColorMapSampler = NULL;
    m_pViewCB = NULL;
    m_pProjCB = NULL;
    m_pWorldCB = NULL;
    m_pCameraPosCB = NULL;
    m_SphericalCamera = XMFLOAT3(0.0f, 0.0f, -5.5f); // rx, ry, distance
    m_SphericalCameraPos = m_SphericalCamera;
    // ---------- Luz Especular
    m_pSpecularIntensity = NULL;
    m_pSpecularIntensity2 = NULL;
    m_pSpecularIntensity3 = NULL;
    specularIntensity = specular;
    specularIntensity2 = specular;
    m_Light = XMFLOAT3(0.0f, 0.0f, 5.5f); //z,y,distancia
    m_LightPos = m_Light;
    m_Light2 = XMFLOAT3(0.0f, 0.0f, 5.5f); //z,y,distancia
    m_LightPos2 = m_Light2;
}

CDemoModel::~CDemoModel()
{
}


//////////////////////////////////////////////////////////////////////
// Overrides

bool CDemoModel::LoadContent()
{
    // Load OBJ file
    // ---------- esfera
    bool res = m_ObjParser.LoadFile("Recursos/esfera2.obj");
    //bool res = m_ObjParser.LoadFile("Cube.txt");
    if (res == false) {
        ::MessageBox(m_hWnd, L"Unable to load OBJ file", L"ERROR", MB_OK);
        return false;
    }

    // Vertex description
    D3D11_BUFFER_DESC vertexDesc;
    ::ZeroMemory(&vertexDesc, sizeof(vertexDesc));
    vertexDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.ByteWidth = sizeof(VertexObj) * m_ObjParser.m_nVertexCount;

    // Resource data
    D3D11_SUBRESOURCE_DATA resourceData;
    ::ZeroMemory(&resourceData, sizeof(resourceData));
    resourceData.pSysMem = m_ObjParser.m_pVertex;

    // Create vertex buffer
    HRESULT hr = m_pD3DDevice->CreateBuffer(&vertexDesc, &resourceData, &m_pVertexBuffer);
    if (FAILED(hr)) {
        return false;
    }


    // Compile vertex shader
    ID3DBlob* pVSBuffer = NULL;
    res = CompileShader(L"ShaderLighting.fx", "VS_Main", "vs_4_0", &pVSBuffer);
    if (res == false) {
        ::MessageBox(m_hWnd, L"Unable to load vertex shader", L"ERROR", MB_OK);
        return false;
    }

    // Create vertex shader
    hr = m_pD3DDevice->CreateVertexShader(
        pVSBuffer->GetBufferPointer(),
        pVSBuffer->GetBufferSize(),
        0, &m_pVS);
    if (FAILED(hr)) {
        if (pVSBuffer)
            pVSBuffer->Release();
        return false;
    }

    // Define input layout
    D3D11_INPUT_ELEMENT_DESC shaderInputLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numLayoutElements = ARRAYSIZE(shaderInputLayout);

    // Create input layout
    hr = m_pD3DDevice->CreateInputLayout(
        shaderInputLayout, numLayoutElements,
        pVSBuffer->GetBufferPointer(),
        pVSBuffer->GetBufferSize(),
        &m_pInputLayout);
    if (FAILED(hr)) {
        return false;
    }

    // Release VS buffer
    pVSBuffer->Release();
    pVSBuffer = NULL;

    // Compile pixel shader
    ID3DBlob* pPSBuffer = NULL;
    res = CompileShader(L"ShaderLighting.fx", "PS_Main", "ps_4_0", &pPSBuffer);
    if (res == false) {
        ::MessageBox(m_hWnd, L"Unable to load pixel shader", L"ERROR", MB_OK);
        return false;
    }

    // Create pixel shader
    hr = m_pD3DDevice->CreatePixelShader(
        pPSBuffer->GetBufferPointer(),
        pPSBuffer->GetBufferSize(),
        0, &m_pPS);
    if (FAILED(hr)) {
        return false;
    }

    // Cleanup PS buffer
    pPSBuffer->Release();
    pPSBuffer = NULL;


    // Load texture
    hr = ::D3DX11CreateShaderResourceViewFromFile(
        m_pD3DDevice, L"Recursos/tierra.jpg", 0, 0, &m_pColorMap, 0);
    if (FAILED(hr)) {
        ::MessageBox(m_hWnd, L"Unable to load texture", L"ERROR", MB_OK);
        return false;
    }

    // Texture sampler
    D3D11_SAMPLER_DESC textureDesc;
    ::ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    textureDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    textureDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    textureDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    textureDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    textureDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = m_pD3DDevice->CreateSamplerState(&textureDesc, &m_pColorMapSampler);
    if (FAILED(hr)) {
        ::MessageBox(m_hWnd, L"Unable to create texture sampler state", L"ERROR", MB_OK);
        return false;
    }

    // Create constant buffers (see fx-file)
    D3D11_BUFFER_DESC constBufferDesc;
    ::ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
    constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constBufferDesc.ByteWidth = sizeof(XMMATRIX);
    constBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pViewCB);
    if (FAILED(hr)) {
        return false;
    }
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pProjCB);
    if (FAILED(hr)) {
        return false;
    }
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pWorldCB);
    if (FAILED(hr)) {
        return false;
    }

    //Buffer para la posición de la cámara
    constBufferDesc.ByteWidth = sizeof(XMFLOAT4);
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pCameraPosCB);
    if (FAILED(hr)) {
        return false;
    }

    // ---------- Buffer para la posición de la Luz Especular
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pSpecularIntensity);
    if (FAILED(hr)) {
        return false;
    }
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pSpecularIntensity2);
    if (FAILED(hr)) {
        return false;
    }
    hr = m_pD3DDevice->CreateBuffer(&constBufferDesc, 0, &m_pSpecularIntensity3);
    if (FAILED(hr)) {
        return false;
    }


    // Initialize matrixes
    m_projMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, 640.0f / 480.0f, 0.01f, 1000.0f);
    m_projMatrix = XMMatrixTranspose(m_projMatrix);
    CalcSphericalCamera();

    return true;
}

void CDemoModel::UnloadContent()
{
    // Cleanup
    if (m_pColorMap)
        m_pColorMap->Release();
    m_pColorMap = NULL;
    if (m_pColorMapSampler)
        m_pColorMapSampler->Release();
    m_pColorMapSampler = NULL;
    if (m_pVS)
        m_pVS->Release();
    m_pVS = NULL;
    if (m_pPS)
        m_pPS->Release();
    m_pPS = NULL;
    if (m_pInputLayout)
        m_pInputLayout->Release();
    m_pInputLayout = NULL;
    if (m_pVertexBuffer)
        m_pVertexBuffer->Release();
    m_pVertexBuffer = NULL;
    if (m_pViewCB)
        m_pViewCB->Release();
    m_pViewCB = NULL;
    if (m_pProjCB)
        m_pProjCB->Release();
    m_pProjCB = NULL;
    if (m_pWorldCB)
        m_pWorldCB->Release();
    m_pWorldCB = NULL;
    if (m_pCameraPosCB)
        m_pCameraPosCB->Release();
    m_pCameraPosCB = NULL;
}

void CDemoModel::Update()
{
    m_SphericalCamera.y += 0.0001f;
    // ---------- variable para mover la Luz Especular
    m_Light.y += .0002f;
    m_Light2.y += .0002f;

    if (pase1 == true)
    {
        cambio = cambio + 0.0005f;
        if (cambio > 0.8f)
        {
            pase1 = false;
        }
    }
    else
    {
        cambio = cambio - 0.0005f;
        if (cambio < 0.1)
        {
            pase1 = true;
        }
    }

    if (pase2 == false)
    {
        cambio2 = cambio2 + 0.0005f;
        if (cambio2 > 0.8f)
        {
            pase2 = true;
        }
    }
    else
    {
        cambio2 = cambio2 - 0.0005f;
        if (cambio2 < 0.1)
        {
            pase2 = false;
        }
    }

    //cambio += 0.005f;
    // 

    // Calculate spherical camera
    CalcSphericalCamera();
}

void CDemoModel::Render()
{
    // Check if D3D is ready
    if (m_pD3DContext == NULL)
        return;

    // Clear back buffer
    float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_pD3DContext->ClearRenderTargetView(m_pD3DRenderTargetView, color);
    m_pD3DContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


    // Stride and offset
    UINT stride = sizeof(VertexObj);
    UINT offset = 0;

    // Set vertex buffer
    m_pD3DContext->IASetInputLayout(m_pInputLayout);
    m_pD3DContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pD3DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Set shaders
    m_pD3DContext->VSSetShader(m_pVS, 0, 0);
    m_pD3DContext->PSSetShader(m_pPS, 0, 0);
    m_pD3DContext->PSSetShaderResources(0, 1, &m_pColorMap);
    m_pD3DContext->PSSetSamplers(0, 1, &m_pColorMapSampler);

    // Position in the world
    XMMATRIX w = XMMatrixIdentity();
    XMMATRIX r = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, XM_PI);
    XMMATRIX t = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
    w = XMMatrixTranspose(w * r * t);

    //Cambiar color de luz difusa

    // Update constant buffers
    m_pD3DContext->UpdateSubresource(m_pWorldCB, 0, 0, &w, 0, 0);
    m_pD3DContext->UpdateSubresource(m_pViewCB, 0, 0, &m_viewMatrix, 0, 0);
    m_pD3DContext->UpdateSubresource(m_pProjCB, 0, 0, &m_projMatrix, 0, 0);
    m_pD3DContext->UpdateSubresource(m_pCameraPosCB, 0, 0, &m_SphericalCameraPos, 0, 0);
    // ---------- Buffer para la Luz Especular
    m_pD3DContext->UpdateSubresource(m_pSpecularIntensity, 0, 0, &specularIntensity, 0, 0);
    m_pD3DContext->UpdateSubresource(m_pSpecularIntensity2, 0, 0, &cambio, 0, 0);
    m_pD3DContext->UpdateSubresource(m_pSpecularIntensity3, 0, 0, &cambio2, 0, 0);
    // Upload constant buffers to GPU
    m_pD3DContext->VSSetConstantBuffers(0, 1, &m_pWorldCB);
    m_pD3DContext->VSSetConstantBuffers(1, 1, &m_pViewCB);
    m_pD3DContext->VSSetConstantBuffers(2, 1, &m_pProjCB);

    m_pD3DContext->VSSetConstantBuffers(3, 1, &m_pCameraPosCB);
    // ---------- constantes para la Luz Especular
    m_pD3DContext->VSSetConstantBuffers(4, 1, &m_pSpecularIntensity);
    m_pD3DContext->VSSetConstantBuffers(4, 1, &m_pSpecularIntensity2);
    m_pD3DContext->VSSetConstantBuffers(4, 1, &m_pSpecularIntensity3);

    // Draw triangles
    m_pD3DContext->Draw(m_ObjParser.m_nVertexCount, 0);


    // Present back buffer to display
    m_pSwapChain->Present(0, 0);
}


//////////////////////////////////////////////////////////////////////
// Implementation

// Calculates a spherical camera (sets m_viewMatrix)
void CDemoModel::CalcSphericalCamera()
{
    // Set view matrix (i.e. camera)
    XMVECTOR pos = { 0.0f, 0.0f, m_SphericalCamera.z };
    //XMVECTOR pos = { 0.0f, -.0f, m_SphericalCamera.z };
    XMVECTOR lookAt = { 0.0f, 0.0f, 0.0f };
    XMVECTOR up = { 0.0f, 1.0f, 0.0f };
    XMMATRIX rm = XMMatrixRotationRollPitchYaw(m_SphericalCamera.x, m_SphericalCamera.y, 0.0f);
    pos = XMVector3Transform(pos, rm);
    up = XMVector3Transform(up, rm);
    m_viewMatrix = XMMatrixLookAtLH(pos, lookAt, up);
    m_viewMatrix = XMMatrixTranspose(m_viewMatrix);

    // Remember camera position
    m_SphericalCameraPos.x = XMVectorGetX(pos);
    m_SphericalCameraPos.y = XMVectorGetY(pos);
    m_SphericalCameraPos.z = XMVectorGetZ(pos);

    // ---------- Movimiento de la Luz Especular
    XMVECTOR lightPos = { 0.0f,0.0f,m_Light.z };
    XMMATRIX lightRot = XMMatrixRotationRollPitchYaw(m_Light.x, m_Light.y, 0.0f);
    XMVECTOR lightPos2 = { 0.0f,0.0f,m_Light2.z };
    XMMATRIX lightRot2 = XMMatrixRotationRollPitchYaw(m_Light2.x, m_Light2.y, 0.0f);

    lightPos = XMVector3Transform(lightPos, lightRot);
    m_LightPos.x = XMVectorGetX(lightPos);
    m_LightPos.y = XMVectorGetY(lightPos);
    m_LightPos.z = XMVectorGetZ(lightPos);
    m_LightPos2.x = XMVectorGetX(lightPos2);
    m_LightPos2.y = XMVectorGetY(lightPos2);
    m_LightPos2.z = XMVectorGetZ(lightPos2);
}