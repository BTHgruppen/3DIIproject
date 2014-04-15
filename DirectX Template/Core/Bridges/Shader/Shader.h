// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: ShaderBridge.h															║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-05-09																║
// ║																					║
// ║ Desciription:																		║
// ║  Shader bridge, used to render scenes.												║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../../Misc/Inclusions.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Shader
{
public:
	public:
		// Functions:
		Shader(ID3D11Device* p_device, HWND p_windowHandle);
		~Shader();

		void SetMatrices(D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projectionMatrix);
		void SetLightMatrices(D3DXMATRIX p_lightViewMatrix, D3DXMATRIX p_lightProjectionMatrix);
		void SetPointLight(PointLight p_pointLight);
		void SetMaterial(Material p_material);
		void SetCameraPosition(D3DXVECTOR3 p_cameraPosition);

		void RenderIndexed(ID3D11DeviceContext* p_deviceContext, int p_indexCount, D3DXMATRIX p_worldMatrix, ID3D11ShaderResourceView* p_texture, ID3D11ShaderResourceView* p_shadowMap);
		void Render(ID3D11DeviceContext* p_deviceContext, int p_vertexCount, D3DXMATRIX p_worldMatrix, ID3D11ShaderResourceView* p_texture, ID3D11ShaderResourceView* p_shadowMap);

	private:
		// Variables:
		struct MatrixBuffer
		{
			D3DXMATRIX m_worldMatrix;
			D3DXMATRIX m_viewMatrix;
			D3DXMATRIX m_projectionMatrix;

			D3DXMATRIX m_lightViewMatrix;
			D3DXMATRIX m_lightProjectionMatrix;
		};

		struct LightSourceBuffer
		{
			D3DXVECTOR3  m_lightPosition;
			float m_padding;
		};

		struct LightBuffer
		{
			PointLight m_pointLight;
			Material m_material;
			D3DXVECTOR3 m_cameraPosition;
			float m_padding;
		};

		PointLight m_pointLight;
		Material m_material;

		D3DXVECTOR3 m_cameraPosition;
		D3DXMATRIX m_worldMatrix;
		D3DXMATRIX m_viewMatrix;
		D3DXMATRIX m_projectionMatrix;

		D3DXMATRIX m_lightViewMatrix;
		D3DXMATRIX m_lightProjectionMatrix;

		ID3D11Buffer* m_matrixBuffer;
		ID3D11Buffer* m_lightSourceBuffer;
		ID3D11Buffer* m_lightBuffer;

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;

		ID3D11InputLayout* m_layout;
		ID3D11SamplerState* m_samplerState;
		ID3D11SamplerState* m_shadowMapSamplerState;
		ID3D11RasterizerState* m_rasterizerState;

		// Functions:
		void CreateVertexShader(ID3D11Device* p_device);
		void CreatePixelShader(ID3D11Device* p_device);
		void CreateRasterizerState(ID3D11Device* p_device);
		void CreateSamplerStates(ID3D11Device* p_device);
		void SetupBuffers(ID3D11Device* p_device);

		HRESULT SetParameters(ID3D11DeviceContext* p_deviceContext, D3DXMATRIX p_worldMatrix, ID3D11ShaderResourceView* p_texture, ID3D11ShaderResourceView* p_shadowMap);
};