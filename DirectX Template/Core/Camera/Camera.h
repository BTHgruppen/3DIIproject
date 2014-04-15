// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Camera.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-07-10																║
// ║																					║
// ║ Desciription:																		║
// ║  Main game camera used in rendering.												║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../Misc/Inclusions.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Camera
{
	public:
		// functions:
		Camera();
		~Camera();

		void UpdateMatrices();

		void UpdatePosition(D3DXVECTOR3 p_position);
		void UpdateTarget(D3DXVECTOR3 p_target);
		void UpdateUpVector(D3DXVECTOR3 p_upVector);

		void UpdateFieldOfView(float p_fieldOfView);
		void UpdateAspectRatio(float p_aspectRatio);
		void UpdateClippingPlanes(float p_nearPlane, float p_farPlane);

		D3DXVECTOR3 GetPosition();
		D3DXMATRIX GetViewMatrix();
		D3DXMATRIX GetProjectionMatrix();
		
	private:
		// variables:
		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_target;
		D3DXVECTOR3 m_upVector;

		float m_fieldOfView;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;

		D3DXMATRIX m_viewMatrix;
		D3DXMATRIX m_projectionMatrix;
};