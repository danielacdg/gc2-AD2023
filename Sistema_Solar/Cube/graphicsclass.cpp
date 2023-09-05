/////////////////////////////////////
//Filename: graphicsclass.cpp
/////////////////////////////////////
#include "graphicsclass.h"
#include "D3dx9shape.h"

GraphicsClass::GraphicsClass(){
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other){
}

GraphicsClass::~GraphicsClass(){
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd){

	bool result;

	//Create the Direct3D Object
	m_D3D = new D3DClass;
	if(!m_D3D)
		return false;

	//Initialize the Direct3D object
	result = m_D3D->Initialize(screenWidth,screenHeight,VSYNC_ENABLED,hwnd,FULL_SCREEN,SCREEN_DEPTH,SCREEN_NEAR);
	if(!result){

		MessageBox(hwnd,L"Could not initialize Direct3D",L"Error",MB_OK);
	
	}

	//Create the camera object
	m_Camera = new CameraClass;
	if(!m_Camera)
		return false;

	//Set the initial position of the camera
	m_Camera->SetPosition(0.0f,0.0f,-50.0f);
	m_Camera->SetRotation(0, 0, 10);

	//Create the model object
	m_Model = new ModelClass;
	if(!m_Model)
		return false;

	//Initialize the model object
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Cube/Cube.txt", L"../Cube/sol.jpg", L"../Cube/Z1.png", L"../Cube/mercurio.png", L"../Cube/venus.jpg", L"../Cube/mundo.jpg", L"../Cube/luna.jpg", L"../Cube/marte.jpg");
	if(!result){
		MessageBox(hwnd,L"Could not initialize the model object.", L"Error",MB_OK);
		return false;
	}

	//Create the light shader object
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
		return false;

	//Initialize the lightShaer object
	result = m_LightShader->Initialize(m_D3D->GetDevice(),hwnd);
	if(!result)
		return false;

	//Create the light object
	m_Light = new LightClass;
	if(!m_Light)
		return false;

	//Initialize the light object
	m_Light->SetDiffuseColor(1.0f,1.0f,1.0f,1.0f);
	m_Light->SetDirection(0.0f,0.0f,1.0f);

	return  true;
}

void GraphicsClass::Shutdown(){

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	//Release the light object
	if(m_Light){
		delete m_Light;
		m_Light = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//Release the Direct3D object
	if(m_D3D){

		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame(){

	bool result;

	static float rotation = 0.0f;

	//Update the rotation variable each frame
	rotation -= (float)D3DX_PI * 0.01f;
	if(rotation < -360)
	rotation = 0.0f;
	

	//Render the graphics scene
	result = Render(rotation);
	if(!result)
		return false;
	return true;
}

bool GraphicsClass::Render(float rotation){

	D3DXMATRIX viewMatrix, projectionMatrix, SunMatrix, auxMatrix, traMatrix, EarthMatrix, MartMatrix, MoonMatrix, MercuryMatrix, VenusMatrix;
	
	bool result;

	//Clear the buffers to begin the scene
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	//Generate the vie matrix based on the camera's position
	m_Camera->Render();

	//Get the world view and projection matrices from the camera and d3d objects
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(SunMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.

	//Rotaci�n del cuerpo
	D3DXMatrixRotationY(&SunMatrix, -rotation);

	//Distanciar del sol(Traslaci�n)

	//Mov. de Traslaci�n(Rotaci�n con sol en centro)

	//Escala del cuerpo
	D3DXMatrixScaling(&auxMatrix, 5.5, 5.5, 5.5);
	D3DXMatrixMultiply(&SunMatrix, &SunMatrix, &auxMatrix);

	//Orientar textura de planeta
	D3DXMatrixRotationX(&traMatrix, 180);

	//Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	//Sol
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), SunMatrix, viewMatrix, projectionMatrix, traMatrix, 
				       m_Model->GetTexture(), m_Model->GetTexture2(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	if (!result)
		return false;

	//Mercurio
	//

	//Venus
	//

	//Tierra
	//

	//Luna
	//

	//Marte
	//

	//Present the rendered scene to the sceen
	m_D3D->EndScene();
	return true;
}
