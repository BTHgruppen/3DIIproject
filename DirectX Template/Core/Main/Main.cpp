// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Main.cpp																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-05																║
// ║																					║
// ║ Desciription:																		║
// ║  Main class of the program, the Win32 window used for rendering and the DirectX	║
// ║  interface are initialized by this class. 											║
// ║  Game logic updates and render commands are also called from here.					║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Main.h"

// I WANT MY TEST COMMENT!!

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Main::Main(HINSTANCE p_instanceHandle, int p_show)
{
	// Default window size.
	Window l_defaultWindow = Window(0, 0, 1016, 539);

	// Initialize the Win32 window. If this fails, an error message is displayed.
	m_win32 = new Win32("Win32Class", "Initializing DirectX . . . ", l_defaultWindow, p_instanceHandle, p_show);
	if(!m_win32)
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of Win32 window failed.\n\nFILE:\nMain\n\nFUNCTION:\nMain (constructor)", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Initialize the DirectX API. If this fails, an error message is displayed.
	m_directX = new DirectX(m_win32 -> GetWindowHandle());
	if(!m_directX)
	{
		MessageBox(NULL, "DESCRIPTION:\nInitialisation of DirectX API failed.\n\nFILE:\nMain\n\nFUNCTION:\nMain (constructor)", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Initialize the timer. If this fails, an error message is displayed.
	m_timer = new Timer();
	if(!m_timer)
	{
		MessageBox(NULL, "DESCRIPTION:\nInitialisation of game timer failed.\n\nFILE:\nMain\n\nFUNCTION:\nMain (constructor)", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Initialize any variables.
	Initialize(l_defaultWindow);
}

Main::~Main()
{
	// Release and delete the Win32 window object if it exists.
	if(m_win32)
	{
		delete m_win32;
		m_win32 = 0;
	}

	// Release and delete the DirectX object if it exists.
	if(m_directX)
	{
		delete m_directX;
		m_directX = 0;
	}

	// Release and delete the timer object if it exists.
	if(m_timer)
	{
		delete m_timer;
		m_timer = 0;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Run function.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
int Main::Run()
{
	// Main message loop, runs until a WM_QUIT message is recieved.
	MSG l_message = {0};

	// Reset the timer.
	m_timer -> Reset();

	while(l_message.message != WM_QUIT)
	{
		// Translates and dispatches incoming messages.
		if(PeekMessage(&l_message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&l_message);
			DispatchMessage(&l_message);
		}

		else
		{
			// Update timer.
			m_timer -> Count();
			m_deltaTime = m_timer -> GetDeltaTime();

			// Update the scene.
			Update(m_deltaTime);

			// Render the scene
			Render();
		}
	}

	return (int)l_message.wParam;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Initialize function.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Main::Initialize(Window p_defaultWindow)
{
	// Initialize camera.
	float l_aspectRatio = (float)((p_defaultWindow.width - 16) / (p_defaultWindow.height - 39));
	m_camera = new Camera();
	m_camera -> UpdatePosition(D3DXVECTOR3(0, 2, -2));
	m_camera -> UpdateTarget(D3DXVECTOR3(0, 0, 0));
	m_camera -> UpdateUpVector(D3DXVECTOR3(0, 1, 0));
	m_camera -> UpdateFieldOfView((float)D3DX_PI * 0.45f);
	m_camera -> UpdateAspectRatio(l_aspectRatio);
	m_camera -> UpdateClippingPlanes(1.0f, 10.0f);
	m_camera -> UpdateMatrices();

	// Set shader variables from the camera.
	m_directX -> GetShader() -> SetCameraPosition(m_camera -> GetPosition());
	m_directX -> GetShader() -> SetMatrices(m_camera -> GetViewMatrix(), m_camera -> GetProjectionMatrix());

	// Initialize the light source.
	m_lightSource = new Camera();
	m_lightSource -> UpdatePosition(D3DXVECTOR3(1.65f, 1.5f, 0.0f));
	m_lightSource -> UpdateTarget(D3DXVECTOR3(0, 0, 0));
	m_lightSource -> UpdateUpVector(D3DXVECTOR3(0, 1, 0));
	m_lightSource -> UpdateFieldOfView((float)D3DX_PI * 0.45f);
	m_lightSource -> UpdateAspectRatio(l_aspectRatio);
	m_lightSource -> UpdateClippingPlanes(1.0f, 10.0f);
	m_lightSource -> UpdateMatrices();

	// Initialize the point light.
	m_pointLight.m_ambientValue		= D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pointLight.m_diffuseValue		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pointLight.m_specularValue	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pointLight.m_lightAttenuation = D3DXVECTOR3(0.0f, 0.7f, 0.0f);
	m_pointLight.m_lightPosition	= m_lightSource -> GetPosition();
	m_pointLight.m_range			= 10;

	// Set shader variables from the light source.
	m_directX -> GetShader() -> SetPointLight(m_pointLight);
	m_directX -> GetDepthShader() -> SetMatrices(m_lightSource -> GetViewMatrix(), m_lightSource -> GetProjectionMatrix());
	m_directX -> GetShader() -> SetLightMatrices(m_lightSource -> GetViewMatrix(), m_lightSource -> GetProjectionMatrix());

	// Setup the test plane.
	m_plane = new Plane(m_directX);
	m_plane -> m_plane -> Scale(D3DXVECTOR3(6, 1, 6));
	m_plane -> m_plane -> Translate(D3DXVECTOR3(-3, 0, 3));

	// Setup the test cube.
	m_cube = new Cube(m_directX);
	m_cube -> m_cube -> Translate(D3DXVECTOR3(-0.5f, 0, 0.5f));

	// Setup material to be used.
	m_material.m_ambientValue	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_material.m_diffuseValue	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_material.m_specularValue	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 10.0f);
	m_directX -> GetShader() -> SetMaterial(m_material);

	// Setup shadow map.
	m_shadowMap = new ShadowMap(m_directX -> GetDevice(), 1000, 500);
	m_shadowMap -> Clear(m_directX -> GetDeviceContext());
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Update function.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Main::Update(float p_deltaTime)
{
	// Keeps the fps down. Temporary solution.
	Sleep(10);

	// Handle keypresses.
	HandleInput();

	// Update scene.
	m_plane -> Update(p_deltaTime);
	m_cube -> Update(p_deltaTime);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Render functions.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Main::Render()
{
	// Render to shadow map first.
	RenderDepth();

	// Clear screen.
	m_directX -> Clear();

	// Render scene.
	m_plane -> Render(m_shadowMap -> GetShadowMap());
	m_cube -> Render(m_shadowMap -> GetShadowMap());

	// Present sceen.
	m_directX -> Present();
}

void Main::RenderDepth()
{
	// Set the shadow map as the render target.
	m_shadowMap -> SetAsRenderTarget(m_directX -> GetDeviceContext());
	
	// Clear shadow map.
	m_shadowMap -> Clear(m_directX -> GetDeviceContext());

	// Render depth data to the shadow map.
	m_plane -> RenderDepth();
	m_cube -> RenderDepth();

	// Reset render target.
	m_directX -> ResetRenderTarget();
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Input handler.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Main::HandleInput()
{
	// Quit if the escape key is pressed.
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}