#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"
#include <string>
#include <ctime>

class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState* alphaBlendState, * commonBlendState;

	int frameBillboard;
	int frameBillboardInicio;
	int frameBillboardFinish;
	bool bglobo=true;
	bool bglobo2 = true;
	bool bglobo3 = true;
	bool bglobo4 = true;
	bool bglobo5 = true;
	bool bglobo6 = true;
	bool bglobo7 = true;

	TerrenoRR* terreno;
	SkyDome* skydome;
	BillboardRR* billboard;
	BillboardRR* billboardInicio;
	BillboardRR* billboardFinish;
	Camara* camara;
	ModeloRR* model; //cofre
	///////////
	// Se agregan dos objetos para modelos nuevos
	///////////
	ModeloRR* carro;

	ModeloRR* balancin;
	ModeloRR* banca;
	ModeloRR* bancaMesa;
	ModeloRR* cono;
	ModeloRR* globo;
	ModeloRR* globo2;
	ModeloRR* globo3;
	ModeloRR* globo4;
	ModeloRR* globo5;
	ModeloRR* globo6;
	ModeloRR* globo7;
	ModeloRR* luminaria;
	ModeloRR* luminaria2;
	ModeloRR* pasamanos;
	ModeloRR* roca;
	ModeloRR* roca2;
	ModeloRR* tunel;
	ModeloRR* llantas;
	ModeloRR* senial;
	ModeloRR* senial2;
	ModeloRR* senial3;
	ModeloRR* casa;
	ModeloRR* piso;
	ModeloRR* silla;
	ModeloRR* mesa;


	//temporizador
	clock_t t;
	float segundos;

	//carrera
	int numeroCheckpoint = 0;
	bool ganaste = false;

	//interfaz
	BillboardRR* interfaz;
	BillboardRR* interfaz1;
	BillboardRR* interfaz2;
	BillboardRR* interfaz3;  //interfaz perder
	BillboardRR* interfaz4;  //interfaz ganar
	BillboardRR* check;
	BillboardRR* checkF;
	BillboardRR* Veloci;
	int vida = 3;

	bool EfectoVelocidad = false;
	float elevacion = 0;
	bool MessageBoxCoord;

	float izqder;
	float arriaba;
	float vel;
	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;
	///////////
	// Se agregan variables para tipo de cámara y rotación de la camara
	///////////
	bool camaraTipo;
	float rotCam; 

	DXRR(HWND hWnd, int Ancho, int Alto)
	{
		breakpoint = false;
		frameBillboard = 0;
		frameBillboardInicio = 0;
		frameBillboardFinish = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();
		t = clock();
		camara = new Camara(D3DXVECTOR3(0, 80, 6), D3DXVECTOR3(0, 80, 0), D3DXVECTOR3(0, 1, 0), Ancho, Alto);
		terreno = new TerrenoRR(500, 500, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"skydome4.jpg");

		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png", L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		billboardInicio = new BillboardRR(L"Assets/Billboards/inicio.png", L"Assets/Billboards/inicio.png", d3dDevice, d3dContext, 5);
		billboardFinish = new BillboardRR(L"Assets/Billboards/finish.png", L"Assets/Billboards/finish.png", d3dDevice, d3dContext, 5);

		interfaz = new BillboardRR(L"Assets/Billboards/interfaz2.png", L"Assets/Billboards/interfaz2.png", d3dDevice, d3dContext, 5);
		interfaz1 = new BillboardRR(L"Assets/Billboards/interfaz3.png", L"Assets/Billboards/interfaz3.png", d3dDevice, d3dContext, 5);
		interfaz2 = new BillboardRR(L"Assets/Billboards/interfaz4.png", L"Assets/Billboards/interfaz4.png", d3dDevice, d3dContext, 5);
		interfaz3 = new BillboardRR(L"Assets/Billboards/interfaz5.png", L"Assets/Billboards/interfaz5.png", d3dDevice, d3dContext, 5);
		interfaz4 = new BillboardRR(L"Assets/Billboards/interfaz6.png", L"Assets/Billboards/interfaz6.png", d3dDevice, d3dContext, 5);
		check = new BillboardRR(L"Assets/Billboards/checkpoint.png", L"Assets/Billboards/checkpoint.png", d3dDevice, d3dContext, 5);
		checkF = new BillboardRR(L"Assets/Billboards/checkpoint2.png", L"Assets/Billboards/checkpoint2.png", d3dDevice, d3dContext, 5);
		Veloci = new BillboardRR(L"Assets/Billboards/powerup.png", L"Assets/Billboards/powerup.png", d3dDevice, d3dContext, 5);

		//model = new ModeloRR(d3dDevice, d3dContext, "Assets/Cofre/Cofre.obj", L"Assets/Cofre/Cofre-color.png", L"Assets/Cofre/Cofre-spec.png", 0, 0);
		///////////
		// Se inicializan los nuevos modelos
		///////////
		carro = new ModeloRR(d3dDevice, d3dContext, "Assets/Drone/drone.obj", L"Assets/Drone/drone.jpg", L"Assets/Drone/drone.jpg", 0, 0);
		balancin = new ModeloRR(d3dDevice, d3dContext, "Assets/Balancin/balancin.obj", L"Assets/Balancin/BalancinTex.png", L"Assets/Balancin/BalancinTex.png",0,0);
		banca = new ModeloRR(d3dDevice, d3dContext, "Assets/Banca/Banca.obj", L"Assets/Banca/BancaTex.png", L"Assets/Banca/BancaTex.png", 0, 0);
		bancaMesa = new ModeloRR(d3dDevice, d3dContext, "Assets/BancaMesa/BancaMesa.obj", L"Assets/BancaMesa/madera.jpg", L"Assets/BancaMesa/madera.jpg", 0, 0);
		cono = new ModeloRR(d3dDevice, d3dContext, "Assets/Cono/cono.obj", L"Assets/Cono/conoTex.png", L"Assets/Cono/conoTex.png", 0, 0);
		globo = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);
		globo2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);
		globo3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);
		globo4 = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);
		globo5 = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);
		globo6 = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);
		globo7 = new ModeloRR(d3dDevice, d3dContext, "Assets/Globo/globo.obj", L"Assets/Globo/globoTex.png", L"Assets/Globo/globoTex.png", 0, 0);

		luminaria = new ModeloRR(d3dDevice, d3dContext, "Assets/Luminaria/luminaria.obj", L"Assets/Luminaria/luminariaTex.png", L"Assets/Luminaria/luminariaTex.png", 0, 0);
		luminaria2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Luminaria/luminaria.obj", L"Assets/Luminaria/luminariaTex.png", L"Assets/Luminaria/luminariaTex.png", 0, 0);
		pasamanos = new ModeloRR(d3dDevice, d3dContext, "Assets/Pasamanos/pasamanos.obj", L"Assets/Pasamanos/pasamanosText.png", L"Assets/Pasamanos/pasamanosText.png", 0, 0);
		roca = new ModeloRR(d3dDevice, d3dContext, "Assets/Roca/roca.obj", L"Assets/Roca/rocaTex.jpg", L"Assets/Roca/rocaTex.jpg", 0, 0);
		tunel = new ModeloRR(d3dDevice, d3dContext, "Assets/Tunel/tunel.obj", L"Assets/Tunel/texturaPared.jpg", L"Assets/Tunel/texturaPared.jpg", 0, 0);
		llantas = new ModeloRR(d3dDevice, d3dContext, "Assets/Llantas/llantas.obj", L"Assets/Llantas/llanta.jpg", L"Assets/Llantas/llanta.jpg", 0, 0);
		senial = new ModeloRR(d3dDevice, d3dContext, "Assets/Senial/senial.obj", L"Assets/Senial/senial.jpg", L"Assets/Senial/senial.jpg", 0, 0);
		senial2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Senial/senial.obj", L"Assets/Senial/senial.jpg", L"Assets/Senial/senial.jpg", 0, 0);
		senial3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Senial/senial.obj", L"Assets/Senial/senial.jpg", L"Assets/Senial/senial.jpg", 0, 0);
		casa = new ModeloRR(d3dDevice, d3dContext, "Assets/Casa/casa.obj", L"Assets/Casa/pared.jpg", L"Assets/Casa/pared.jpg", 0, 0);
		piso = new ModeloRR(d3dDevice, d3dContext, "Assets/Piso/piso.obj", L"Assets/Piso/piso.jpg", L"Assets/Piso/piso.jpg", 0, 0);
		silla = new ModeloRR(d3dDevice, d3dContext, "Assets/Silla/silla.obj", L"Assets/Silla/madera.jpg", L"Assets/Silla/madera.jpg", 0, 0);
		mesa = new ModeloRR(d3dDevice, d3dContext, "Assets/mesa/mesa.obj", L"Assets/mesa/madera.jpg", L"Assets/mesa/madera.jpg", 0, 0);

		// Se inicializan las nuevas variables
		///////////
		camaraTipo = true;
		rotCam = 0.0;
	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}

	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for (driver = 0; driver < totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels,
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if (SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if (FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}

		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if (FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if (backBufferTexture)
			backBufferTexture->Release();

		if (FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;

		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		// Initialize XACT3
		bool res = m_XACT3.Initialize();
		if (!res) {
			MessageBox(0, L"Error", L"Error al inicializar XACT Audio", MB_OK);
			return false;
		}
		res = m_XACT3.LoadWaveBank(L"Win\\WB1.xwb");
		if (!res) {
			MessageBox(0, L"Error", L"Error al cargar el banco wav", MB_OK);
			return false;
		}
		res = m_XACT3.LoadSoundBank(L"Win\\SB1.xsb");
		if (!res) {
			MessageBox(0, L"Error", L"Error al cargar el banco sound", MB_OK);
			return false;
		}

		// Play XACT3 cue
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("intro");
		m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");

		return true;

	}

	void LiberaD3D(void)
	{
		if (depthTexture)
			depthTexture->Release();
		if (depthStencilView)
			depthStencilView->Release();
		if (backBufferTarget)
			backBufferTarget->Release();
		if (swapChain)
			swapChain->Release();
		if (d3dContext)
			d3dContext->Release();
		if (d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}

	void Render(void)
	{
		///////////
		// breakpoint
		///////////
		if (breakpoint) {
			int x = 0;
		}

		rotCam += izqder;

		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if (d3dContext == 0)
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView(backBufferTarget, clearColor);
		d3dContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 5 + elevacion;;
		///////////
		// Se agrega variable de altura en cámara tercera persona
		///////////
		camara->posCam3P.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 10 + elevacion;;

		///////////
		// Se agrega variable de tipo de camara en UpdateCam
		///////////
		camara->UpdateCam(vel, arriaba, izqder, camaraTipo);

		// nuevo
		/*if (isPointInsideSphere(camara->getPos(), tierra->getCollisionSphere(5))) {
			vel = 0.0f;
			camara->posCam = camara->posCamPast;
		}
		else {
			camara->RenderCam();
		}*/

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);
		TurnOnAlphaBlending();
		billboard->Draw(camara->vista, camara->proyeccion, camara->posCam, -11, -78, 0, 7, uv1, uv2, uv3, uv4, frameBillboard,true);
		billboardInicio->Draw(camara->vista, camara->proyeccion, camara->posCam, 170, -13, terreno->Superficie(170,-13), 5, uv1, uv2, uv3, uv4, frameBillboardInicio, false);
		billboardFinish->Draw(camara->vista, camara->proyeccion, camara->posCam, -90, -40, terreno->Superficie(-90, -40), 5, uv1, uv2, uv3, uv4, frameBillboardFinish, false);
		

							//POWER UP
		
		if (EfectoVelocidad == false) {
			Veloci->Draw(camara->vista, camara->proyeccion, camara->posCam, 90, -40, terreno->Superficie(90, -40), 3, uv1, uv2, uv3, uv4, frameBillboardFinish, false);
			if (isPointInsideSphere4(camara->getPos(), 90, -40)) {                     //se le pasa camara.getPos()   y la direccion donde esta el billboard
				EfectoVelocidad = true;
			}
		}


												//sistema de vida
		switch (vida) {
		case 3:interfaz->Draw(camara->vista, camara->proyeccion, camara->posCam,
			camara->hdveo.x, camara->hdveo.z, terreno->Superficie(camara->getPos()[0], camara->getPos()[1]) + 2.5 + elevacion, 1.2, uv1, uv2, uv3, uv4, frameBillboard, false);
			break;
		case 2:interfaz1->Draw(camara->vista, camara->proyeccion, camara->posCam,
			camara->hdveo.x, camara->hdveo.z, terreno->Superficie(camara->getPos()[0], camara->getPos()[1]) + 2.5 + elevacion, 1.2, uv1, uv2, uv3, uv4, frameBillboard, false);
			break;
		case 1:interfaz2->Draw(camara->vista, camara->proyeccion, camara->posCam,
			camara->hdveo.x, camara->hdveo.z, terreno->Superficie(camara->getPos()[0], camara->getPos()[1]) + 2.5 + elevacion, 1.2, uv1, uv2, uv3, uv4, frameBillboard, false);
			break;
		case 0:interfaz3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			camara->hdveo.x, camara->hdveo.z, terreno->Superficie(camara->getPos()[0], camara->getPos()[1]) + 2.7 + elevacion, 1.2, uv1, uv2, uv3, uv4, frameBillboard, false);
			break;
		case 39:
			vida = 3;
			camara->posCam3P.x = 0;
			camara->posCam3P.z = 0;
			break;
		}

		//TurnOffAlphaBlending();
		///////////
		// Se agregan variables a la función de Draw
		///////////
		
												//SISTEMA CARRERAS
		switch (numeroCheckpoint) {
		case 0:
			check->Draw(camara->vista, camara->proyeccion, camara->posCam,
				153, -22, terreno->Superficie(-11, 78), 5, uv1, uv2, uv3, uv4, frameBillboard, false);
			if (isPointInsideSphere2(camara->getPos(), 153, -22)) {
				numeroCheckpoint = 1;
				ganaste = false;
			}
			break;
		case 1:
			check->Draw(camara->vista, camara->proyeccion, camara->posCam,
				74, -64, terreno->Superficie(-11, 78), 5, uv1, uv2, uv3, uv4, frameBillboard, false);
			if (isPointInsideSphere2(camara->getPos(), 74, -64)) {
				numeroCheckpoint = 2;
			}
			break;
		case 2:
			check->Draw(camara->vista, camara->proyeccion, camara->posCam,
				60, 35, terreno->Superficie(-11, 78), 5, uv1, uv2, uv3, uv4, frameBillboard, false);
			if (isPointInsideSphere2(camara->getPos(), 60, 35)) {
				numeroCheckpoint = 3;
			}
			break;
		case 3:
			checkF->Draw(camara->vista, camara->proyeccion, camara->posCam,
				-68, 38, terreno->Superficie(-11, 78), 5, uv1, uv2, uv3, uv4, frameBillboard, false);
			if (isPointInsideSphere2(camara->getPos(), -68, 38)) {
				numeroCheckpoint = 4;
			}
			break;
		case 4:
			t = clock() - t;
			segundos = float(t) / CLOCKS_PER_SEC;
			if (segundos < 90) {
				ganaste = true;
			}
			else {
				interfaz3->Draw(camara->vista, camara->proyeccion, camara->posCam,
					camara->hdveo.x, camara->hdveo.z, terreno->Superficie(camara->getPos()[0], camara->getPos()[1]) + 2.9 + elevacion, 1.2, uv1, uv2, uv3, uv4, frameBillboard, false);
			}
			numeroCheckpoint = 0;
			break;
		}
		if (ganaste == true) {
			interfaz4->Draw(camara->vista, camara->proyeccion, camara->posCam,
				camara->hdveo.x, camara->hdveo.z, terreno->Superficie(camara->getPos()[0], camara->getPos()[1]) + 2.9 + elevacion, 1.2, uv1, uv2, uv3, uv4, frameBillboard, false);
		}


		luminaria->setPosZ(-20);
		luminaria->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		luminaria2->setPosZ(-60);
		luminaria2->setPosX(-30);
		luminaria2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		bancaMesa->setPosX(65);
		bancaMesa->setPosZ(-35);
		bancaMesa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		/*model->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1, false, false);*/

		balancin->setPosZ(-70);
		balancin->setPosX(30);
		balancin->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		banca->setPosZ(-30);
		banca->setPosX(-15);
		banca->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		cono->setPosZ(-40);
		cono->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);


		pasamanos->setPosZ(-40);
		pasamanos->setPosX(55);
		pasamanos->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		roca->setPosX(0);
		roca->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

		tunel->setPosX(130);
		tunel->setPosZ(-30);
		tunel->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		llantas->setPosX(130);
		llantas->setPosZ(-30);
		llantas->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		senial->setPosX(70);
		senial->setPosZ(-75);
		senial->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		senial2->setPosX(80);
		senial2->setPosZ(-75);
		senial2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		senial3->setPosX(60);
		senial3->setPosZ(-75);
		senial3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		casa->setPosX(-10);
		casa->setPosZ(-26);
		casa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20)+2, camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		piso->setPosX(-10);
		piso->setPosZ(-26);
		piso->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20)+2, camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		silla->setPosX(-10);
		silla->setPosZ(-26);
		silla->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 2, camara->posCam, 10.0f, 0, 'A', 4, false, false, false);

		mesa->setPosX(-10);
		mesa->setPosZ(-26);
		mesa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 2, camara->posCam, 10.0f, 0, 'A', 4, false, false, false);
		///////////
		// Se utilizan funciones de seteo de variables
		///////////
		carro->setPosX(camara->hdveo.x);
		carro->setPosZ(camara->hdveo.z + 6);
		///////////
		// Se manda a dibujar el objeto del carro
		///////////

		if (EfectoVelocidad == true) {
			carro->Draw(camara->vista, camara->proyeccion
				, terreno->Superficie(carro->getPosX(), carro->getPosZ()) + 2.5 +elevacion
				, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 1, camaraTipo, true, true);
		}
		else {
			carro->Draw(camara->vista, camara->proyeccion
				, terreno->Superficie(carro->getPosX(), carro->getPosZ()) + 2.5 +elevacion
				, camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 1, camaraTipo, true, false);
		}

		if (MessageBoxCoord == true) {
			MessageBoxXD();
		}

		//para no salir del mapa
		if (camara->posCam.z > 230.0f) {
			vel = 0.0f;
			camara->posCam = camara->posCamPast;
		}

		if (camara->posCam.z < -230.0f) {
			vel = 0.0f;
			camara->posCam = camara->posCamPast;
		}
		if (camara->posCam.x > 230.0f) {
			vel = 0.0f;
			camara->posCam = camara->posCamPast;
		}
		if (camara->posCam.x < -230.0f) {
			vel = 0.0f;
			camara->posCam = camara->posCamPast;
		}
		                                                                             //EJEMPLO DE COLISION REDONDA ---- EL "5 " ES EL RADIO DE LA COLISION ---se usa la colision del "globo"
		if (bglobo == true) {                      //esto solo aplica para los globos, cuando uno se revienta deja de aparecer en pantalla
			globo->setPosZ(-35);
			globo->setPosX(-10);
			globo->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);
																					//Para los objetos que no sean globos se puede usar todo lo siguiente, menos lo de la vida
			if (isPointInsideSphere(camara->getPos(), globo->getCollisionSphere(7))) {
				//Primero se mueve a la camara a su posicion pasada
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				//Luego bajo 1 de vida
				vida -= 1;
				//luego quito el efecto de velocidad
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				//luego desaparezco el globo, en este caso con bglobo , ya estan preparados los bools de globo 2,3,4,5,6 y 7 
				bglobo = false;
			}
		}

		if (bglobo2 == true) {
			globo2->setPosZ(-50);
			globo2->setPosX(80);
			globo2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) - 1, camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

			if (isPointInsideSphere5(camara->getPos(), globo2->getCollisionSphere(7))) {
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				vida -= 1;
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				bglobo2 = false;
			}
		}

		if (bglobo3 == true) {
			globo3->setPosX(65);
			globo3->setPosZ(-60);
			globo3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) - 3, camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

			if (isPointInsideSphere6(camara->getPos(), globo3->getCollisionSphere(7))) {
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				vida -= 1;
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				bglobo3 = false;
			}
		}

		if (bglobo4 == true) {
			globo4->setPosX(50);
			globo4->setPosZ(-55);
			globo4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

			if (isPointInsideSphere7(camara->getPos(), globo4->getCollisionSphere(7))) {
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				vida -= 1;
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				bglobo4 = false;
			}
		}

		if (bglobo5 == true) {
			globo5->setPosX(35);
			globo5->setPosZ(-40);
			globo5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 1, camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

			if (isPointInsideSphere8(camara->getPos(), globo5->getCollisionSphere(7))) {
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				vida -= 1;
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				bglobo5 = false;
			}
		}

		if (bglobo6 == true) {
			globo6->setPosX(20);
			globo6->setPosZ(-50);
			globo6->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) - 4, camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

			if (isPointInsideSphere(camara->getPos(), globo6->getCollisionSphere(7))) {
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				vida -= 1;
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				bglobo6 = false;
			}
		}

		if (bglobo7 == true) {
			globo7->setPosX(5);
			globo7->setPosZ(-50);
			globo7->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 6, false, false, false);

			if (isPointInsideSphere(camara->getPos(), globo7->getCollisionSphere(7))) {
				vel = 0.0f;
				camara->posCam = camara->posCamPast;
				vida -= 1;
				if (EfectoVelocidad == true) {
					EfectoVelocidad = false;
				}
				bglobo7 = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), pasamanos->getCollisionSphere(8))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;
		
			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), luminaria->getCollisionSphere(8))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), luminaria2->getCollisionSphere(8))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), silla->getCollisionSphere(8))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}



		if (isPointInsideSphereChoque(camara->getPos(), balancin->getCollisionSphere(9))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), senial->getCollisionSphere(6))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), senial2->getCollisionSphere(6))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}

		if (isPointInsideSphereChoque(camara->getPos(), senial3->getCollisionSphere(6))) {
			//Primero se mueve a la camara a su posicion pasada
			vel = 0.0f;
			camara->posCam = camara->posCamPast;

			//luego quito el efecto de velocidad
			if (EfectoVelocidad == true) {
				EfectoVelocidad = false;
			}
		}
		
		
		swapChain->Present(1, 0);
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	bool isPointInsideSphereChoque(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;

		}
		return collition;
	}


	bool isPointInsideSphere5(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	bool isPointInsideSphere6(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	bool isPointInsideSphere7(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	bool isPointInsideSphere8(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	bool isPointInsideSphere9(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	bool isPointInsideSphere10(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		}
		return collition;
	}

	//colisiones usadas en los checkpoints
	bool isPointInsideSphere2(float* point, float x, float z) {
		bool collition = false;
		float distance = sqrt((point[0] - x) * (point[0] - x) +
			(point[1] - z) * (point[1] - z));

		if (distance < 30) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("win");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
			//MessageBox(0, L"COLISION", L"El objeto esta colisionando", MB_OK);
		}

		return collition;
	}
	//colision de radio con altura parametro 1 y 2 de la camara , otros parametros de la colision -distancia=radioCol
	bool isPointInsideSphere3(float* point, float altura, float x, float z, float distancia, float y1, float y2) {
		bool collition = false;
		float distance = sqrt((point[0] - x) * (point[0] - x) +
			(point[1] - z) * (point[1] - z));

		if (distance < distancia) {
			if (altura > y1 && altura < y2) {
				collition = true;
				cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("globo");
				m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
				//MessageBox(0, L"COLISION", L"El objeto esta colisionando", MB_OK);
			}
		}

		return collition;
	}

	//colision usada en powerups
	bool isPointInsideSphere4(float* point, float x, float z) {
		bool collition = false;
		float distance = sqrt((point[0] - x) * (point[0] - x) +
			(point[1] - z) * (point[1] - z));

		if (distance < 30) {
			collition = true;
			cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("power");
			m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
			//MessageBox(0, L"COLISION", L"El objeto esta colisionando", MB_OK);
		}

		return collition;
	}


	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable = true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);

		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable = true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

	void MessageBoxXD() {
		string xPos = to_string(camara->posCam.x);
		xPos.append("  ");
		xPos.append(to_string(camara->posCam.z));
		xPos;
		wstring hola2 = wstring(xPos.begin(), xPos.end());
		LPCWSTR hola = hola2.c_str();
		MessageBoxCoord = false;
	}

};
#endif