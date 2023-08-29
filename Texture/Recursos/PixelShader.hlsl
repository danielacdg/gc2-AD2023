//PixelShader.hlsl
// 
// 
// 
//Constantes Globales para la Textura
Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

Texture2D colorMap2 : register(t1);
SamplerState colorSampler2 : register(s1);

//Estructura de Entrada para el Shader
struct PS_Input {
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD;
};

float4 PS_Main(PS_Input frag) : SV_TARGET
{
    float4 colorFinal = (colorMap.Sample(colorSampler, frag.uv) *
    colorMap2.Sample(colorSampler2, frag.uv) * float4(2.0f, 1.0f, 1.0f, 1.0f));

    return colorFinal;
}
