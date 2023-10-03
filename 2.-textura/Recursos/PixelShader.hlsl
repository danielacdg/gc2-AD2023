//PixelShader.hlsl
//Constantes Globales para la Textura
Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);


// * agregamos una nueva variable para la textura
Texture2D colorMap2 : register(t1);


//Estructura de Entrada para el Shader
struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 PS_Main(PS_Input frag) : SV_TARGET
{
   
    float4 color1 = colorMap.Sample(colorSampler, frag.uv);
    float4 color2 = colorMap2.Sample(colorSampler, frag.uv);

    //float4 resultante = lerp(color1, color2, 0.5f); ¿ES  COMO UN MIX del GLSL?
    float4 resultante = color1 + color2;

    return resultante;
}
