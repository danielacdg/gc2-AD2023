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

    void animColor();

    // Implementation
protected:
    void CalcSphericalCamera();
    XMFLOAT3 ChangeColor(XMFLOAT3 arcoiris);
    

    // Members
protected:
    ID3D11VertexShader* m_pVS;
    ID3D11PixelShader* m_pPS;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11Buffer* m_pVertexBuffer;
    ID3D11ShaderResourceView* m_pColorMap;
    ID3D11SamplerState* m_pColorMapSampler;
    ID3D11Buffer* m_pViewCB;
    ID3D11Buffer* m_pProjCB;
    ID3D11Buffer* m_pWorldCB;
    ID3D11Buffer* m_pCameraPosCB;
    XMMATRIX m_viewMatrix;
    XMMATRIX m_projMatrix;
    CObjParser m_ObjParser;
    XMFLOAT3 m_SphericalCamera;
    XMFLOAT3 m_SphericalCameraPos;

    //Color de Luz Difusa
    ID3D11Buffer* m_pDiffuseColorCB;
    XMFLOAT3 m_DiffuseColor;

    //cambiar de color
    float varR = 0.0f;
    float varG = 5.0f;
    float varB = 10.0f;

    bool positiveR = false;
    bool positiveG = false;
    bool positiveB = false;



};


#endif // _DEMOMODEL_H_
