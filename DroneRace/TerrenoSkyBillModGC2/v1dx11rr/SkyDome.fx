Texture2D textures : register(t0);

SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projMatrix;
	float4 valores;
};

cbuffer cbChangesOccasionally : register(b1)
{
    float opacidad;
}

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
    float opa : TEXCOORD1;
};

PS_Input VS_Main(VS_Input vertex)
{
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, worldMatrix);
	vsOut.pos = mul(vsOut.pos, viewMatrix);
	vsOut.pos = mul(vsOut.pos, projMatrix);

	vsOut.tex0 = vertex.tex0;
    vsOut.opa = opacidad;
	return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
    float4 color2 = float4(0, 0, 0, 0);
    float4 finalColor = textures.Sample(colorSampler, pix.tex0);
    float4 resultado = lerp(color2, finalColor, pix.opa);
    return resultado;
}