// DemoModel.h : Defines the CDemoModel class.
//
//
//

#ifndef _DEMOMODEL_H_
#define _DEMOMODEL_H_

#include "Dx11Base.h"
#include "ObjParser.h"


class CDemoModel : public CDx11Base
{
// Constructors
public:
    CDemoModel();
    virtual ~CDemoModel();

// Overrides
public:
    virtual bool LoadContent();
    virtual void UnloadContent();

    virtual void Update();
    virtual void Render();

// Implementation
protected:
    void CalcSphericalCamera();
    XMFLOAT3 ChangeColor(XMFLOAT3 arcoiris);

// Members
protected:
    float objRotation;

    // Shaders
    ID3D11VertexShader* m_pVS;
    ID3D11PixelShader* m_pPS;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11Buffer* m_pVertexBuffer;

    // Textures
    ID3D11ShaderResourceView* m_pColorMap;
    ID3D11ShaderResourceView* m_pColorMap2;
    ID3D11SamplerState* m_pColorMapSampler;

    // Matrices de espacio
    ID3D11Buffer* m_pViewCB;
    ID3D11Buffer* m_pProjCB;
    ID3D11Buffer* m_pWorldCB;
    XMMATRIX m_viewMatrix;
    XMMATRIX m_projMatrix;

    // Camera buffer and controller
    ID3D11Buffer* m_pCameraPosCB;
    XMFLOAT3 m_SphericalCamera;
    XMFLOAT3 m_SphericalCameraPos;

    // Obj Parser
    CObjParser m_ObjParser;

    // Light
    ID3D11Buffer* m_pLightPosCB;
    XMFLOAT3 m_Light;
    XMFLOAT3 m_LightPos;
    ID3D11Buffer* m_pDiffuseColorCB;
    XMFLOAT3 m_DiffuseColor;

    // LightMap
    ID3D11ShaderResourceView* m_pLightMap;

    // AlphaMap
    ID3D11ShaderResourceView* m_pAlphaMap;

    // BumpMap
    ID3D11ShaderResourceView* m_pBumpMap;

    // SpecularMap
    ID3D11ShaderResourceView* m_pSpecularMap;
};


#endif // _DEMOMODEL_H_
