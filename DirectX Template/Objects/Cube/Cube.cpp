// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Cube.cpp																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-03																║
// ║																					║
// ║ Desciription:																		║
// ║  Test renderable object, cube.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Cube.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Cube::Cube(DirectX* p_directXHandle)
{
	// Setup main cube parts.
	D3DXVECTOR3 l_positions[8] = 
	{
		D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(1, 0, 0), 
		D3DXVECTOR3(0, 0, -1), 
		D3DXVECTOR3(1, 0, -1), 
		D3DXVECTOR3(0, 1, 0), 
		D3DXVECTOR3(1, 1, 0), 
		D3DXVECTOR3(0, 1, -1), 
		D3DXVECTOR3(1, 1, -1)
	};

	D3DXVECTOR2 l_textureCoordinates[4] = 
	{
		D3DXVECTOR2(0, 0), 
		D3DXVECTOR2(1, 0), 
		D3DXVECTOR2(0, 1), 
		D3DXVECTOR2(1, 1)
	};

	D3DXVECTOR3 l_normals[6] = 
	{
		D3DXVECTOR3(1, 0, 0), 
		D3DXVECTOR3(-1, 0, 0),
		D3DXVECTOR3(0, 1, 0),
		D3DXVECTOR3(0, -1, 0), 
		D3DXVECTOR3(0, 0, 1), 
		D3DXVECTOR3(0, 0, -1)
	};

	// Build cube.
	m_cube = new Object(p_directXHandle);
	vector<Vertex> l_planeMesh;
	Vertex l_planeVertex;

	// Top.
	l_planeVertex = Vertex(l_positions[4], l_textureCoordinates[0], l_normals[2]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[5], l_textureCoordinates[1], l_normals[2]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[6], l_textureCoordinates[2], l_normals[2]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[5], l_textureCoordinates[1], l_normals[2]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[7], l_textureCoordinates[3], l_normals[2]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[6], l_textureCoordinates[2], l_normals[2]);
	l_planeMesh.push_back(l_planeVertex);

	// Bottom.
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[0], l_normals[3]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[1], l_normals[3]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[2], l_normals[3]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[1], l_normals[3]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[3], l_normals[3]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[2], l_normals[3]);
	l_planeMesh.push_back(l_planeVertex);

	// Front.
	l_planeVertex = Vertex(l_positions[6], l_textureCoordinates[0], l_normals[5]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[7], l_textureCoordinates[1], l_normals[5]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[2], l_normals[5]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[7], l_textureCoordinates[1], l_normals[5]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[3], l_normals[5]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[2], l_normals[5]);
	l_planeMesh.push_back(l_planeVertex);

	// Back.
	l_planeVertex = Vertex(l_positions[5], l_textureCoordinates[0], l_normals[4]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[4], l_textureCoordinates[1], l_normals[4]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[2], l_normals[4]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[4], l_textureCoordinates[1], l_normals[4]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[3], l_normals[4]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[2], l_normals[4]);
	l_planeMesh.push_back(l_planeVertex);

	// Right.
	l_planeVertex = Vertex(l_positions[7], l_textureCoordinates[0], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[5], l_textureCoordinates[1], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[2], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[5], l_textureCoordinates[1], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[1], l_textureCoordinates[3], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[3], l_textureCoordinates[2], l_normals[0]);
	l_planeMesh.push_back(l_planeVertex);

	// Left.
	l_planeVertex = Vertex(l_positions[4], l_textureCoordinates[0], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[6], l_textureCoordinates[1], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[2], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[6], l_textureCoordinates[1], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[2], l_textureCoordinates[3], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);
	l_planeVertex = Vertex(l_positions[0], l_textureCoordinates[2], l_normals[1]);
	l_planeMesh.push_back(l_planeVertex);

	// Set mesh and texture.
	m_cube -> SetMesh(l_planeMesh);
	m_cube -> SetTexture("Textures/Cube.png");
}

Cube::~Cube()
{
	if(m_cube)
	{
		delete m_cube;
		m_cube = 0;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Object update function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Cube::Update(float p_deltaTime)
{
	m_cube -> Rotate(D3DXVECTOR3(0.0f, p_deltaTime, 0.0f));
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Object render function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Cube::Render(ID3D11ShaderResourceView* p_shadowMap)
{
	m_cube -> Render(p_shadowMap);
}

void Cube::RenderDepth()
{
	m_cube -> RenderDepth();
}