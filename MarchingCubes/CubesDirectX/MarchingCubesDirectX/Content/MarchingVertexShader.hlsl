//Once per frame constant buffer
cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

//Vertex shader output description
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
};

//Main vertex shader
VS_OUTPUT main(float4 Pos : POSITION, float4 Color : COLOR)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = float4(Pos.xyz, 1);
	output.Color = Color;
	return output;
}