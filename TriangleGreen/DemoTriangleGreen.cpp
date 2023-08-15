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


//////////////////////////////////////////////////////////////////////
// Overrides

bool CDemoTriangleGreen::LoadContent()
{
    // Compilando el vertex shader
    ID3DBlob* pVSBuffer = NULL;
    //--
    

    // Creando el vertex shader
    HRESULT hr = S_OK;
    //--

    if (FAILED(hr)) {
        if (pVSBuffer)
            pVSBuffer->Release();
        return false;
    }

    // Definimos el input layout
    D3D11_INPUT_ELEMENT_DESC shaderInputLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numLayoutElements = ARRAYSIZE(shaderInputLayout);

    // Creamos el input layout
    //--

    if (FAILED(hr)) {
        return false;
    }

    // Release VS buffer
    if(pVSBuffer)
        pVSBuffer->Release();
    pVSBuffer = NULL;

    // Compilamos el pixel shader
    ID3DBlob* pPSBuffer = NULL;
    //--

    // Creamos el pixel shader
    //--

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

    // Vertex description
    D3D11_BUFFER_DESC vertexDesc;
    //--

    // Resource data
    D3D11_SUBRESOURCE_DATA resourceData;
    //--

    // Creamos el vertex buffer
    //--

    if (FAILED(hr)) {
        return false;
    }

    return true;
}

void CDemoTriangleGreen::UnloadContent()
{
    // Cleanup
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
    // Check if D3D is ready
    //--

    // Clear back buffer
    //--

    // Stride and offset
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    // Set vertex buffer
    //--

    // Set shaders
    //--

    // Draw triangle
    //--

    // Present back buffer to display
    //--

}
