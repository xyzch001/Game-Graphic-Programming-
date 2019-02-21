
// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	float3 normal       : NORMAL;       // Normal of the vertex
	float3 worldPos     : POSITION;
	float2 uv           : TEXCOORD;      // UV for the textures coordinate
	//float4 color		: COLOR;
};

struct DirectionalLight
{
	// Data type
	//   |
	//   |     Name
	//   |      |
	//   v      v
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};

struct PointLight
{
	// Data type
	//   |
	//   |     Name
	//   |      |
	//   v      v
	float3 Position;
	float  junk;
	float3 Color;
};

cbuffer externalData : register(b0)
{
	DirectionalLight light1;
	DirectionalLight light2;
	PointLight light3;
	float3 CameraPosition;
};

// Global variables for the texture and sampler
Texture2D diffuseTexture : register(t0);
SamplerState basicSampler : register(s0);

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	float4 surfaceColor = diffuseTexture.Sample(basicSampler, input.uv);
	float shininess = 32.0f; // Arbitraty surface shininess vaule
    float3 dirToCamera = normalize(CameraPosition - input.worldPos);

	//------------DirectionalLight--------------
	float4 result = float4(0.0f, 0.0f, 0.0f, 0.0f);
	input.normal = normalize(input.normal);
    float3 resultDirection = float3(0.0f, 0.0f, 0.0f);
	resultDirection = normalize(-light1.Direction);
	float lightAmount = dot(input.normal, resultDirection);
	lightAmount = saturate(lightAmount);

	

	result += light1.DiffuseColor * lightAmount + light1.AmbientColor;

	resultDirection = normalize(-light2.Direction);
	lightAmount = dot(input.normal, resultDirection);
	lightAmount = saturate(lightAmount);

	

	result += light2.DiffuseColor * lightAmount + light2.AmbientColor;

	//  ------------------POINT LIGHT-------------------------
	float3 dirToPointLight = normalize(light3.Position - input.worldPos);
	lightAmount = dot(input.normal, dirToPointLight);
	lightAmount = saturate(lightAmount);
	
	// Specular calculation for reflections (Phong)
	float3 pointRefl = reflect(-dirToPointLight, input.normal);
	float3 pointSpec = pow(saturate(dot(pointRefl, dirToCamera)), shininess);

	//Conmbine the surface and lighting
	//result += light3.Color * lightAmount + pointSpec.rrr;

	return surfaceColor * (result + float4(light3.Color * lightAmount + pointSpec.rrr , 1.0f));
}