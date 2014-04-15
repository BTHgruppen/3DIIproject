// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Plane.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-03																║
// ║																					║
// ║ Desciription:																		║
// ║  Test renderable object, plane.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../Object.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Plane
{
	public:
		// functions:
		 Plane(DirectX* p_directXHandle);
		~Plane();

		void Update(float p_deltaTime);
		void Render(ID3D11ShaderResourceView* p_shadowMap);
		void RenderDepth();

		Object* m_plane;
};