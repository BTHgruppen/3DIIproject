// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: ShaderBridge.cpp															║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-05-09																║
// ║																					║
// ║ Desciription:																		║
// ║  Shader bridge, used to render scenes.												║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Shader.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Shader::Shader(ID3D11Device* p_device, HWND p_windowHandle) 
{
	// Set variables to initial values.
	m_matrixBuffer			= 0;
	m_lightSourceBuffer		= 0;
	m_lightBuffer			= 0;
	m_vertexShader			= 0;
	m_pixelShader			= 0;
	m_layout				= 0;
	m_samplerState			= 0;
	m_shadowMapSamplerState = 0;
	m_rasterizerState		= 0;

	// Compile and create the shaders.
	CreateVertexShader(p_device);
	CreatePixelShader(p_device);

	// Create the states.
	CreateRasterizerState(p_device);
	CreateSamplerStates(p_device);

	// Setup buffers.
	SetupBuffers(p_device);
}

Shader::~Shader()
{

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Vertex shader compilation and creation.											║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::CreateVertexShader(ID3D11Device* p_device)
{
	// Set variables to initial values.
	ID3D10Blob*	l_vertexShader = 0;
	ID3D10Blob*	l_errorMessage = 0;

	// Compile the vertex shader.
	if(FAILED(D3DX10CompileFromFileA("Shaders/VertexShader.hlsl", NULL, NULL, "main", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &l_vertexShader, &l_errorMessage, NULL)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCompilation of vertex shader failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreateVertexShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
	
	// Create the vertex shader.
	if(FAILED(p_device -> CreateVertexShader(l_vertexShader -> GetBufferPointer(), l_vertexShader -> GetBufferSize(), NULL, &m_vertexShader)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of vertex shader failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreateVertexShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Set variables to initial values.
	D3D11_INPUT_ELEMENT_DESC l_layout[3];
	unsigned int l_size;

	// Configure vertex layout.
	l_layout[0].SemanticName			= "POSITION";
	l_layout[0].SemanticIndex			= 0;
	l_layout[0].Format					= DXGI_FORMAT_R32G32B32_FLOAT;
	l_layout[0].InputSlot				= 0;
	l_layout[0].AlignedByteOffset		= 0;
	l_layout[0].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
	l_layout[0].InstanceDataStepRate	= 0;
	
	l_layout[1].SemanticName			= "TEXCOORD";
	l_layout[1].SemanticIndex			= 0;
	l_layout[1].Format					= DXGI_FORMAT_R32G32_FLOAT;
	l_layout[1].InputSlot				= 0;
	l_layout[1].AlignedByteOffset		= D3D11_APPEND_ALIGNED_ELEMENT;
	l_layout[1].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
	l_layout[1].InstanceDataStepRate	= 0;

	l_layout[2].SemanticName			= "NORMAL";
	l_layout[2].SemanticIndex			= 0;
	l_layout[2].Format					= DXGI_FORMAT_R32G32B32_FLOAT;
	l_layout[2].InputSlot				= 0;
	l_layout[2].AlignedByteOffset		= D3D11_APPEND_ALIGNED_ELEMENT;
	l_layout[2].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
	l_layout[2].InstanceDataStepRate	= 0;

	// Compute size of layout.
	l_size = sizeof(l_layout) / sizeof(l_layout[0]);

	// Create the vertex input layout.
	if(FAILED(p_device -> CreateInputLayout(l_layout, l_size, l_vertexShader -> GetBufferPointer(), l_vertexShader -> GetBufferSize(), &m_layout)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of vertex layout failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreateVertexShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Release the shader.
	l_vertexShader -> Release();
	l_vertexShader = 0;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Pixel shader compilation and creation.												║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::CreatePixelShader(ID3D11Device* p_device)
{
	// Set variables to initial values.
	ID3D10Blob*	l_pixelShader	= 0;
	ID3D10Blob* l_errorMessage	= 0;

	// Compile the pixel shader.
	if(FAILED(D3DX10CompileFromFileA("Shaders/PixelShader.hlsl", NULL, NULL, "main", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &l_pixelShader, &l_errorMessage, NULL)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCompilation of pixel shader failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreatePixelShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Create the pixel shader.
	if(FAILED(p_device -> CreatePixelShader(l_pixelShader -> GetBufferPointer(), l_pixelShader -> GetBufferSize(), NULL, &m_pixelShader)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of pixel shader failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreatePixelShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Rasterizer state creation.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::CreateRasterizerState(ID3D11Device* p_device)
{
	// Create the rasterizer description.
	D3D11_RASTERIZER_DESC l_rasterizerDescription;
	l_rasterizerDescription.FillMode				= D3D11_FILL_SOLID;
	l_rasterizerDescription.CullMode				= D3D11_CULL_BACK;
	l_rasterizerDescription.FrontCounterClockwise	= false;
	l_rasterizerDescription.DepthBias				= 0;
	l_rasterizerDescription.SlopeScaledDepthBias	= 0.0f;
	l_rasterizerDescription.DepthBiasClamp			= 0.0f;
	l_rasterizerDescription.DepthClipEnable			= true;
	l_rasterizerDescription.ScissorEnable			= false;
	l_rasterizerDescription.MultisampleEnable		= false;
	l_rasterizerDescription.AntialiasedLineEnable	= false;
	
	// Create the rasterizer state.
	if(FAILED(p_device -> CreateRasterizerState(&l_rasterizerDescription, &m_rasterizerState)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of rasterizer state failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreatePixelShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Sampler state creation.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::CreateSamplerStates(ID3D11Device* p_device)
{
	// Create the sampler state description.
	D3D11_SAMPLER_DESC l_samplerDescription;
	l_samplerDescription.Filter				= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	l_samplerDescription.AddressU			= D3D11_TEXTURE_ADDRESS_WRAP;
	l_samplerDescription.AddressV			= D3D11_TEXTURE_ADDRESS_WRAP;
	l_samplerDescription.AddressW			= D3D11_TEXTURE_ADDRESS_WRAP;
	l_samplerDescription.MipLODBias			= 0.0f;
	l_samplerDescription.MaxAnisotropy		= 1;
	l_samplerDescription.ComparisonFunc		= D3D11_COMPARISON_ALWAYS;
	l_samplerDescription.BorderColor[0]		= 0;
	l_samplerDescription.BorderColor[1]		= 0;
	l_samplerDescription.BorderColor[2]		= 0;
	l_samplerDescription.BorderColor[3]		= 0;
	l_samplerDescription.MinLOD				= 0;
	l_samplerDescription.MaxLOD				= D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	if(FAILED(p_device -> CreateSamplerState(&l_samplerDescription, &m_samplerState)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of sampler state failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreateSamplerStates", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Create the shadow map sampler state description.
	l_samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	l_samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	l_samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	// Create the shadow map sampler state.
	if(FAILED(p_device -> CreateSamplerState(&l_samplerDescription, &m_shadowMapSamplerState)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of shadow map sampler state failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nCreateSamplerStates", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Matrix Buffer creation.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::SetupBuffers(ID3D11Device* p_device)
{
	// Create the matrix buffer description.
	D3D11_BUFFER_DESC l_matrixBufferDescription;
	l_matrixBufferDescription.Usage					= D3D11_USAGE_DYNAMIC;
	l_matrixBufferDescription.ByteWidth				= sizeof(MatrixBuffer);
	l_matrixBufferDescription.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
	l_matrixBufferDescription.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	l_matrixBufferDescription.MiscFlags				= 0;
	l_matrixBufferDescription.StructureByteStride	= 0;

	// Create the matrix buffer.
	if(FAILED(p_device -> CreateBuffer(&l_matrixBufferDescription, NULL, &m_matrixBuffer)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of matrix buffer failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nSetupBuffers", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Create the light source buffer description.
	D3D11_BUFFER_DESC l_lightSourceBufferDescription;
	l_lightSourceBufferDescription.Usage				= D3D11_USAGE_DYNAMIC;
	l_lightSourceBufferDescription.ByteWidth			= sizeof(LightSourceBuffer);
	l_lightSourceBufferDescription.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	l_lightSourceBufferDescription.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	l_lightSourceBufferDescription.MiscFlags			= 0;
	l_lightSourceBufferDescription.StructureByteStride	= 0;

	// Create the light buffer.
	if(FAILED(p_device -> CreateBuffer(&l_lightSourceBufferDescription, NULL, &m_lightSourceBuffer)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of light source buffer failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nSetupBuffers", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Create the light buffer description.
	D3D11_BUFFER_DESC l_lightBufferDescription;
	l_lightBufferDescription.Usage					= D3D11_USAGE_DYNAMIC;
	l_lightBufferDescription.ByteWidth				= sizeof(LightBuffer);
	l_lightBufferDescription.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
	l_lightBufferDescription.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
	l_lightBufferDescription.MiscFlags				= 0;
	l_lightBufferDescription.StructureByteStride	= 0;

	// Create the light buffer.
	if(FAILED(p_device -> CreateBuffer(&l_lightBufferDescription, NULL, &m_lightBuffer)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of light buffer failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nSetupBuffers", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Set buffer data																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::SetMatrices(D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projectionMatrix)
{
	D3DXMatrixTranspose(&p_viewMatrix, &p_viewMatrix);
	D3DXMatrixTranspose(&p_projectionMatrix, &p_projectionMatrix);

	m_viewMatrix = p_viewMatrix;
	m_projectionMatrix = p_projectionMatrix;
}

void Shader::SetLightMatrices(D3DXMATRIX p_lightViewMatrix, D3DXMATRIX p_lightProjectionMatrix)
{
	D3DXMatrixTranspose(&p_lightViewMatrix, &p_lightViewMatrix);
	D3DXMatrixTranspose(&p_lightProjectionMatrix, &p_lightProjectionMatrix);

	m_lightViewMatrix = p_lightViewMatrix;
	m_lightProjectionMatrix = p_lightProjectionMatrix;
}

void Shader::SetPointLight(PointLight p_pointLight)
{
	m_pointLight = p_pointLight;
}

void Shader::SetMaterial(Material p_material)
{
	m_material = p_material;
}

void Shader::SetCameraPosition(D3DXVECTOR3 p_cameraPosition)
{
	m_cameraPosition = p_cameraPosition;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Render functions.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Shader::RenderIndexed(ID3D11DeviceContext* p_deviceContext, int p_indexCount, D3DXMATRIX p_worldMatrix, ID3D11ShaderResourceView* p_texture, ID3D11ShaderResourceView* p_shadowMap)
{
	// Set parameters needed to render.
	if(FAILED(SetParameters(p_deviceContext, p_worldMatrix, p_texture, p_shadowMap)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nSetting of parameters for indexed rendering failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nRenderIndexed", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Render indexed.
	p_deviceContext -> IASetInputLayout(m_layout);
	p_deviceContext -> VSSetShader(m_vertexShader, NULL, 0);
	p_deviceContext -> PSSetShader(m_pixelShader, NULL, 0);
	p_deviceContext -> PSSetSamplers(0, 1, &m_samplerState);
	p_deviceContext -> PSSetSamplers(1, 1, &m_shadowMapSamplerState);
	p_deviceContext -> DrawIndexed(p_indexCount, 0, 0);
}

void Shader::Render(ID3D11DeviceContext* p_deviceContext, int p_vertexCount, D3DXMATRIX p_worldMatrix, ID3D11ShaderResourceView* p_texture, ID3D11ShaderResourceView* p_shadowMap)
{
	// Set parameters needed to render.
	if(FAILED(SetParameters(p_deviceContext, p_worldMatrix, p_texture, p_shadowMap)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nSetting of parameters for unindexed rendering failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nRenderIndexed", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Render unindexed.
	p_deviceContext -> IASetInputLayout(m_layout);
	p_deviceContext -> VSSetShader(m_vertexShader, NULL, 0);
	p_deviceContext -> PSSetShader(m_pixelShader, NULL, 0);
	p_deviceContext -> PSSetSamplers(0, 1, &m_samplerState);
	p_deviceContext -> PSSetSamplers(1, 1, &m_shadowMapSamplerState);
	p_deviceContext -> Draw(p_vertexCount, 0);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Set shader parameter data.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
HRESULT Shader::SetParameters(ID3D11DeviceContext* p_deviceContext, D3DXMATRIX p_worldMatrix, ID3D11ShaderResourceView* p_texture, ID3D11ShaderResourceView* p_shadowMap)
{
	// Transpose the world matrix.
	D3DXMatrixTranspose(&m_worldMatrix, &p_worldMatrix);

	// Lock matrix buffer so that it can be written to.
	D3D11_MAPPED_SUBRESOURCE l_mappedMatrixResource;
	if(FAILED(p_deviceContext -> Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &l_mappedMatrixResource)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nMapping of matrix buffer failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nSetParameters", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return E_FAIL;
	}

	// Get pointer to the matrix buffer data.
	MatrixBuffer* l_matrixBuffer;
	l_matrixBuffer = (MatrixBuffer*)l_mappedMatrixResource.pData;

	// Set matrices in buffer.
	l_matrixBuffer -> m_worldMatrix				= m_worldMatrix;
	l_matrixBuffer -> m_viewMatrix				= m_viewMatrix;
	l_matrixBuffer -> m_projectionMatrix		= m_projectionMatrix;
	l_matrixBuffer -> m_lightViewMatrix			= m_lightViewMatrix;
	l_matrixBuffer -> m_lightProjectionMatrix	= m_lightProjectionMatrix;

	// Unlock the matrix buffer after it has been written to.
	p_deviceContext -> Unmap(m_matrixBuffer, 0);

	// Set the matrix buffer.
	p_deviceContext -> VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	// Lock light source buffer so that it can be written to.
	D3D11_MAPPED_SUBRESOURCE l_mappedLightSourceResource;
	if(FAILED(p_deviceContext -> Map(m_lightSourceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &l_mappedLightSourceResource)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nMapping of light source buffer failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nSetParameters", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return E_FAIL;
	}

	// Get pointer to the light source buffer data.
	LightSourceBuffer* l_lightSourceBuffer;
	l_lightSourceBuffer = (LightSourceBuffer*)l_mappedLightSourceResource.pData;

	// Set matrices in buffer.
	l_lightSourceBuffer -> m_lightPosition = m_pointLight.m_lightPosition;
	l_lightSourceBuffer -> m_padding = 0.0f;

	// Unlock the matrix buffer after it has been written to.
	p_deviceContext -> Unmap(m_lightSourceBuffer, 0);

	// Set the matrix buffer.
	p_deviceContext -> VSSetConstantBuffers(1, 1, &m_lightSourceBuffer);

	// Lock light buffer so that it can be written to.
	D3D11_MAPPED_SUBRESOURCE l_mappedLightResource;
	if(FAILED(p_deviceContext -> Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &l_mappedLightResource)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nMapping of light buffer failed.\n\nFILE:\nShaders.cpp\n\nFUNCTION:\nSetParameters", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return E_FAIL;
	}

	// Get pointer to the light buffer data.
	LightBuffer* l_lightBuffer;
	l_lightBuffer = (LightBuffer*)l_mappedLightResource.pData;

	// Set light data in buffer.
	l_lightBuffer -> m_pointLight = m_pointLight;
	l_lightBuffer -> m_material = m_material;
	l_lightBuffer -> m_cameraPosition = m_cameraPosition;

	// Unlock the light buffer after it has been written to.
	p_deviceContext -> Unmap(m_lightBuffer, 0);

	// Set the light buffer.
	p_deviceContext -> PSSetConstantBuffers(0, 1, &m_lightBuffer);

	// Set the textures.
	p_deviceContext -> PSSetShaderResources(0, 1, &p_texture);
	p_deviceContext -> PSSetShaderResources(1, 1, &p_shadowMap);
	
	// Set the rasterizer state.
	p_deviceContext -> RSSetState(m_rasterizerState);

	return S_OK;
}