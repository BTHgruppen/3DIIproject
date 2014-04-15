// Light source structures.
struct DirectionalLight
{
	float4 m_ambientValue;
	float4 m_diffuseValue;
	float4 m_specularValue;

	float3 m_lightDirection;
	float m_padding;
};

struct PointLight
{
	float4 m_ambientValue;
	float4 m_diffuseValue;
	float4 m_specularValue;

	float3 m_lightAttenuation;
	float m_padding;

	float3 m_lightPosition;
	float m_range;
};

struct Spotlight
{
	float4 m_ambientValue;
	float4 m_diffuseValue;
	float4 m_specularValue;

	float3 m_lightDirection;
	float m_spot;

	float3 m_lightAttenuation;
	float m_padding;

	float3 m_lightPosition;
	float m_range;
};

// Material structure.
struct Material
{
	float4 m_ambientValue;
	float4 m_diffuseValue;
	float4 m_specularValue;
	float4 m_reflectiveValue;
};

// Directional lighting computation.
void CalculateDirectionalLight(DirectionalLight p_lightSource, Material p_material, float3 p_normal, float3 p_surfaceToCamera, out float4 o_ambientValue, out float4 o_diffuseValue, out float4 o_specularValue)
{
	// Initialize outputs values.
	o_ambientValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	o_diffuseValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	o_specularValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Set surface ambient value.
	o_ambientValue = p_material.m_ambientValue * p_lightSource.m_ambientValue;

	// Calculate the vector from surface to lightsource.
	float3 l_surfaceVector = -p_lightSource.m_lightDirection;

	// Calculate scalar product between the surface vector and the surface normal.
	float l_scalarProduct = dot(l_surfaceVector, p_normal);

	// If the scalar product is greater than 0, the surface is lit.
	[flatten] if(l_scalarProduct > 0.0f)
	{
		// Calculate light reflection vector.
		float3 l_reflectionVector = reflect(-l_surfaceVector, p_normal);

		// Calculate specular factor.
		float l_specularFactor = pow(max(dot(l_reflectionVector, p_surfaceToCamera), 0.0f), p_material.m_specularValue.w);

		// Set the lit surface diffuse and specular values.
		o_diffuseValue	= l_scalarProduct * p_material.m_diffuseValue * p_lightSource.m_diffuseValue;
		o_specularValue = l_specularFactor * p_material.m_specularValue * p_lightSource.m_specularValue;
	}
}

// Point lighting computation.
void CalculatePointLight(PointLight p_lightSource, Material p_material, float3 p_position, float3 p_normal, float3 p_surfaceToCamera, out float4 o_ambientValue, out float4 o_diffuseValue, out float4 o_specularValue)
{
	// Initialize outputs values.
	o_ambientValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	o_diffuseValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	o_specularValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Calculate the vector from surface to lightsource.
	float3 l_surfaceVector = p_lightSource.m_lightPosition - p_position;

	// Calculate the distance between surface and light source.
	float l_distance = length(l_surfaceVector);

	// Test if the surface within the light source range.
	if(l_distance > p_lightSource.m_range)
	{
		// If the surface is out of range, the function halts.
		return;
	}

	// Set surface ambient value.
	o_ambientValue = p_material.m_ambientValue * p_lightSource.m_ambientValue;

	// Normalize the surface vector using its length.
	l_surfaceVector /= l_distance;

	// Calculate scalar product between the surface vector and the surface normal.
	float l_scalarProduct = dot(l_surfaceVector, p_normal);

	// If the scalar product is greater than 0, the surface is lit.
	[flatten] if(l_scalarProduct > 0.0f)
	{
		// Calculate light reflection vector.
		float3 l_reflectionVector = reflect(-l_surfaceVector, p_normal);

		// Calculate specular factor.
		float l_specularFactor = pow(max(dot(l_reflectionVector, p_surfaceToCamera), 0.0f), p_material.m_specularValue.w);

		// Set the lit surface diffuse and specular values.
		o_diffuseValue	= l_scalarProduct * p_material.m_diffuseValue * p_lightSource.m_diffuseValue;
		o_specularValue = l_specularFactor * p_material.m_specularValue * p_lightSource.m_specularValue;
	}

	// Calculate light attenuation
	float l_attenuation = 1.0f / dot(p_lightSource.m_lightAttenuation, float3(1.0f, l_distance, l_distance * l_distance));

	// Attenuate surface lighting.
	o_diffuseValue *= l_attenuation;
	o_specularValue *= l_attenuation;
}

// Spotlight lighting computation.
void CalculateSpotlight(Spotlight p_lightSource, Material p_material, float3 p_position, float3 p_normal, float3 p_surfaceToCamera, out float4 o_ambientValue, out float4 o_diffuseValue, out float4 o_specularValue)
{
	// Initialize outputs values.
	o_ambientValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	o_diffuseValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);
	o_specularValue	= float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Calculate the vector from surface to lightsource.
	float3 l_surfaceVector = p_lightSource.m_lightPosition - p_position;

	// Calculate the distance between surface and light source.
	float l_distance = length(l_surfaceVector);

	// Test if the surface within the light source range.
	if(l_distance > p_lightSource.m_range)
	{
		// If the surface is out of range, the function halts.
		return;
	}

	// Set surface ambient value.
	o_ambientValue	= p_material.m_ambientValue * p_lightSource.m_ambientValue;

	// Normalize the surface vector using its length.
	l_surfaceVector /= l_distance;

	// Calculate scalar product between the surface vector and the surface normal.
	float l_scalarProduct = dot(l_surfaceVector, p_normal);

	// If the scalar product is greater than 0, the surface is lit.
	[flatten] if(l_scalarProduct > 0.0f)
	{
		// Calculate light reflection vector.
		float3 l_reflectionVector = reflect(-l_surfaceVector, p_normal);

		// Calculate specular factor.
		float l_specularFactor = pow(max(dot(l_reflectionVector, p_surfaceToCamera), 0.0f), p_material.m_specularValue.w);

		// Set the lit surface diffuse and specular values.
		o_diffuseValue	= l_scalarProduct * p_material.m_diffuseValue * p_lightSource.m_diffuseValue;
		o_specularValue = l_specularFactor * p_material.m_specularValue * p_lightSource.m_specularValue;
	}

	// Calculate the spot factor.
	float l_spotFactor = pow(max(dot(-l_surfaceVector, p_lightSource.m_lightDirection), 0.0f), p_lightSource.m_spot);

	// Calculate light attenuation
	float l_attenuation = l_spotFactor / dot(p_lightSource.m_lightAttenuation, float3(1.0f, l_distance, l_distance * l_distance));

	// Attenuate surface lighting.
	o_ambientValue *= l_spotFactor;
	o_diffuseValue *= l_attenuation;
	o_specularValue *= l_attenuation;
}