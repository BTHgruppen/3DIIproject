// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: ShadowMap.cpp															║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-28																║
// ║																					║
// ║ Desciription:																		║
// ║  Class used to create a secondary render target to be used as shadow map			║
// ║  for the shadowing of geometry.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "ShadowMap.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
ShadowMap::ShadowMap(ID3D11Device* p_device, int p_width, int p_height)
{
	// Initialize the shadow map texture desdcription, and clear memory.
	D3D11_TEXTURE2D_DESC l_textureDescription;
	ZeroMemory(&l_textureDescription, sizeof(l_textureDescription));

	// Describe the shadow map texture.
	l_textureDescription.Width				= p_width;
	l_textureDescription.Height				= p_height;
	l_textureDescription.MipLevels			= 1;
	l_textureDescription.ArraySize			= 1;
	l_textureDescription.Format				= DXGI_FORMAT_R32G32B32A32_FLOAT;
	l_textureDescription.SampleDesc.Count	= 1;
	l_textureDescription.Usage				= D3D11_USAGE_DEFAULT;
	l_textureDescription.BindFlags			= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	l_textureDescription.CPUAccessFlags		= 0;
	l_textureDescription.MiscFlags			= 0;

	// Create the shadow map texture, if this fails an error message is displayed.
	if(FAILED(p_device -> CreateTexture2D(&l_textureDescription, NULL, &m_shadowMap)))
	{
		MessageBox(NULL, "DESCRIPTION:\nFailed to create a shadow map texture.\n\nFILE:\nShadowMap\n\nFUNCTION:\nShadowMap (constructor)", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Describe the shadow map target view.
	D3D11_RENDER_TARGET_VIEW_DESC l_targetViewDescription;
	l_targetViewDescription.Format				= l_textureDescription.Format;
	l_targetViewDescription.ViewDimension		= D3D11_RTV_DIMENSION_TEXTURE2D;
	l_targetViewDescription.Texture2D.MipSlice	= 0;

	// Create the shadow map target view, if this fails an error message is displayed.
	if(FAILED(p_device -> CreateRenderTargetView(m_shadowMap, &l_targetViewDescription, &m_shadowMapTargetView)))
	{
		MessageBox(NULL, "DESCRIPTION:\nFailed to create a shadow map target view.\n\nFILE:\nShadowMap\n\nFUNCTION:\nShadowMap (constructor)", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Describe the shadow map shader resource view.
	D3D11_SHADER_RESOURCE_VIEW_DESC l_ResourceViewDescription;
	l_ResourceViewDescription.Format						= l_textureDescription.Format;
	l_ResourceViewDescription.ViewDimension					= D3D11_SRV_DIMENSION_TEXTURE2D;
	l_ResourceViewDescription.Texture2D.MostDetailedMip		= 0;
	l_ResourceViewDescription.Texture2D.MipLevels			= 1;

	// Create the shadow map shader resource view, if this fails an error message is displayed.
	if(FAILED(p_device -> CreateShaderResourceView(m_shadowMap, &l_ResourceViewDescription, &m_shadowMapResourceView)))
	{
		MessageBox(NULL, "DESCRIPTION:\nFailed to create a shadow map shader resource view.\n\nFILE:\nShadowMap\n\nFUNCTION:\nShadowMap (constructor)", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Describe the depth stencil.
	D3D11_TEXTURE2D_DESC l_depthStencilDescription;
	ZeroMemory(&l_depthStencilDescription, sizeof(l_depthStencilDescription));
	l_depthStencilDescription.Width					= p_width;
	l_depthStencilDescription.Height				= p_height;
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
	if(FAILED(p_device -> CreateTexture2D(&l_depthStencilDescription, NULL, &m_depthStencil)))
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
	if(FAILED(p_device -> CreateDepthStencilView(m_depthStencil, &l_depthStencilViewDescription, &m_depthStencilView)))
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of depth stencil view failed.\n\nFILE:\nDirectX\n\nFUNCTION:\nCreateTextures", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

ShadowMap::~ShadowMap()
{
	if(m_shadowMapResourceView)
	{
		m_shadowMapResourceView -> Release();
		m_shadowMapResourceView = 0;
	}

	if(m_shadowMapTargetView)
	{
		m_shadowMapTargetView -> Release();
		m_shadowMapTargetView = 0;
	}

	if(m_shadowMap)
	{
		m_shadowMap -> Release();
		m_shadowMap = 0;
	}

	if(m_depthStencil)
	{
		m_depthStencil -> Release();
		m_depthStencil = 0;
	}

	if(m_depthStencilView)
	{
		m_depthStencilView -> Release();
		m_depthStencilView = 0;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Function to set shadow map as current render target.								║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void ShadowMap::SetAsRenderTarget(ID3D11DeviceContext* p_deviceContext)
{
	// Set pixel shader shadow map to NULL.
	ID3D11ShaderResourceView* p_nullPointer = NULL;
	p_deviceContext -> PSSetShaderResources(1, 1, &p_nullPointer);

	// Bind the shadow map as the new render target.
	p_deviceContext -> OMSetRenderTargets(1, &m_shadowMapTargetView, m_depthStencilView);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Clear shadow map function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void ShadowMap::Clear(ID3D11DeviceContext* p_deviceContext)
{
	// Set color to clear the back buffer to.
	float l_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

	// Clear back and depth buffers.
	p_deviceContext -> ClearRenderTargetView(m_shadowMapTargetView, l_color);
	p_deviceContext -> ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Shadow map get function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
ID3D11ShaderResourceView* ShadowMap::GetShadowMap()
{
	return m_shadowMapResourceView;
}