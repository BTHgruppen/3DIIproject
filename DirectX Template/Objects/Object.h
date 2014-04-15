// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Object.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-07-10																║
// ║																					║
// ║ Desciription:																		║
// ║  General template for renderable objects.											║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../Misc/Inclusions.h"

#include "../Core/DirectX/DirectX.h"
#include "../Core/Bridges/Shader/Shader.h"
#include "../Core/Bridges/DepthShader/DepthShader.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Object
{
	public:
		// functions:
		 Object(DirectX* p_directXHandle);
		~Object();

		void SetTexture(const char* p_filepath);
		void SetTexture(ID3D11ShaderResourceView* p_texture);
		void SetMesh(vector<Vertex> p_mesh);

		void Rotate(D3DXVECTOR3 p_rotation);
		void Translate(D3DXVECTOR3 p_translation);
		void Scale(D3DXVECTOR3 p_scale);
		void ResetObject();

		void Render(ID3D11ShaderResourceView* p_shadowMap);
		void RenderDepth();

	protected:
		// variables:
		DirectX* m_handle;
		Shader* m_shader;
		DepthShader* m_depthShader;

		ID3D11ShaderResourceView* m_texture;
		vector<Vertex> m_mesh;
		ID3D11Buffer* m_vertexBuffer;

		D3DXMATRIX m_worldMatrix;
};