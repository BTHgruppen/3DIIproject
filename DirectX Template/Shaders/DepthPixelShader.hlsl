// Vertex structure.
struct Vertex
{
	float4 m_positionH : SV_POSITION;
	float4 m_positionW : POSITION; 
};

// Pixel depth shader function.
float4 main(Vertex p_input) : SV_TARGET
{
	// Initialize outputs values.
	float l_depth;
	float4 l_color;

	// The depth value of the pixel is obtained by dividing the pixel depth by the homogeneous W coordinate.
	l_depth = p_input.m_positionW.z / p_input.m_positionW.w;

	// Save the depth value to the color, making the texture range from black to white.
	l_color = float4(l_depth, l_depth, l_depth, 1.0f);

	// Return depth value.
	return l_color;
}