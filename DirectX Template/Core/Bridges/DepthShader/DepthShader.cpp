// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: DepthShader.cpp															║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-28																║
// ║																					║
// ║ Desciription:																		║
// ║  Depth shader bridge, used to render depth data to a shadow map.					║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "DepthShader.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
DepthShader::DepthShader(ID3D11Device* p_device, HWND p_windowHandle)
{
	// Set variables to initial values.
	m_matrixBuffer = 0;
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;

	// Compile and create the shaders.
	CreateVertexShader(p_device);
	CreatePixelShader(p_device);

	// Setup buffers.
	SetupBuffer(p_device);
}

DepthShader::~DepthShader()
{
	
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Depth vertex shader compilation and creation.										║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DepthShader::CreateVertexShader(ID3D11Device* p_device)
{
	// Set variables to initial values.
	ID3D10Blob*	l_vertexShader = 0;
	ID3D10Blob*	l_errorMessage = 0;

	// Compile the depth vertex shader.
	if(FAILED(D3DX11CompileFromFile("Shaders/DepthVertexShader.hlsl", NULL, NULL, "main", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &l_vertexShader, &l_errorMessage, NULL)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCompilation of depth vertex shader failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nCreateVertexShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Create the depth vertex shader.
    if(FAILED(p_device -> CreateVertexShader(l_vertexShader -> GetBufferPointer(), l_vertexShader -> GetBufferSize(), NULL, &m_vertexShader)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of depth vertex shader failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nCreateVertexShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Set variables to initial values.
	D3D11_INPUT_ELEMENT_DESC l_layout[1];
	unsigned int l_size;

	// Configure vertex layout.
	l_layout[0].SemanticName			= "POSITION";
	l_layout[0].SemanticIndex			= 0;
	l_layout[0].Format					= DXGI_FORMAT_R32G32B32_FLOAT;
	l_layout[0].InputSlot				= 0;
	l_layout[0].AlignedByteOffset		= 0;
	l_layout[0].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
	l_layout[0].InstanceDataStepRate	= 0;

	// Compute size of layout.
	l_size = sizeof(l_layout) / sizeof(l_layout[0]);

	// Create the depth vertex input layout.
	if(FAILED(p_device -> CreateInputLayout(l_layout, l_size, l_vertexShader -> GetBufferPointer(), l_vertexShader -> GetBufferSize(), &m_layout)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of depth vertex layout failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nCreateVertexShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Release the shader.
	l_vertexShader -> Release();
	l_vertexShader = 0;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Pixel depth shader compilation and creation.										║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DepthShader::CreatePixelShader(ID3D11Device* p_device)
{
	// Set variables to initial values.
	ID3D10Blob*	l_pixelShader	= 0;
	ID3D10Blob* l_errorMessage	= 0;

	// Compile the pixel shader code.
	if(FAILED(D3DX11CompileFromFile("Shaders/DepthPixelShader.hlsl", NULL, NULL, "main", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &l_pixelShader, &l_errorMessage, NULL)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCompilation of depth pixel shader failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nCreatePixelShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	 // Create the pixel depth shader.
    if(FAILED(p_device -> CreatePixelShader(l_pixelShader -> GetBufferPointer(), l_pixelShader -> GetBufferSize(), NULL, &m_pixelShader)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of depth pixel shader failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nCreatePixelShader", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Release the shader.
	l_pixelShader -> Release();
	l_pixelShader = 0;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Matrix Buffer creation.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DepthShader::SetupBuffer(ID3D11Device* p_device)
{
	// Setup matrix buffer description.
	D3D11_BUFFER_DESC l_matrixBufferDescription;
    l_matrixBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	l_matrixBufferDescription.ByteWidth = sizeof(MatrixBuffer);
    l_matrixBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    l_matrixBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    l_matrixBufferDescription.MiscFlags = 0;
	l_matrixBufferDescription.StructureByteStride = 0;

	// Create the constant buffer.
	if(FAILED(p_device -> CreateBuffer(&l_matrixBufferDescription, NULL, &m_matrixBuffer)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nCreation of matrix buffer failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nSetupBuffers", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Set buffer data																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DepthShader::SetMatrices(D3DXMATRIX p_viewMatrix, D3DXMATRIX p_projectionMatrix)
{
	D3DXMatrixTranspose(&p_viewMatrix, &p_viewMatrix);
	D3DXMatrixTranspose(&p_projectionMatrix, &p_projectionMatrix);

	m_viewMatrix = p_viewMatrix;
	m_projectionMatrix = p_projectionMatrix;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Render functions.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void DepthShader::RenderIndexed(ID3D11DeviceContext* p_deviceContext, int p_indexCount, D3DXMATRIX p_worldMatrix)
{
	// Set parameters needed to render.
	if(FAILED(SetParameters(p_deviceContext, p_worldMatrix)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nSetting of parameters for indexed rendering failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nRenderIndexed", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Render indexed.
	p_deviceContext -> IASetInputLayout(m_layout);
    p_deviceContext -> VSSetShader(m_vertexShader, NULL, 0);
    p_deviceContext -> PSSetShader(m_pixelShader, NULL, 0);
	p_deviceContext -> DrawIndexed(p_indexCount, 0, 0);
}

void DepthShader::Render(ID3D11DeviceContext* p_deviceContext, int p_vertexCount, D3DXMATRIX p_worldMatrix)
{
	// Set parameters needed to render.
	if(FAILED(SetParameters(p_deviceContext, p_worldMatrix)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nSetting of parameters for unindexed rendering failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nRenderIndexed", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Render unindexed.
	p_deviceContext -> IASetInputLayout(m_layout);
    p_deviceContext -> VSSetShader(m_vertexShader, NULL, 0);
    p_deviceContext -> PSSetShader(m_pixelShader, NULL, 0);
	p_deviceContext -> Draw(p_vertexCount, 0);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Set shader parameter data.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
HRESULT DepthShader::SetParameters(ID3D11DeviceContext* p_deviceContext, D3DXMATRIX p_worldMatrix)
{
	// Transpose the world matrix.
	D3DXMatrixTranspose(&m_worldMatrix, &p_worldMatrix);

	// Lock matrix buffer so that it can be written to.
	D3D11_MAPPED_SUBRESOURCE l_mappedMatrixResource;
	if(FAILED(p_deviceContext -> Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &l_mappedMatrixResource)))
	{
		// If this fails, an error message is displayed.
		MessageBox(NULL, "DESCRIPTION:\nMapping of matrix buffer failed.\n\nFILE:\nDepthShader.cpp\n\nFUNCTION:\nSetParameters", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return E_FAIL;
	}

	// Get pointer to the matrix buffer data.
	MatrixBuffer* l_matrixBuffer;
	l_matrixBuffer = (MatrixBuffer*)l_mappedMatrixResource.pData;

	// Set matrices in buffer.
	l_matrixBuffer -> m_worldMatrix		 = m_worldMatrix;
	l_matrixBuffer -> m_viewMatrix		 = m_viewMatrix;
	l_matrixBuffer -> m_projectionMatrix = m_projectionMatrix;

	// Unlock the matrix buffer after it has been written to.
	p_deviceContext -> Unmap(m_matrixBuffer, 0);

	// Set the matrix buffer.
	p_deviceContext -> VSSetConstantBuffers(0, 1, &m_matrixBuffer);
}