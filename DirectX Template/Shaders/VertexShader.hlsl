// Matrix buffer.
cbuffer MatrixBuffer
{
	matrix m_worldMatrix;
	matrix m_viewMatrix;
	matrix m_projectionMatrix;

	matrix m_lightViewMatrix;
	matrix m_lightProjectionMatrix;
};

// Light source buffer.
cbuffer LightSourceBuffer
{
    float3 m_lightPosition;
    float m_padding;
};


// Vertex structures.
struct VertexInput
{
	float4 m_positionW : POSITION;
	float2 m_textureCoordinate : TEXCOORD0;
	float3 m_normal : NORMAL; 
};

struct VertexOutput
{
	float4 m_positionH : SV_POSITION;
	float4 m_positionW : POSITION;
	float2 m_textureCoordinate : TEXCOORD0;
	float3 m_normal : NORMAL; 

	float4 m_lightPositionH : TEXCOORD1;
    float3 m_lightPositionW : TEXCOORD2;
};

// Vertex shader function.
VertexOutput main(VertexInput p_input) 
{
	// Setup vertex output.
	VertexOutput l_output;
	l_output.m_positionH		 = p_input.m_positionW;
	l_output.m_positionW		 = p_input.m_positionW;
	l_output.m_positionH.w		 = 1.0f;
	l_output.m_positionW.w		 = 1.0f;
	l_output.m_textureCoordinate = p_input.m_textureCoordinate;
	l_output.m_normal			 = p_input.m_normal;

	l_output.m_lightPositionH	= p_input.m_positionW;
	l_output.m_lightPositionW	= p_input.m_positionW;
	l_output.m_lightPositionH.w = 1.0f;

	// Store vertex position in world space.
	l_output.m_positionW = mul(l_output.m_positionW, m_worldMatrix);

	// Transform vertex position to homogenous clip space.
	l_output.m_positionH = mul(l_output.m_positionH, m_worldMatrix);
	l_output.m_positionH = mul(l_output.m_positionH, m_viewMatrix);
	l_output.m_positionH = mul(l_output.m_positionH, m_projectionMatrix);

	// Transform  the normals.
	l_output.m_normal = mul(l_output.m_normal, (float3x3)m_worldMatrix);

	// Determine the light position based on the position of the light and the position of the vertex in the world.
    l_output.m_lightPositionW = m_lightPosition - l_output.m_positionW.xyz;

	 // Normalize the light position vector.
    l_output.m_lightPositionW = normalize(l_output.m_lightPositionW);

	// Calculate the position of the vertice as viewed by the light source.
    l_output.m_lightPositionH = mul(l_output.m_lightPositionH, m_worldMatrix);
    l_output.m_lightPositionH = mul(l_output.m_lightPositionH, m_lightViewMatrix);
    l_output.m_lightPositionH = mul(l_output.m_lightPositionH, m_lightProjectionMatrix);

	// Return output.
	return l_output;
}