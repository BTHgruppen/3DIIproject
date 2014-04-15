// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Object.cpp																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-07-10																║
// ║																					║
// ║ Desciription:																		║
// ║  General template for renderable objects.											║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Object.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Object::Object(DirectX* p_directXHandle)
{
	// Setup initial values for variables.
	m_vertexBuffer = 0;
	m_texture = 0;
	m_mesh.clear();

	ResetObject();

	m_handle = p_directXHandle;
	m_shader = p_directXHandle -> GetShader();
	m_depthShader = p_directXHandle -> GetDepthShader();
}

Object::~Object()
{

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Texture loader.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Object::SetTexture(const char* p_filepath)
{
	D3DX11CreateShaderResourceViewFromFileA(m_handle -> GetDevice(), p_filepath, NULL, NULL, &m_texture, NULL);
}

void Object::SetTexture(ID3D11ShaderResourceView* p_texture)
{
	m_texture = p_texture;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Mesh setting and buffer creation.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Object::SetMesh(vector<Vertex> p_mesh)
{
	// Set the mesh.
	m_mesh = p_mesh;
	
	// Setup vertex buffer description.
	D3D11_BUFFER_DESC l_vertexBufferDescription;
	l_vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	l_vertexBufferDescription.ByteWidth = sizeof(Vertex) * m_mesh.size();
	l_vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	l_vertexBufferDescription.CPUAccessFlags = 0;
	l_vertexBufferDescription.MiscFlags = 0;
	l_vertexBufferDescription.StructureByteStride = 0;

	// Setup vertex buffer data.
	D3D11_SUBRESOURCE_DATA l_vertexData;
	l_vertexData.pSysMem = m_mesh.data();
	l_vertexData.SysMemPitch = 0;
	l_vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	m_handle -> GetDevice() -> CreateBuffer(&l_vertexBufferDescription, &l_vertexData, &m_vertexBuffer);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Object render functions.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Object::Render(ID3D11ShaderResourceView* p_shadowMap)
{
	// Set stride and offset.
	unsigned int l_stride = sizeof(Vertex);
	unsigned int l_offset = 0;

	// Set vertex buffer and topology.
	m_handle -> GetDeviceContext() -> IASetVertexBuffers(0, 1, &m_vertexBuffer, &l_stride, &l_offset);
	m_handle -> GetDeviceContext() -> IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Render the object.
	m_shader -> Render(m_handle -> GetDeviceContext(), m_mesh.size(), m_worldMatrix, m_texture, p_shadowMap);
}

void Object::RenderDepth()
{
	// Set stride and offset.
	unsigned int l_stride = sizeof(Vertex);
	unsigned int l_offset = 0;

	// Set vertex buffer and topology.
	m_handle -> GetDeviceContext() -> IASetVertexBuffers(0, 1, &m_vertexBuffer, &l_stride, &l_offset);
	m_handle -> GetDeviceContext() -> IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Render the object.
	m_depthShader -> Render(m_handle -> GetDeviceContext(), m_mesh.size(), m_worldMatrix);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Mesh manipulations.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Object::Rotate(D3DXVECTOR3 p_rotation)
{
	D3DXMATRIX l_matrix;
	D3DXMatrixRotationYawPitchRoll(&l_matrix, p_rotation.y, p_rotation.x, p_rotation.z);
	m_worldMatrix = m_worldMatrix * l_matrix;
}

void Object::Translate(D3DXVECTOR3 p_translation)
{
	D3DXMATRIX l_matrix;
	D3DXMatrixTranslation(&l_matrix, p_translation.x, p_translation.y, p_translation.z);
	m_worldMatrix = m_worldMatrix * l_matrix;
}

void Object::Scale(D3DXVECTOR3 p_scale)
{
	D3DXMATRIX l_matrix;
	D3DXMatrixScaling(&l_matrix, p_scale.x, p_scale.y, p_scale.z);
	m_worldMatrix = m_worldMatrix * l_matrix;
}

void Object::ResetObject()
{
	D3DXMatrixIdentity(&m_worldMatrix);	
}