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
    virtual void cambiarColor(XMFLOAT3 color);

// Implementation
protected:
    void CalcSphericalCamera();
    XMFLOAT3 ChangeColor(XMFLOAT3 arcoiris);

// Members
protected:
    ID3D11VertexShader* m_pVS;
    ID3D11PixelShader* m_pPS;
    ID3D11InputLayout* m_pInputLayout; // DIBUJAR EN LA PANTALLa
    ID3D11Buffer* m_pVertexBuffer;
    ID3D11ShaderResourceView* m_pColorMap; // texturas
    ID3D11SamplerState* m_pColorMapSampler; // texturas
    ID3D11Buffer* m_pViewCB;
    ID3D11Buffer* m_pProjCB;
    ID3D11Buffer* m_pWorldCB; // matriz para la transfotmacion de cada objeto
    
    ID3D11Buffer* m_pCameraPosCB; // matrix de la posición de la camara
    XMMATRIX m_viewMatrix; // nueva iluminación
    XMMATRIX m_projMatrix; // nueva iluminación
    CObjParser m_ObjParser;
    XMFLOAT3 m_SphericalCamera;
    XMFLOAT3 m_SphericalCameraPos;

    //Color de Luz Difusa
    ID3D11Buffer* m_pDiffuseColorCB;
    XMFLOAT3 m_DiffuseColor; 


    //cambiar colores
    float R = 1.0f;
    float G = 0.4f;
    float B = 0.4f;

    bool colorAzul = false;
    bool colorRojo = false;
};


#endif // _DEMOMODEL_H_
