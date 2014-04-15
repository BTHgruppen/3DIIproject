// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: DepthShader.h															║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-28																║
// ║																					║
// ║ Desciription:																		║
// ║  Depth shader bridge, used to render depth data to a shadow map.					║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../../Misc/Inclusions.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class DepthShader
{
	public:
		// Functions.
		DepthShader(ID3D11Device* p_device, HWND p_windowHandle);
		~DepthShader();

		void SetMatrices(D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projectionMatrix);

		void Render(ID3D11DeviceContext* p_deviceContext, int p_vertexCount, D3DXMATRIX p_worldMatrix);
		void RenderIndexed(ID3D11DeviceContext* p_deviceContext, int p_indexCount, D3DXMATRIX p_worldMatrix);

	private:
		// Variables.
		struct MatrixBuffer
		{
			D3DXMATRIX m_worldMatrix;
			D3DXMATRIX m_viewMatrix;
			D3DXMATRIX m_projectionMatrix;
		};

		D3DXMATRIX m_worldMatrix;
		D3DXMATRIX m_viewMatrix;
		D3DXMATRIX m_projectionMatrix;

		ID3D11Buffer* m_matrixBuffer;

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		
		ID3D11InputLayout* m_layout;

		// Functions.
		void CreateVertexShader(ID3D11Device* p_device);
		void CreatePixelShader(ID3D11Device* p_device);
		void SetupBuffer(ID3D11Device* p_device);

		HRESULT SetParameters(ID3D11DeviceContext* p_deviceContext, D3DXMATRIX p_worldMatrix);
};