// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Inclusions.h																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-08																║
// ║																					║
// ║ Desciription:																		║
// ║  Global definitions of inclusion files, paths and structures.						║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Inclusions.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include <Windows.h>

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX11async.h>

#include <D3DX10math.h>

#include <string>
#include <vector>

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Namespace.																			║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

using namespace std;

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Structures.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

// Window struct, used by windows when creating application window.
struct Window
{
	// Variables.
	long x;
	long y;
	long width;
	long height;

	// Constructors.
	Window()
	{ 
		ZeroMemory(this, sizeof(this)); 
	}

	Window(long p_x, long p_y, long p_width, long p_height)
	{
		x = p_x;
		y = p_y;

		width = p_width;
		height = p_height;
	}
};

// Generall vertex struct used in rendering.
struct Vertex
{
	// Variables.
	D3DXVECTOR3 m_position;
	D3DXVECTOR2 m_textureCoordinates;
	D3DXVECTOR3 m_normal;

	// Constructors.
	Vertex()
	{
		ZeroMemory(this, sizeof(this)); 
	}

	Vertex(D3DXVECTOR3 p_position, D3DXVECTOR2 p_textureCoordinates, D3DXVECTOR3 p_normal)
	{
		m_position				= p_position;
		m_textureCoordinates	= p_textureCoordinates;
		m_normal				= p_normal;
	}
};

// Directional light source structure.
struct DirectionalLight
{
	// Variables.
	D3DXVECTOR4 m_ambientValue;
	D3DXVECTOR4 m_diffuseValue;
	D3DXVECTOR4 m_specularValue;

	D3DXVECTOR3 m_lightDirection;
	float m_padding;

	// Constructors.
	DirectionalLight() 
	{ 
		ZeroMemory(this, sizeof(this)); 
	}

	DirectionalLight(D3DXVECTOR4 p_ambientValue, D3DXVECTOR4 p_diffuseValue, D3DXVECTOR4 p_specularValue, D3DXVECTOR3 p_lightDirection) 
	{ 
		m_ambientValue		= p_ambientValue;
		m_diffuseValue		= p_diffuseValue;
		m_specularValue		= p_specularValue;
		m_lightDirection	= p_lightDirection; 
	}
};

// Point light source structure.
struct PointLight
{
	// Variables.
	D3DXVECTOR4 m_ambientValue;
	D3DXVECTOR4 m_diffuseValue;
	D3DXVECTOR4 m_specularValue;

	D3DXVECTOR3 m_lightAttenuation;
	float m_padding;

	D3DXVECTOR3 m_lightPosition;
	float m_range;

	// Constructors.
	PointLight() 
	{ 
		ZeroMemory(this, sizeof(this)); 
	}

	PointLight(D3DXVECTOR4 p_ambientValue, D3DXVECTOR4 p_diffuseValue, D3DXVECTOR4 p_specularValue, D3DXVECTOR3 p_lightAttenuation, D3DXVECTOR3 p_lightPosition) 
	{ 
		m_ambientValue		= p_ambientValue;
		m_diffuseValue		= p_diffuseValue;
		m_specularValue		= p_specularValue;
		m_lightAttenuation	= p_lightAttenuation; 
		m_lightPosition		= p_lightPosition;
	}
};

// Spotlight light source structure.
struct Spotlight
{
	// Variables.
	D3DXVECTOR4 m_ambientValue;
	D3DXVECTOR4 m_diffuseValue;
	D3DXVECTOR4 m_specularValue;

	D3DXVECTOR3 m_lightDirection;
	float m_spot;

	D3DXVECTOR3 m_lightAttenuation;
	float m_padding;

	D3DXVECTOR3 m_lightPosition;
	float m_range;

	// Constructors.
	Spotlight() 
	{ 
		ZeroMemory(this, sizeof(this)); 
	}

	Spotlight(D3DXVECTOR4 p_ambientValue, D3DXVECTOR4 p_diffuseValue, D3DXVECTOR4 p_specularValue, D3DXVECTOR3 p_lightDirection, D3DXVECTOR3 p_lightAttenuation, D3DXVECTOR3 p_lightPosition) 
	{ 
		m_ambientValue		= p_ambientValue;
		m_diffuseValue		= p_diffuseValue;
		m_specularValue		= p_specularValue;
		m_lightDirection	= p_lightDirection; 
		m_lightAttenuation	= p_lightAttenuation;
		m_lightPosition		= p_lightPosition;
	}
};

// Object material structure.
struct Material
{
	// Variables.
	D3DXVECTOR4 m_ambientValue;
	D3DXVECTOR4 m_diffuseValue;
	D3DXVECTOR4 m_specularValue;
	D3DXVECTOR4 m_reflectiveValue;

	// Constructors.
	Material() 
	{ 
		ZeroMemory(this, sizeof(this)); 
	}

	Material(D3DXVECTOR4 p_ambientValue, D3DXVECTOR4 p_diffuseValue, D3DXVECTOR4 p_specularValue, D3DXVECTOR4 p_reflectiveValue) 
	{ 
		m_ambientValue		= p_ambientValue;
		m_diffuseValue		= p_diffuseValue;
		m_specularValue		= p_specularValue;
		m_reflectiveValue	= p_reflectiveValue;
	}
};