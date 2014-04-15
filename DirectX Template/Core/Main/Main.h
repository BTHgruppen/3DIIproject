// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Main.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-05																║
// ║																					║
// ║ Desciription:																		║
// ║  Main class of the program, the Win32 window used for rendering and the DirectX	║
// ║  interface are initialized by this class. 											║
// ║  Game logic updates and render commands are also called from here.					║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../Misc/Inclusions.h"

#include "../Win32/Win32.h"
#include "../DirectX/DirectX.h"
#include "../Camera/Camera.h"
#include "../Timer/Timer.h"
#include "../ShadowMap/ShadowMap.h"

#include "../../Objects/Cube/Cube.h"
#include "../../Objects/Plane/Plane.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Main
{
	public:
		// Functions:
		 Main(HINSTANCE p_instanceHandle, int p_show);
		~Main();

		int Run();

	private:
		// Variables:
		Win32* m_win32;
		DirectX* m_directX;
		Camera* m_camera;

		ShadowMap* m_shadowMap;

		Timer* m_timer;
		float m_deltaTime;

		Cube* m_cube;
		Plane* m_plane;

		PointLight m_pointLight;
		Camera* m_lightSource;
		Material m_material;

		// Functions:
		void Initialize(Window p_defaultWindow);
		void Update(float p_deltaTime);
		void Render();
		void RenderDepth();
		void HandleInput();
};