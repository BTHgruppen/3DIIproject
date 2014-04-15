// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Cube.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-08-03																║
// ║																					║
// ║ Desciription:																		║
// ║  Test renderable object, cube.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../Object.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Cube
{
	public:
		// functions:
		 Cube(DirectX* p_directXHandle);
		~Cube();

		void Update(float p_deltaTime);
		void Render(ID3D11ShaderResourceView* p_shadowMap);
		void RenderDepth();

		Object* m_cube;
};