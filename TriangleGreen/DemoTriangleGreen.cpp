// DemoTriangleGreen.cpp : Implementando la clase CDemoTriangleGreen.
//
// 
//

#include "DemoTriangleGreen.h"

// Estructura de vértice
struct Vertex
{
    XMFLOAT3 pos;
};


//////////////////////////////////////////////////////////////////////
// Contructor

CDemoTriangleGreen::CDemoTriangleGreen()
{
    m_pVSGreenColor = NULL;
    m_pPSGreenColor = NULL;
    m_pInputLayout  = NULL;
    m_pVertexBuffer = NULL;
}

CDemoTriangleGreen::~CDemoTriangleGreen()
{
}


/////////////////////////////////////////////////////////////////////
// Overrides

bool CDemoTriangleGreen::LoadContent()
{
    // Compilando el vertex shader //__
    ID3DBlob* pVSBuffer = NULL;
    bool res = CompileShader(L"Recursos/VertexShader.hlsl", "VS_Main", "ps_4_0", &pVSBuffer);
    if(res==false)
    {
        ::MessageBox(m_hWnd, L"No se pudo cargar el VertexShader", L"ERROR", MB_OK);
        return false;
    }
    // Creando el vertex shader //__
    HRESULT hr = S_OK;
    hr = m_pD3DDevice->CreateVertexShader(
        pVSBuffer->GetBufferPointer(),
        pVSBuffer->GetBufferSize(),
        0, 
        &m_pVSGreenColor
    );
    if (FAILED(hr)) {
        if (pVSBuffer)
            pVSBuffer->Release();
        return false;
    }

    // Definimos el input layout = Declaramos que vamos a dibujar
    D3D11_INPUT_ELEMENT_DESC shaderInputLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numLayoutElements = ARRAYSIZE(shaderInputLayout);

    // Creamos el input layout //__
    hr = m_pD3DDevice->CreateInputLayout(
        shaderInputLayout, numLayoutElements,
        pVSBuffer->GetBufferPointer(),
        pVSBuffer->GetBufferSize(),
        &m_pInputLayout
        );
    if (FAILED(hr)) {
        return false;
    }

    // Release VS buffer
    if(pVSBuffer)
        pVSBuffer->Release();
    pVSBuffer = NULL;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Compilamos el pixel shader //__
    ID3DBlob* pPSBuffer = NULL;
    res = CompileShader(L"Recursos/PixelShader.hlsl", "VS_Main", "vs_4_0", &pVSBuffer);
    if (res == false)
    {
        ::MessageBox(m_hWnd, L"No se pudo cargar el PixelShader", L"ERROR", MB_OK);
        return false;
    }
    // Creamos el pixel shader //__
    hr = m_pD3DDevice->CreatePixelShader(
        pVSBuffer->GetBufferPointer(),
        pVSBuffer->GetBufferSize(),
        0,
        &m_pPSGreenColor
    );

    if (FAILED(hr)) {
        return false;
    }

    // Cleanup PS buffer
    if(pPSBuffer)
        pPSBuffer->Release();
    pPSBuffer = NULL;

    // Definimos nuestro triangulo
    Vertex vertices[] =
    {
        XMFLOAT3(0.0f,  0.5f, 0.0f),
        XMFLOAT3(0.5f, -0.5f, 0.0f),
        XMFLOAT3(-0.5f, -0.5f, 0.0f)
    };

    // Vertex description //__
    D3D11_BUFFER_DESC vertexDesc;
    ::ZeroMemory(&vertexDesc, sizeof(vertexDesc)); //borra lo que hay antes y dibuja sobre eso
    vertexDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.ByteWidth = sizeof(Vertex) * 3;

    // Resource data //__
    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory(&resourceData, sizeof(resourceData));
    resourceData.pSysMem = vertices; 

    // Creamos el vertex buffer //__
    hr = m_pD3DDevice->CreateBuffer(
        &vertexDesc,
        &resourceData,
        &m_pVertexBuffer
    );

    if (FAILED(hr)) {
        return false;
    }

    return true;
}

void CDemoTriangleGreen::UnloadContent()
{
    // Cleanup LIMPIADO DEL BUFFER
    if (m_pVSGreenColor)
        m_pVSGreenColor->Release();
    m_pVSGreenColor = NULL;
    if (m_pPSGreenColor)
        m_pPSGreenColor->Release();
    m_pPSGreenColor = NULL;
    if (m_pInputLayout)
        m_pInputLayout->Release();
    m_pInputLayout = NULL;
    if (m_pVertexBuffer)
        m_pVertexBuffer->Release();
    m_pVertexBuffer = NULL;
}

void CDemoTriangleGreen::Update()
{
}

void CDemoTriangleGreen::Render()
{
    // Check if D3D is ready //__
    if (m_pD3DContext == NULL)
    {
        return;
    }

    // Clear back buffer //__
    float color[4] = { 0.0f,0.0f,0.0f,1.0f };
    m_pD3DContext->ClearRenderTargetView (m_pD3DRenderTargetView, color);

    // Stride and offset
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    // Set vertex buffer //__
    m_pD3DContext->IASetInputLayout(m_pInputLayout);
    m_pD3DContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pD3DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Set shaders
    m_pD3DContext->VSSetShader(m_pVSGreenColor, 0, 0);
    m_pD3DContext->PSSetShader(m_pPSGreenColor, 0, 0);

    // Draw triangle
    m_pD3DContext->Draw(3, 0);

    // Present back buffer to display
    m_pSwapChain->Present(0, 0);

}
