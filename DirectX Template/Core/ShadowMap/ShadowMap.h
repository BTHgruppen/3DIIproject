// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: ShadowMap.h																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-28																║
// ║																					║
// ║ Desciription:																		║
// ║  Class used to create a secondary render target to be used as shadow map			║
// ║  for the shadowing of geometry.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../Misc/Inclusions.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class ShadowMap
{
	public:
		ShadowMap(ID3D11Device* p_device, int p_width, int p_height);
		~ShadowMap();

		void SetAsRenderTarget(ID3D11DeviceContext* p_deviceContext);
		void Clear(ID3D11DeviceContext* p_deviceContext);

		ID3D11ShaderResourceView* GetShadowMap();

	private:
		ID3D11Texture2D* m_shadowMap;
		ID3D11RenderTargetView* m_shadowMapTargetView;
		ID3D11ShaderResourceView* m_shadowMapResourceView;

		ID3D11Texture2D* m_depthStencil;
		ID3D11DepthStencilView*	m_depthStencilView;
};