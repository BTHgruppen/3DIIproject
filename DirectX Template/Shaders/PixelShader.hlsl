// Dependencies
#include "LightingShader.hlsl"

// Variables.
Texture2D m_texture;
Texture2D m_shadowMap;

SamplerState m_sampler;
SamplerState m_shadowMapSampler;

// Light buffer.
cbuffer LightBuffer
{
	PointLight m_pointLight;
	Material m_material;
	float3 m_cameraPosition;
	float m_padding;
};

// Vertex structure.
struct Vertex
{
	float4 m_positionH : SV_POSITION;
	float4 m_positionW : POSITION;
	float2 m_textureCoordinate : TEXCOORD0;
	float3 m_normal : NORMAL; 

	float4 m_lightPositionH : TEXCOORD1;
    float3 m_lightPositionW : TEXCOORD2;
};

// Pixel shader function.
float4 main(Vertex p_input) : SV_Target
{
	// Set the bias adjustment to counteract the low floating point precision.
    float l_bias = 0.001f;
	
	// Initialize outputs values.
	float4 p_ambientValue  = m_material.m_ambientValue * m_pointLight.m_ambientValue;
	float4 p_diffuseValue  = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 p_specularValue = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Calculate the projected shadow map coordinates.
	float2 l_shadowMapCoordinates;
	l_shadowMapCoordinates.x = p_input.m_lightPositionH.x / p_input.m_lightPositionH.w / 2.0f + 0.5f;
    l_shadowMapCoordinates.y = -p_input.m_lightPositionH.y / p_input.m_lightPositionH.w / 2.0f + 0.5f;

	// Calculate if the coordinates are in the range 0 to 1. If they are then the pixel is lit.
    if((saturate(l_shadowMapCoordinates.x) == l_shadowMapCoordinates.x) && (saturate(l_shadowMapCoordinates.y) == l_shadowMapCoordinates.y))
    {
		// Sample the shadow map at the projected shadow map coordinates.
        float l_depth = m_shadowMap.Sample(m_shadowMapSampler, l_shadowMapCoordinates).r;

		// Calculate the depth of the light.
		float l_lightDepth  = p_input.m_lightPositionH.z / p_input.m_lightPositionH.w;
		
		// Subtract the bias from the depth value of the light.
        l_lightDepth = l_lightDepth - l_bias;

		// Compare the depth of the shadow map and the depth of the light to determine whether to shadow or to light this pixel.
        if(l_lightDepth < l_depth)
        {
			// Normalize input normal.
			p_input.m_normal = normalize(p_input.m_normal);

			// Normalize the surface to camera vector.
			float3 l_surfaceToCamera = normalize(m_cameraPosition - p_input.m_positionH);

			// Calculate point lighting.
			CalculatePointLight(m_pointLight, m_material, p_input.m_positionW.xyz, p_input.m_normal, l_surfaceToCamera, p_ambientValue, p_diffuseValue, p_specularValue);
		}
	}

	// Summarize lighting values.
	float4 l_lighting = p_ambientValue + p_diffuseValue + p_specularValue;
	l_lighting.a = m_material.m_diffuseValue.a;

	// Sample texture using texture coordinates.
	float4 l_color = m_texture.Sample(m_sampler, p_input.m_textureCoordinate);

	// Color and light pixel.
	float4 l_pixel = l_color * l_lighting;

	// Return shaded pixel.
	return l_pixel;
}