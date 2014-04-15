// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: DirectX.h																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-07																║
// ║																					║
// ║ Desciription:																		║
// ║  Initialization of the Direct X component,	for communicating with the grapichs		║
// ║  hardware.																			║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../Misc/Inclusions.h"

#include "../Bridges/Shader/Shader.h"
#include "../Bridges/DepthShader/DepthShader.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class DirectX
{
	public:
		// functions:
		 DirectX(HWND p_windowHandle);
		~DirectX();

		void Clear();
		void Present();
		void ResetRenderTarget();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();	
		ID3D11DepthStencilView*	GetDepthStencilView();

		Shader* GetShader();
		DepthShader* GetDepthShader();
		
	private:
		// variables:
		int	m_screenWidth;
		int m_screenHeight;

		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;

		ID3D11Texture2D* m_depthStencil;
		ID3D11DepthStencilView*	m_depthStencilView;

		ID3D11RenderTargetView*	m_renderTargetView;
		IDXGISwapChain*	m_swapChain;

		Shader* m_shader;
		DepthShader* m_depthShader;

		// functions:
		void CreateSwapChain(HWND p_windowHandle);
		void CreateTextures();
		void CreateViewPort();

		void LoadShaders(HWND p_windowHandle);

		char* BuildTitle(D3D_FEATURE_LEVEL p_featureLevel);
};