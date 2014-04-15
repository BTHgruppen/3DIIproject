// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Camera.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-07-10																║
// ║																					║
// ║ Desciription:																		║
// ║  A camera used to generate rendering matrices like the view and projection			║
// ║  matrices.																			║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Camera.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Camera::Camera()
{
	m_position = D3DXVECTOR3(0, 0, 0);
	m_target = D3DXVECTOR3(0, 0, 0);
	m_upVector = D3DXVECTOR3(0, 0, 0);

	m_fieldOfView = 0;
	m_aspectRatio = 0;
	m_nearPlane = 0;
	m_farPlane = 0;

	D3DXMatrixIdentity(&m_viewMatrix);
	D3DXMatrixIdentity(&m_projectionMatrix);	
}

Camera::~Camera()
{

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Camera variable update function.													║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Camera::UpdatePosition(D3DXVECTOR3 p_position)
{
	// Set the camera position.
	m_position = p_position;
}

void Camera::UpdateTarget(D3DXVECTOR3 p_target)
{
	// Set the camera target.
	m_target = p_target;
}

void Camera::UpdateUpVector(D3DXVECTOR3 p_upVector)
{
	// Set the camera up vector.
	m_upVector = p_upVector;
}

void Camera::UpdateFieldOfView(float p_fieldOfView)
{
	// Set the camera field of view.
	m_fieldOfView = p_fieldOfView;
}

void Camera::UpdateAspectRatio(float p_aspectRatio)
{
	// Set the camera aspect ratio.
	m_aspectRatio = p_aspectRatio;
}

void Camera::UpdateClippingPlanes(float p_nearPlane, float p_farPlane)
{
	// Set clipping planes.
	m_nearPlane = p_nearPlane;
	m_farPlane = p_farPlane;
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Camera matrix update function.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Camera::UpdateMatrices()
{
	// Update view matrix.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_target, &m_upVector);

	// Update projection matrix.
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Camera get functions.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
D3DXVECTOR3 Camera::GetPosition()
{
	// Return view matrix
	return m_position;
}

D3DXMATRIX Camera::GetViewMatrix()
{
	// Return view matrix
	return m_viewMatrix;
}

D3DXMATRIX Camera::GetProjectionMatrix()
{
	// Return projection matrix.
	return m_projectionMatrix;
}