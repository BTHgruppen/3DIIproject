// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Plane.cpp																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-03																║
// ║																					║
// ║ Desciription:																		║
// ║  Test renderable object, plane.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Plane.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Plane::Plane(DirectX* p_directXHandle)
{
	// Setup main plane parts.
	D3DXVECTOR3 l_positions[4] = 
	{
		D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(1, 0, 0), 
		D3DXVECTOR3(0, 0, -1), 
		D3DXVECTOR3(1, 0, -1)
	};

	D3DXVECTOR2 l_textureCoordinates[4] = 
	{
		D3DXVECTOR2(0, 0), 
		D3DXVECTOR2(1, 0), 
		D3DXVECTOR2(0, 1), 
		D3DXVECTOR2(1, 1)
	};

	D3DXVECTOR3 l_normals[2] = 
	{
		D3DXVECTOR3(0, 1, 0), 
		D3DXVECTOR3(0, -1, 0)
	};

	// Build plane.
	m_plane = new Object(p_directXHandle);
	vector<Vertex> l_planeMesh;
	Vertex l_planeVertex;

	// Top.
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[0], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[1], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[2], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[1], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[3], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[2], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);

	// Bottom.
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[0], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[1], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[2], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[1], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[3], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[2], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);

	// Set mesh and texture.
	m_plane -> SetMesh(l_planeMesh);
	m_plane -> SetTexture("Textures/Plane.png");
}

Plane::~Plane()
{
	if(m_plane)
	{
		delete m_plane;
		m_plane = 0;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Object update function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Plane::Update(float p_deltaTime)
{

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Object render functions.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Plane::Render(ID3D11ShaderResourceView* p_shadowMap)
{
	m_plane -> Render(p_shadowMap);
}

void Plane::RenderDepth()
{
	m_plane -> RenderDepth();
}