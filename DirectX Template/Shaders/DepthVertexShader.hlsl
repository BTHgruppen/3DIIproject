// Matrix buffer.
cbuffer MatrixBuffer
{
    matrix m_worldMatrix;
	matrix m_viewMatrix;
	matrix m_projectionMatrix;
};

// Vertex structures.
struct VertexInput
{
    float4 m_positionW : POSITION;
};

struct VertexOutput
{
    float4 m_positionH : SV_POSITION;
    float4 m_positionW : POSITION;
};

// Vertex depth shader function.
VertexOutput main(VertexInput p_input)
{
	// Setup vertex output.
    VertexOutput l_output;
    l_output.m_positionH   = p_input.m_positionW;
	l_output.m_positionW   = p_input.m_positionW;
	l_output.m_positionH.w = 1.0f;

    // Transform vertex position to homogenous clip space.
    l_output.m_positionH = mul(l_output.m_positionH, m_worldMatrix);
    l_output.m_positionH = mul(l_output.m_positionH, m_viewMatrix);
    l_output.m_positionH = mul(l_output.m_positionH, m_projectionMatrix);

	// Store the none offset postion.
	l_output.m_positionW = l_output.m_positionH;

	// Return output.
    return l_output;
}