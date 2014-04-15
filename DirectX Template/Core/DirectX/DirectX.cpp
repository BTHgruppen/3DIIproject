// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: DirectX.cpp																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-07																║
// ║																					║
// ║ Desciription:																		║
// ║  Initialization of the Direct X component,	for communicating with the grapichs		║
// ║  hardware.																			║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "DirectX.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
DirectX::DirectX(HWND p_windowHandle)
{
	// Set variables to initial values.
	m_swapChain			= 0;
	m_device			= 0;
	m_deviceContext		= 0;
	m_depthStencil		= 0;
	m_depthStencilView	= 0;
	m_renderTargetView	= 0;

	m_shader			= 0;
	m_depthShader		= 0;

	// Create the device, context and swap chain.
	CreateSwapChain(p_windowHandle);

	// Setup render textures.
	CreateTextures();

	// Create view port.
	CreateViewPort();

	// Set default topology
	m_deviceContext -> IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Setup shader.
	LoadShaders(p_windowHandle);

	// Initialize render texture.
	Clear();
}

DirectX::~DirectX()
{
	// Release and delete the shader object if it exists.
	if(m_shader)
	{
		delete m_shader;
		m_shader = 0;
	}

	// Release and delete the shader object if it exists.
	if(m_depthShader)
	{
		delete m_depthShader;
		m_depthShader = 0;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Device and swap chain creator.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::CreateSwapChain(HWND p_windowHandle)
{
	HRESULT result = S_OK;

	// Gets screen size.
	RECT l_rectangle;
	GetClientRect(p_windowHandle, &l_rectangle);
	m_screenWidth = (l_rectangle.right - l_rectangle.left);
	m_screenHeight = (l_rectangle.bottom - l_rectangle.top);

	// Device flags to use.
	UINT l_deviceFlags = D3D11_CREATE_DEVICE_DEBUG;

	// Describe the swap chain.
	DXGI_SWAP_CHAIN_DESC l_swapChainDescription;
	ZeroMemory(&l_swapChainDescription, sizeof(l_swapChainDescription));
	l_swapChainDescription.BufferCount							= 1;
	l_swapChainDescription.BufferDesc.Width						= m_screenWidth;
	l_swapChainDescription.BufferDesc.Height					= m_screenHeight;
	l_swapChainDescription.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	l_swapChainDescription.BufferDesc.RefreshRate.Numerator		= 60;
	l_swapChainDescription.BufferDesc.RefreshRate.Denominator	= 1;
	l_swapChainDescription.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	l_swapChainDescription.OutputWindow							= p_windowHandle;
	l_swapChainDescription.SampleDesc.Count						= 1;
	l_swapChainDescription.SampleDesc.Quality					= 0;
	l_swapChainDescription.Windowed								= TRUE;

	// DirectX feature level used.
	D3D_FEATURE_LEVEL l_initiatedFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	// DirectX feature levels to try.
	D3D_FEATURE_LEVEL l_featureLevelsToTry[] = 
	{
		D3D_FEATURE_LEVEL_11_0, 
		D3D_FEATURE_LEVEL_10_1, 
		D3D_FEATURE_LEVEL_10_0
	};

	// Tries to create the device and swap chain. 
	result = D3D11CreateDeviceAndSwapChain
	(
		NULL, 
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL, 
		l_deviceFlags, 
		l_featureLevelsToTry, 
		ARRAYSIZE(l_featureLevelsToTry), 
		D3D11_SDK_VERSION, 
		&l_swapChainDescription, 
		&m_swapChain, 
		&m_device, 
		&l_initiatedFeatureLevel, 
		&m_deviceContext
	);

	// If device and swap chain succeeds to be created the window title is set.
	if(SUCCEEDED(result))
	{
		char l_title[256];
		sprintf_s(l_title, sizeof(l_title), BuildTitle(l_initiatedFeatureLevel));
		SetWindowTextA(p_windowHandle, l_title);
	}

	// If device and swap chain fails to be created, display an error message.
	else
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of device and swap chain failed.\n\nFILE:\nDirectX\n\nFUNCTION:\nCreateSwapChain", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Render texture setup.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::CreateTextures()
{
	HRESULT result = S_OK;

	// Set up temporary backbuffer texture.
	ID3D11Texture2D* l_backBuffer;

	// Create back buffer texture. If this fails, display an error message.
	result = m_swapChain -> GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&l_backBuffer);
	if(FAILED(result))
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of back buffer texture failed.\n\nFILE:\nDirectX\n\nFUNCTION:\nCreateTextures", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Create render target. If this fails, display an error message.
	result = m_device -> CreateRenderTargetView(l_backBuffer, NULL, &m_renderTargetView);
	if(FAILED(result))
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of render target failed.\n\nFILE:\nDirectX\n\nFUNCTION:\nCreateTextures", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Release the back buffer texture, as it is no longer needed.
	l_backBuffer -> Release();

	// Describe the depth stencil.
	D3D11_TEXTURE2D_DESC l_depthStencilDescription;
	ZeroMemory(&l_depthStencilDescription, sizeof(l_depthStencilDescription));
	l_depthStencilDescription.Width					= m_screenWidth;
	l_depthStencilDescription.Height				= m_screenHeight;
	l_depthStencilDescription.MipLevels				= 1;
	l_depthStencilDescription.ArraySize				= 1;
	l_depthStencilDescription.Format				= DXGI_FORMAT_D32_FLOAT;
	l_depthStencilDescription.SampleDesc.Count		= 1;
	l_depthStencilDescription.SampleDesc.Quality	= 0;
	l_depthStencilDescription.Usage					= D3D11_USAGE_DEFAULT;
	l_depthStencilDescription.BindFlags				= D3D11_BIND_DEPTH_STENCIL;
	l_depthStencilDescription.CPUAccessFlags		= 0;
	l_depthStencilDescription.MiscFlags				= 0;

	// Create depth stencil texture. If this fails, display an error message.
	result = m_device -> CreateTexture2D(&l_depthStencilDescription, NULL, &m_depthStencil);
	if(FAILED(result))
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of depth stencil failed.\n\nFILE:\nDirectX\n\nFUNCTION:\nCreateTextures", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Describe the depth stencil view.
	D3D11_DEPTH_STENCIL_VIEW_DESC l_depthStencilViewDescription;
	ZeroMemory(&l_depthStencilViewDescription, sizeof(l_depthStencilViewDescription));
	l_depthStencilViewDescription.Format			 = l_depthStencilViewDescription.Format;
	l_depthStencilViewDescription.ViewDimension		 = D3D11_DSV_DIMENSION_TEXTURE2D;
	l_depthStencilViewDescription.Texture2D.MipSlice = 0;

	// Create depth stencil view. If this fails, display an error message.
	result = m_device -> CreateDepthStencilView(m_depthStencil, &l_depthStencilViewDescription, &m_depthStencilView);
	if(FAILED(result))
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of depth stencil view failed.\n\nFILE:\nDirectX\n\nFUNCTION:\nCreateTextures", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Set device render target.
	m_deviceContext -> OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ View port creator.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::CreateViewPort()
{
	// Describe the view port.
	D3D11_VIEWPORT l_viewPort;
	ZeroMemory(&l_viewPort, sizeof(l_viewPort));
	l_viewPort.Width	= (float)m_screenWidth;
	l_viewPort.Height	= (float)m_screenHeight;
	l_viewPort.MinDepth	= 0.0f;
	l_viewPort.MaxDepth	= 1.0f;
	l_viewPort.TopLeftX	= 0;
	l_viewPort.TopLeftY	= 0;

	// Create the view port.
	m_deviceContext -> RSSetViewports(1, &l_viewPort);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Load shaders.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::LoadShaders(HWND p_windowHandle)
{
	// Compile and create the shaders.
	m_shader = new Shader(m_device, p_windowHandle);

	// Compile and create the depth shaders.
	m_depthShader = new DepthShader(m_device, p_windowHandle);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Clear render target function.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::Clear()
{
	// Set color to clear render target to.
	float l_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	// Clear render target with the set color.
	m_deviceContext -> ClearRenderTargetView(m_renderTargetView, l_color);
	m_deviceContext -> ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Render call.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::Present()
{
	m_swapChain -> Present(0, 0);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Render target reset function.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DirectX::ResetRenderTarget()
{
	// Set render target to the standard texture.
	m_deviceContext -> OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Feature level to string function.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
char* DirectX::BuildTitle(D3D_FEATURE_LEVEL p_featureLevel)
{
	if(p_featureLevel == D3D_FEATURE_LEVEL_11_0)
	{
		return "Application Name [running in DirectX 11.0]";
	}

	if(p_featureLevel == D3D_FEATURE_LEVEL_10_1)
	{
		return "Application Name [running in DirectX 10.1]";
	}

	if(p_featureLevel == D3D_FEATURE_LEVEL_10_0)
	{
		return "Application Name [running in DirectX 10.0]";
	}

	return "Application Name [ERROR: unknown DirectX version]";
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Various get functions.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

// Returns the device pointer.
ID3D11Device* DirectX::GetDevice()
{
	return m_device;
}

// Returns the context pointer.
ID3D11DeviceContext* DirectX::GetDeviceContext()
{
	return m_deviceContext;
}	

// Returns the depth stencil view.
ID3D11DepthStencilView*	DirectX::GetDepthStencilView()
{
	return m_depthStencilView;
}

// Returns the shader pointer.
Shader* DirectX::GetShader()
{
	return m_shader;
}

// Returns the shader pointer.
DepthShader* DirectX::GetDepthShader()
{
	return m_depthShader;
}